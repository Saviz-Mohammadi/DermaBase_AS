#ifndef DIAGNOSESLISTMODEL_H
#define DIAGNOSESLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <vector>
#include "database.hpp"
#include "diagnosis.hpp"

class DiagnosesListModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(Database *database READ getDatabase WRITE setDatabase NOTIFY databaseChanged FINAL)

public:
    explicit DiagnosesListModel(QObject *parent = Q_NULLPTR, const QString& name = "No name");
    ~DiagnosesListModel();

    // PUBLIC Enum
public:
    enum {
        DiagnosisID = Qt::UserRole + 1,
        Name
    };

    // Fields
private:
    Database *m_Database;
    std::vector<Diagnosis> m_Data;

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
    void setData(std::vector<Diagnosis> newData);
};

#endif // DIAGNOSESLISTMODEL_H
