#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>

#include "database.hpp"
#include "search_model.hpp"
#include "starred_patients_model.hpp"
#include "diagnoses_list_model.hpp"
#include "patient_diagnoses_model.hpp"
#include "treatments_list_model.hpp"
#include "patient_treatments_model.hpp"
#include "procedures_list_model.hpp"
#include "patient_procedures_model.hpp"
#include "consultants_list_model.hpp"
#include "patient_consultations_model.hpp"
#include "patient_images_model.hpp"
#include "labs_list_model.hpp"
#include "patient_lab_tests_model.hpp"
#include "date.hpp"
#include "proxy_filter.hpp"

int main(int argc, char *argv[])
{
    qSetMessagePattern("%{function} (Line: %{line}) >> %{message}");

    QGuiApplication app(argc, argv);
    QGuiApplication::setWindowIcon(QIcon(":/resources/icons/inkscape/export/application.png"));
    app.setOrganizationName("UFOCoder");
    app.setOrganizationDomain("ufocoder.com");
    app.setApplicationName("DermaBase_AS");
    app.setApplicationDisplayName("DermaBase (AS)");
    app.setApplicationVersion("1.0");

    qmlRegisterType<Database>("Database", 1, 0, "Database");
    qmlRegisterType<SearchModel>("SearchModel", 1, 0, "SearchModel");
    qmlRegisterType<StarredPatientsModel>("StarredPatientsModel", 1, 0, "StarredPatientsModel");
    qmlRegisterType<ProxyFilter>("ProxyFilter", 1, 0, "ProxyFilter");
    qmlRegisterType<DiagnosesListModel>("DiagnosesListModel", 1, 0, "DiagnosesListModel");
    qmlRegisterType<PatientDiagnosesModel>("PatientDiagnosesModel", 1, 0, "PatientDiagnosesModel");
    qmlRegisterType<TreatmentsListModel>("TreatmentsListModel", 1, 0, "TreatmentsListModel");
    qmlRegisterType<PatientTreatmentsModel>("PatientTreatmentsModel", 1, 0, "PatientTreatmentsModel");
    qmlRegisterType<ProceduresListModel>("ProceduresListModel", 1, 0, "ProceduresListModel");
    qmlRegisterType<PatientProceduresModel>("PatientProceduresModel", 1, 0, "PatientProceduresModel");
    qmlRegisterType<ConsultantsListModel>("ConsultantsListModel", 1, 0, "ConsultantsListModel");
    qmlRegisterType<PatientConsultationsModel>("PatientConsultationsModel", 1, 0, "PatientConsultationsModel");
    qmlRegisterType<LabsListModel>("LabsListModel", 1, 0, "LabsListModel");
    qmlRegisterType<PatientLabTestsModel>("PatientLabTestsModel", 1, 0, "PatientLabTestsModel");
    qmlRegisterType<PatientImagesModel>("PatientImagesModel", 1, 0, "PatientImagesModel");
    qmlRegisterSingletonType<Date>("Date", 1, 0, "Date", &Date::qmlInstance);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("DermaBase_AS", "Main");

    return app.exec();
}
