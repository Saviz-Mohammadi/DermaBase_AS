#ifndef SEARCHMODEL_H
#define SEARCHMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <vector>
#include "database.hpp"
#include "search_result.hpp"

class SearchModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(Database *database READ getDatabase WRITE setDatabase NOTIFY databaseChanged FINAL)

public:
    explicit SearchModel(QObject *parent = Q_NULLPTR, const QString& name = "No name");
    ~SearchModel();

    // PUBLIC Enum
public:
    enum {
        PatientID = Qt::UserRole + 1,
        FirstName,
        LastName,
        BirthYear,
        PhoneNumber,
        Email,
        Gender,
        MaritalStatus
    };

    // Fields
private:
    bool m_Enabled;
    Database *m_Database;
    std::vector<SearchResult> m_Data;

    // Signals
signals:
    void databaseChanged();

    // PUBLIC Slots:
public slots:

    // PRIVATE Slots:
private slots:

    // PUBLIC Methods
public:
    Q_INVOKABLE void clear();

    // PRIVATE Methods
private:

    // OVERRIDES
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;

    // PUBLIC Getters
public:
    Database *getDatabase() const;

    // PRIVATE Getters
public:

    // PUBLIC Setters
public:
    void setDatabase(Database *newDatabase);

    // PRIVATE Setters
private:
    void setData(std::vector<SearchResult> newData);
};

#endif // SEARCHMODEL_H
