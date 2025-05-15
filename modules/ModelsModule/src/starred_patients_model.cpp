#include <QDebug>
#include "starred_patients_model.hpp"

// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

StarredPatientsModel::StarredPatientsModel(QObject *parent, const QString &name)
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

StarredPatientsModel::~StarredPatientsModel()
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

void StarredPatientsModel::requestCreateStarredPatient(const int patientID)
{
    if(m_OperationIsInProgress)
    {
        return;
    }

    m_OperationIsInProgress = true;
    emit operationIsInProgressChanged();

    m_Database->createStarredPatient(patientID);
}

void StarredPatientsModel::requestGetAllStarredPatients()
{
    if(m_OperationIsInProgress)
    {
        return;
    }

    m_OperationIsInProgress = true;
    emit operationIsInProgressChanged();

    m_Database->getAllStarredPatients();
}

void StarredPatientsModel::requestRemoveAllStarredPatients()
{
    if(m_OperationIsInProgress)
    {
        return;
    }

    m_OperationIsInProgress = true;
    emit operationIsInProgressChanged();

    m_Database->removeAllStarredPatients();
}

void StarredPatientsModel::requestUpdateVisitStatusOfStarredPatient(const int row, bool newStatus)
{
    if(m_OperationIsInProgress)
    {
        return;
    }

    m_OperationIsInProgress = true;
    emit operationIsInProgressChanged();

    m_Row = row;

    m_Database->updateVisitStatusOfStarredPatient(
        m_Data[row].patientID,
        newStatus
    );
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC OVERRIDES
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

int StarredPatientsModel::rowCount(const QModelIndex &parent) const
{
    // If is parent:
    if(parent.isValid())
    {
        return(0);
    }

    return(m_Data.size());
}

QVariant StarredPatientsModel::data(const QModelIndex &index, int role) const
{
#ifdef QT_DEBUG
    if(!checkIndex(index, CheckIndexOption::IndexIsValid))
    {
        return(QVariant());
    }
#endif

    const int row = index.row();

    // Matching:
    if (role == PatientID)
    {
        return(m_Data[row].patientID);
    }

    else if (role == FirstName)
    {
        return(m_Data[row].firstName);
    }

    else if (role == LastName)
    {
        return(m_Data[row].lastName);
    }

    else if (role == BirthYear)
    {
        return(m_Data[row].birthYear);
    }

    else if (role == PhoneNumber)
    {
        return(m_Data[row].phoneNumber);
    }

    else if (role == Email)
    {
        return(m_Data[row].email);
    }

    else if (role == Gender)
    {
        return(m_Data[row].gender);
    }

    else if (role == MaritalStatus)
    {
        return(m_Data[row].maritalStatus);
    }

    else if (role == HasVisited)
    {
        return(m_Data[row].hasVisited);
    }

    return(QVariant());
}

QHash<int, QByteArray> StarredPatientsModel::roleNames() const
{
    static QHash<int, QByteArray> roleMapping = {
        { PatientID, "patientID" },
        { FirstName, "firstName" },
        { LastName, "lastName" },
        { BirthYear, "birthYear" },
        { PhoneNumber, "phoneNumber" },
        { Email, "email" },
        { Gender, "gender" },
        { MaritalStatus, "maritalStatus" },
        { HasVisited, "hasVisited" }
    };

    return(roleMapping);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC Setters
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

void StarredPatientsModel::setDatabase(Database *newDatabase)
{
    if(newDatabase == nullptr)
    {
        return;
    }

    // TODO (SAVIZ): I should probably make sure that I disconnect from the previous database, but since replacing databases never happens: I DON'T CARE!

    m_Database = newDatabase;

    connect(
        m_Database,
        &Database::finishedGettingAllStarredPatients,
        this,
        [this](int status, const QString& message, const std::vector<StarredPatient> data)
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
        &Database::finishedCreatingStarredPatient,
        this,
        [this](int status, const QString& message, StarredPatient starredPatient)
        {
            Q_UNUSED(message);

            if(status == 1)
            {
                const int index = m_Data.size();

                beginInsertRows(QModelIndex(), index, index);

                m_Data.emplace_back(
                    starredPatient.patientID,
                    starredPatient.firstName,
                    starredPatient.lastName,
                    starredPatient.birthYear,
                    starredPatient.phoneNumber,
                    starredPatient.email,
                    starredPatient.gender,
                    starredPatient.maritalStatus,
                    starredPatient.hasVisited
                );

                endInsertRows();
            }

            m_OperationIsInProgress = false;
            emit operationIsInProgressChanged();
        }
    );

    connect(
        m_Database,
        &Database::finishedUpdatingStarredPatientVisitStatus,
        this,
        [this](int status, const QString& message)
        {
            Q_UNUSED(message);

            if(status == 1)
            {
                m_Data[m_Row].hasVisited = !m_Data[m_Row].hasVisited;
            }

            else
            {
                m_Data[m_Row].hasVisited = false;
            }

            // NOTE (SAVIZ): In this case, we're working with a one-dimensional list (i.e., only column 0), so it's safe to hardcode the column value. However, for tables with multiple columns, we should store the column index in a member variable and account for it accordingly.
            QModelIndex targetIndex = index(m_Row, 0);

            emit dataChanged(targetIndex, targetIndex, { HasVisited });

            m_OperationIsInProgress = false;
            emit operationIsInProgressChanged();
        }
    );

    connect(
        m_Database,
        &Database::finishedRemovingAllStarredPatients,
        this,
        [this](int status, const QString& message)
        {
            Q_UNUSED(message);

            if(status == 1)
            {
                beginResetModel();

                m_Data.clear();

                endResetModel();

                emit visitedCountChanged();
            }

            m_OperationIsInProgress = false;
            emit operationIsInProgressChanged();
        }
    );

    connect(
        this,
        &StarredPatientsModel::dataChanged,
        this,
        &StarredPatientsModel::visitedCountChanged
    );

    emit databaseChanged();
}

void StarredPatientsModel::setVisitedCount(int newVisitedCount)
{
    // TODO (SAVIZ): I don't have the energy to remove this. Lord forgive me...
}

void StarredPatientsModel::setData(std::vector<StarredPatient> newData)
{
    beginResetModel();

    m_Data = newData;

    endResetModel();

    emit visitedCountChanged();
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC Getters
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

Database *StarredPatientsModel::getDatabase() const
{
    return(m_Database);
}

bool StarredPatientsModel::getOperationIsInProgress() const
{
    return(m_OperationIsInProgress);
}

int StarredPatientsModel::getVisitedCount() const
{
    int count = 0;

    for(std::size_t index = 0; index < m_Data.size(); ++index)
    {
        if(m_Data[count].hasVisited)
        {
            count += 1;
        }
    }

    return(count);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]
