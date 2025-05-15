#ifndef FILTER_H
#define FILTER_H

#include <QObject>
#include <QSortFilterProxyModel>
#include <QVariant>
#include <QVariantMap>
#include <qqmlintegration.h>

class ProxyFilter : public QSortFilterProxyModel
{
    Q_OBJECT

    // Q_PROPERTY
    Q_PROPERTY(bool filterStatus READ getFilterStatus WRITE setFilterStatus NOTIFY filterStatusChanged)
    Q_PROPERTY(bool sensitivityStatus READ getSensitivityStatus WRITE setSensitivityStatus NOTIFY sensitivityStatusChanged)
    Q_PROPERTY(QString filterValue READ getFilterValue WRITE setFilterValue NOTIFY filterValueChanged)
    Q_PROPERTY(QString roleText READ getRoleText WRITE setRoleText NOTIFY roleTextChanged)

    // PUBLIC Enums
public:

public:
    explicit ProxyFilter(QObject *parent = nullptr);
    ~ProxyFilter();

    // Fields
private:
    bool m_FilterStatus;
    bool m_SensitivityStatus;
    QString m_FilterValue;
    QString m_RoleText;

    // Signals
signals:
    void filterStatusChanged();
    void sensitivityStatusChanged();
    void filterValueChanged();
    void roleTextChanged();

    // PUBLIC Slots:
public slots:

    // PRIVATE Slots:
private slots:

    // PUBLIC Methods
public:
    Q_INVOKABLE QVariantMap get(int ProxyFilterRow) const;
    Q_INVOKABLE void refresh();

    // PRIVATE Methods
private:
    int mapToRole(const QString &role) const;

    // PUBLIC Getters
public:
    bool getFilterStatus() const;
    bool getSensitivityStatus() const;
    QString getFilterValue() const;
    QString getRoleText() const;

    // PRIVATE Getters
public:

    // PUBLIC Setters
public:
    void setFilterStatus(bool newFilterStatus);
    void setSensitivityStatus(bool newSensitivityStatus);
    void setRoleText(const QString &newRoleText);
    void setFilterValue(const QString &newFilterValue);

    // PRIVATE Setters
private:

    // OVERRIDES
protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
};

#endif // FILTER_H
