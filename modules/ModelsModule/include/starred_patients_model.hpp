#ifndef STARREDPATIENTSMODEL_H
#define STARREDPATIENTSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <vector>
#include "database.hpp"
#include "starred_patient.hpp"

class StarredPatientsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(Database *database READ getDatabase WRITE setDatabase NOTIFY databaseChanged FINAL)
    Q_PROPERTY(bool operationIsInProgress READ getOperationIsInProgress NOTIFY operationIsInProgressChanged FINAL)
    Q_PROPERTY(int visitedCount READ getVisitedCount WRITE setVisitedCount NOTIFY visitedCountChanged FINAL)

public:
    explicit StarredPatientsModel(QObject *parent = Q_NULLPTR, const QString& name = "No name");
    ~StarredPatientsModel();

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
        MaritalStatus,
        HasVisited
    };

    // Fields
private:
    Database *m_Database;
    bool m_OperationIsInProgress;
    int m_Row;
    std::vector<StarredPatient> m_Data;

    // Signals
signals:
    void databaseChanged();
    void operationIsInProgressChanged();
    void visitedCountChanged();

    // PUBLIC Slots:
public slots:

    // PRIVATE Slots:
private slots:

    // PUBLIC Methods
public:
    Q_INVOKABLE void requestCreateStarredPatient(const int patientID);
    Q_INVOKABLE void requestUpdateVisitStatusOfStarredPatient(const int row, bool newStatus);
    Q_INVOKABLE void requestGetAllStarredPatients();
    Q_INVOKABLE void requestRemoveAllStarredPatients();

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
    bool getOperationIsInProgress() const;
    int getVisitedCount() const;

    // PRIVATE Getters
public:

    // PUBLIC Setters
public:
    void setDatabase(Database *newDatabase);


    // PRIVATE Setters
private:
    void setVisitedCount(int newVisitedCount);
    void setData(std::vector<StarredPatient> newData);
};

#endif // STARREDPATIENTSMODEL_H
