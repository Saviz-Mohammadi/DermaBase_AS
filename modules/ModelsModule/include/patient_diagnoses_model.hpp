#ifndef PATIENTDIAGNOSESMODEL_H
#define PATIENTDIAGNOSESMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <vector>
#include "database.hpp"
#include "diagnosis.hpp"

class PatientDiagnosesModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(Database *database READ getDatabase WRITE setDatabase NOTIFY databaseChanged FINAL)
    Q_PROPERTY(bool operationIsInProgress READ getOperationIsInProgress NOTIFY operationIsInProgressChanged FINAL)

public:
    explicit PatientDiagnosesModel(QObject *parent = Q_NULLPTR, const QString& name = "No name");
    ~PatientDiagnosesModel();

    // PUBLIC Enum
public:
    enum {
        DiagnosisID = Qt::UserRole + 1,
        Name
    };

    // Fields
private:
    Database *m_Database;
    bool m_OperationIsInProgress;
    int m_Row;
    Diagnosis m_Diagnosis;
    std::vector<Diagnosis> m_Data;

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
    Q_INVOKABLE void requestInsertPatientDiagnosis(const int patientID, const int diagnosisID, const QString &name);
    Q_INVOKABLE void requestRemovePatientDiagnosis(const int patientID, const int diagnosisID, const int row);

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
    void setData(std::vector<Diagnosis> newData);
};

#endif // PATIENTDIAGNOSESMODEL_H
