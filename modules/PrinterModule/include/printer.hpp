#ifndef PRINTER_H
#define PRINTER_H

#include <QObject>
#include <QQmlEngine>
#include <QVariant>
#include <QVariantList>
#include <QVariantMap>
#include <QPrinterInfo>
#include <QPrintDialog>
#include <QFile>
#include <QTextStream>
#include <QTextDocument>
#include <QStringList>
#include <QStandardPaths>

class Printer : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(Printer) // Needed for Singleton

    // Q_PROPERTY
    Q_PROPERTY(QUrl outputDirectoryUrl READ getOutputDirectoryUrl WRITE setOutputDirectoryUrl NOTIFY outputDirectoryUrlChanged)

public:
    explicit Printer(QObject *parent = Q_NULLPTR, const QString& name = "No name");
    ~Printer();

    static Printer *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);
    static Printer *cppInstance(QObject *parent = Q_NULLPTR);

    static void Init();
    static void ShutDown();

    // PUBLIC Enums
public:

    // Fields
private:
    static Printer *m_Instance;
    unsigned int m_PatientID;
    QString m_TemplateFilePath;
    QUrl m_OutputDirectoryUrl;
    QString m_OutputFilePath;

    // Signals
signals:
    void printStatusChanged(QVariantMap resultMap);

    void outputDirectoryUrlChanged();

    void pageLayoutChanged();

    // PUBLIC Slots:
public slots:

    // PRIVATE Slots:
private slots:

    // PUBLIC Methods
public:
    Q_INVOKABLE bool printPatientData();

    // PRIVATE Methods
private:

    // PUBLIC Getters
public:
    QUrl getOutputDirectoryUrl() const;

    // PRIVATE Getters
public:

    // PUBLIC Setters
public:
    Q_INVOKABLE void setPatientID(unsigned int newPatientID);
    void setOutputDirectoryUrl(const QUrl newOutputDirectoryUrl);

    // PRIVATE Setters
private:
};

#endif // PRINTER_H
