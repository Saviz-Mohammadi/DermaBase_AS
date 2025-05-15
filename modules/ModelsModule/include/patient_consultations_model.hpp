#ifndef PATIENTCONSULTATIONSMODEL_H
#define PATIENTCONSULTATIONSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <vector>
#include "database.hpp"
#include "consultation.hpp"

class PatientConsultationsModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(Database *database READ getDatabase WRITE setDatabase NOTIFY databaseChanged FINAL)
    Q_PROPERTY(bool operationIsInProgress READ getOperationIsInProgress NOTIFY operationIsInProgressChanged FINAL)

public:
    explicit PatientConsultationsModel(QObject *parent = Q_NULLPTR, const QString& name = "No name");
    ~PatientConsultationsModel();

    // PUBLIC Enum
public:
    enum {
        ConsultationID = Qt::UserRole + 1,
        PatientID,
        ConsultantID,
        Name,
        Specialization,
        Date,
        Outcome
    };

    // Fields
private:
    Database *m_Database;
    bool m_OperationIsInProgress;
    int m_Row;
    Consultation m_Consultation;
    std::vector<Consultation> m_Data;

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
    Q_INVOKABLE void requestInsertPatientConsultation(const int patientID, const int consultantID);
    Q_INVOKABLE void requestRemovePatientConsultation(const int row);
    Q_INVOKABLE void requestUpdatePatientConsultationDateAndOutcome(const int consultationID, const QString &date, const QString &outcome, const int row);

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
    void setData(std::vector<Consultation> newData);
};

#endif // PATIENTCONSULTATIONSMODEL_H
