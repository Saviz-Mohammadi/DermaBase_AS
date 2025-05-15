#ifndef LabsListModel_H
#define LabsListModel_H

#include <QObject>
#include <QAbstractListModel>
#include <vector>
#include "database.hpp"
#include "lab.hpp"

class LabsListModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(Database *database READ getDatabase WRITE setDatabase NOTIFY databaseChanged FINAL)

public:
    explicit LabsListModel(QObject *parent = Q_NULLPTR, const QString& name = "No name");
    ~LabsListModel();

    // PUBLIC Enum
public:
    enum {
        LabID = Qt::UserRole + 1,
        Name,
        Specialization
    };

    // Fields
private:
    Database *m_Database;
    std::vector<Lab> m_Data;

    // Signals
signals:
    void databaseChanged();

    // PUBLIC Slots:
public slots:

    // PRIVATE Slots:
private slots:

    // PUBLIC Methods
public:

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
    void setData(std::vector<Lab> newData);
};

#endif // LabsListModel_H
