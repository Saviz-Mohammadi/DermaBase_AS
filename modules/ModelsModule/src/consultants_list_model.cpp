#include <QDebug>
#include "consultants_list_model.hpp"

// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

ConsultantsListModel::ConsultantsListModel(QObject *parent, const QString &name)
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

ConsultantsListModel::~ConsultantsListModel()
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

int ConsultantsListModel::rowCount(const QModelIndex &parent) const
{
    // If is parent:
    if(parent.isValid())
    {
        return(0);
    }

    return(m_Data.size());
}

QVariant ConsultantsListModel::data(const QModelIndex &index, int role) const
{
#ifdef QT_DEBUG
    if(!checkIndex(index, CheckIndexOption::IndexIsValid))
    {
        return(QVariant());
    }
#endif

    const int row = index.row();

    // Matching:
    if (role == ConsultantID)
    {
        return(m_Data[row].consultantID);
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

QHash<int, QByteArray> ConsultantsListModel::roleNames() const
{
    static QHash<int, QByteArray> roleMapping = {
        { ConsultantID, "consultantID" },
        { Name, "name" },
        { Specialization, "specialization"}
    };

    return(roleMapping);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC Setters
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

void ConsultantsListModel::setDatabase(Database *newDatabase)
{
    if(newDatabase == nullptr)
    {
        return;
    }

    // TODO (SAVIZ): I should probably make sure that I disconnect from the previous database, but since replacing databases never happens: I DON'T GIVE A FUCK!

    m_Database = newDatabase;

    connect(
        m_Database,
        &Database::finishedGettingConsultantsList,
        this,
        [this](int status, const QString& message, const std::vector<Consultant> data)
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

void ConsultantsListModel::setData(std::vector<Consultant> newData)
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

Database *ConsultantsListModel::getDatabase() const
{
    return(m_Database);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]
