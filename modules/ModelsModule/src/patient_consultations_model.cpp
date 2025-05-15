#include <QDebug>
#include "patient_consultations_model.hpp"

// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

PatientConsultationsModel::PatientConsultationsModel(QObject *parent, const QString &name)
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

PatientConsultationsModel::~PatientConsultationsModel()
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

void PatientConsultationsModel::requestInsertPatientConsultation(const int patientID, const int consultantID)
{
    if(m_OperationIsInProgress)
    {
        return;
    }

    m_OperationIsInProgress = true;
    emit operationIsInProgressChanged();

    m_Database->insertPatientConsultation(patientID, consultantID);
}

void PatientConsultationsModel::requestRemovePatientConsultation(const int row)
{
    if(m_OperationIsInProgress)
    {
        return;
    }

    m_OperationIsInProgress = true;
    emit operationIsInProgressChanged();

    m_Row = row;
    m_Database->removePatientConsultation(m_Data[row].consultationID);
}

void PatientConsultationsModel::requestUpdatePatientConsultationDateAndOutcome(const int consultationID, const QString &date, const QString &outcome, const int row)
{
    if(m_OperationIsInProgress)
    {
        return;
    }

    m_OperationIsInProgress = true;
    emit operationIsInProgressChanged();

    m_Row = row;
    m_Consultation.date = date;
    m_Consultation.outcome = outcome;

    m_Database->updatePatientConsultationDateAndOutcome(
        consultationID,
        date,
        outcome
    );
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC OVERRIDES
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

int PatientConsultationsModel::rowCount(const QModelIndex &parent) const
{
    // If is parent:
    if(parent.isValid())
    {
        return(0);
    }

    return(m_Data.size());
}

QVariant PatientConsultationsModel::data(const QModelIndex &index, int role) const
{
#ifdef QT_DEBUG
    if(!checkIndex(index, CheckIndexOption::IndexIsValid))
    {
        return(QVariant());
    }
#endif

    const int row = index.row();

    // Matching:
    if (role == ConsultationID)
    {
        return(m_Data[row].consultationID);
    }

    else if (role == PatientID)
    {
        return(m_Data[row].patientID);
    }

    else if (role == ConsultantID)
    {
        return(m_Data[row].consultantID);
    }

    else if (role == Date)
    {
        return(m_Data[row].date);
    }

    else if (role == Outcome)
    {
        return(m_Data[row].outcome);
    }

    else if (role == Name)
    {
        return(m_Data[row].name);
    }

    else if (role == Specialization)
    {
        return(m_Data[row].specialization);
    }

    return(QVariant());
}

QHash<int, QByteArray> PatientConsultationsModel::roleNames() const
{
    static QHash<int, QByteArray> roleMapping = {
        { ConsultationID, "consultationID" },
        { PatientID, "patientID" },
        { ConsultantID, "consultantID" },
        { Name, "name" },
        { Specialization, "specialization" },
        { Date, "date" },
        { Outcome, "outcome" },
    };

    return(roleMapping);
}

bool PatientConsultationsModel::removeRows(int row, int count, const QModelIndex &parent)
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

void PatientConsultationsModel::setDatabase(Database *newDatabase)
{
    if(newDatabase == nullptr)
    {
        return;
    }

    // TODO (SAVIZ): I should probably make sure that I disconnect from the previous database, but since replacing databases never happens: I DON'T GIVE A FUCK!

    m_Database = newDatabase;

    connect(
        m_Database,
        &Database::finishedGettingPatientConsultations,
        this,
        [this](int status, const QString& message, const std::vector<Consultation> data)
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
        &Database::finishedInsertingPatientConsultation,
        this,
        [this](int status, const QString& message, Consultation consultation)
        {
            Q_UNUSED(message);

            if(status == 1)
            {
                const int index = m_Data.size();

                beginInsertRows(QModelIndex(), index, index);

                m_Data.emplace_back(
                    consultation.consultationID,
                    consultation.patientID,
                    consultation.consultantID,
                    consultation.date,
                    consultation.outcome,
                    consultation.name,
                    consultation.specialization
                );

                endInsertRows();
            }

            m_OperationIsInProgress = false;
            emit operationIsInProgressChanged();
        }
    );

    connect(
        m_Database,
        &Database::finishedRemovingPatientConsultation,
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
        &Database::finishedUpdatingPatientConsultationDateAndOutcome,
        this,
        [this](int status, const QString& message)
        {
            Q_UNUSED(message);

            if(status == 1)
            {
                m_Data[m_Row].date = m_Consultation.date;
                m_Data[m_Row].outcome = m_Consultation.outcome;
            }

            // NOTE (SAVIZ): In this case, we're working with a one-dimensional list (i.e., only column 0), so it's safe to hardcode the column value. However, for tables with multiple columns, we should store the column index in a member variable and account for it accordingly.
            QModelIndex targetIndex = index(m_Row, 0);

            emit dataChanged(targetIndex, targetIndex, { Date, Outcome });

            m_OperationIsInProgress = false;
            emit operationIsInProgressChanged();
        }
    );

    emit databaseChanged();
}

void PatientConsultationsModel::setData(std::vector<Consultation> newData)
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

Database *PatientConsultationsModel::getDatabase() const
{
    return(m_Database);
}

bool PatientConsultationsModel::getOperationIsInProgress() const
{
    return(m_OperationIsInProgress);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]
