#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QThread>

#include "database_worker.hpp"

class Database : public QObject
{
    Q_OBJECT

public:
    explicit Database(QObject *parent = Q_NULLPTR, const QString& name = "No name");
    ~Database();

    // PUBLIC Enum
public:

    // Fields
private:
    QThread *m_Thread;
    DatabaseWorker *m_DatabaseWorker;

    // Signals
signals:
    // Pattern:
    // -2 >> Operation finished on fail
    // -1 >> Operation finished on warning
    // 1  >> Operation finished on success
    void startedConnecting();
    void finishedConnecting(int status, const QString &message);
    void startedCreatingPatient();
    void finishedCreatingPatient(int status, const QString &message);
    void startedFinding();
    void finishedFinding(int status, const QString &message, std::vector<SearchResult> data);
    void startedCreatingStarredPatient();
    void finishedCreatingStarredPatient(int status, const QString &message, StarredPatient starredPatient);
    void startedGettingAllStarredPatients();
    void finishedGettingAllStarredPatients(int status, const QString &message, std::vector<StarredPatient> data);
    void startedRemovingAllStarredPatients();
    void finishedRemovingAllStarredPatients(int status, const QString &message);
    void startedUpdatingStarredPatientVisitStatus();
    void finishedUpdatingStarredPatientVisitStatus(int status, const QString &message);
    void startedGettingPatientBasicInformation();
    void finishedGettingPatientBasicInformation(int status, const QString &message, const QString &firstName, const QString &lastName, int birthYear, const QString &phoneNumber, const QString &email, const QString &gender, const QString &maritalStatus);
    void startedUpdatingPatientBasicInformation();
    void finishedUpdatingPatientBasicInformation(int status, const QString &message);
    void startedGettingPatientVisitInformation();
    void finishedGettingPatientVisitInformation(int status, const QString &message, const int numberOfPreviousVisits, const QString &firstVisitDate, const QString &recentVisitDate, const QString &expectedVisitDate);
    void startedUpdatingPatientVisitInformation();
    void finishedUpdatingPatientVisitInformation(int status, const QString &message);
    void startedGettingPatientPaymentInformation();
    void finishedGettingPatientPaymentInformation(int status, const QString &message, const double servicePrice, const double paidPrice);
    void startedUpdatingPatientPaymentInformation();
    void finishedUpdatingPatientPaymentInformation(int status, const QString &message);
    void startedGettingDiagnosesList();
    void finishedGettingDiagnosesList(int status, const QString &message, std::vector<Diagnosis> data);
    void startedInsertingPatientDiagnosis();
    void finishedInsertingPatientDiagnosis(int status, const QString &message);
    void startedGettingPatientDiagnoses();
    void finishedGettingPatientDiagnoses(int status, const QString &message, std::vector<Diagnosis> data);
    void startedRemovingPatientDiagnosis();
    void finishedRemovingPatientDiagnosis(int status, const QString &message);
    void startedGettingPatientDiagnosesNote();
    void finishedGettingPatientDiagnosesNote(int status, const QString &message, const QString &note);
    void startedUpdatingPatientDiagnosesNote();
    void finishedUpdatingPatientDiagnosesNote(int status, const QString &message);
    void startedGettingTreatmentsList();
    void finishedGettingTreatmentsList(int status, const QString &message, std::vector<Treatment> data);
    void startedInsertingPatientTreatment();
    void finishedInsertingPatientTreatment(int status, const QString &message);
    void startedGettingPatientTreatments();
    void finishedGettingPatientTreatments(int status, const QString &message, std::vector<Treatment> data);
    void startedRemovingPatientTreatment();
    void finishedRemovingPatientTreatment(int status, const QString &message);
    void startedGettingPatientTreatmentsNote();
    void finishedGettingPatientTreatmentsNote(int status, const QString &message, const QString &note);
    void startedUpdatingPatientTreatmentsNote();
    void finishedUpdatingPatientTreatmentsNote(int status, const QString &message);
    void startedGettingProceduresList();
    void finishedGettingProceduresList(int status, const QString &message, std::vector<Procedure> data);
    void startedInsertingPatientProcedure();
    void finishedInsertingPatientProcedure(int status, const QString &message);
    void startedGettingPatientProcedures();
    void finishedGettingPatientProcedures(int status, const QString &message, std::vector<Procedure> data);
    void startedRemovingPatientProcedure();
    void finishedRemovingPatientProcedure(int status, const QString &message);
    void startedUpdatingPatientProcedureFee();
    void finishedUpdatingPatientProcedureFee(int status, const QString &message);
    void startedGettingPatientProceduresNote();
    void finishedGettingPatientProceduresNote(int status, const QString &message, const QString &note);
    void startedUpdatingPatientProceduresNote();
    void finishedUpdatingPatientProceduresNote(int status, const QString &message);
    void startedGettingConsultantsList();
    void finishedGettingConsultantsList(int status, const QString &message, std::vector<Consultant> data);
    void startedInsertingPatientConsultation();
    void finishedInsertingPatientConsultation(int status, const QString &message, Consultation consultation);
    void startedGettingPatientConsultations();
    void finishedGettingPatientConsultations(int status, const QString &message, std::vector<Consultation> data);
    void startedRemovingPatientConsultation();
    void finishedRemovingPatientConsultation(int status, const QString &message);
    void startedUpdatingPatientConsultationDateAndOutcome();
    void finishedUpdatingPatientConsultationDateAndOutcome(int status, const QString &message);
    void startedGettingLabsList();
    void finishedGettingLabsList(int status, const QString &message, std::vector<Lab> data);
    void startedInsertingPatientLabTest();
    void finishedInsertingPatientLabTest(int status, const QString &message, LabTest labTest);
    void startedRemovingPatientLabTest();
    void finishedRemovingPatientLabTest(int status, const QString &message);
    void startedGettingPatientLabTests();
    void finishedGettingPatientLabTests(int status, const QString &message, std::vector<LabTest> data);
    void startedUpdatingPatientLabTest();
    void finishedUpdatingPatientLabTest(int status, const QString &message);
    void startedGettingPatientImages();
    void finishedGettingPatientImages(int status, const QString &message, std::vector<Image> data);
    void startedInsertingPatientImage();
    void finishedInsertingPatientImage(int status, const QString &message);
    void startedRemovingPatientImage();
    void finishedRemovingPatientImage(int status, const QString &message);
    void startedUpdatingPatientImageName();
    void finishedUpdatingPatientImageName(int status, const QString &message);
    void startedUpdatingPatientDeletionStatus();
    void finishedUpdatingPatientDeletionStatus(int status, const QString &message);

    // PUBLIC Slots:
public slots:

    // PRIVATE Slots:
private slots:

    // PUBLIC Methods
public:
    Q_INVOKABLE void establishConnection(const QString &ipAddress, int port, const QString &schema, const QString &username, const QString &password);
    Q_INVOKABLE void cutConnection();
    Q_INVOKABLE void createPatient(const QString &firstName, const QString &lastName, int birthYear, const QString &phoneNumber, const QString &email, const QString &gender, const QString &maritalStatus);
    Q_INVOKABLE void findPatient(const int patientID);
    Q_INVOKABLE void findPatients(int mask, const QString &firstName, const QString &lastName, int birthYearStart, int birthYearEnd, const QString &phoneNumber, const QString &gender, const QString &maritalStatus);
    Q_INVOKABLE void findFirstPatients(const int count);
    Q_INVOKABLE void findLastPatients(const int count);
    void createStarredPatient(const int patientID);
    void getAllStarredPatients();
    void removeAllStarredPatients();
    void updateVisitStatusOfStarredPatient(const int patientID, const bool newStatus);
    Q_INVOKABLE void getPatientBasicInformation(const int patientID);
    Q_INVOKABLE void updatePatientBasicInformation(const int patientID, const QString &newFirstName, const QString &newLastName, int newBirthYear, const QString &newPhoneNumber, const QString &newEmail, const QString &newGender, const QString &newMaritalStatus);
    Q_INVOKABLE void getPatientVisitInformation(const int patientID);
    Q_INVOKABLE void updatePatientVisitInformation(const int patientID, const int newNumberOfPreviousVisits, const QString &newFirstVisitDate, const QString &newRecentVisitDate, const QString &newExpectedVisitDate);
    Q_INVOKABLE void getPatientPaymentInformation(const int patientID);
    Q_INVOKABLE void updatePatientPaymentInformation(const int patientID, const double newServicePrice, const double newPaidPrice);
    Q_INVOKABLE void getDiagnosesList();
    Q_INVOKABLE void insertPatientDiagnosis(const int patientID, const int diagnosisID);
    Q_INVOKABLE void getPatientDiagnoses(const int patientID);
    Q_INVOKABLE void removePatientDiagnosis(const int patientID, const int diagnosisID);
    Q_INVOKABLE void getPatientDiagnosesNote(const int patientID);
    Q_INVOKABLE void updatePatientDiagnosesNote(const int patientID, const QString &newNote);
    Q_INVOKABLE void getTreatmentsList();
    Q_INVOKABLE void insertPatientTreatment(const int patientID, const int treatmentID);
    Q_INVOKABLE void getPatientTreatments(const int patientID);
    Q_INVOKABLE void removePatientTreatment(const int patientID, const int treatmentID);
    Q_INVOKABLE void getPatientTreatmentsNote(const int patientID);
    Q_INVOKABLE void updatePatientTreatmentsNote(const int patientID, const QString &newNote);
    Q_INVOKABLE void getProceduresList();
    Q_INVOKABLE void insertPatientProcedure(const int patientID, const int procedureID);
    Q_INVOKABLE void getPatientProcedures(const int patientID);
    Q_INVOKABLE void removePatientProcedure(const int patientID, const int procedureID);
    Q_INVOKABLE void updatePatientProcedureFee(const int patientID, const int procedureID, const double newFee);
    Q_INVOKABLE void getPatientProceduresNote(const int patientID);
    Q_INVOKABLE void updatePatientProceduresNote(const int patientID, const QString &newNote);
    Q_INVOKABLE void getConsultantsList();
    Q_INVOKABLE void insertPatientConsultation(const int patientID, const int consultantID);
    Q_INVOKABLE void getPatientConsultations(const int patientID);
    Q_INVOKABLE void removePatientConsultation(const int consultationID);
    Q_INVOKABLE void updatePatientConsultationDateAndOutcome(const int consultationID, const QString &date, const QString &outcome);
    Q_INVOKABLE void getLabsList();
    Q_INVOKABLE void insertPatientLabTest(const int patientID, const int labID);
    Q_INVOKABLE void removePatientLabTest(const int labTestID);
    Q_INVOKABLE void getPatientLabTests(const int patientID);
    Q_INVOKABLE void updatePatientLabTest(const LabTest labTest);
    Q_INVOKABLE void getPatientImages(const int patientID);
    Q_INVOKABLE void insertPatientImage(const int patientID, const QString &name, const QByteArray &data);
    Q_INVOKABLE void removePatientImage(const int patientID, const QString &name);
    Q_INVOKABLE void updatePatientImageName(const int patientID, const QString &name, const QString &newName);
    Q_INVOKABLE void updatePatientDeletionStatus(const int patientID, const bool newStatus);

    // PRIVATE Methods
private:

    // PUBLIC Getters
public:

    // PRIVATE Getters
public:

    // PUBLIC Setters
public:

    // PRIVATE Setters
private:
};

#endif // DATABASE_H
