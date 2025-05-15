#ifndef PATIENTTREATMENTSMODEL_H
#define PATIENTTREATMENTSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <vector>
#include "database.hpp"
#include "treatment.hpp"

class PatientTreatmentsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(Database *database READ getDatabase WRITE setDatabase NOTIFY databaseChanged FINAL)
    Q_PROPERTY(bool operationIsInProgress READ getOperationIsInProgress NOTIFY operationIsInProgressChanged FINAL)

public:
    explicit PatientTreatmentsModel(QObject *parent = Q_NULLPTR, const QString& name = "No name");
    ~PatientTreatmentsModel();

    // PUBLIC Enum
public:
    enum {
        TreatmentID = Qt::UserRole + 1,
        Name
    };

    // Fields
private:
    Database *m_Database;
    bool m_OperationIsInProgress;
    int m_Row;
    Treatment m_Treatment;
    std::vector<Treatment> m_Data;

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
    Q_INVOKABLE void requestInsertPatientTreatment(const int patientID, const int treatmentID, const QString &name);
    Q_INVOKABLE void requestRemovePatientTreatment(const int patientID, const int treatmentID, const int row);

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
    void setData(std::vector<Treatment> newData);
};

#endif // PATIENTTREATMENTSMODEL_H
