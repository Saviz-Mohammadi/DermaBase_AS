#ifndef DATABASEWORKER_H
#define DATABASEWORKER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <vector>
#include "search_result.hpp"
#include "starred_patient.hpp"
#include "diagnosis.hpp"
#include "treatment.hpp"
#include "procedure.hpp"
#include "consultant.hpp"
#include "consultation.hpp"
#include "image.hpp"
#include "lab.hpp"
#include "lab_test.hpp"

class DatabaseWorker : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseWorker(QObject *parent = Q_NULLPTR, const QString& name = "No name");
    ~DatabaseWorker();

    // PUBLIC Enum
public:

    // Fields
private:
    const QString c_ConnectionName;

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

    /*

    // DELETION
    Q_INVOKABLE QVariantMap changeDeletionStatus(bool newStatus);

    // Miscellaneous
    Q_INVOKABLE QVariantMap totalPatients()*/;

    // PUBLIC Methods
public:
    void establishConnection(const QString &ipAddress, int port, const QString &schema, const QString &username, const QString &password);
    void cutConnection();
    void createPatient(const QString &firstName, const QString &lastName, int birthYear, const QString &phoneNumber, const QString &email, const QString &gender, const QString &maritalStatus);
    void findPatient(const int patientID);
    void findPatients(int mask, const QString &firstName, const QString &lastName, int birthYearStart, int birthYearEnd, const QString &phoneNumber, const QString &gender, const QString &maritalStatus);
    void findFirstPatients(const int count);
    void findLastPatients(const int count);
    void createStarredPatient(const int patientID);
    void getAllStarredPatients();
    void removeAllStarredPatients();
    void updateVisitStatusOfStarredPatient(const int patientID, const bool newStatus);
    void getPatientBasicInformation(const int patientID);
    void updatePatientBasicInformation(const int patientID, const QString &newFirstName, const QString &newLastName, int newBirthYear, const QString &newPhoneNumber, const QString &newEmail, const QString &newGender, const QString &newMaritalStatus);
    void getPatientVisitInformation(const int patientID);
    void updatePatientVisitInformation(const int patientID, const int newNumberOfPreviousVisits, const QString &newFirstVisitDate, const QString &newRecentVisitDate, const QString &newExpectedVisitDate);
    void getPatientPaymentInformation(const int patientID);
    void updatePatientPaymentInformation(const int patientID, const double newServicePrice, const double newPaidPrice);
    void getDiagnosesList();
    void insertPatientDiagnosis(const int patientID, const int diagnosisID);
    void getPatientDiagnoses(const int patientID);
    void removePatientDiagnosis(const int patientID, const int diagnosisID);
    void getPatientDiagnosesNote(const int patientID);
    void updatePatientDiagnosesNote(const int patientID, const QString &newNote);
    void getTreatmentsList();
    void insertPatientTreatment(const int patientID, const int treatmentID);
    void getPatientTreatments(const int patientID);
    void removePatientTreatment(const int patientID, const int treatmentID);
    void getPatientTreatmentsNote(const int patientID);
    void updatePatientTreatmentsNote(const int patientID, const QString &newNote);
    void getProceduresList();
    void insertPatientProcedure(const int patientID, const int procedureID);
    void getPatientProcedures(const int patientID);
    void removePatientProcedure(const int patientID, const int procedureID);
    void updatePatientProcedureFee(const int patientID, const int procedureID, const double newFee);
    void getPatientProceduresNote(const int patientID);
    void updatePatientProceduresNote(const int patientID, const QString &newNote);
    void getConsultantsList();
    void insertPatientConsultation(const int patientID, const int consultantID);
    void getPatientConsultations(const int patientID);
    void removePatientConsultation(const int consultationID);
    void updatePatientConsultationDateAndOutcome(const int consultationID, const QString &date, const QString &outcome);
    void getLabsList();
    void insertPatientLabTest(const int patientID, const int labID);
    void removePatientLabTest(const int labTestID);
    void updatePatientLabTest(const LabTest labTest);
    void getPatientLabTests(const int patientID);
    void getPatientImages(const int patientID);
    void insertPatientImage(const int patientID, const QString &name, const QByteArray &data);
    void removePatientImage(const int patienID, const QString &name);
    void updatePatientImageName(const int patientID, const QString &name, const QString &newName);
    void updatePatientDeletionStatus(const int patientID, const bool newStatus);

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

#endif // DATABASEWORKER_H
