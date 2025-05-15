#include <QDebug>
#include "treatments_list_model.hpp"

// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

TreatmentsListModel::TreatmentsListModel(QObject *parent, const QString &name)
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

TreatmentsListModel::~TreatmentsListModel()
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

int TreatmentsListModel::rowCount(const QModelIndex &parent) const
{
    // If is parent:
    if(parent.isValid())
    {
        return(0);
    }

    return(m_Data.size());
}

QVariant TreatmentsListModel::data(const QModelIndex &index, int role) const
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

QHash<int, QByteArray> TreatmentsListModel::roleNames() const
{
    static QHash<int, QByteArray> roleMapping = {
        { TreatmentID, "treatmentID" },
        { Name, "name" }
    };

    return(roleMapping);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC Setters
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

void TreatmentsListModel::setDatabase(Database *newDatabase)
{
    if(newDatabase == nullptr)
    {
        return;
    }

    // TODO (SAVIZ): I should probably make sure that I disconnect from the previous database, but since replacing databases never happens: I DON'T GIVE A FUCK!

    m_Database = newDatabase;

    connect(
        m_Database,
        &Database::finishedGettingTreatmentsList,
        this,
        [this](int status, const QString& message, const std::vector<Treatment> data)
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

void TreatmentsListModel::setData(std::vector<Treatment> newData)
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

Database *TreatmentsListModel::getDatabase() const
{
    return(m_Database);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]
