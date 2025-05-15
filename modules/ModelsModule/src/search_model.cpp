#include <QDebug>
#include "search_model.hpp"

// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

SearchModel::SearchModel(QObject *parent, const QString &name)
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

SearchModel::~SearchModel()
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

void SearchModel::clear()
{
    beginResetModel();

    m_Data.clear();

    endResetModel();
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC OVERRIDES
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

int SearchModel::rowCount(const QModelIndex &parent) const
{
    // If is parent:
    if(parent.isValid())
    {
        return(0);
    }

    return(m_Data.size());
}

QVariant SearchModel::data(const QModelIndex &index, int role) const
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

    return(QVariant());
}

QHash<int, QByteArray> SearchModel::roleNames() const
{
    static QHash<int, QByteArray> roleMapping = {
        { PatientID, "patientID" },
        { FirstName, "firstName" },
        { LastName, "lastName" },
        { BirthYear, "birthYear" },
        { PhoneNumber, "phoneNumber" },
        { Email, "email" },
        { Gender, "gender" },
        { MaritalStatus, "maritalStatus" }
    };

    return(roleMapping);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC Getters
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

Database *SearchModel::getDatabase() const
{
    return(m_Database);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC Setters
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

void SearchModel::setDatabase(Database *newDatabase)
{
    if(newDatabase == nullptr)
    {
        return;
    }

    // TODO (SAVIZ): I should probably make sure that I disconnect from the previous database, but since replacing databases never happens: I DON'T GIVE A FUCK!

    m_Database = newDatabase;

    connect(
        m_Database,
        &Database::finishedFinding,
        this,
        [this](int status, const QString& message, const std::vector<SearchResult> data)
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

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PRIVATE Setters
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

void SearchModel::setData(std::vector<SearchResult> newData)
{
    beginResetModel();

    m_Data = newData;

    endResetModel();
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]
