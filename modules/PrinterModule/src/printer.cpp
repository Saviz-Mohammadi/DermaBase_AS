#ifdef QT_DEBUG
    #include <QDebug>
#endif

#include "printer.hpp"
#include "database.hpp"

Printer *Printer::m_Instance = Q_NULLPTR;

// Constructors, Init, ShutDown, Destructor
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

Printer::Printer(QObject *parent, const QString &name)
    : QObject{parent}
    , m_PatientID(0)
    , m_TemplateFilePath(":/resources/html/template.html")
    , m_OutputDirectoryUrl(QUrl::fromLocalFile(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)))
    , m_OutputFilePath("")
{
    this->setObjectName(name);

#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "None";

    qDebug() << "Log Output :";

    for (const QPrinterInfo &printer : QPrinterInfo::availablePrinters())
    {
        qDebug() << printer.printerName();
    }
#endif
}

Printer::~Printer()
{
#ifdef QT_DEBUG
    qDebug() << "objectName :" << this->objectName();
    qDebug() << "Arguments  :" << "None";
    qDebug() << "Log Output :" << "None";
#endif
}

Printer *Printer::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    if (!m_Instance)
    {
        m_Instance = new Printer();
    }

    return (m_Instance);
}

Printer *Printer::cppInstance(QObject *parent)
{
    if (m_Instance)
    {
        return (qobject_cast<Printer *>(Printer::m_Instance));
    }

    auto instance = new Printer(parent);
    m_Instance = instance;

    return (instance);
}

// NOTE (SAVIZ): Not needed. However, provided just in case.
void Printer::Init()
{
    // Init resources;
}

// NOTE (SAVIZ): In Qt, this isn't necessary due to its parent-child memory management system. However, in standard C++, it's a good practice to either explicitly call this when we're done with the object or ensure it gets invoked within the destructor.
void Printer::ShutDown()
{
    delete (m_Instance);

    m_Instance = Q_NULLPTR;
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]





// PUBLIC Methods
// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

bool Printer::printPatientData()
{
    Database *database = Database::cppInstance();

    QVariantMap resultMap
    {
        {"status", QVariant(false)},
        {"message", QVariant(QString())}
    };

    // NOTE (SAVIZ): This check is unnecessary because the database is guaranteed to be connected when this function is called. However, I included it as a precaution:
    if(database->getConnectionStatus() == false)
    {
#ifdef QT_DEBUG
        qDebug() << "Connection to database is not established!";
#endif

        resultMap["status"] = false;
        resultMap["message"] = "اتصالی به پایگاه داده شناسایی نشد";

        emit printStatusChanged(resultMap);

        return (false);
    }

    QVariantMap patientBasicDataMap = database->pullPatientBasicData(m_PatientID)["data"].toMap();
    QVariantList patientTreatmentList = database->pullPatientTreatments(m_PatientID)["data"].toList();

    QFile file(m_TemplateFilePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
#ifdef QT_DEBUG
        qDebug() << "Failed to open HTML template.";
#endif

        resultMap["status"] = false;
        resultMap["message"] = "امکان خواندن فایل الگو وجود ندارد";

        emit printStatusChanged(resultMap);

        return (false);
    }

    QTextStream in(&file);
    QString htmlContent = in.readAll();
    file.close();

    quint32 id = patientBasicDataMap["patient_id"].toUInt();
    QString firstName = patientBasicDataMap["first_name"].toString().trimmed();
    QString lastName = patientBasicDataMap["last_name"].toString().trimmed();

    // NOTE (SAVIZ): Just a reminder that I placed a Persian space character between %2 and %3:
    m_OutputFilePath = QString("%0/MR_%1_(%2 %3).pdf").arg(m_OutputDirectoryUrl.toLocalFile(), QString::number(id), firstName, lastName);

    htmlContent.replace("{{id}}", QString::number(patientBasicDataMap["patient_id"].toInt()));
    htmlContent.replace("{{first_name}}", patientBasicDataMap["first_name"].toString());
    htmlContent.replace("{{last_name}}", patientBasicDataMap["last_name"].toString());
    htmlContent.replace("{{service_price}}", QString::number(patientBasicDataMap["service_price"].toDouble(), 'f', 3));

    QStringList treatmentList;
    for (const QVariant &treatment : patientTreatmentList)
    {
        QVariantMap treatmentMap = treatment.toMap();

        treatmentList.append("<li>" + treatmentMap["treatment_name"].toString() + "</li>");
    }

    htmlContent.replace("{{treatments}}", treatmentList.join(""));

    QTextDocument document;
    document.setHtml(htmlContent);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(m_OutputFilePath);
    printer.setPageSize(QPageSize::A4);

    document.print(&printer);

#ifdef QT_DEBUG
    qDebug() << "PDF saved to: " << m_OutputFilePath;
#endif

    resultMap["status"] = true;
    resultMap["message"] = "فایل ایجاد شد و در مسیر قرار گرفت: " + m_OutputFilePath;

    emit printStatusChanged(resultMap);

    return (true);
}

void Printer::setPatientID(unsigned int newPatientID)
{
    if(m_PatientID == newPatientID)
    {
        return;
    }

    m_PatientID = newPatientID;
}

// [[------------------------------------------------------------------------]]
// [[------------------------------------------------------------------------]]

QUrl Printer::getOutputDirectoryUrl() const
{
    return (m_OutputDirectoryUrl);
}

void Printer::setOutputDirectoryUrl(const QUrl newOutputDirectoryUrl)
{
    if (m_OutputDirectoryUrl == newOutputDirectoryUrl)
    {
        return;
    }

    m_OutputDirectoryUrl = newOutputDirectoryUrl;
    emit outputDirectoryUrlChanged();
}
