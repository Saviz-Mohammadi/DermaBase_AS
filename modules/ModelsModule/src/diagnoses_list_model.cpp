#include <QDebug>
#include "diagnoses_list_model.hpp"

// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

DiagnosesListModel::DiagnosesListModel(QObject *parent, const QString &name)
    : QAbstractListModel{parent}
    , m_Database(nullptr)
    , m_Data()
{
    this->setObjectName(name);

#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "None";
    qDebug() << "Log Output :" << "None";
#endif
}

DiagnosesListModel::~DiagnosesListModel()
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

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC OVERRIDES
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

int DiagnosesListModel::rowCount(const QModelIndex &parent) const
{
    // If is parent:
    if(parent.isValid())
    {
        return(0);
    }

    return(m_Data.size());
}

QVariant DiagnosesListModel::data(const QModelIndex &index, int role) const
{
#ifdef QT_DEBUG
    if(!checkIndex(index, CheckIndexOption::IndexIsValid))
    {
        return(QVariant());
    }
#endif

    const int row = index.row();

    // Matching:
    if (role == DiagnosisID)
    {
        return(m_Data[row].diagnosisID);
    }

    else if (role == Name)
    {
        return(m_Data[row].name);
    }

    return(QVariant());
}

QHash<int, QByteArray> DiagnosesListModel::roleNames() const
{
    static QHash<int, QByteArray> roleMapping = {
        { DiagnosisID, "diagnosisID" },
        { Name, "name" }
    };

    return(roleMapping);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC Setters
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

void DiagnosesListModel::setDatabase(Database *newDatabase)
{
    if(newDatabase == nullptr)
    {
        return;
    }

    // TODO (SAVIZ): I should probably make sure that I disconnect from the previous database, but since replacing databases never happens: I DON'T GIVE A FUCK!

    m_Database = newDatabase;

    connect(
        m_Database,
        &Database::finishedGettingDiagnosesList,
        this,
        [this](int status, const QString& message, const std::vector<Diagnosis> data)
        {
            Q_UNUSED(message);

            if(status == 1)
            {
                setData(data);
            }
        }
    );

    emit databaseChanged();
}

void DiagnosesListModel::setData(std::vector<Diagnosis> newData)
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

Database *DiagnosesListModel::getDatabase() const
{
    return(m_Database);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]
