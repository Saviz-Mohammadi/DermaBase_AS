#ifndef PATIENTPROCEDURESMODEL_H
#define PATIENTPROCEDURESMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <vector>
#include "database.hpp"
#include "procedure.hpp"

class PatientProceduresModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(Database *database READ getDatabase WRITE setDatabase NOTIFY databaseChanged FINAL)
    Q_PROPERTY(bool operationIsInProgress READ getOperationIsInProgress NOTIFY operationIsInProgressChanged FINAL)

public:
    explicit PatientProceduresModel(QObject *parent = Q_NULLPTR, const QString& name = "No name");
    ~PatientProceduresModel();

    // PUBLIC Enum
public:
    enum {
        ProcedureID = Qt::UserRole + 1,
        Name,
        Fee
    };

    // Fields
private:
    Database *m_Database;
    bool m_OperationIsInProgress;
    int m_Row;
    Procedure m_Procedure;
    std::vector<Procedure> m_Data;

    // Signals
signals:
    void databaseChanged();
    void operationIsInProgressChanged();

    // PUBLIC Slots:
public slots:

    // PRIVATE Slots:
private slots:

    // PUBLIC Methods
public:
    Q_INVOKABLE void requestInsertPatientProcedure(const int patientID, const int procedureID, const QString &name);
    Q_INVOKABLE void requestRemovePatientProcedure(const int patientID, const int procedureID, const int row);
    Q_INVOKABLE void requestUpdatePatientProcedureFee(const int patientID, const int procedureID, const double newFee, const int row);

    // PRIVATE Methods
private:

    // OVERRIDES
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    virtual bool removeRows(int row, int count, const QModelIndex &parent) override;

    // PUBLIC Getters
public:
    Database *getDatabase() const;
    bool getOperationIsInProgress() const;

    // PRIVATE Getters
public:

    // PUBLIC Setters
public:
    void setDatabase(Database *newDatabase);

    // PRIVATE Setters
private:
    void setData(std::vector<Procedure> newData);
};

#endif // PATIENTPROCEDURESMODEL_H
