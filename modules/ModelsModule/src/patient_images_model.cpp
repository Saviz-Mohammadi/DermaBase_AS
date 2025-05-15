#include <QDebug>
#include "patient_images_model.hpp"

// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

PatientImagesModel::PatientImagesModel(QObject *parent, const QString &name)
    : QAbstractListModel{parent}
    , m_Database(nullptr)
    , m_OperationIsInProgress(false)
    , m_Row(-1)
    , m_Data()
{
    this->setObjectName(name);

#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "None";
    qDebug() << "Log Output :" << "None";
#endif
}

PatientImagesModel::~PatientImagesModel()
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "None";
    qDebug() << "Log Output :" << "None";
#endif
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC Methods
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

void PatientImagesModel::requestInsertPatientImage(const int patientID, const QUrl &url)
{
    if(m_OperationIsInProgress)
    {
        return;
    }

    m_OperationIsInProgress = true;
    emit operationIsInProgressChanged();

    m_Image.name = "image_" + QDateTime::currentDateTime().toString("yyyy/MM/dd (HH::mm::ss)");

    QFile file(url.toLocalFile());

    if (!file.open(QIODevice::ReadOnly))
    {
#ifdef QT_DEBUG
        qDebug() << "Could not open file:" << url.toLocalFile();
#endif

        // TODO (SAVIZ): I should probably do something more useful here...

        m_OperationIsInProgress = false;
        emit operationIsInProgressChanged();

        return;
    }

    QByteArray imageData = file.readAll();

    file.close();

    m_Image.data = imageData;
    m_Database->insertPatientImage(patientID, m_Image.name, imageData);
}

void PatientImagesModel::requestRemovePatientImage(const int patientID, const QString &name, const int row)
{
    if(m_OperationIsInProgress)
    {
        return;
    }

    m_OperationIsInProgress = true;
    emit operationIsInProgressChanged();

    m_Row = row;
    m_Database->removePatientImage(patientID, name);
}

void PatientImagesModel::requestUpdatePatientImageName(const int patientID, const QString &name, const QString &newName, const int row)
{
    if(m_OperationIsInProgress)
    {
        return;
    }

    m_OperationIsInProgress = true;
    emit operationIsInProgressChanged();

    m_Row = row;
    m_Image.name = newName;

    m_Database->updatePatientImageName(
        patientID,
        name,
        newName
    );
}

QUrl PatientImagesModel::getImage(const int row)
{
    QImage image;

    if (!image.loadFromData(m_Data[row].data))
    {
#ifdef QT_DEBUG
        qDebug() << "Failed to load image";
#endif

        return QUrl();
    }

    QDir dir("./cache/images");

    if (!QDir().mkpath(dir.absolutePath()))
    {
#ifdef QT_DEBUG
        qDebug() << "Failed to create folder:" << dir.absolutePath();
#endif

        return QUrl();
    }

    QString filePath = dir.absolutePath() + "/temp" + ".png";

    // NOTE (SAVIZ): nullptr forces the QImage to decide for itself what the best format for the image file will be.
    if (!image.save(filePath, nullptr))
    {
#ifdef QT_DEBUG
        qDebug() << "Failed to save to path: " << filePath;
#endif

        return QUrl();
    }

    return QUrl::fromLocalFile(filePath);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC OVERRIDES
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

int PatientImagesModel::rowCount(const QModelIndex &parent) const
{
    // If is parent:
    if(parent.isValid())
    {
        return(0);
    }

    return(m_Data.size());
}

QVariant PatientImagesModel::data(const QModelIndex &index, int role) const
{
#ifdef QT_DEBUG
    if(!checkIndex(index, CheckIndexOption::IndexIsValid))
    {
        return(QVariant());
    }
#endif

    const int row = index.row();

    // Matching:
    if (role == ImageID)
    {
        return(m_Data[row].imageID);
    }

    else if (role == Name)
    {
        return(m_Data[row].name);
    }

    else if (role == Data)
    {
        return(m_Data[row].data);
    }

    return(QVariant());
}

QHash<int, QByteArray> PatientImagesModel::roleNames() const
{
    static QHash<int, QByteArray> roleMapping = {
        { ImageID, "imageID" },
        { Name, "name" },
        { Data, "data" }
    };

    return(roleMapping);
}

bool PatientImagesModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0 || row > m_Data.size() || row + count < 0 || row + count > m_Data.size())
    {
        return(false);
    }

    beginRemoveRows(parent, row, row + count - 1);

    m_Data.erase(
        m_Data.begin() + row,
        m_Data.begin() + row + count
    );

    endRemoveRows();

    return(true);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC Setters
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

void PatientImagesModel::setDatabase(Database *newDatabase)
{
    if(newDatabase == nullptr)
    {
        return;
    }

    // TODO (SAVIZ): I should probably make sure that I disconnect from the previous database, but since replacing databases never happens: I DON'T GIVE A FUCK!

    m_Database = newDatabase;

    connect(
        m_Database,
        &Database::finishedGettingPatientImages,
        this,
        [this](int status, const QString& message, const std::vector<Image> data)
        {
            Q_UNUSED(message);

            if(status == 1)
            {
                setData(data);
            }

            m_OperationIsInProgress = false;
            emit operationIsInProgressChanged();
        }
    );

    connect(
        m_Database,
        &Database::finishedInsertingPatientImage,
        this,
        [this](int status, const QString& message)
        {
            Q_UNUSED(message);

            if(status == 1)
            {
                const int index = m_Data.size();

                beginInsertRows(QModelIndex(), index, index);

                m_Data.emplace_back(
                    m_Image.imageID,
                    m_Image.name,
                    m_Image.data
                );

                endInsertRows();
            }

            m_OperationIsInProgress = false;
            emit operationIsInProgressChanged();
        }
    );

    connect(
        m_Database,
        &Database::finishedRemovingPatientImage,
        this,
        [this](int status, const QString& message)
        {
            Q_UNUSED(message);

            if(status == 1)
            {
                removeRows(m_Row, 1, QModelIndex());
            }

            m_OperationIsInProgress = false;
            emit operationIsInProgressChanged();
        }
    );

    connect(
        m_Database,
        &Database::finishedUpdatingPatientImageName,
        this,
        [this](int status, const QString& message)
        {
            Q_UNUSED(message);

            if(status == 1)
            {
                m_Data[m_Row].name = m_Image.name;
            }

            // NOTE (SAVIZ): In this case, we're working with a one-dimensional list (i.e., only column 0), so it's safe to hardcode the column value. However, for tables with multiple columns, we should store the column index in a member variable and account for it accordingly.
            QModelIndex targetIndex = index(m_Row, 0);

            emit dataChanged(targetIndex, targetIndex, { Name });

            m_OperationIsInProgress = false;
            emit operationIsInProgressChanged();
        }
    );

    emit databaseChanged();
}

void PatientImagesModel::setData(std::vector<Image> newData)
{
    beginResetModel();

    m_Data = newData;

    endResetModel();
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC Getters
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

Database *PatientImagesModel::getDatabase() const
{
    return(m_Database);
}

bool PatientImagesModel::getOperationIsInProgress() const
{
    return(m_OperationIsInProgress);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]
