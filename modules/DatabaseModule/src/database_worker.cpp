#include <QDebug>
#include "date.hpp"
#include "database_worker.hpp"

// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

DatabaseWorker::DatabaseWorker(QObject *parent, const QString &name)
    : QObject{parent}
    , c_ConnectionName("DermaBase Connection")
{
    this->setObjectName(name);

#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "None";
    qDebug() << "Log Output :" << "List of SQL drivers: " << QSqlDatabase::drivers().join(", ");
#endif
}

DatabaseWorker::~DatabaseWorker()
{
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

void DatabaseWorker::establishConnection(const QString &ipAddress, int port, const QString &schema, const QString &username, const QString &password)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "IP address :" << ipAddress << "\n"
             << "Port       :" << port      << "\n"
             << "Schema     :" << schema    << "\n"
             << "Username   :" << username  << "\n"
             << "Password   :" << password;
#endif

    emit startedConnecting();

    QSqlDatabase sqlDatabase;

    if (QSqlDatabase::contains(c_ConnectionName))
    {
        sqlDatabase = QSqlDatabase::database(c_ConnectionName, false);
    }

    else
    {
        sqlDatabase = QSqlDatabase::addDatabase("QMYSQL", c_ConnectionName);
    }

    // If connection is open, then close it first:
    if(sqlDatabase.isOpen())
    {
        sqlDatabase.close();
    }

    sqlDatabase.setHostName(ipAddress);
    sqlDatabase.setPort(port);
    sqlDatabase.setDatabaseName(schema);
    sqlDatabase.setUserName(username);
    sqlDatabase.setPassword(password);

    // Now we try to open it:
    if (!sqlDatabase.open())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << sqlDatabase.lastError().text();
#endif

        emit finishedConnecting(-2, "اتصال برقرار نشد: " + sqlDatabase.lastError().text());

        return;
    }

#ifdef QT_DEBUG
    QSqlDriver *driver = QSqlDatabase::database(c_ConnectionName, false).driver();

    qDebug() << "Driver features:";
    qDebug() << "  Transactions:           " << driver->hasFeature(QSqlDriver::Transactions);
    qDebug() << "  QuerySize:              " << driver->hasFeature(QSqlDriver::QuerySize);
    qDebug() << "  BLOB:                   " << driver->hasFeature(QSqlDriver::BLOB);
    qDebug() << "  Unicode:                " << driver->hasFeature(QSqlDriver::Unicode);
    qDebug() << "  PreparedQueries:        " << driver->hasFeature(QSqlDriver::PreparedQueries);
    qDebug() << "  NamedPlaceholders:      " << driver->hasFeature(QSqlDriver::NamedPlaceholders);
    qDebug() << "  PositionalPlaceholders: " << driver->hasFeature(QSqlDriver::PositionalPlaceholders);
    qDebug() << "  LastInsertId:           " << driver->hasFeature(QSqlDriver::LastInsertId);
    qDebug() << "  BatchOperations:        " << driver->hasFeature(QSqlDriver::BatchOperations);
    qDebug() << "  SimpleLocking:          " << driver->hasFeature(QSqlDriver::SimpleLocking);
    qDebug() << "  LowPrecisionNumbers:    " << driver->hasFeature(QSqlDriver::LowPrecisionNumbers);
    qDebug() << "  EventNotifications:     " << driver->hasFeature(QSqlDriver::EventNotifications);
    qDebug() << "  FinishQuery:            " << driver->hasFeature(QSqlDriver::FinishQuery);
    qDebug() << "  MultipleResultSets:     " << driver->hasFeature(QSqlDriver::MultipleResultSets);
    qDebug() << "  CancelQuery:            " << driver->hasFeature(QSqlDriver::CancelQuery);
#endif

    emit finishedConnecting(1, "اتصال برقرار شد");

    return;
}

void DatabaseWorker::cutConnection()
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "None";
#endif

    if(!QSqlDatabase::contains(c_ConnectionName))
    {
        QSqlDatabase::database(c_ConnectionName, false).close();
        QSqlDatabase::removeDatabase(c_ConnectionName);
    }
}

void DatabaseWorker::createPatient(const QString &firstName, const QString &lastName, int birthYear, const QString &phoneNumber, const QString &email, const QString &gender, const QString &maritalStatus)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :"     << "\n"
             << "First name     :" << firstName   << "\n"
             << "Last name      :" << lastName    << "\n"
             << "Phone number   :" << phoneNumber << "\n"
             << "Email          :" << email       << "\n"
             << "Birth year     :" << birthYear   << "\n"
             << "Gender         :" << gender      << "\n"
             << "Marital status :" << maritalStatus;
#endif

    emit startedCreatingPatient();

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedCreatingPatient(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

    QString queryString = R"(
        INSERT IGNORE INTO patients (first_name, last_name, birth_year, phone_number, email, gender, marital_status)

        VALUES (:first_name, :last_name, :birth_year, :phone_number, :email, :gender, :marital_status);
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":first_name", firstName);
    query.bindValue(":last_name", lastName);
    query.bindValue(":birth_year", birthYear);
    query.bindValue(":phone_number", phoneNumber);
    query.bindValue(":email", email);
    query.bindValue(":gender", gender);
    query.bindValue(":marital_status", maritalStatus);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedCreatingPatient(-2, "فرآیند ایجاد بیمار ناموفق بود: " + query.lastError().text());

        return;
    }

    if (query.numRowsAffected() == 0)
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "The patient record existed and was not created!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedCreatingPatient(-1, "پرونده بیمار وجود داشت و درج نشد");

        return;
    }

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedCreatingPatient(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "New patient record created!";
#endif

    emit finishedCreatingPatient(1, "پرونده جدید با موفقیت درج شد");

    return;
}

void DatabaseWorker::findPatient(const int patientID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID :" << patientID;
#endif

    emit startedFinding();

    std::vector<SearchResult> data;

    QString queryString = R"(
        SELECT patient_id, first_name, last_name, birth_year, phone_number, email, gender, marital_status FROM patients

        WHERE patient_id = :patient_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        emit finishedFinding(-2, "فرآیند جستجو ناموفق بود: " + query.lastError().text(), data);

        return;
    }

    if (query.size() == 0)
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Search returned no results.";
#endif

        emit finishedFinding(-1, "فرآیند جستجو نتیجه‌ای نداشت", data);

        return;
    }

    data.reserve(query.size());

    while (query.next())
    {
        data.emplace_back(
            query.value("patient_id").toInt(),
            query.value("first_name").toString(),
            query.value("last_name").toString(),
            query.value("birth_year").toInt(),
            query.value("phone_number").toString(),
            query.value("email").toString(),
            query.value("gender").toString(),
            query.value("marital_status").toString()
        );
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Search succeeded!";
#endif

    emit finishedFinding(1, "فرآیند جستجو موفقیت‌آمیز بود", data);

    return;
}

void DatabaseWorker::findPatients(int mask, const QString &firstName, const QString &lastName, int birthYearStart, int birthYearEnd, const QString &phoneNumber, const QString &gender, const QString &maritalStatus)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "First name       :" << firstName      << "\n"
             << "Last name        :" << lastName       << "\n"
             << "Birth year start :" << birthYearStart << "\n"
             << "Birth year end   :" << birthYearEnd   << "\n"
             << "Phone number     :" << phoneNumber    << "\n"
             << "Gender           :" << gender         << "\n"
             << "Marital status   :" << maritalStatus;
#endif

    emit startedFinding();

    std::vector<SearchResult> data;

    QStringList where;

    // bit 0 = First name
    if (mask & (1 << 0))
    {
        where << "first_name LIKE :first_name";
    }

    // bit 1 = Last name
    if (mask & (1 << 1))
    {
        where << "last_name LIKE :last_name";
    }

    // bit 2 = Birth year start
    if (mask & (1 << 2))
    {
        where << "birth_year >= :birth_year_start";
    }

    // bit 3 = Birth year end
    if (mask & (1 << 3))
    {
        where << "birth_year <= :birth_year_end";
    }

    // bit 4 = Phone number
    if (mask & (1 << 4))
    {
        where << "phone_number LIKE :phone_number";
    }

    // bit 5 = Gender
    if (mask & (1 << 5))
    {
        where << "gender = :gender";
    }

    // bit 6 = Marital status
    if (mask & (1 << 6))
    {
        where << "marital_status = :marital_status";
    }

    QString queryString = R"(
        SELECT patient_id, first_name, last_name, birth_year, phone_number, email, gender, marital_status FROM patients
    )";

    // Construct final SQL
    if (!where.isEmpty())
    {
        queryString += " WHERE " + where.join(" AND ");
    }

    queryString += ";";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    // bit 0 = First name
    if (mask & (1 << 0))
    {
        query.bindValue(":first_name", firstName + "%");
    }

    // bit 1 = Last name
    if (mask & (1 << 1))
    {
        query.bindValue(":last_name", lastName + "%");
    }

    // bit 2 = Birth year start
    if (mask & (1 << 2))
    {
        query.bindValue(":birth_year_start", birthYearStart);
    }

    // bit 3 = Birth year end
    if (mask & (1 << 3))
    {
        query.bindValue(":birth_year_end", birthYearEnd);
    }

    // bit 4 = Phone number
    if (mask & (1 << 4))
    {
        query.bindValue(":phone_number", phoneNumber + "%");
    }

    // bit 5 = Gender
    if (mask & (1 << 5))
    {
        query.bindValue(":gender", gender);
    }

    // bit 6 = Marital status
    if (mask & (1 << 6))
    {
        query.bindValue(":marital_status", maritalStatus);
    }

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        emit finishedFinding(-2, "فرآیند جستجو ناموفق بود: " + query.lastError().text(), data);

        return;
    }

    if (query.size() == 0)
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Search returned no results.";
#endif

        emit finishedFinding(-1, "فرآیند جستجو نتیجه‌ای نداشت", data);

        return;
    }

    data.reserve(query.size());

    while (query.next())
    {
        data.emplace_back(
            query.value("patient_id").toInt(),
            query.value("first_name").toString(),
            query.value("last_name").toString(),
            query.value("birth_year").toInt(),
            query.value("phone_number").toString(),
            query.value("email").toString(),
            query.value("gender").toString(),
            query.value("marital_status").toString()
        );
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Search succeeded!";
#endif

    emit finishedFinding(1, "فرآیند جستجو موفقیت‌آمیز بود", data);

    return;
}

void DatabaseWorker::findFirstPatients(const int count)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Count :" << count;
#endif

    emit startedFinding();

    std::vector<SearchResult> data;

    QString queryString = R"(
        SELECT patient_id, first_name, last_name, birth_year, phone_number, email, gender, marital_status FROM patients

        ORDER BY patient_id ASC LIMIT :count;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":count", count);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        emit finishedFinding(-2, "فرآیند جستجو ناموفق بود: " + query.lastError().text(), data);

        return;
    }

    if (query.size() == 0)
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Search returned no results.";
#endif

        emit finishedFinding(-1, "فرآیند جستجو نتیجه‌ای نداشت", data);

        return;
    }

    data.reserve(query.size());

    while (query.next())
    {
        data.emplace_back(
            query.value("patient_id").toInt(),
            query.value("first_name").toString(),
            query.value("last_name").toString(),
            query.value("birth_year").toInt(),
            query.value("phone_number").toString(),
            query.value("email").toString(),
            query.value("gender").toString(),
            query.value("marital_status").toString()
        );
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Search succeeded!";
#endif

    emit finishedFinding(1, "فرآیند جستجو موفقیت‌آمیز بود", data);

    return;
}

void DatabaseWorker::findLastPatients(const int count)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Count :" << count;
#endif

    emit startedFinding();

    std::vector<SearchResult> data;

    QString queryString = R"(
        SELECT patient_id, first_name, last_name, birth_year, phone_number, email, gender, marital_status FROM patients

        ORDER BY patient_id DESC LIMIT :count;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":count", count);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        emit finishedFinding(-2, "فرآیند جستجو ناموفق بود: " + query.lastError().text(), data);

        return;
    }

    if (query.size() == 0)
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Search returned no results.";
#endif

        emit finishedFinding(-1, "فرآیند جستجو نتیجه‌ای نداشت", data);

        return;
    }

    data.reserve(query.size());

    while (query.next())
    {
        data.emplace_back(
            query.value("patient_id").toInt(),
            query.value("first_name").toString(),
            query.value("last_name").toString(),
            query.value("birth_year").toInt(),
            query.value("phone_number").toString(),
            query.value("email").toString(),
            query.value("gender").toString(),
            query.value("marital_status").toString()
        );
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Search operation succeeded!";
#endif

    emit finishedFinding(1, "فرآیند جستجو موفقیت‌آمیز بود", data);

    return;
}

void DatabaseWorker::createStarredPatient(const int patientID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID :" << patientID;
#endif

    emit startedCreatingStarredPatient();

    StarredPatient starredPatient;

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedCreatingStarredPatient(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text(), starredPatient);

        return;
    }

    QString queryString = R"(
        INSERT IGNORE INTO starred_patients (patient_id) VALUES (:patient_id);
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedCreatingStarredPatient(-2, "فرآیند ستاره دار کردن ناموفق بود: " + query.lastError().text(), starredPatient);

        return;
    }

    if (query.numRowsAffected() == 0)
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "The starred patient record existed and was not created!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedCreatingStarredPatient(-1, "این پرونده بیمار قبلاً ستاره‌دار شده بود", starredPatient);

        return;
    }

    int id = query.lastInsertId().toInt();

    query.clear();

    queryString = R"(
        SELECT patients.patient_id, patients.first_name, patients.last_name, patients.birth_year, patients.phone_number, patients.email, patients.gender, patients.marital_status, starred_patients.has_visited FROM patients

        INNER JOIN starred_patients ON patients.patient_id = starred_patients.patient_id

        WHERE patients.patient_id = :patient_id;
    )";

    query.prepare(queryString);

    query.bindValue(":patient_id", id);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        query.clear();

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedCreatingStarredPatient(-2, "فرآیند ستاره دار کردن ناموفق بود: " + query.lastError().text(), starredPatient);

        return;
    }

    while (query.next())
    {
        starredPatient.patientID = query.value("patients.patient_id").toInt();
        starredPatient.firstName = query.value("patients.first_name").toString();
        starredPatient.lastName = query.value("patients.last_name").toString();
        starredPatient.birthYear = query.value("patients.birth_year").toInt();
        starredPatient.phoneNumber = query.value("patients.phone_number").toString();
        starredPatient.email = query.value("patients.email").toString();
        starredPatient.gender = query.value("patients.gender").toString();
        starredPatient.maritalStatus = query.value("patients.marital_status").toString();
        starredPatient.gender = query.value("patients.gender").toString();
        starredPatient.hasVisited = query.value("starred_patients.has_visited").toBool();
    }

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        query.clear();

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedCreatingStarredPatient(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text(), starredPatient);

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Starring succeeded!";
#endif

    emit finishedCreatingStarredPatient(1, "بیمار با موفقیت ستاره دار شد", starredPatient);

    return;
}

void DatabaseWorker::getAllStarredPatients()
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "None";
#endif

    emit startedGettingAllStarredPatients();

    std::vector<StarredPatient> data;

    QString queryString = R"(
        SELECT patients.patient_id, patients.first_name, patients.last_name, patients.birth_year, patients.phone_number, patients.email, patients.gender, patients.marital_status, starred_patients.has_visited FROM patients

        INNER JOIN starred_patients ON patients.patient_id = starred_patients.patient_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        emit finishedGettingAllStarredPatients(-2, "فرآیند گرفتن بیماران ستاره دار ناموفق بود: " + query.lastError().text(), data);

        return;
    }

    if (query.size() == 0)
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Getting starred patients returned no results.";
#endif

        emit finishedGettingAllStarredPatients(-1, "فرآیند گرفتن بیماران ستاره دار هیچ نتیجه ای برنگرداند", data);

        return;
    }

    data.reserve(query.size());

    while (query.next())
    {
        data.emplace_back(
            query.value("patients.patient_id").toInt(),
            query.value("patients.first_name").toString(),
            query.value("patients.last_name").toString(),
            query.value("patients.birth_year").toInt(),
            query.value("patients.phone_number").toString(),
            query.value("patients.email").toString(),
            query.value("patients.gender").toString(),
            query.value("patients.marital_status").toString(),
            query.value("starred_patients.has_visited").toBool()
        );
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Getting starred patients succeeded!";
#endif

    emit finishedGettingAllStarredPatients(1, "فرآیند گرفتن بیماران ستاره دار موفقیت آمیز بود", data);

    return;
}

void DatabaseWorker::removeAllStarredPatients()
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "None";
#endif

    emit startedRemovingAllStarredPatients();

    QString queryString = R"(
        TRUNCATE TABLE starred_patients;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        emit finishedRemovingAllStarredPatients(-2, "فرآیند حذف بیماران ستاره دار ناموفق بود: " + query.lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Remove all starred patients succeeded!";
#endif

    emit finishedRemovingAllStarredPatients(1, "فرآیند حذف بیماران ستاره دار موفقیت آمیز بود");

    return;
}

void DatabaseWorker::updateVisitStatusOfStarredPatient(const int patientID, const bool newStatus)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID :" << patientID << "\n"
             << "New status :" << newStatus;
#endif

    emit startedUpdatingStarredPatientVisitStatus();

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedUpdatingStarredPatientVisitStatus(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

    QString queryString = R"(
        UPDATE starred_patients

        SET has_visited = :has_visited

        WHERE patient_id = :patient_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":has_visited", newStatus);
    query.bindValue(":patient_id", patientID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingStarredPatientVisitStatus(-2, "فرآیند تغییر وضعیت ویزیت ناموفق بود: " + query.lastError().text());

        return;
    }

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingStarredPatientVisitStatus(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Update starred patient visit status succeeded!";
#endif

    emit finishedUpdatingStarredPatientVisitStatus(1, "فرآیند تغییر وضعیت ویزیت موفقیت آمیز بود");

    return;
}

void DatabaseWorker::getPatientBasicInformation(const int patientID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID :" << patientID;
#endif

    emit startedGettingPatientBasicInformation();

    QString firstName = "";
    QString lastName = "";
    int birthYear = 0;
    QString phoneNumber = "";
    QString email = "";
    QString gender = "";
    QString maritalStatus = "";

    QString queryString = R"(
        SELECT first_name, last_name, birth_year, phone_number, email, gender, marital_status FROM patients

        WHERE patient_id = :patient_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        emit finishedGettingPatientBasicInformation(
            -2,
            "فرآیند دریافت اطلاعات اولیه بیمار ناموفق بود: " + query.lastError().text(),
            firstName,
            lastName,
            birthYear,
            phoneNumber,
            email,
            gender,
            maritalStatus
        );

        return;
    }

    if (query.size() == 0)
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Get patient basic information returned no results.";
#endif

        emit finishedGettingPatientBasicInformation(
            -1,
            "فرآیند دریافت اطلاعات اولیه بیمار هیچ نتیجه‌ای برنگرداند",
            firstName,
            lastName,
            birthYear,
            phoneNumber,
            email,
            gender,
            maritalStatus
        );

        return;
    }

    while (query.next())
    {
        firstName = query.value("first_name").toString();
        lastName = query.value("last_name").toString();
        birthYear = query.value("birth_year").toInt();
        phoneNumber = query.value("phone_number").toString();
        email = query.value("email").toString();
        gender = query.value("gender").toString();
        maritalStatus = query.value("marital_status").toString();
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Get patient basic information succeeded!";
#endif

    emit finishedGettingPatientBasicInformation(
        1,
        "فرآیند دریافت اطلاعات اولیه بیمار موفقیت آمیز بود",
        firstName,
        lastName,
        birthYear,
        phoneNumber,
        email,
        gender,
        maritalStatus
    );

    return;
}

void DatabaseWorker::updatePatientBasicInformation(const int patientID, const QString &newFirstName, const QString &newLastName, int newBirthYear, const QString &newPhoneNumber, const QString &newEmail, const QString &newGender, const QString &newMaritalStatus)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID         :" << patientID        << "\n"
             << "New first name     :" << newFirstName     << "\n"
             << "New last name      :" << newLastName      << "\n"
             << "New birth year     :" << newBirthYear     << "\n"
             << "New phone number   :" << newPhoneNumber   << "\n"
             << "New email          :" << newEmail         << "\n"
             << "New gender         :" << newGender        << "\n"
             << "New marital status :" << newMaritalStatus << "\n";
#endif

    emit startedUpdatingPatientBasicInformation();

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedUpdatingPatientBasicInformation(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

    QString queryString = R"(
        UPDATE patients SET first_name = :first_name, last_name = :last_name, birth_year = :birth_year, phone_number = :phone_number, email = :email, gender = :gender, marital_status = :marital_status

        WHERE patient_id = :patient_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);
    query.bindValue(":first_name", newFirstName);
    query.bindValue(":last_name", newLastName);
    query.bindValue(":birth_year", newBirthYear);
    query.bindValue(":phone_number", newPhoneNumber);
    query.bindValue(":email", newEmail);
    query.bindValue(":gender", newGender);
    query.bindValue(":marital_status", newMaritalStatus);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingPatientBasicInformation(-2, "فرآیند آپدیت اطلاعات اولیه بیمار ناموفق بود: " + query.lastError().text());

        return;
    }

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingPatientBasicInformation(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Patient basic information update applied!";
#endif

    emit finishedUpdatingPatientBasicInformation(1, "فرآیند آپدیت اطلاعات اولیه بیمار موفقیت آمیز بود");

    return;
}

void DatabaseWorker::getPatientVisitInformation(const int patientID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID :" << patientID;
#endif

    emit startedGettingPatientVisitInformation();

    int numberOfPreviousVisits = 0;
    QString firstVisitDate = "";
    QString recentVisitDate = "";
    QString expectedVisitDate = "";

    QString queryString = R"(
        SELECT number_of_previous_visits, first_visit_date, recent_visit_date, expected_visit_date FROM patient_visit_info

        WHERE patient_id = :patient_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        emit finishedGettingPatientVisitInformation(
            -2,
            "فرآیند دریافت اطلاعات ویزیت بیمار ناموفق بود: " + query.lastError().text(),
            numberOfPreviousVisits,
            firstVisitDate,
            recentVisitDate,
            expectedVisitDate
        );

        return;
    }

    while (query.next())
    {
        numberOfPreviousVisits = query.value("number_of_previous_visits").toInt();

        // NOTE (SAVIZ): At the moment, this is the best solution I could find for transforming dates between 'Gregorian' and 'Jalili'.
        QDate firstVisitGregorianDate = query.value("first_visit_date").toDate();

        if(!firstVisitGregorianDate.isNull())
        {
            QString firstVisitJaliliDateString = Date::cppInstance()->gregorianToJalali(firstVisitGregorianDate);

            firstVisitDate = firstVisitJaliliDateString;
        }

        QDate recentVisitGregorianDate = query.value("recent_visit_date").toDate();

        if(!recentVisitGregorianDate.isNull())
        {
            QString recentVisitJaliliDateString = Date::cppInstance()->gregorianToJalali(recentVisitGregorianDate);

            recentVisitDate = recentVisitJaliliDateString;
        }

        QDate expectedVisitGregorianDate = query.value("expected_visit_date").toDate();

        if(!expectedVisitGregorianDate.isNull())
        {
            QString expectedVisitJaliliDateString = Date::cppInstance()->gregorianToJalali(expectedVisitGregorianDate);

            expectedVisitDate = expectedVisitJaliliDateString;
        }
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Get patient visit information operation succeeded!";
#endif

    emit finishedGettingPatientVisitInformation(
        1,
        "فرآیند دریافت اطلاعات ویزیت بیمار با موفقیت موفقیت آمیز بود",
        numberOfPreviousVisits,
        firstVisitDate,
        recentVisitDate,
        expectedVisitDate
    );

    return;
}

void DatabaseWorker::updatePatientVisitInformation(const int patientID, const int newNumberOfPreviousVisits, const QString &newFirstVisitDate, const QString &newRecentVisitDate, const QString &newExpectedVisitDate)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID                    :" << patientID                 << "\n"
             << "New number of previous visits :" << newNumberOfPreviousVisits << "\n"
             << "New first visit date          :" << newFirstVisitDate         << "\n"
             << "New recent visit date         :" << newRecentVisitDate        << "\n"
             << "New expected visit date       :" << newExpectedVisitDate      << "\n";
#endif

    emit startedUpdatingPatientVisitInformation();

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedUpdatingPatientBasicInformation(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

    QString queryString = R"(
        UPDATE patient_visit_info SET number_of_previous_visits = :number_of_previous_visits, first_visit_date = :first_visit_date, recent_visit_date = :recent_visit_date, expected_visit_date = :expected_visit_date

        WHERE patient_id = :patient_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);

    // NOTE (SAVIZ): We need to convert dates before attempting to bind.

    QCalendar calendarJalali(QCalendar::System::Jalali);

    QDate firstVisitGregorianDate;
    firstVisitGregorianDate = QDate::fromString(newFirstVisitDate, "yyyy-MM-dd", calendarJalali);

    QDate recentVisitGregorianDate;
    recentVisitGregorianDate = QDate::fromString(newRecentVisitDate, "yyyy-MM-dd", calendarJalali);

    QDate expectedVisitGregorianDate;
    expectedVisitGregorianDate = QDate::fromString(newExpectedVisitDate, "yyyy-MM-dd", calendarJalali);

    // TODO (SAVIZ): I am not sure why I make these checks, since I have regex enabled and there is no way for the date format to fail due to the correctness of the format. But, still I will keep this.
    if(firstVisitGregorianDate.isNull() || !firstVisitGregorianDate.isValid())
    {
        query.bindValue(":first_visit_date", QVariant(QMetaType::fromType<QDate>()));
    }

    else
    {
        query.bindValue(":first_visit_date", firstVisitGregorianDate);
    }

    if(recentVisitGregorianDate.isNull() || !recentVisitGregorianDate.isValid())
    {
        query.bindValue(":recent_visit_date", QVariant(QMetaType::fromType<QDate>()));
    }

    else
    {
        query.bindValue(":recent_visit_date", recentVisitGregorianDate);
    }

    if(expectedVisitGregorianDate.isNull() || !expectedVisitGregorianDate.isValid())
    {
        query.bindValue(":expected_visit_date", QVariant(QMetaType::fromType<QDate>()));
    }

    else
    {
        query.bindValue(":expected_visit_date", expectedVisitGregorianDate);
    }


    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingPatientVisitInformation(-2, "فرآیند آپدیت اطلاعات ویزیت بیمار ناموفق بود: " + query.lastError().text());

        return;
    }

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingPatientVisitInformation(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Updates applied!";
#endif

    emit finishedUpdatingPatientVisitInformation(1, "فرآیند آپدیت اطلاعات ویزیت بیمار موفقیت آمیز بود");

    return;
}

void DatabaseWorker::getPatientPaymentInformation(const int patientID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID :" << patientID;
#endif

    emit startedGettingPatientPaymentInformation();

    double servicePrice = 0.0;
    double paidPrice = 0.0;

    QString queryString = R"(
        SELECT service_price, paid_price FROM patient_payment_info

        WHERE patient_id = :patient_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        emit finishedGettingPatientPaymentInformation(
            -2,
            "فرآیند گرفتن اطلاعات پرداخت بیمار ناموفق بود: " + query.lastError().text(),
            servicePrice,
            paidPrice
        );

        return;
    }

    while (query.next())
    {
        servicePrice = query.value("service_price").toDouble();
        paidPrice = query.value("paid_price").toDouble();
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Get patient payment information succeeded!";
#endif

    emit finishedGettingPatientPaymentInformation(
        1,
        "فرآیند گرفتن اطلاعات پرداخت بیمار موفقیت آمیز بود",
        servicePrice,
        paidPrice
    );

    return;
}

void DatabaseWorker::updatePatientPaymentInformation(const int patientID, const double newServicePrice, const double newPaidPrice)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID        :" << patientID       << "\n"
             << "New service price :" << newServicePrice << "\n"
             << "New paid price    :" << newPaidPrice    << "\n";
#endif

    emit startedUpdatingPatientPaymentInformation();

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedUpdatingPatientPaymentInformation(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

    QString queryString = R"(
        UPDATE patient_payment_info SET service_price = :service_price, paid_price = :paid_price

        WHERE patient_id = :patient_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);
    query.bindValue(":service_price", newServicePrice);
    query.bindValue(":paid_price", newPaidPrice);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingPatientPaymentInformation(-2, "فرآیند آپدیت اطلاعات پرداخت بیمار ناموفق بود: " + query.lastError().text());

        return;
    }

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingPatientPaymentInformation(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Updates applied!";
#endif

    emit finishedUpdatingPatientPaymentInformation(1, "فرآیند آپدیت اطلاعات پرداخت بیمار موفقیت آمیز بود");

    return;
}

void DatabaseWorker::getDiagnosesList()
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "None";
#endif

    emit startedGettingDiagnosesList();

    std::vector<Diagnosis> data;

    QString queryString = R"(
        SELECT diagnosis_id, name FROM diagnoses

        WHERE is_active = TRUE;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        emit finishedGettingDiagnosesList(-2, "فرآیند دریافت لیست تشخیص‌ها ناموفق بود: " + query.lastError().text(), data);

        return;
    }

    // NOTE (SAVIZ): The condition query.size() == 0 should never occur, as the database is prepopulated with the required information.

    data.reserve(query.size());

    while (query.next())
    {
        data.emplace_back(
            query.value("diagnosis_id").toInt(),
            query.value("name").toString()
        );
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Diagnoses list retrieval succeeded!";
#endif

    emit finishedGettingDiagnosesList(1, "فرآیند دریافت لیست تشخیص‌ها موفقیت آمیز بود.", data);

    return;
}

void DatabaseWorker::insertPatientDiagnosis(const int patientID, const int diagnosisID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID   :" << patientID << "\n"
             << "Diagnosis ID :" << diagnosisID;
#endif

    emit startedInsertingPatientDiagnosis();

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedInsertingPatientDiagnosis(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

    QString queryString = R"(
        INSERT IGNORE INTO patient_diagnoses (patient_id, diagnosis_id)

        VALUES (:patient_id, :diagnosis_id);
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);
    query.bindValue(":diagnosis_id", diagnosisID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedInsertingPatientDiagnosis(-2, "فرآیند درج تشخیص ناموفق بود: " + query.lastError().text());

        return;
    }

    if (query.numRowsAffected() == 0)
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "The diagnosis already exists and was not inserted!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedInsertingPatientDiagnosis(-1, "تشخیص وجود داشت و درج نشده بود.");

        return;
    }

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedInsertingPatientDiagnosis(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Diagnosis insertion succeeded!";
#endif

    emit finishedInsertingPatientDiagnosis(1, "فرآیند درج تشخیص موفقیت آمیز بود");

    return;
}

void DatabaseWorker::getPatientDiagnoses(const int patientID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID :" << patientID;
#endif

    emit startedGettingPatientDiagnoses();

    std::vector<Diagnosis> data;

    QString queryString = R"(
        SELECT diagnoses.diagnosis_id, diagnoses.name AS name FROM diagnoses

        INNER JOIN patient_diagnoses ON patient_diagnoses.diagnosis_id = diagnoses.diagnosis_id

        WHERE patient_diagnoses.patient_id = :patient_id
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        emit finishedGettingPatientDiagnoses(-2, "فرآیند دریافت تشخیص‌ها ناموفق بود: " + query.lastError().text(), data);

        return;
    }

    if (query.size() == 0)
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Patient  Diagnoses retrieval returned no results.";
#endif

        emit finishedGettingPatientDiagnoses(-1, "فرآیند هیچ نتیجه‌ای برنگرداند.", data);

        return;
    }

    data.reserve(query.size());

    while (query.next())
    {
        data.emplace_back(
            query.value("diagnosis_id").toInt(),
            query.value("name").toString()
        );
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Patient Diagnoses retrieval succeeded!";
#endif

    emit finishedGettingPatientDiagnoses(1, "فرآیند دریافت تشخیص‌ها موفقیت آمیز بود.", data);

    return;
}

void DatabaseWorker::removePatientDiagnosis(const int patientID, const int diagnosisID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID   :" << patientID << "\n"
             << "Diagnosis ID :" << diagnosisID;
#endif

    emit startedRemovingPatientDiagnosis();

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedRemovingPatientDiagnosis(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

    QString queryString = R"(
        DELETE FROM patient_diagnoses

        WHERE patient_id = :patient_id AND diagnosis_id = :diagnosis_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);
    query.bindValue(":diagnosis_id", diagnosisID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedRemovingPatientDiagnosis(-2, "فرآیند حذف تشخیص بیمار ناموفق بود: " + query.lastError().text());

        return;
    }

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedRemovingPatientDiagnosis(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Diagnosis removal succeeded!";
#endif

    emit finishedRemovingPatientDiagnosis(1, "فرآیند حذف تشخیص بیمار موفقیت آمیز بود");

    return;
}

void DatabaseWorker::getPatientDiagnosesNote(const int patientID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID :" << patientID;
#endif

    emit startedGettingPatientDiagnosesNote();

    QString note;

    QString queryString = R"(
        SELECT note FROM diagnosis_notes

        WHERE patient_id = :patient_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        emit finishedGettingPatientDiagnosesNote(-2, "فرآیند دریافت یادداشت تشخیص ها ناموفق بود: " + query.lastError().text(), note);

        return;
    }

    // NOTE (SAVIZ): The condition query.size() == 0 should never occur, as the database is prepopulated with the required information.

    while (query.next())
    {
        note = query.value("note").toString();
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Diagnoses note retrieval succeeded!";
#endif

    emit finishedGettingPatientDiagnosesNote(1, "فرآیند دریافت یادداشت تشخیص ها موفقیت آمیز بود.", note);

    return;
}

void DatabaseWorker::updatePatientDiagnosesNote(const int patientID, const QString &newNote)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID :" << patientID << "\n"
             << "New note   :" << newNote;
#endif

    emit startedUpdatingPatientDiagnosesNote();

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedUpdatingPatientDiagnosesNote(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

    QString queryString = R"(
        UPDATE diagnosis_notes SET note = :note

        WHERE patient_id = :patient_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);
    query.bindValue(":note", newNote);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingPatientDiagnosesNote(-2, "آپدیت یادداشت تشخیص ها ناموفق بود: " + query.lastError().text());

        return;
    }

    // NOTE (SAVIZ): The condition query.size() == 0 should never occur, as the database is prepopulated with the required information.

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingPatientDiagnosesNote(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Diagnoses note update succeeded!";
#endif

    emit finishedUpdatingPatientDiagnosesNote(1, "آپدیت یادداشت تشخیص ها موفقیت آمیز بود");

    return;
}

void DatabaseWorker::getTreatmentsList()
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "None";
#endif

    emit startedGettingTreatmentsList();

    std::vector<Treatment> data;

    QString queryString = R"(
        SELECT treatment_id, name FROM treatments

        WHERE is_active = TRUE;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        emit finishedGettingTreatmentsList(-2, "فرآیند گرفتن لیست درمان‌ها ناموفق بود: " + query.lastError().text(), data);

        return;
    }

    // NOTE (SAVIZ): The condition query.size() == 0 should never occur, as the database is prepopulated with the required information.

    data.reserve(query.size());

    while (query.next())
    {
        data.emplace_back(
            query.value("treatment_id").toInt(),
            query.value("name").toString()
        );
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Treatments list retrieval succeeded!";
#endif

    emit finishedGettingTreatmentsList(1, "فرآیند گرفتن لیست درمان‌ها موفقیت آمیز بود", data);

    return;
}

void DatabaseWorker::insertPatientTreatment(const int patientID, const int treatmentID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID   :" << patientID << "\n"
             << "Treatment ID :" << treatmentID;
#endif

    emit startedInsertingPatientTreatment();

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedInsertingPatientTreatment(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

    QString queryString = R"(
        INSERT IGNORE INTO patient_treatments (patient_id, treatment_id)

        VALUES (:patient_id, :treatment_id);
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);
    query.bindValue(":treatment_id", treatmentID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedInsertingPatientTreatment(-2, "فرآیند درج درمان ناموفق بود: " + query.lastError().text());

        return;
    }

    if (query.numRowsAffected() == 0)
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "The treatment already exists and was not inserted!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedInsertingPatientTreatment(-1, "درمان وجود داشت و درج نشد");

        return;
    }

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedInsertingPatientTreatment(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Treatment insertion succeeded!";
#endif

    emit finishedInsertingPatientTreatment(1, "فرآیند درج درمان موفقیت آمیز بود");

    return;
}

void DatabaseWorker::getPatientTreatments(const int patientID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID :" << patientID;
#endif

    emit startedGettingPatientTreatments();

    std::vector<Treatment> data;

    QString queryString = R"(
        SELECT treatments.treatment_id, treatments.name AS name FROM treatments

        INNER JOIN patient_treatments ON patient_treatments.treatment_id = treatments.treatment_id

        WHERE patient_treatments.patient_id = :patient_id
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        emit finishedGettingPatientTreatments(-2, "فرآیند گرفتن درمان‌ها ناموفق بود: " + query.lastError().text(), data);

        return;
    }

    if (query.size() == 0)
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Patient treatments retrieval returned no results.";
#endif

        emit finishedGettingPatientTreatments(-1, "فرآیند گرفتن درمان ها هیچ نتیجه‌ای برنگرداند.", data);

        return;
    }

    data.reserve(query.size());

    while (query.next())
    {
        data.emplace_back(
            query.value("treatment_id").toInt(),
            query.value("name").toString()
        );
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Patient treatments retrieval succeeded!";
#endif

    emit finishedGettingPatientTreatments(1, "فرآیند گرفتن درمان‌ها موفقیت آمیز بود.", data);

    return;
}

void DatabaseWorker::removePatientTreatment(const int patientID, const int treatmentID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID   :" << patientID << "\n"
             << "Treatment ID :" << treatmentID;
#endif

    emit startedRemovingPatientTreatment();

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedRemovingPatientTreatment(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

    QString queryString = R"(
        DELETE FROM patient_treatments

        WHERE patient_id = :patient_id AND treatment_id = :treatment_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);
    query.bindValue(":treatment_id", treatmentID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedRemovingPatientTreatment(-2, "فرآیند حذف درمان بیمار ناموفق بود: " + query.lastError().text());

        return;
    }

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedRemovingPatientTreatment(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Patient treatment removal succeeded!";
#endif

    emit finishedRemovingPatientTreatment(1, "فرآیند حذف درمان بیمار موفقیت آمیز بود");

    return;
}

void DatabaseWorker::getPatientTreatmentsNote(const int patientID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID :" << patientID;
#endif

    emit startedGettingPatientTreatmentsNote();

    QString note;

    QString queryString = R"(
        SELECT note FROM treatment_notes

        WHERE patient_id = :patient_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        emit finishedGettingPatientTreatmentsNote(-2, "فرآیند گرفتن یادداشت درمان ها ناموفق بود: " + query.lastError().text(), note);

        return;
    }

    // NOTE (SAVIZ): The condition query.size() == 0 should never occur, as the database is prepopulated with the required information.

    while (query.next())
    {
        note = query.value("note").toString();
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Treatments note retrieval succeeded!";
#endif

    emit finishedGettingPatientTreatmentsNote(1, "فرآیند دریافت یادداشت درمان ها موفقیت آمیز بود", note);

    return;
}

void DatabaseWorker::updatePatientTreatmentsNote(const int patientID, const QString &newNote)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID :" << patientID << "\n"
             << "New note   :" << newNote;
#endif

    emit startedUpdatingPatientTreatmentsNote();

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedUpdatingPatientTreatmentsNote(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

    QString queryString = R"(
        UPDATE treatment_notes SET note = :note

        WHERE patient_id = :patient_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);
    query.bindValue(":note", newNote);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingPatientTreatmentsNote(-2, "آپدیت یادداشت درمان ها ناموفق بود: " + query.lastError().text());

        return;
    }

    // NOTE (SAVIZ): under no circumstances should numRowseffected == 0

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingPatientTreatmentsNote(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Treatments note update succeeded!";
#endif

    emit finishedUpdatingPatientTreatmentsNote(1, "آپدیت یادداشت درمان ها موفقیت آمیز بود");

    return;
}

void DatabaseWorker::getProceduresList()
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "None";
#endif

    emit startedGettingProceduresList();

    std::vector<Procedure> data;

    QString queryString = R"(
        SELECT procedure_id, name FROM procedures

        WHERE is_active = TRUE;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        emit finishedGettingProceduresList(-2, "فرآیند گرفتن لیست پروسیجر ناموفق بود: " + query.lastError().text(), data);

        return;
    }

    // NOTE (SAVIZ): The condition query.size() == 0 should never occur, as the database is prepopulated with the required information.

    data.reserve(query.size());

    while (query.next())
    {
        data.emplace_back(
            query.value("procedure_id").toInt(),
            query.value("name").toString(),
            double(0.000)
        );
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Procedures list retrieval succeeded!";
#endif

    emit finishedGettingProceduresList(1, "فرآیند گرفتن لیست پروسیجر موفقیت آمیز بود", data);

    return;
}

void DatabaseWorker::insertPatientProcedure(const int patientID, const int procedureID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID   :" << patientID << "\n"
             << "Procedure ID :" << procedureID;
#endif

    emit startedInsertingPatientProcedure();

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedInsertingPatientTreatment(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

    QString queryString = R"(
        INSERT IGNORE INTO patient_procedures (patient_id, procedure_id, procedure_fee)

        VALUES (:patient_id, :procedure_id, :procedure_fee);
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);
    query.bindValue(":procedure_id", procedureID);
    query.bindValue(":procedure_fee", double(0.0));

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedInsertingPatientProcedure(-2, "فرآیند درج پروسیجر ناموفق بود: " + query.lastError().text());

        return;
    }

    if (query.numRowsAffected() == 0)
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "The procedure already exists and was not inserted!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedInsertingPatientProcedure(-1, "پروسیجر وجود داشت و درج نشد");

        return;
    }

    // FIXME: Right here you can place a while loop and get the return:

    query.lastInsertId().toInt();

    // Make sure that the query in inactive, or teh commit will fail.
    // Call both finish() and clear() on the selcet query to make sure that it is inactive.


    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedInsertingPatientProcedure(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Procedure insertion succeeded!";
#endif

    emit finishedInsertingPatientProcedure(1, "فرآیند درج پروسیجر موفقیت آمیز بود");

    return;
}

void DatabaseWorker::getPatientProcedures(const int patientID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID :" << patientID;
#endif

    emit startedGettingPatientProcedures();

    std::vector<Procedure> data;

    QString queryString = R"(
        SELECT procedures.procedure_id, procedures.name AS name, patient_procedures.procedure_fee AS fee FROM procedures

        INNER JOIN patient_procedures ON patient_procedures.procedure_id = procedures.procedure_id

        WHERE patient_procedures.patient_id = :patient_id
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        emit finishedGettingPatientProcedures(-2, "فرآیند گرفتن پروسیجر ها ناموفق بود: " + query.lastError().text(), data);

        return;
    }

    if (query.size() == 0)
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Patient procedures retrieval returned no results.";
#endif

        emit finishedGettingPatientProcedures(-1, "فرآیند گرفتن پروسیجر ها هیچ نتیجه‌ای برنگرداند.", data);

        return;
    }

    data.reserve(query.size());

    while (query.next())
    {
        data.emplace_back(
            query.value("procedure_id").toInt(),
            query.value("name").toString(),
            query.value("fee").toDouble()
        );
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Patient procedures retrieval succeeded!";
#endif

    emit finishedGettingPatientProcedures(1, "فرآیند گرفتن پروسیجر ها موفقیت آمیز بود.", data);

    return;
}

void DatabaseWorker::removePatientProcedure(const int patientID, const int procedureID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID   :" << patientID << "\n"
             << "Procedure ID :" << procedureID;
#endif

    emit startedRemovingPatientProcedure();

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedRemovingPatientProcedure(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

    QString queryString = R"(
        DELETE FROM patient_procedures

        WHERE patient_id = :patient_id AND procedure_id = :procedure_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);
    query.bindValue(":procedure_id", procedureID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedRemovingPatientProcedure(-2, "فرآیند حذف پروسیجر بیمار ناموفق بود: " + query.lastError().text());

        return;
    }

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedRemovingPatientProcedure(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Patient procedure removal succeeded!";
#endif

    emit finishedRemovingPatientProcedure(1, "فرآیند حذف پروسیجر بیمار موفقیت آمیز بود");

    return;
}

void DatabaseWorker::updatePatientProcedureFee(const int patientID, const int procedureID, const double newFee)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID   :" << patientID   << "\n"
             << "Procedure ID :" << procedureID << "\n"
             << "New fee      :" << newFee;
#endif

    emit startedUpdatingPatientProcedureFee();

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedUpdatingPatientProcedureFee(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

    QString queryString = R"(
        UPDATE patient_procedures SET procedure_fee = :procedure_fee

        WHERE patient_id = :patient_id AND procedure_id = :procedure_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);
    query.bindValue(":procedure_id", procedureID);
    query.bindValue(":procedure_fee", newFee);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingPatientProcedureFee(-2, "فرآیند آپدیت اطلاعات پروسیجر بیمار ناموفق بود: " + query.lastError().text());

        return;
    }

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingPatientProcedureFee(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Updates applied!";
#endif

    emit finishedUpdatingPatientProcedureFee(1, "فرآیند آپدیت اطلاعات پروسیجر بیمار موفقیت آمیز بود");

    return;
}

void DatabaseWorker::getPatientProceduresNote(const int patientID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID :" << patientID;
#endif

    emit startedGettingPatientProceduresNote();

    QString note;

    QString queryString = R"(
        SELECT note FROM procedure_notes

        WHERE patient_id = :patient_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        emit finishedGettingPatientProceduresNote(-2, "فرآیند گرفتن یادداشت پروسیجر ها ناموفق بود: " + query.lastError().text(), note);

        return;
    }

    // NOTE (SAVIZ): The condition query.size() == 0 should never occur, as the database is prepopulated with the required information.

    while (query.next())
    {
        note = query.value("note").toString();
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Procedures note retrieval succeeded!";
#endif

    emit finishedGettingPatientProceduresNote(1, "فرآیند دریافت یادداشت پروسیجر ها موفقیت آمیز بود", note);

    return;
}

void DatabaseWorker::updatePatientProceduresNote(const int patientID, const QString &newNote)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID :" << patientID << "\n"
             << "New note   :" << newNote;
#endif

    emit startedUpdatingPatientProceduresNote();

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedUpdatingPatientProceduresNote(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

    QString queryString = R"(
        UPDATE procedure_notes SET note = :note

        WHERE patient_id = :patient_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);
    query.bindValue(":note", newNote);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingPatientProceduresNote(-2, "آپدیت یادداشت پروسیجر ها ناموفق بود: " + query.lastError().text());

        return;
    }

    // NOTE (SAVIZ): under no circumstances should numRowseffected == 0

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingPatientProceduresNote(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Procedures note update succeeded!";
#endif

    emit finishedUpdatingPatientProceduresNote(1, "آپدیت یادداشت پروسیجر ها موفقیت آمیز بود");

    return;
}

void DatabaseWorker::getConsultantsList()
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "None";
#endif

    emit startedGettingConsultantsList();

    std::vector<Consultant> data;

    QString queryString = R"(
        SELECT consultant_id, name, specialization FROM consultants

        WHERE is_active = TRUE;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        emit finishedGettingConsultantsList(-2, "فرآیند گرفتن لیست مشاوران ناموفق بود: " + query.lastError().text(), data);

        return;
    }

    // NOTE (SAVIZ): The condition query.size() == 0 should never occur, as the database is prepopulated with the required information.

    data.reserve(query.size());

    while (query.next())
    {
        data.emplace_back(
            query.value("consultant_id").toInt(),
            query.value("name").toString(),
            query.value("specialization").toString()
        );
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Consultants list retrieval succeeded!";
#endif

    emit finishedGettingConsultantsList(1, "فرآیند گرفتن لیست مشاوران موفقیت آمیز بود", data);

    return;
}

void DatabaseWorker::insertPatientConsultation(const int patientID, const int consultantID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID    :" << patientID << "\n"
             << "Consultant ID :" << consultantID;
#endif

    emit startedInsertingPatientConsultation();

    Consultation consultation;

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedInsertingPatientConsultation(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text(), consultation);

        return;
    }

    QString queryString = R"(
        INSERT INTO patient_consultations (patient_id, consultant_id)

        VALUES (:patient_id, :consultant_id);
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);
    query.bindValue(":consultant_id", consultantID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedInsertingPatientConsultation(-2, "فرآیند درج مشاوره ناموفق بود: " + query.lastError().text(), consultation);

        return;
    }

    int id = query.lastInsertId().toInt();

    query.clear();

    queryString = R"(
        SELECT patient_consultations.consultation_id AS consultation_id, patient_consultations.patient_id AS patient_id, consultants.consultant_id AS consultant_id, patient_consultations.consultation_date AS date, patient_consultations.consultation_outcome AS outcome, consultants.name AS name, consultants.specialization AS specialization FROM patient_consultations

        INNER JOIN consultants ON patient_consultations.consultant_id = consultants.consultant_id

        WHERE patient_consultations.consultation_id = :consultation_id
    )";

    query.prepare(queryString);

    query.bindValue(":consultation_id", id);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        query.clear();

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedInsertingPatientConsultation(-2, "فرآیند درج مشاوره ناموفق بود: " + query.lastError().text(), consultation);

        return;
    }

    while (query.next())
    {
        QString date = "";

        QDate outcomeGregorianDate = query.value("date").toDate();

        if(!outcomeGregorianDate.isNull())
        {
            QString outcomeJaliliDateString = Date::cppInstance()->gregorianToJalali(outcomeGregorianDate);

            date = outcomeJaliliDateString;
        }

        consultation.consultationID = query.value("consultation_id").toInt();
        consultation.patientID = query.value("patient_id").toInt();
        consultation.consultantID = query.value("consultant_id").toInt();
        consultation.date = date;
        consultation.outcome = query.value("outcome").toString();
        consultation.name = query.value("name").toString();
        consultation.specialization = query.value("specialization").toString();
    }

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        query.clear();

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedInsertingPatientConsultation(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text(), consultation);

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Consultation insertion succeeded!";
#endif

    emit finishedInsertingPatientConsultation(1, "فرآیند درج مشاوره موفقیت آمیز بود", consultation);

    return;
}

void DatabaseWorker::getPatientConsultations(const int patientID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID :" << patientID;
#endif

    emit startedGettingPatientConsultations();

    std::vector<Consultation> data;

    QString queryString = R"(
        SELECT patient_consultations.consultation_id AS consultation_id, patient_consultations.patient_id AS patient_id, consultants.consultant_id AS consultant_id, patient_consultations.consultation_date AS date, patient_consultations.consultation_outcome AS outcome, consultants.name AS name, consultants.specialization AS specialization FROM patient_consultations

        INNER JOIN consultants ON patient_consultations.consultant_id = consultants.consultant_id

        WHERE patient_consultations.patient_id = :patient_id

        ORDER BY patient_consultations.consultation_date DESC;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        emit finishedGettingPatientConsultations(-2, "فرآیند گرفتن مشاوره ها ناموفق بود: " + query.lastError().text(), data);

        return;
    }

    if (query.size() == 0)
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Patient consultations retrieval returned no results.";
#endif

        emit finishedGettingPatientConsultations(-1, "فرآیند گرفتن مشاوره ها هیچ نتیجه‌ای برنگرداند.", data);

        return;
    }

    data.reserve(query.size());

    while (query.next())
    {
        QString date = "";

        QDate outcomeGregorianDate = query.value("date").toDate();

        if(!outcomeGregorianDate.isNull())
        {
            QString outcomeJaliliDateString = Date::cppInstance()->gregorianToJalali(outcomeGregorianDate);

            date = outcomeJaliliDateString;
        }

        data.emplace_back(
            query.value("consultation_id").toInt(),
            query.value("patient_id").toInt(),
            query.value("consultant_id").toInt(),
            date,
            query.value("outcome").toString(),
            query.value("name").toString(),
            query.value("specialization").toString()
        );
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Patient consultations retrieval succeeded!";
#endif

    emit finishedGettingPatientConsultations(1, "فرآیند گرفتن مشاوره ها موفقیت آمیز بود.", data);

    return;
}

void DatabaseWorker::removePatientConsultation(const int consultationID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Consultation ID   :" << consultationID;
#endif

    emit startedRemovingPatientConsultation();

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedRemovingPatientConsultation(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

    QString queryString = R"(
        DELETE FROM patient_consultations

        WHERE consultation_id = :consultation_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":consultation_id", consultationID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedRemovingPatientConsultation(-2, "فرآیند حذف مشاوره بیمار ناموفق بود: " + query.lastError().text());

        return;
    }

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedRemovingPatientConsultation(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Patient consultation removal succeeded!";
#endif

    emit finishedRemovingPatientConsultation(1, "فرآیند حذف مشاوره بیمار موفقیت آمیز بود");

    return;
}

void DatabaseWorker::updatePatientConsultationDateAndOutcome(const int consultationID, const QString &date, const QString &outcome)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Consultation ID :" << consultationID << "\n"
             << "Date            :" << date << "\n"
             << "Outcome         :" << outcome;
#endif

    emit startedUpdatingPatientConsultationDateAndOutcome();

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedUpdatingPatientConsultationDateAndOutcome(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

    QString queryString = R"(
        UPDATE patient_consultations SET consultation_date = :consultation_date, consultation_outcome = :consultation_outcome

        WHERE consultation_id = :consultation_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":consultation_id", consultationID);

    QCalendar calendarJalali(QCalendar::System::Jalali);

    QDate consultationGregorianDate;
    consultationGregorianDate = QDate::fromString(date, "yyyy-MM-dd", calendarJalali);

    if(consultationGregorianDate.isNull() || !consultationGregorianDate.isValid())
    {
        query.bindValue(":consultation_date", QVariant(QMetaType::fromType<QDate>()));
    }

    else
    {
        query.bindValue(":consultation_date", consultationGregorianDate);
    }

    query.bindValue(":consultation_outcome", outcome);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingPatientConsultationDateAndOutcome(-2, "آپدیت اطلاعات مشاوره ناموفق بود: " + query.lastError().text());

        return;
    }

    // NOTE (SAVIZ): under no circumstances should numRowseffected == 0

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingPatientConsultationDateAndOutcome(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Consultations information update succeeded!";
#endif

    emit finishedUpdatingPatientConsultationDateAndOutcome(1, "آپدیت اطلاعات مشاوره موفقیت آمیز بود");

    return;
}

void DatabaseWorker::getLabsList()
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "None";
#endif

    emit startedGettingLabsList();

    std::vector<Lab> data;

    QString queryString = R"(
        SELECT lab_id, name, specialization FROM labs

        WHERE is_active = TRUE;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        emit finishedGettingLabsList(-2, "فرآیند گرفتن لیست آزمایشگاه‌ها ناموفق بود: " + query.lastError().text(), data);

        return;
    }

    // NOTE (SAVIZ): The condition query.size() == 0 should never occur, as the database is prepopulated with the required information.

    data.reserve(query.size());

    while (query.next())
    {
        data.emplace_back(
            query.value("lab_id").toInt(),
            query.value("name").toString(),
            query.value("specialization").toString()
            );
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Labs list retrieval succeeded!";
#endif

    emit finishedGettingLabsList(1, "فرآیند گرفتن لیست آزمایشگاه‌ها موفقیت آمیز بود", data);

    return;
}

void DatabaseWorker::insertPatientLabTest(const int patientID, const int labID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID :" << patientID << "\n"
             << "Lab ID     :" << labID;
#endif

    emit startedInsertingPatientLabTest();

    LabTest labTest;

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedInsertingPatientLabTest(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text(), labTest);

        return;
    }

    QString queryString = R"(
        INSERT INTO patient_lab_tests (patient_id, lab_id, properties)

        VALUES (:patient_id, :lab_id,

        JSON_OBJECT(
          'CBC',              0,
          'WBC',              0,
          'Hgb',              0,
          'Ferritin',         0,
          'ESR',              0,
          'Na',               0,
          'K',                0,
          'Mg',               0,
          'VitaminD',         0,
          'FBS',              0,
          'TG',               0,
          'Cholestrol',       0,
          'AST',              0,
          'ALT',              0,
          'ALKPh',            0,
          'BUN',              0,
          'Cr',               0,
          'UA',               0,
          'SE_OB',            0,
          'SE_OP',            0,
          'H_Pylori_Ab',      0,
          'H_Pylori_Ag_SE',   0,
          'Tuberculin_test',  0,
          'Pathergy_test',    0,
          'Sonography',       0,
          'TSH',              0,
          'LH',               0,
          'FSH',              0,
          'DHEAS',            0,
          'OH_P_17',          0,
          'Prolactine',       0,
          'Testosterone',     0,
          'Hepatitis_Ag',     0,
          'Hepatitis_Ab',     0,
          'ANA',              0,
          'Anti_DS_Ab',       0,
          'Anti_SCL70_Ab',    0,
          'IgE',              0)
        );
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);
    query.bindValue(":lab_id", labID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedInsertingPatientLabTest(-2, "فرآیند درج آزمایش ناموفق بود: " + query.lastError().text(), labTest);

        return;
    }

    int id = query.lastInsertId().toInt();

    query.clear();

    queryString = R"(
        SELECT
            patient_lab_tests.lab_test_id AS lab_test_id,
            patient_lab_tests.patient_id AS patient_id,
            labs.lab_id AS lab_id,
            patient_lab_tests.lab_test_date AS date,
            patient_lab_tests.lab_test_outcome AS outcome,
            labs.name AS name,
            labs.specialization AS specialization,
            properties->>'$.CBC'              AS CBC,
            properties->>'$.WBC'              AS WBC,
            properties->>'$.Hgb'              AS Hgb,
            properties->>'$.Ferritin'         AS Ferritin,
            properties->>'$.ESR'              AS ESR,
            properties->>'$.Na'               AS Na,
            properties->>'$.K'                AS K,
            properties->>'$.Mg'               AS Mg,
            properties->>'$.VitaminD'         AS VitaminD,
            properties->>'$.FBS'              AS FBS,
            properties->>'$.TG'               AS TG,
            properties->>'$.Cholestrol'       AS Cholestrol,
            properties->>'$.AST'              AS AST,
            properties->>'$.ALT'              AS ALT,
            properties->>'$.ALKPh'            AS ALKPh,
            properties->>'$.BUN'              AS BUN,
            properties->>'$.Cr'               AS Cr,
            properties->>'$.UA'               AS UA,
            properties->>'$.SE_OB'            AS SE_OB,
            properties->>'$.SE_OP'            AS SE_OP,
            properties->>'$.H_Pylori_Ab'      AS H_Pylori_Ab,
            properties->>'$.H_Pylori_Ag_SE'   AS H_Pylori_Ag_SE,
            properties->>'$.Tuberculin_test'  AS Tuberculin_test,
            properties->>'$.Pathergy_test'    AS Pathergy_test,
            properties->>'$.Sonography'       AS Sonography,
            properties->>'$.TSH'              AS TSH,
            properties->>'$.LH'               AS LH,
            properties->>'$.FSH'              AS FSH,
            properties->>'$.DHEAS'            AS DHEAS,
            properties->>'$.OH_P_17'          AS OH_P_17,
            properties->>'$.Prolactine'       AS Prolactine,
            properties->>'$.Testosterone'     AS Testosterone,
            properties->>'$.Hepatitis_Ag'     AS Hepatitis_Ag,
            properties->>'$.Hepatitis_Ab'     AS Hepatitis_Ab,
            properties->>'$.ANA'              AS ANA,
            properties->>'$.Anti_DS_Ab'       AS Anti_DS_Ab,
            properties->>'$.Anti_SCL70_Ab'    AS Anti_SCL70_Ab,
            properties->>'$.IgE'              AS IgE

        FROM patient_lab_tests

        INNER JOIN labs ON patient_lab_tests.lab_id = labs.lab_id

        WHERE patient_lab_tests.lab_test_id = :lab_test_id;
    )";

    query.prepare(queryString);

    query.bindValue(":lab_test_id", id);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        query.clear();

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedInsertingPatientLabTest(-2, "فرآیند درج آزمایش ناموفق بود: " + query.lastError().text(), labTest);

        return;
    }

    while (query.next())
    {
        QString date = "";

        QDate outcomeGregorianDate = query.value("date").toDate();

        if(!outcomeGregorianDate.isNull())
        {
            QString outcomeJaliliDateString = Date::cppInstance()->gregorianToJalali(outcomeGregorianDate);

            date = outcomeJaliliDateString;
        }

        labTest.labTestID = query.value("lab_test_id").toInt();
        labTest.patientID = query.value("patient_id").toInt();
        labTest.labID = query.value("lab_id").toInt();
        labTest.date = date;
        labTest.outcome = query.value("outcome").toString();
        labTest.name = query.value("name").toString();
        labTest.specialization = query.value("specialization").toString();
        labTest.CBC = query.value("CBC").toInt();
        labTest.WBC = query.value("WBC").toInt();
        labTest.Hgb = query.value("Hgb").toInt();
        labTest.Ferritin = query.value("Ferritin").toInt();
        labTest.ESR = query.value("ESR").toInt();
        labTest.Na = query.value("Na").toInt();
        labTest.K = query.value("K").toInt();
        labTest.Mg = query.value("Mg").toInt();
        labTest.VitaminD = query.value("VitaminD").toInt();
        labTest.FBS = query.value("FBS").toInt();
        labTest.TG = query.value("TG").toInt();
        labTest.Cholestrol = query.value("Cholestrol").toInt();
        labTest.AST = query.value("AST").toInt();
        labTest.ALT = query.value("ALT").toInt();
        labTest.ALKPh = query.value("ALKPh").toInt();
        labTest.BUN = query.value("BUN").toInt();
        labTest.Cr = query.value("Cr").toInt();
        labTest.UA = query.value("UA").toInt();
        labTest.SE_OB = query.value("SE_OB").toInt();
        labTest.SE_OP = query.value("SE_OP").toInt();
        labTest.H_Pylori_Ab = query.value("H_Pylori_Ab").toInt();
        labTest.H_Pylori_Ag_SE = query.value("H_Pylori_Ag_SE").toInt();
        labTest.Tuberculin_test = query.value("Tuberculin_test").toInt();
        labTest.Pathergy_test = query.value("Pathergy_test").toInt();
        labTest.Sonography = query.value("Sonography").toInt();
        labTest.TSH = query.value("TSH").toInt();
        labTest.LH = query.value("LH").toInt();
        labTest.FSH = query.value("FSH").toInt();
        labTest.DHEAS = query.value("DHEAS").toInt();
        labTest.OH_P_17 = query.value("OH_P_17").toInt();
        labTest.Prolactine = query.value("Prolactine").toInt();
        labTest.Testosterone = query.value("Testosterone").toInt();
        labTest.Hepatitis_Ag = query.value("Hepatitis_Ag").toInt();
        labTest.Hepatitis_Ab = query.value("Hepatitis_Ab").toInt();
        labTest.ANA = query.value("ANA").toInt();
        labTest.Anti_DS_Ab = query.value("Anti_DS_Ab").toInt();
        labTest.Anti_SCL70_Ab = query.value("Anti_SCL70_Ab").toInt();
        labTest.IgE = query.value("IgE").toInt();
    }

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif
        query.clear();

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedInsertingPatientLabTest(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text(), labTest);

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Lab test insertion succeeded!";
#endif

    emit finishedInsertingPatientLabTest(1, "فرآیند درج آزمایش موفقیت آمیز بود", labTest);

    return;
}

void DatabaseWorker::removePatientLabTest(const int labTestID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Lab test ID :" << labTestID;
#endif

    emit startedRemovingPatientLabTest();

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedRemovingPatientLabTest(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

    QString queryString = R"(
        DELETE FROM patient_lab_tests

        WHERE lab_test_id = :lab_test_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":lab_test_id", labTestID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedRemovingPatientLabTest(-2, "فرآیند حذف آزمایش بیمار ناموفق بود: " + query.lastError().text());

        return;
    }

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedRemovingPatientLabTest(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Patient lab test removal succeeded!";
#endif

    emit finishedRemovingPatientLabTest(1, "فرآیند حذف آزمایش بیمار موفقیت آمیز بود");

    return;
}

void DatabaseWorker::updatePatientLabTest(const LabTest labTest)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :";
#endif

    emit startedUpdatingPatientLabTest();

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedUpdatingPatientLabTest(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

    QString queryString = R"(
        UPDATE patient_lab_tests SET lab_test_date = :lab_test_date, lab_test_outcome = :lab_test_outcome, properties = JSON_SET(
        properties,
        '$.CBC',              :CBC,
        '$.WBC',              :WBC,
        '$.Hgb',              :Hgb,
        '$.Ferritin',         :Ferritin,
        '$.ESR',              :ESR,
        '$.Na',               :Na,
        '$.K',                :K,
        '$.Mg',               :Mg,
        '$.VitaminD',         :VitaminD,
        '$.FBS',              :FBS,
        '$.TG',               :TG,
        '$.Cholestrol',       :Cholestrol,
        '$.AST',              :AST,
        '$.ALT',              :ALT,
        '$.ALKPh',            :ALKPh,
        '$.BUN',              :BUN,
        '$.Cr',               :Cr,
        '$.UA',               :UA,
        '$.SE_OB',            :SE_OB,
        '$.SE_OP',            :SE_OP,
        '$.H_Pylori_Ab',      :H_Pylori_Ab,
        '$.H_Pylori_Ag_SE',   :H_Pylori_Ag_SE,
        '$.Tuberculin_test',  :Tuberculin_test,
        '$.Pathergy_test',    :Pathergy_test,
        '$.Sonography',       :Sonography,
        '$.TSH',              :TSH,
        '$.LH',               :LH,
        '$.FSH',              :FSH,
        '$.DHEAS',            :DHEAS,
        '$.OH_P_17',          :OH_P_17,
        '$.Prolactine',       :Prolactine,
        '$.Testosterone',     :Testosterone,
        '$.Hepatitis_Ag',     :Hepatitis_Ag,
        '$.Hepatitis_Ab',     :Hepatitis_Ab,
        '$.ANA',              :ANA,
        '$.Anti_DS_Ab',       :Anti_DS_Ab,
        '$.Anti_SCL70_Ab',    :Anti_SCL70_Ab,
        '$.IgE',              :IgE)

        WHERE lab_test_id = :lab_test_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":lab_test_id", labTest.labTestID);

    QCalendar calendarJalali(QCalendar::System::Jalali);

    QDate consultationGregorianDate;
    consultationGregorianDate = QDate::fromString(labTest.date, "yyyy-MM-dd", calendarJalali);

    if(consultationGregorianDate.isNull() || !consultationGregorianDate.isValid())
    {
        query.bindValue(":lab_test_date", QVariant(QMetaType::fromType<QDate>()));
    }

    else
    {
        query.bindValue(":lab_test_date", consultationGregorianDate);
    }

    query.bindValue(":lab_test_outcome", labTest.outcome);
    query.bindValue(":CBC",             labTest.CBC);
    query.bindValue(":WBC",             labTest.WBC);
    query.bindValue(":Hgb",             labTest.Hgb);
    query.bindValue(":Ferritin",        labTest.Ferritin);
    query.bindValue(":ESR",             labTest.ESR);
    query.bindValue(":Na",              labTest.Na);
    query.bindValue(":K",               labTest.K);
    query.bindValue(":Mg",              labTest.Mg);
    query.bindValue(":VitaminD",        labTest.VitaminD);
    query.bindValue(":FBS",             labTest.FBS);
    query.bindValue(":TG",              labTest.TG);
    query.bindValue(":Cholestrol",      labTest.Cholestrol);
    query.bindValue(":AST",             labTest.AST);
    query.bindValue(":ALT",             labTest.ALT);
    query.bindValue(":ALKPh",           labTest.ALKPh);
    query.bindValue(":BUN",             labTest.BUN);
    query.bindValue(":Cr",              labTest.Cr);
    query.bindValue(":UA",              labTest.UA);
    query.bindValue(":SE_OB",           labTest.SE_OB);
    query.bindValue(":SE_OP",           labTest.SE_OP);
    query.bindValue(":H_Pylori_Ab",     labTest.H_Pylori_Ab);
    query.bindValue(":H_Pylori_Ag_SE",  labTest.H_Pylori_Ag_SE);
    query.bindValue(":Tuberculin_test", labTest.Tuberculin_test);
    query.bindValue(":Pathergy_test",   labTest.Pathergy_test);
    query.bindValue(":Sonography",      labTest.Sonography);
    query.bindValue(":TSH",             labTest.TSH);
    query.bindValue(":LH",              labTest.LH);
    query.bindValue(":FSH",             labTest.FSH);
    query.bindValue(":DHEAS",           labTest.DHEAS);
    query.bindValue(":OH_P_17",         labTest.OH_P_17);
    query.bindValue(":Prolactine",      labTest.Prolactine);
    query.bindValue(":Testosterone",    labTest.Testosterone);
    query.bindValue(":Hepatitis_Ag",    labTest.Hepatitis_Ag);
    query.bindValue(":Hepatitis_Ab",    labTest.Hepatitis_Ab);
    query.bindValue(":ANA",             labTest.ANA);
    query.bindValue(":Anti_DS_Ab",      labTest.Anti_DS_Ab);
    query.bindValue(":Anti_SCL70_Ab",   labTest.Anti_SCL70_Ab);
    query.bindValue(":IgE",             labTest.IgE);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingPatientLabTest(-2, "آپدیت اطلاعات آزمایش ناموفق بود: " + query.lastError().text());

        return;
    }

    // NOTE (SAVIZ): under no circumstances should numRowseffected == 0

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingPatientLabTest(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Lab test information update succeeded!";
#endif

    emit finishedUpdatingPatientLabTest(1, "آپدیت اطلاعات آزمایش موفقیت آمیز بود");

    return;
}

void DatabaseWorker::getPatientLabTests(const int patientID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID :" << patientID;
#endif

    emit startedGettingPatientLabTests();

    std::vector<LabTest> data;

    QString queryString = R"(
        SELECT
            patient_lab_tests.lab_test_id AS lab_test_id,
            patient_lab_tests.patient_id AS patient_id,
            labs.lab_id AS lab_id,
            patient_lab_tests.lab_test_date AS date,
            patient_lab_tests.lab_test_outcome AS outcome,
            labs.name AS name,
            labs.specialization AS specialization,
            properties->>'$.CBC'              AS CBC,
            properties->>'$.WBC'              AS WBC,
            properties->>'$.Hgb'              AS Hgb,
            properties->>'$.Ferritin'         AS Ferritin,
            properties->>'$.ESR'              AS ESR,
            properties->>'$.Na'               AS Na,
            properties->>'$.K'                AS K,
            properties->>'$.Mg'               AS Mg,
            properties->>'$.VitaminD'         AS VitaminD,
            properties->>'$.FBS'              AS FBS,
            properties->>'$.TG'               AS TG,
            properties->>'$.Cholestrol'       AS Cholestrol,
            properties->>'$.AST'              AS AST,
            properties->>'$.ALT'              AS ALT,
            properties->>'$.ALKPh'            AS ALKPh,
            properties->>'$.BUN'              AS BUN,
            properties->>'$.Cr'               AS Cr,
            properties->>'$.UA'               AS UA,
            properties->>'$.SE_OB'            AS SE_OB,
            properties->>'$.SE_OP'            AS SE_OP,
            properties->>'$.H_Pylori_Ab'      AS H_Pylori_Ab,
            properties->>'$.H_Pylori_Ag_SE'   AS H_Pylori_Ag_SE,
            properties->>'$.Tuberculin_test'  AS Tuberculin_test,
            properties->>'$.Pathergy_test'    AS Pathergy_test,
            properties->>'$.Sonography'       AS Sonography,
            properties->>'$.TSH'              AS TSH,
            properties->>'$.LH'               AS LH,
            properties->>'$.FSH'              AS FSH,
            properties->>'$.DHEAS'            AS DHEAS,
            properties->>'$.OH_P_17'          AS OH_P_17,
            properties->>'$.Prolactine'       AS Prolactine,
            properties->>'$.Testosterone'     AS Testosterone,
            properties->>'$.Hepatitis_Ag'     AS Hepatitis_Ag,
            properties->>'$.Hepatitis_Ab'     AS Hepatitis_Ab,
            properties->>'$.ANA'              AS ANA,
            properties->>'$.Anti_DS_Ab'       AS Anti_DS_Ab,
            properties->>'$.Anti_SCL70_Ab'    AS Anti_SCL70_Ab,
            properties->>'$.IgE'              AS IgE

        FROM patient_lab_tests

        INNER JOIN labs ON patient_lab_tests.lab_id = labs.lab_id

        WHERE patient_lab_tests.patient_id = :patient_id

        ORDER BY patient_lab_tests.lab_test_date DESC;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        emit finishedGettingPatientLabTests(-2, "فرآیند گرفتن آزمایش‌ها ناموفق بود: " + query.lastError().text(), data);

        return;
    }

    if (query.size() == 0)
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Patient lab tests retrieval returned no results.";
#endif

        emit finishedGettingPatientLabTests(-1, "فرآیند گرفتن آزمایش‌ها هیچ نتیجه‌ای برنگرداند.", data);

        return;
    }

    data.reserve(query.size());

    while (query.next())
    {
        QString date = "";

        QDate outcomeGregorianDate = query.value("date").toDate();

        if(!outcomeGregorianDate.isNull())
        {
            QString outcomeJaliliDateString = Date::cppInstance()->gregorianToJalali(outcomeGregorianDate);

            date = outcomeJaliliDateString;
        }

        data.emplace_back(
            query.value("lab_test_id").toInt(),
            query.value("patient_id").toInt(),
            query.value("lab_id").toInt(),
            date,
            query.value("outcome").toString(),
            query.value("name").toString(),
            query.value("specialization").toString(),
            query.value("CBC").toInt(),
            query.value("WBC").toInt(),
            query.value("Hgb").toInt(),
            query.value("Ferritin").toInt(),
            query.value("ESR").toInt(),
            query.value("Na").toInt(),
            query.value("K").toInt(),
            query.value("Mg").toInt(),
            query.value("VitaminD").toInt(),
            query.value("FBS").toInt(),
            query.value("TG").toInt(),
            query.value("Cholestrol").toInt(),
            query.value("AST").toInt(),
            query.value("ALT").toInt(),
            query.value("ALKPh").toInt(),
            query.value("BUN").toInt(),
            query.value("Cr").toInt(),
            query.value("UA").toInt(),
            query.value("SE_OB").toInt(),
            query.value("SE_OP").toInt(),
            query.value("H_Pylori_Ab").toInt(),
            query.value("H_Pylori_Ag_SE").toInt(),
            query.value("Tuberculin_test").toInt(),
            query.value("Pathergy_test").toInt(),
            query.value("Sonography").toInt(),
            query.value("TSH").toInt(),
            query.value("LH").toInt(),
            query.value("FSH").toInt(),
            query.value("DHEAS").toInt(),
            query.value("OH_P_17").toInt(),
            query.value("Prolactine").toInt(),
            query.value("Testosterone").toInt(),
            query.value("Hepatitis_Ag").toInt(),
            query.value("Hepatitis_Ab").toInt(),
            query.value("ANA").toInt(),
            query.value("Anti_DS_Ab").toInt(),
            query.value("Anti_SCL70_Ab").toInt(),
            query.value("IgE").toInt()
        );
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Patient lab tests retrieval succeeded!";
#endif

    emit finishedGettingPatientLabTests(1, "فرآیند گرفتن آزمایش‌ها موفقیت آمیز بود.", data);

    return;
}

void DatabaseWorker::getPatientImages(const int patientID)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID :" << patientID;
#endif

    emit startedGettingPatientImages();

    std::vector<Image> data;

    QString queryString = R"(
        SELECT image_id, image_name AS name, image_data AS data FROM patient_images

        WHERE patient_id = :patient_id
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        emit finishedGettingPatientImages(-2, "فرآیند گرفتن تصاویر ناموفق بود: " + query.lastError().text(), data);

        return;
    }

    if (query.size() == 0)
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Patient images retrieval returned no results.";
#endif

        emit finishedGettingPatientImages(-1, "فرآیند گرفتن تصاویر هیچ نتیجه‌ای برنگرداند.", data);

        return;
    }

    data.reserve(query.size());

    while (query.next())
    {
        data.emplace_back(
            query.value("image_id").toInt(),
            query.value("name").toString(),
            query.value("data").toByteArray()
        );
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Patient images retrieval succeeded!";
#endif

    emit finishedGettingPatientImages(1, "فرآیند گرفتن تصاویر موفقیت آمیز بود.", data);

    return;
}

void DatabaseWorker::insertPatientImage(const int patientID, const QString &name, const QByteArray &data)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID :" << patientID << "\n"
             << "Name       :" << name;

    // NOTE (SAVIZ): Printing the byte array is unnecessary—it is performance-intensive and provides no meaningful output, as it only displays raw binary data (0s and 1s).
#endif

    emit startedInsertingPatientImage();

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedInsertingPatientImage(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

    QString queryString = R"(
        INSERT INTO patient_images (patient_id, image_name, image_data)

        VALUES (:patient_id, :image_name, :image_data)
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);
    query.bindValue(":image_name", name);
    query.bindValue(":image_data", data);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedInsertingPatientImage(-2, "فرآیند درج تصویر ناموفق بود: " + query.lastError().text());

        return;
    }

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedInsertingPatientImage(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Image insertion succeeded!";
#endif

    emit finishedInsertingPatientImage(1, "فرآیند درج تصویر موفقیت آمیز بود");

    return;
}

void DatabaseWorker::removePatientImage(const int patientID, const QString &name)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID   :" << patientID << "\n"
             << "Name         :" << name;
#endif

    emit startedRemovingPatientImage();

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedRemovingPatientImage(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

    QString queryString = R"(
        DELETE FROM patient_images

        WHERE patient_id = :patient_id AND image_name = :image_name;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);
    query.bindValue(":image_name", name);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedRemovingPatientImage(-2, "فرآیند حذف تصویر ناموفق بود: " + query.lastError().text());

        return;
    }

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedRemovingPatientImage(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Patient image removal succeeded!";
#endif

    emit finishedRemovingPatientImage(1, "فرآیند حذف تصویر موفقیت آمیز بود");

    return;
}

void DatabaseWorker::updatePatientImageName(const int patientID, const QString &name, const QString &newName)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID :" << patientID << "\n"
             << "Name       :" << name << "\n"
             << "New name   :" << newName;
#endif

    emit startedUpdatingPatientImageName();

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedUpdatingPatientImageName(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

    QString queryString = R"(
        UPDATE patient_images SET image_name = :new_name

        WHERE patient_id = :patient_id AND image_name = :search_name;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);
    query.bindValue(":search_name", name);
    query.bindValue(":new_name", newName);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingPatientImageName(-2, "آپدیت نام تصویر ناموفق بود: " + query.lastError().text());

        return;
    }

    // NOTE (SAVIZ): under no circumstances should numRowseffected == 0

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingPatientImageName(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Image name update succeeded!";
#endif

    emit finishedUpdatingPatientImageName(1, "آپدیت نام تصویر موفقیت آمیز بود");

    return;
}

void DatabaseWorker::updatePatientDeletionStatus(const int patientID, const bool newStatus)
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "\n"
             << "Patient ID :" << patientID << "\n"
             << "New status :" << newStatus;
#endif

    emit startedUpdatingPatientDeletionStatus();

    if (!QSqlDatabase::database(c_ConnectionName).transaction())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Transaction could not be started :" << QSqlDatabase::database(c_ConnectionName).lastError().text();
#endif

        emit finishedUpdatingPatientDeletionStatus(-2, "شروع تراکنش شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

    QString queryString = R"(
        UPDATE patients SET is_marked_for_deletion = :newStatus

        WHERE patient_id = :patient_id;
    )";

    QSqlQuery query(QSqlDatabase::database(c_ConnectionName));

    query.prepare(queryString);

    query.bindValue(":patient_id", patientID);
    query.bindValue(":newStatus", newStatus);

    if (!query.exec())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << query.lastError().text();
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingPatientDeletionStatus(-2, "فرآیند تغییر وضعیت حذف ناموفق بود: " + query.lastError().text());

        return;
    }

    if (!QSqlDatabase::database(c_ConnectionName).commit())
    {
#ifdef QT_DEBUG
        qDebug() << "Log Output :" << "Commit failed!";
#endif

        QSqlDatabase::database(c_ConnectionName).rollback();

        emit finishedUpdatingPatientDeletionStatus(-2, "تأیید تغییرات شکست خورد: " + QSqlDatabase::database(c_ConnectionName).lastError().text());

        return;
    }

#ifdef QT_DEBUG
    qDebug() << "Log Output :" << "Update patient deletion status succeeded!";
#endif

    emit finishedUpdatingPatientDeletionStatus(1, "فرآیند تغییر وضعیت حذف موفقیت آمیز بود");

    return;
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
