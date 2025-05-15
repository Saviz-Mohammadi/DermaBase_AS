#include <QDebug>
#include "patient_diagnoses_model.hpp"

// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

PatientDiagnosesModel::PatientDiagnosesModel(QObject *parent, const QString &name)
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

PatientDiagnosesModel::~PatientDiagnosesModel()
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

void PatientDiagnosesModel::requestInsertPatientDiagnosis(const int patientID, const int diagnosisID, const QString &name)
{
    if(m_OperationIsInProgress)
    {
        return;
    }

    m_OperationIsInProgress = true;
    emit operationIsInProgressChanged();

    m_Diagnosis.diagnosisID = diagnosisID;
    m_Diagnosis.name = name;
    m_Database->insertPatientDiagnosis(patientID, diagnosisID);
}

void PatientDiagnosesModel::requestRemovePatientDiagnosis(const int patientID, const int diagnosisID, const int row)
{
    if(m_OperationIsInProgress)
    {
        return;
    }

    m_OperationIsInProgress = true;
    emit operationIsInProgressChanged();

    m_Diagnosis.diagnosisID = diagnosisID;
    m_Row = row;
    m_Database->removePatientDiagnosis(patientID, diagnosisID);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC OVERRIDES
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

int PatientDiagnosesModel::rowCount(const QModelIndex &parent) const
{
    // If is parent:
    if(parent.isValid())
    {
        return(0);
    }

    return(m_Data.size());
}

QVariant PatientDiagnosesModel::data(const QModelIndex &index, int role) const
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

QHash<int, QByteArray> PatientDiagnosesModel::roleNames() const
{
    static QHash<int, QByteArray> roleMapping = {
        { DiagnosisID, "diagnosisID" },
        { Name, "name" }
    };

    return(roleMapping);
}

bool PatientDiagnosesModel::removeRows(int row, int count, const QModelIndex &parent)
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

void PatientDiagnosesModel::setDatabase(Database *newDatabase)
{
    if(newDatabase == nullptr)
    {
        return;
    }

    // TODO (SAVIZ): I should probably make sure that I disconnect from the previous database, but since replacing databases never happens: I DON'T GIVE A FUCK!

    m_Database = newDatabase;

    connect(
        m_Database,
        &Database::finishedGettingPatientDiagnoses,
        this,
        [this](int status, const QString& message, const std::vector<Diagnosis> data)
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
        &Database::finishedInsertingPatientDiagnosis,
        this,
        [this](int status, const QString& message)
        {
            Q_UNUSED(message);

            if(status == 1)
            {
                const int index = m_Data.size();

                beginInsertRows(QModelIndex(), index, index);

                m_Data.emplace_back(m_Diagnosis.diagnosisID, m_Diagnosis.name);

                endInsertRows();
            }

            m_OperationIsInProgress = false;
            emit operationIsInProgressChanged();
        }
    );

    connect(
        m_Database,
        &Database::finishedRemovingPatientDiagnosis,
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

void PatientDiagnosesModel::setData(std::vector<Diagnosis> newData)
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

Database *PatientDiagnosesModel::getDatabase() const
{
    return(m_Database);
}

bool PatientDiagnosesModel::getOperationIsInProgress() const
{
    return(m_OperationIsInProgress);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]
