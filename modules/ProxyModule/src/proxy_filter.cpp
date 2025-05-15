#include <QDebug>
#include "proxy_filter.hpp"

// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

ProxyFilter::ProxyFilter(QObject *parent) :
    QSortFilterProxyModel(parent)
    , m_FilterStatus (true)
    , m_SensitivityStatus(true)
    , m_FilterValue("")
    , m_RoleText("")
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "None";
    qDebug() << "Log Output :" << "None";
#endif
}

ProxyFilter::~ProxyFilter()
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

QVariantMap ProxyFilter::get(int ProxyFilterRow) const
{
    QModelIndex ProxyFilterIndex = index(ProxyFilterRow, 0);
    QModelIndex sourceIndex = mapToSource(ProxyFilterIndex);

    QVariantMap itemMap;

    const auto roles = roleNames();
    for (auto it = roles.constBegin(); it != roles.constEnd(); ++it)
    {
        itemMap.insert(
            QString::fromUtf8(it.value()),
            sourceModel()->data(sourceIndex, it.key())
        );
    }

    return (itemMap);
}

void ProxyFilter::refresh()
{
    invalidate();
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PRIVATE Methods
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

int ProxyFilter::mapToRole(const QString &role) const
{
    int roleIndex = sourceModel()->roleNames().key(role.toUtf8(), Qt::DisplayRole);

    return (roleIndex);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC Getters
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

bool ProxyFilter::getFilterStatus() const
{
    return (m_FilterStatus);
}

bool ProxyFilter::getSensitivityStatus() const
{
    return (m_SensitivityStatus);
}

QString ProxyFilter::getFilterValue() const
{
    return (m_FilterValue);
}

QString ProxyFilter::getRoleText() const
{
    return (m_RoleText);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC Setters
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

void ProxyFilter::setFilterStatus(bool newFilterStatus)
{
    if (m_FilterStatus == newFilterStatus)
    {
        return;
    }

    m_FilterStatus = newFilterStatus;
    emit filterStatusChanged();

    // Force filter to update:
    invalidateFilter();
}

void ProxyFilter::setSensitivityStatus(bool newSensitivityStatus)
{
    if (m_SensitivityStatus == newSensitivityStatus)
    {
        return;
    }

    m_SensitivityStatus = newSensitivityStatus;
    emit sensitivityStatusChanged();

    // Force filter to update:
    invalidateFilter();
}

void ProxyFilter::setFilterValue(const QString &newFilterValue)
{
    if (m_FilterValue == newFilterValue)
    {
        return;
    }

    m_FilterValue = newFilterValue;
    emit filterValueChanged();

    // Force filter to update:
    invalidateFilter();
}

void ProxyFilter::setRoleText(const QString &newRoleText)
{
    if (m_RoleText == newRoleText)
    {
        return;
    }

    m_RoleText = newRoleText;
    emit roleTextChanged();

    // Force filter to update:
    invalidateFilter();
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// OVERRIDES
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

bool ProxyFilter::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (m_FilterStatus == false)
    {
        return (true); // Accept all rows
    }

    if(m_FilterValue == "")
    {
        return (true); // Accept all rows
    }

    if(m_RoleText == "")
    {
        return (true); // Accept all rows
    }

    QString data = sourceModel()->data(
        sourceModel()->index(sourceRow, 0, sourceParent),
        mapToRole(m_RoleText)
    ).toString();

#ifdef QT_DEBUG
    qDebug() << "Data found: " << data;
#endif

    return m_SensitivityStatus ? data.contains(m_FilterValue, Qt::CaseSensitive) : data.contains(m_FilterValue, Qt::CaseInsensitive);
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]
