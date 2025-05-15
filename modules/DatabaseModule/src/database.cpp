#include <QDebug>
#include "database.hpp"

// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

Database::Database(QObject *parent, const QString &name)
    : QObject{parent}
    , m_Thread(new QThread(nullptr))
    , m_DatabaseWorker(new DatabaseWorker(nullptr))
{
    this->setObjectName(name);

    // Setup:
    m_Thread->setObjectName("Worker Thread");
    m_DatabaseWorker->moveToThread(m_Thread);

    // Thread connections:
    connect(
        m_Thread,
        &QThread::finished,
        m_DatabaseWorker,
        &QObject::deleteLater
    );

    connect(
        m_Thread,
        &QThread::finished,
        m_Thread,
        &QObject::deleteLater
    );

    // Connection connections:
    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedConnecting,
        this,
        &Database::startedConnecting,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedConnecting,
        this,
        &Database::finishedConnecting,
        Qt::QueuedConnection
    );

    // Creating patient connections:
    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedCreatingPatient,
        this,
        &Database::startedCreatingPatient,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedCreatingPatient,
        this,
        &Database::finishedCreatingPatient,
        Qt::QueuedConnection
    );

    // Finding connections:
    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedFinding,
        this,
        &Database::startedFinding,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedFinding,
        this,
        &Database::finishedFinding,
        Qt::QueuedConnection
    );

    // Star connections:
    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedCreatingStarredPatient,
        this,
        &Database::startedCreatingStarredPatient,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedCreatingStarredPatient,
        this,
        &Database::finishedCreatingStarredPatient,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedGettingAllStarredPatients,
        this,
        &Database::startedGettingAllStarredPatients,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedGettingAllStarredPatients,
        this,
        &Database::finishedGettingAllStarredPatients,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedRemovingAllStarredPatients,
        this,
        &Database::startedRemovingAllStarredPatients,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedRemovingAllStarredPatients,
        this,
        &Database::finishedRemovingAllStarredPatients,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedUpdatingStarredPatientVisitStatus,
        this,
        &Database::startedUpdatingStarredPatientVisitStatus,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedUpdatingStarredPatientVisitStatus,
        this,
        &Database::finishedUpdatingStarredPatientVisitStatus,
        Qt::QueuedConnection
    );

    // Edit connections:
    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedGettingPatientBasicInformation,
        this,
        &Database::startedGettingPatientBasicInformation,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedGettingPatientBasicInformation,
        this,
        &Database::finishedGettingPatientBasicInformation,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedUpdatingPatientBasicInformation,
        this,
        &Database::startedUpdatingPatientBasicInformation,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedUpdatingPatientBasicInformation,
        this,
        &Database::finishedUpdatingPatientBasicInformation,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedGettingPatientVisitInformation,
        this,
        &Database::startedGettingPatientVisitInformation,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedGettingPatientVisitInformation,
        this,
        &Database::finishedGettingPatientVisitInformation,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedUpdatingPatientVisitInformation,
        this,
        &Database::startedUpdatingPatientVisitInformation,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedUpdatingPatientVisitInformation,
        this,
        &Database::finishedUpdatingPatientVisitInformation,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedGettingPatientPaymentInformation,
        this,
        &Database::startedGettingPatientPaymentInformation,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedGettingPatientPaymentInformation,
        this,
        &Database::finishedGettingPatientPaymentInformation,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedUpdatingPatientPaymentInformation,
        this,
        &Database::startedUpdatingPatientPaymentInformation,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedUpdatingPatientPaymentInformation,
        this,
        &Database::finishedUpdatingPatientPaymentInformation,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedGettingDiagnosesList,
        this,
        &Database::startedGettingDiagnosesList,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedGettingDiagnosesList,
        this,
        &Database::finishedGettingDiagnosesList,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedInsertingPatientDiagnosis,
        this,
        &Database::startedInsertingPatientDiagnosis,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedInsertingPatientDiagnosis,
        this,
        &Database::finishedInsertingPatientDiagnosis,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedGettingPatientDiagnoses,
        this,
        &Database::startedGettingPatientDiagnoses,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedGettingPatientDiagnoses,
        this,
        &Database::finishedGettingPatientDiagnoses,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedRemovingPatientDiagnosis,
        this,
        &Database::startedRemovingPatientDiagnosis,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedRemovingPatientDiagnosis,
        this,
        &Database::finishedRemovingPatientDiagnosis,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedGettingPatientDiagnosesNote,
        this,
        &Database::startedGettingPatientDiagnosesNote,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedGettingPatientDiagnosesNote,
        this,
        &Database::finishedGettingPatientDiagnosesNote,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedUpdatingPatientDiagnosesNote,
        this,
        &Database::startedUpdatingPatientDiagnosesNote,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedUpdatingPatientDiagnosesNote,
        this,
        &Database::finishedUpdatingPatientDiagnosesNote,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedGettingTreatmentsList,
        this,
        &Database::startedGettingTreatmentsList,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedGettingTreatmentsList,
        this,
        &Database::finishedGettingTreatmentsList,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedInsertingPatientTreatment,
        this,
        &Database::startedInsertingPatientTreatment,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedInsertingPatientTreatment,
        this,
        &Database::finishedInsertingPatientTreatment,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedGettingPatientTreatments,
        this,
        &Database::startedGettingPatientTreatments,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedGettingPatientTreatments,
        this,
        &Database::finishedGettingPatientTreatments,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedRemovingPatientTreatment,
        this,
        &Database::startedRemovingPatientTreatment,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedRemovingPatientTreatment,
        this,
        &Database::finishedRemovingPatientTreatment,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedGettingPatientTreatmentsNote,
        this,
        &Database::startedGettingPatientTreatmentsNote,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedGettingPatientTreatmentsNote,
        this,
        &Database::finishedGettingPatientTreatmentsNote,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedUpdatingPatientTreatmentsNote,
        this,
        &Database::startedUpdatingPatientTreatmentsNote,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedUpdatingPatientTreatmentsNote,
        this,
        &Database::finishedUpdatingPatientTreatmentsNote,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedGettingPatientProcedures,
        this,
        &Database::startedGettingPatientProcedures,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedGettingProceduresList,
        this,
        &Database::finishedGettingProceduresList,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedInsertingPatientProcedure,
        this,
        &Database::startedInsertingPatientProcedure,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedInsertingPatientProcedure,
        this,
        &Database::finishedInsertingPatientProcedure,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedGettingPatientProcedures,
        this,
        &Database::startedGettingPatientProcedures,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedGettingPatientProcedures,
        this,
        &Database::finishedGettingPatientProcedures,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedRemovingPatientProcedure,
        this,
        &Database::startedRemovingPatientProcedure,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedRemovingPatientProcedure,
        this,
        &Database::finishedRemovingPatientProcedure,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedUpdatingPatientProcedureFee,
        this,
        &Database::startedUpdatingPatientProcedureFee,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedUpdatingPatientProcedureFee,
        this,
        &Database::finishedUpdatingPatientProcedureFee,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedGettingPatientProceduresNote,
        this,
        &Database::startedGettingPatientProceduresNote,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedGettingPatientProceduresNote,
        this,
        &Database::finishedGettingPatientProceduresNote,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedUpdatingPatientProceduresNote,
        this,
        &Database::startedUpdatingPatientProceduresNote,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedUpdatingPatientProceduresNote,
        this,
        &Database::finishedUpdatingPatientProceduresNote,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedGettingConsultantsList,
        this,
        &Database::startedGettingConsultantsList,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedGettingConsultantsList,
        this,
        &Database::finishedGettingConsultantsList,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedInsertingPatientConsultation,
        this,
        &Database::startedInsertingPatientConsultation,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedInsertingPatientConsultation,
        this,
        &Database::finishedInsertingPatientConsultation,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedGettingPatientConsultations,
        this,
        &Database::startedGettingPatientConsultations,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedGettingPatientConsultations,
        this,
        &Database::finishedGettingPatientConsultations,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedRemovingPatientConsultation,
        this,
        &Database::startedRemovingPatientConsultation,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedRemovingPatientConsultation,
        this,
        &Database::finishedRemovingPatientConsultation,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedUpdatingPatientConsultationDateAndOutcome,
        this,
        &Database::startedUpdatingPatientConsultationDateAndOutcome,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedUpdatingPatientConsultationDateAndOutcome,
        this,
        &Database::finishedUpdatingPatientConsultationDateAndOutcome,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedGettingLabsList,
        this,
        &Database::startedGettingLabsList,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedGettingLabsList,
        this,
        &Database::finishedGettingLabsList,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedGettingPatientImages,
        this,
        &Database::startedGettingPatientImages,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedGettingPatientImages,
        this,
        &Database::finishedGettingPatientImages,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedInsertingPatientImage,
        this,
        &Database::startedInsertingPatientImage,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedInsertingPatientImage,
        this,
        &Database::finishedInsertingPatientImage,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedRemovingPatientImage,
        this,
        &Database::startedRemovingPatientImage,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedRemovingPatientImage,
        this,
        &Database::finishedRemovingPatientImage,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedUpdatingPatientImageName,
        this,
        &Database::startedUpdatingPatientImageName,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedUpdatingPatientImageName,
        this,
        &Database::finishedUpdatingPatientImageName,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedInsertingPatientLabTest,
        this,
        &Database::startedInsertingPatientLabTest,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedInsertingPatientLabTest,
        this,
        &Database::finishedInsertingPatientLabTest,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedRemovingPatientLabTest,
        this,
        &Database::startedRemovingPatientLabTest,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedRemovingPatientLabTest,
        this,
        &Database::finishedRemovingPatientLabTest,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedGettingPatientLabTests,
        this,
        &Database::startedGettingPatientLabTests,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedGettingPatientLabTests,
        this,
        &Database::finishedGettingPatientLabTests,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedUpdatingPatientLabTest,
        this,
        &Database::startedUpdatingPatientLabTest,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedUpdatingPatientLabTest,
        this,
        &Database::finishedUpdatingPatientLabTest,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::startedUpdatingPatientDeletionStatus,
        this,
        &Database::startedUpdatingPatientDeletionStatus,
        Qt::QueuedConnection
    );

    connect(
        m_DatabaseWorker,
        &DatabaseWorker::finishedUpdatingPatientDeletionStatus,
        this,
        &Database::finishedUpdatingPatientDeletionStatus,
        Qt::QueuedConnection
    );

    // Start thread:
    m_Thread->start();

#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "None";
    qDebug() << "Log Output :" << "None";
#endif
}

Database::~Database()
{
    // Arrange shutdown:
    m_Thread->quit();
    m_Thread->wait();

#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "None";
    qDebug() << "Log Output :" << "None";
#endif
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC Methods
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

void Database::establishConnection(const QString &ipAddress, int port, const QString &schema, const QString &username, const QString &password)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::establishConnection,
        Qt::QueuedConnection,
        ipAddress,
        port,
        schema,
        username,
        password
    );
}

void Database::cutConnection()
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::cutConnection,
        Qt::BlockingQueuedConnection
    );
}

void Database::createPatient(const QString &firstName, const QString &lastName, int birthYear, const QString &phoneNumber, const QString &email, const QString &gender, const QString &maritalStatus)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::createPatient,
        Qt::QueuedConnection,
        firstName,
        lastName,
        birthYear,
        phoneNumber,
        email,
        gender,
        maritalStatus
    );
}

void Database::findPatient(const int patientID)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::findPatient,
        Qt::QueuedConnection,
        patientID
    );
}

void Database::findPatients(int mask, const QString &firstName, const QString &lastName, int birthYearStart, int birthYearEnd, const QString &phoneNumber, const QString &gender, const QString &maritalStatus)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::findPatients,
        Qt::QueuedConnection,
        mask,
        firstName,
        lastName,
        birthYearStart,
        birthYearEnd,
        phoneNumber,
        gender,
        maritalStatus
    );
}

void Database::findFirstPatients(const int count)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::findFirstPatients,
        Qt::QueuedConnection,
        count
    );
}

void Database::findLastPatients(const int count)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::findLastPatients,
        Qt::QueuedConnection,
        count
    );
}

void Database::createStarredPatient(const int patientID)
{

    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::createStarredPatient,
        Qt::QueuedConnection,
        patientID
    );
}

void Database::getAllStarredPatients()
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::getAllStarredPatients,
        Qt::QueuedConnection
    );
}

void Database::removeAllStarredPatients()
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::removeAllStarredPatients,
        Qt::QueuedConnection
    );
}

void Database::updateVisitStatusOfStarredPatient(const int patientID, const bool newStatus)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::updateVisitStatusOfStarredPatient,
        Qt::QueuedConnection,
        patientID,
        newStatus
    );
}

void Database::getPatientBasicInformation(const int patientID)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::getPatientBasicInformation,
        Qt::QueuedConnection,
        patientID
    );
}

void Database::updatePatientBasicInformation(const int patientID, const QString &newFirstName, const QString &newLastName, int newBirthYear, const QString &newPhoneNumber, const QString &newEmail, const QString &newGender, const QString &newMaritalStatus)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::updatePatientBasicInformation,
        Qt::QueuedConnection,
        patientID,
        newFirstName,
        newLastName,
        newBirthYear,
        newPhoneNumber,
        newEmail,
        newGender,
        newMaritalStatus
    );
}

void Database::getPatientVisitInformation(const int patientID)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::getPatientVisitInformation,
        Qt::QueuedConnection,
        patientID
    );
}

void Database::updatePatientVisitInformation(const int patientID, const int newNumberOfPreviousVisits, const QString &newFirstVisitDate, const QString &newRecentVisitDate, const QString &newExpectedVisitDate)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::updatePatientVisitInformation,
        Qt::QueuedConnection,
        patientID,
        newNumberOfPreviousVisits,
        newFirstVisitDate,
        newRecentVisitDate,
        newExpectedVisitDate
    );
}

void Database::getPatientPaymentInformation(const int patientID)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::getPatientPaymentInformation,
        Qt::QueuedConnection,
        patientID
    );
}

void Database::updatePatientPaymentInformation(const int patientID, const double newServicePrice, const double newPaidPrice)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::updatePatientPaymentInformation,
        Qt::QueuedConnection,
        patientID,
        newServicePrice,
        newPaidPrice
    );
}

void Database::getDiagnosesList()
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::getDiagnosesList,
        Qt::QueuedConnection
    );
}

void Database::insertPatientDiagnosis(const int patientID, const int diagnosisID)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::insertPatientDiagnosis,
        Qt::QueuedConnection,
        patientID,
        diagnosisID
    );
}

void Database::getPatientDiagnoses(const int patientID)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::getPatientDiagnoses,
        Qt::QueuedConnection,
        patientID
    );
}

void Database::removePatientDiagnosis(const int patientID, const int diagnosisID)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::removePatientDiagnosis,
        Qt::QueuedConnection,
        patientID,
        diagnosisID
    );
}

void Database::getPatientDiagnosesNote(const int patientID)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::getPatientDiagnosesNote,
        Qt::QueuedConnection,
        patientID
    );
}

void Database::updatePatientDiagnosesNote(const int patientID, const QString &newNote)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::updatePatientDiagnosesNote,
        Qt::QueuedConnection,
        patientID,
        newNote
    );
}

void Database::getTreatmentsList()
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::getTreatmentsList,
        Qt::QueuedConnection
    );
}

void Database::insertPatientTreatment(const int patientID, const int treatmentID)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::insertPatientTreatment,
        Qt::QueuedConnection,
        patientID,
        treatmentID
    );
}

void Database::getPatientTreatments(const int patientID)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::getPatientTreatments,
        Qt::QueuedConnection,
        patientID
    );
}

void Database::removePatientTreatment(const int patientID, const int treatmentID)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::removePatientTreatment,
        Qt::QueuedConnection,
        patientID,
        treatmentID
    );
}

void Database::getPatientTreatmentsNote(const int patientID)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::getPatientTreatmentsNote,
        Qt::QueuedConnection,
        patientID
    );
}

void Database::updatePatientTreatmentsNote(const int patientID, const QString &newNote)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::updatePatientTreatmentsNote,
        Qt::QueuedConnection,
        patientID,
        newNote
    );
}

void Database::getProceduresList()
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::getProceduresList,
        Qt::QueuedConnection
    );
}

void Database::insertPatientProcedure(const int patientID, const int procedureID)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::insertPatientProcedure,
        Qt::QueuedConnection,
        patientID,
        procedureID
    );
}

void Database::getPatientProcedures(const int patientID)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::getPatientProcedures,
        Qt::QueuedConnection,
        patientID
    );
}

void Database::removePatientProcedure(const int patientID, const int procedureID)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::removePatientProcedure,
        Qt::QueuedConnection,
        patientID,
        procedureID
    );
}

void Database::updatePatientProcedureFee(const int patientID, const int procedureID, const double newFee)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::updatePatientProcedureFee,
        Qt::QueuedConnection,
        patientID,
        procedureID,
        newFee
    );
}

void Database::getPatientProceduresNote(const int patientID)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::getPatientProceduresNote,
        Qt::QueuedConnection,
        patientID
    );
}

void Database::updatePatientProceduresNote(const int patientID, const QString &newNote)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::updatePatientProceduresNote,
        Qt::QueuedConnection,
        patientID,
        newNote
    );
}

void Database::getConsultantsList()
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::getConsultantsList,
        Qt::QueuedConnection
    );
}

void Database::insertPatientConsultation(const int patientID, const int consultantID)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::insertPatientConsultation,
        Qt::QueuedConnection,
        patientID,
        consultantID
    );
}

void Database::getPatientConsultations(const int patientID)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::getPatientConsultations,
        Qt::QueuedConnection,
        patientID
    );
}

void Database::removePatientConsultation(const int consultationID)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::removePatientConsultation,
        Qt::QueuedConnection,
        consultationID
    );
}

void Database::updatePatientConsultationDateAndOutcome(const int consultationID, const QString &date, const QString &outcome)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::updatePatientConsultationDateAndOutcome,
        Qt::QueuedConnection,
        consultationID,
        date,
        outcome
    );
}

void Database::getLabsList()
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::getLabsList,
        Qt::QueuedConnection
    );
}

void Database::insertPatientLabTest(const int patientID, const int labID)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::insertPatientLabTest,
        Qt::QueuedConnection,
        patientID,
        labID
    );
}

void Database::removePatientLabTest(const int labTestID)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::removePatientLabTest,
        Qt::QueuedConnection,
        labTestID
    );
}

void Database::getPatientLabTests(const int patientID)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::getPatientLabTests,
        Qt::QueuedConnection,
        patientID
    );
}

void Database::updatePatientLabTest(const LabTest labTest)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::updatePatientLabTest,
        Qt::QueuedConnection,
        labTest
    );
}

void Database::getPatientImages(const int patientID)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::getPatientImages,
        Qt::QueuedConnection,
        patientID
    );
}

void Database::insertPatientImage(const int patientID, const QString &name, const QByteArray &data)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::insertPatientImage,
        Qt::QueuedConnection,
        patientID,
        name,
        data
    );
}

void Database::removePatientImage(const int patientID, const QString &name)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::removePatientImage,
        Qt::QueuedConnection,
        patientID,
        name
    );
}

void Database::updatePatientImageName(const int patientID, const QString &name, const QString &newName)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::updatePatientImageName,
        Qt::QueuedConnection,
        patientID,
        name,
        newName
    );
}

void Database::updatePatientDeletionStatus(const int patientID, const bool newStatus)
{
    QMetaObject::invokeMethod(
        m_DatabaseWorker,
        &DatabaseWorker::updatePatientDeletionStatus,
        Qt::QueuedConnection,
        patientID,
        newStatus
    );
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PRIVATE Methods
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC Getters
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]
