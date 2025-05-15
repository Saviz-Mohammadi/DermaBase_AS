#include <QDebug>
#include "patient_treatments_model.hpp"

// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

PatientTreatmentsModel::PatientTreatmentsModel(QObject *parent, const QString &name)
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

PatientTreatmentsModel::~PatientTreatmentsModel()
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

void PatientTreatmentsModel::requestInsertPatientTreatment(const int patientID, const int treatmentID, const QString &name)
{
    if(m_OperationIsInProgress)
    {
        return;
    }

    m_OperationIsInProgress = true;
    emit operationIsInProgressChanged();

    m_Treatment.treatmentID = treatmentID;
    m_Treatment.name = name;
    m_Database->insertPatientTreatment(patientID, treatmentID);
}

void PatientTreatmentsModel::requestRemovePatientTreatment(const int patientID, const int treatmentID, const int row)
{
    if(m_OperationIsInProgress)
    {
        return;
    }

    m_OperationIsInProgress = true;
    emit operationIsInProgressChanged();

    m_Treatment.treatmentID = treatmentID;
    m_Row = row;
    m_Database->removePatientTreatment(patientID, treatmentID);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC OVERRIDES
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

int PatientTreatmentsModel::rowCount(const QModelIndex &parent) const
{
    // If is parent:
    if(parent.isValid())
    {
        return(0);
    }

    return(m_Data.size());
}

QVariant PatientTreatmentsModel::data(const QModelIndex &index, int role) const
{
#ifdef QT_DEBUG
    if(!checkIndex(index, CheckIndexOption::IndexIsValid))
    {
        return(QVariant());
    }
#endif

    const int row = index.row();

    // Matching:
    if (role == TreatmentID)
    {
        return(m_Data[row].treatmentID);
    }

    else if (role == Name)
    {
        return(m_Data[row].name);
    }

    return(QVariant());
}

QHash<int, QByteArray> PatientTreatmentsModel::roleNames() const
{
    static QHash<int, QByteArray> roleMapping = {
        { TreatmentID, "treatmentID" },
        { Name, "name" }
    };

    return(roleMapping);
}

bool PatientTreatmentsModel::removeRows(int row, int count, const QModelIndex &parent)
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

void PatientTreatmentsModel::setDatabase(Database *newDatabase)
{
    if(newDatabase == nullptr)
    {
        return;
    }

    // TODO (SAVIZ): I should probably make sure that I disconnect from the previous database, but since replacing databases never happens: I DON'T GIVE A FUCK!

    m_Database = newDatabase;

    connect(
        m_Database,
        &Database::finishedGettingPatientTreatments,
        this,
        [this](int status, const QString& message, const std::vector<Treatment> data)
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
        &Database::finishedInsertingPatientTreatment,
        this,
        [this](int status, const QString& message)
        {
            Q_UNUSED(message);

            if(status == 1)
            {
                const int index = m_Data.size();

                beginInsertRows(QModelIndex(), index, index);

                m_Data.emplace_back(m_Treatment.treatmentID, m_Treatment.name);

                endInsertRows();
            }

            m_OperationIsInProgress = false;
            emit operationIsInProgressChanged();
        }
    );

    connect(
        m_Database,
        &Database::finishedRemovingPatientTreatment,
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

    emit databaseChanged();
}

void PatientTreatmentsModel::setData(std::vector<Treatment> newData)
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

Database *PatientTreatmentsModel::getDatabase() const
{
    return(m_Database);
}

bool PatientTreatmentsModel::getOperationIsInProgress() const
{
    return(m_OperationIsInProgress);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]
