#include <QDebug>
#include "patient_procedures_model.hpp"

// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

PatientProceduresModel::PatientProceduresModel(QObject *parent, const QString &name)
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

PatientProceduresModel::~PatientProceduresModel()
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

void PatientProceduresModel::requestInsertPatientProcedure(const int patientID, const int procedureID, const QString &name)
{
    if(m_OperationIsInProgress)
    {
        return;
    }

    m_OperationIsInProgress = true;
    emit operationIsInProgressChanged();

    m_Procedure.ProcedureID = procedureID;
    m_Procedure.name = name;
    m_Database->insertPatientProcedure(patientID, procedureID);
}

void PatientProceduresModel::requestRemovePatientProcedure(const int patientID, const int procedureID, const int row)
{
    if(m_OperationIsInProgress)
    {
        return;
    }

    m_OperationIsInProgress = true;
    emit operationIsInProgressChanged();

    m_Procedure.ProcedureID = procedureID;
    m_Row = row;
    m_Database->removePatientProcedure(patientID, procedureID);
}

void PatientProceduresModel::requestUpdatePatientProcedureFee(const int patientID, const int procedureID, const double newFee, const int row)
{
    if(m_OperationIsInProgress)
    {
        return;
    }

    m_OperationIsInProgress = true;
    emit operationIsInProgressChanged();

    m_Row = row;
    m_Procedure.fee = newFee;

    m_Database->updatePatientProcedureFee(
        patientID,
        procedureID,
        newFee
    );
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC OVERRIDES
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

int PatientProceduresModel::rowCount(const QModelIndex &parent) const
{
    // If is parent:
    if(parent.isValid())
    {
        return(0);
    }

    return(m_Data.size());
}

QVariant PatientProceduresModel::data(const QModelIndex &index, int role) const
{
#ifdef QT_DEBUG
    if(!checkIndex(index, CheckIndexOption::IndexIsValid))
    {
        return(QVariant());
    }
#endif

    const int row = index.row();

    // Matching:
    if (role == ProcedureID)
    {
        return(m_Data[row].ProcedureID);
    }

    else if (role == Name)
    {
        return(m_Data[row].name);
    }

    else if (role == Fee)
    {
        return(m_Data[row].fee);
    }

    return(QVariant());
}

QHash<int, QByteArray> PatientProceduresModel::roleNames() const
{
    static QHash<int, QByteArray> roleMapping = {
        { ProcedureID, "procedureID" },
        { Name, "name" },
        { Fee, "fee"}
    };

    return(roleMapping);
}

bool PatientProceduresModel::removeRows(int row, int count, const QModelIndex &parent)
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

void PatientProceduresModel::setDatabase(Database *newDatabase)
{
    if(newDatabase == nullptr)
    {
        return;
    }

    // TODO (SAVIZ): I should probably make sure that I disconnect from the previous database, but since replacing databases never happens: I DON'T GIVE A FUCK!

    m_Database = newDatabase;

    connect(
        m_Database,
        &Database::finishedGettingPatientProcedures,
        this,
        [this](int status, const QString& message, const std::vector<Procedure> data)
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
        &Database::finishedInsertingPatientProcedure,
        this,
        [this](int status, const QString& message)
        {
            Q_UNUSED(message);

            if(status == 1)
            {
                const int index = m_Data.size();

                beginInsertRows(QModelIndex(), index, index);

                m_Data.emplace_back(m_Procedure.ProcedureID, m_Procedure.name, double(0.000));

                endInsertRows();
            }

            m_OperationIsInProgress = false;
            emit operationIsInProgressChanged();
        }
    );

    connect(
        m_Database,
        &Database::finishedRemovingPatientProcedure,
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
        &Database::finishedUpdatingPatientProcedureFee,
        this,
        [this](int status, const QString& message)
        {
            Q_UNUSED(message);

            if(status == 1)
            {
                m_Data[m_Row].fee = m_Procedure.fee;
            }

            // NOTE (SAVIZ): In this case, we're working with a one-dimensional list (i.e., only column 0), so it's safe to hardcode the column value. However, for tables with multiple columns, we should store the column index in a member variable and account for it accordingly.
            QModelIndex targetIndex = index(m_Row, 0);

            emit dataChanged(targetIndex, targetIndex, { Fee });

            m_OperationIsInProgress = false;
            emit operationIsInProgressChanged();
        }
    );

    emit databaseChanged();
}

void PatientProceduresModel::setData(std::vector<Procedure> newData)
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

Database *PatientProceduresModel::getDatabase() const
{
    return(m_Database);
}

bool PatientProceduresModel::getOperationIsInProgress() const
{
    return(m_OperationIsInProgress);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]
