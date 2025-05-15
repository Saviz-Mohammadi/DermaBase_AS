import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

// Custom CPP:
import Database 1.0

ApplicationWindow {
    id: mainApplicationWindow

    width: 640
    height: 480

    visible: true
    title: Qt.application.displayName

    LayoutMirroring.enabled: true // NOTE (SAVIZ): Usually, a check against: 'Qt.application.layoutDirection === Qt.RightToLeft' is better.
    LayoutMirroring.childrenInherit: true

    Database {
        id: mainDatabase

        Component.onDestruction: {
            mainDatabase.cutConnection();
        }
    }

    UFOToast {
        id: mainToast

        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 0.5
        z: 1

        Connections {
            target: mainDatabase

            function onStartedConnecting() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست اتصال شروع شد");
            }

            function onFinishedConnecting(status: int, message: string) {
                switch(status) {
                // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedCreatingPatient() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست ایجاد پرونده بیمار ارسال شد");
            }

            function onFinishedCreatingPatient(status: int, message: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedFinding() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست جستجوی بیمار/بیماران ارسال شد");
            }

            function onFinishedFinding(status: int, message: string, data) {
                switch(status) {
                // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedCreatingStarredPatient() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست ستاره دار کردن بیمار ارسال شد");
            }

            function onFinishedCreatingStarredPatient(status: int, message: string, starredPatient) {
                switch(status) {
                // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message + "." + " " + "لطفلا لیست را آپدیت کنید");
                    break;
                default:
                    break;
                }
            }

            function onStartedGettingAllStarredPatients() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست گرفتن بیماران ستاره دار ارسال شد");
            }

            function onFinishedGettingAllStarredPatients(status: int, message: string, data) {
                switch(status) {
                // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedRemovingAllStarredPatients() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست حذف همه بیماران ستاره دار ارسال شد");
            }

            function onFinishedRemovingAllStarredPatients(status: int, message: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedUpdatingStarredPatientVisitStatus() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست تغییر وضعیت ویزیت ارسال شد");
            }

            function onFinishedUpdatingStarredPatientVisitStatus(status: int, message: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedUpdatingPatientBasicInformation() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست آپدیت اطلاعات اولیه بیمار ارسال شد");
            }

            function onFinishedUpdatingPatientBasicInformation(status: int, message: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedUpdatingPatientVisitInformation() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست آپدیت اطلاعات ویزیت بیمار ارسال شد");
            }

            function onFinishedUpdatingPatientVisitInformation(status: int, message: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedUpdatingPatientPaymentInformation() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست آپدیت اطلاعات پرداخت بیمار ارسال شد");
            }

            function onFinishedUpdatingPatientPaymentInformation(status: int, message: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedInsertingPatientDiagnosis() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست برای درج تشخیص ارسال شد");
            }

            function onFinishedInsertingPatientDiagnosis(status: int, message: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedRemovingPatientDiagnosis() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست حذف تشخیص ارسال شد");
            }

            function onFinishedRemovingPatientDiagnosis(status: int, message: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedUpdatingPatientDiagnosesNote() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست آپدیت متن یادداشت تشخیص ارسال شد");
            }

            function onFinishedUpdatingPatientDiagnosesNote(status: int, message: string, note: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedInsertingPatientTreatment() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست برای درج درمان ارسال شد");
            }

            function onFinishedInsertingPatientTreatment(status: int, message: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedRemovingPatientTreatment() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست حذف درمان ارسال شد");
            }

            function onFinishedRemovingPatientTreatment(status: int, message: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedUpdatingPatientTreatmentsNote() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست آپدیت متن یادداشت درمان ارسال شد");
            }

            function onFinishedUpdatingPatientTreatmentsNote(status: int, message: string, note: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedInsertingPatientProcedure() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست برای درج پروسیجر ارسال شد");
            }

            function onFinishedInsertingPatientProcedure(status: int, message: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedRemovingPatientProcedure() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست حذف پروسیجر ارسال شد");
            }

            function onFinishedRemovingPatientProcedure(status: int, message: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedUpdatingPatientProcedureFee() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست آپدیت هزینه پروسیجر ارسال شد");
            }

            function onFinishedUpdatingPatientProcedureFee(status: int, message: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedUpdatingPatientProceduresNote() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست آپدیت متن یادداشت پروسیجر ارسال شد");
            }

            function onFinishedUpdatingPatientProceduresNote(status: int, message: string, note: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedInsertingPatientConsultation() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست برای درج مشاوره ارسال شد");
            }

            function onFinishedInsertingPatientConsultation(status: int, message: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedRemovingPatientConsultation() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست حذف مشاوره ارسال شد");
            }

            function onFinishedRemovingPatientConsultation(status: int, message: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedUpdatingPatientConsultationDateAndOutcome() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست آپدیت اطلاعات مشاوره ارسال شد");
            }

            function onFinishedUpdatingPatientConsultationDateAndOutcome(status: int, message: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedInsertingPatientLabTest() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست درج آزمایش ارسال شد");
            }

            function onFinishedInsertingPatientLabTest(status: int, message: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedRemovingPatientLabTest() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست حذف آزمایش ارسال شد");
            }

            function onFinishedRemovingPatientLabTest(status: int, message: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedUpdatingPatientLabTest() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست آپدیت آزمایش ارسال شد");
            }

            function onFinishedUpdatingPatientLabTest(status: int, message: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedInsertingPatientImage() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست درج تصویر ارسال شد");
            }

            function onFinishedInsertingPatientImage(status: int, message: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedRemovingPatientImage() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست حذف تصویر ارسال شد");
            }

            function onFinishedRemovingPatientImage(status: int, message: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }

            function onStartedUpdatingPatientImageName() {
                mainToast.displayMessage(UFOToast.Status.Info, "درخواست آپدیت نام تصویر ارسال شد");
            }

            function onFinishedUpdatingPatientImageName(status: int, message: string) {
                switch(status) {
                    // Operation finished on fail
                case -2:
                    mainToast.displayMessage(UFOToast.Status.Error, message);
                    break;
                    // Operation finished on warning
                case -1:
                    mainToast.displayMessage(UFOToast.Status.Warning, message);
                    break;
                    // Operation finished on success
                case 1:
                    mainToast.displayMessage(UFOToast.Status.Success, message);
                    break;
                default:
                    break;
                }
            }
        }

        Connections {
            target: mainEditPage

            function onStartedLoadingPatientForEditing() {
                mainToast.displayMessage(UFOToast.Status.Info, "فرآیند باز کردن بیمار برای ویرایش آغاز شد.");
            }

            function onFinishedLoadingPatientForEditing(isSuccessful: bool) {
                if(isSuccessful) {
                    mainToast.displayMessage(UFOToast.Status.Success, "بیمار با موفقیت برای ویرایش باز شد.");

                    return;
                }

                mainToast.displayMessage(UFOToast.Status.Error, "به دلیل خطاهای پایگاه داده، بیمار برای ویرایش باز نشد. لطفاً دوباره سعی کنید بیمار را برای ویرایش باز کنید.");
            }
        }
    }

    UFODialog {
        id: mainDialog

        spacing: 10
        anchors.centerIn: parent
    }

    footer: UFOStatusBar {
        id: mainStatusBar

        height: 30

        Connections {
            target: mainDatabase

            // NOTE (SAVIZ): When operations finish, we display the message regardless of the outcome.

            function onStartedConnecting() {
                mainStatusBar.displayMessage("درخواست اتصال شروع شد");
            }

            function onFinishedConnecting(status: int, message: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedCreatingPatient() {
                mainStatusBar.displayMessage("درخواست ایجاد پرونده بیمار ارسال شد");
            }

            function onFinishedCreatingPatient(status: int, message: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedFinding() {
                mainStatusBar.displayMessage("درخواست جستجوی بیمار/بیماران ارسال شد");
            }

            function onFinishedFinding(status: int, message: string, data) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedCreatingStarredPatient() {
                mainStatusBar.displayMessage("درخواست ستاره دار کردن بیمار ارسال شد");
            }

            function onFinishedCreatingStarredPatient(status: int, message: string, starredPatient) {
                if(status === 1) {
                    mainStatusBar.displayMessage(message + "." + " " + "لطفلا لیست را آپدیت کنید");

                    return;
                }

                mainStatusBar.displayMessage(message);
            }

            function onStartedGettingAllStarredPatients() {
                mainStatusBar.displayMessage("درخواست گرفتن بیماران ستاره دار ارسال شد");
            }

            function onFinishedGettingAllStarredPatients(status: int, message: string, data) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedRemovingAllStarredPatients() {
                mainStatusBar.displayMessage("درخواست حذف همه بیماران ستاره دار ارسال شد");
            }

            function onFinishedRemovingAllStarredPatients(status: int, message: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedUpdatingStarredPatientVisitStatus() {
                mainStatusBar.displayMessage("درخواست تغییر وضعیت ویزیت ارسال شد");
            }

            function onFinishedUpdatingStarredPatientVisitStatus(status: int, message: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedUpdatingPatientBasicInformation() {
                mainStatusBar.displayMessage("درخواست آپدیت اطلاعات اولیه بیمار ارسال شد");
            }

            function onFinishedUpdatingPatientBasicInformation(status: int, message: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedUpdatingPatientVisitInformation() {
                mainStatusBar.displayMessage("درخواست آپدیت اطلاعات ویزیت بیمار ارسال شد");
            }

            function onFinishedUpdatingPatientVisitInformation(status: int, message: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedUpdatingPatientPaymentInformation() {
                mainStatusBar.displayMessage("درخواست آپدیت اطلاعات پرداخت بیمار ارسال شد");
            }

            function onFinishedUpdatingPatientPaymentInformation(status: int, message: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedInsertingPatientDiagnosis() {
                mainStatusBar.displayMessage("درخواست برای درج تشخیص ارسال شد");
            }

            function onFinishedInsertingPatientDiagnosis(status: int, message: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedRemovingPatientDiagnosis() {
                mainStatusBar.displayMessage("درخواست حذف تشخیص ارسال شد");
            }

            function onFinishedRemovingPatientDiagnosis(status: int, message: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedUpdatingPatientDiagnosesNote() {
                mainStatusBar.displayMessage("درخواست آپدیت متن یادداشت تشخیص ارسال شد");
            }

            function onFinishedUpdatingPatientDiagnosesNote(status: int, message: string, note: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedInsertingPatientTreatment() {
                mainStatusBar.displayMessage("درخواست برای درج درمان ارسال شد");
            }

            function onFinishedInsertingPatientTreatment(status: int, message: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedRemovingPatientTreatment() {
                mainStatusBar.displayMessage("درخواست حذف درمان ارسال شد");
            }

            function onFinishedRemovingPatientTreatment(status: int, message: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedUpdatingPatientTreatmentsNote() {
                mainStatusBar.displayMessage("درخواست آپدیت متن یادداشت درمان ارسال شد");
            }

            function onFinishedUpdatingPatientTreatmentsNote(status: int, message: string, note: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedInsertingPatientProcedure() {
                mainStatusBar.displayMessage("درخواست برای درج پروسیجر ارسال شد");
            }

            function onFinishedInsertingPatientProcedure(status: int, message: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedRemovingPatientProcedure() {
                mainStatusBar.displayMessage("درخواست حذف پروسیجر ارسال شد");
            }

            function onFinishedRemovingPatientProcedure(status: int, message: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedUpdatingPatientProcedureFee() {
                mainStatusBar.displayMessage("درخواست آپدیت هزینه پروسیجر ارسال شد");
            }

            function onFinishedUpdatingPatientProcedureFee(status: int, message: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedUpdatingPatientProceduresNote() {
                mainStatusBar.displayMessage("درخواست آپدیت متن یادداشت پروسیجر ارسال شد");
            }

            function onFinishedUpdatingPatientProceduresNote(status: int, message: string, note: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedInsertingPatientConsultation() {
                mainStatusBar.displayMessage("درخواست برای درج مشاوره ارسال شد");
            }

            function onFinishedInsertingPatientConsultation(status: int, message: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedRemovingPatientConsultation() {
                mainStatusBar.displayMessage("درخواست حذف مشاوره ارسال شد");
            }

            function onFinishedRemovingPatientConsultation(status: int, message: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedUpdatingPatientConsultationDateAndOutcome() {
                mainStatusBar.displayMessage("درخواست آپدیت اطلاعات مشاوره ارسال شد");
            }

            function onFinishedUpdatingPatientConsultationDateAndOutcome(status: int, message: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedInsertingPatientLabTest() {
                mainStatusBar.displayMessage("درخواست درج آزمایش ارسال شد");
            }

            function onFinishedInsertingPatientLabTest(status: int, message: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedRemovingPatientLabTest() {
                mainStatusBar.displayMessage("درخواست حذف آزمایش ارسال شد");
            }

            function onFinishedRemovingPatientLabTest(status: int, message: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedUpdatingPatientLabTest() {
                mainStatusBar.displayMessage("درخواست آپدیت آزمایش ارسال شد");
            }

            function onFinishedUpdatingPatientLabTest(status: int, message: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedInsertingPatientImage() {
                mainStatusBar.displayMessage("درخواست درج تصویر ارسال شد");
            }

            function onFinishedInsertingPatientImage(status: int, message: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedRemovingPatientImage() {
                mainStatusBar.displayMessage("درخواست حذف تصویر ارسال شد");
            }

            function onFinishedRemovingPatientImage(status: int, message: string) {
                mainStatusBar.displayMessage(message);
            }

            function onStartedUpdatingPatientImageName() {
                mainStatusBar.displayMessage("درخواست آپدیت نام تصویر ارسال شد");
            }

            function onFinishedUpdatingPatientImageName(status: int, message: string) {
                mainStatusBar.displayMessage(message);
            }
        }

        Connections {
            target: mainEditPage

            function onStartedLoadingPatientForEditing() {
                mainStatusBar.displayMessage("فرآیند باز کردن بیمار برای ویرایش آغاز شد.");
            }

            function onFinishedLoadingPatientForEditing(isSuccessful: bool) {
                if(isSuccessful) {
                    mainStatusBar.displayMessage("بیمار با موفقیت برای ویرایش باز شد.");

                    return;
                }

                mainStatusBar.displayMessage("به دلیل خطاهای پایگاه داده، بیمار برای ویرایش باز نشد. لطفاً دوباره سعی کنید بیمار را برای ویرایش باز کنید.");
            }
        }
    }

    RowLayout {
        anchors.fill: parent

        spacing: 0
        z: 0

        UFOSideBar {
            id: mainSideBar

            Layout.preferredWidth: 200
            Layout.fillHeight: true
        }

        StackLayout {
            id: mainStackLayout

            Layout.fillWidth: true
            Layout.fillHeight: true

            currentIndex: 4

            StarPage {
                id: mainStarPage

                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            SearchPage {
                id: mainSearchPage

                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            EditPage {
                id: mainEditPage

                Layout.fillWidth: true
                Layout.fillHeight: true

                Connections {
                    target: mainSearchPage

                    function onPatientSelectedForEdit(patientID: int) {
                        mainEditPage.loadPatient(patientID);
                    }
                }

                Connections {
                    target: mainStarPage

                    function onPatientSelectedForEdit(patientID: int) {
                        mainEditPage.loadPatient(patientID);
                    }
                }
            }

            CreatePage {
                id: mainCreatePage

                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            SettingsPage {
                id: mainSettingsPage

                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            AboutPage {
                id: mainAboutPage

                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            Connections {
                target: mainSideBar

                function onTabSelected(index: int) {
                    mainStackLayout.currentIndex = index;
                }
            }

            Connections {
                target: mainEditPage

                function onFinishedLoadingPatientForEditing(isSuccessful: bool) {
                    if(isSuccessful) {
                        mainStackLayout.currentIndex = 2;
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        mainToast.displayMessage(UFOToast.Status.Warning, "قبل از انجام هر کاری، لطفاً از اتصال به پایگاه داده در صفحه تنظیمات اطمینان حاصل کنید.");
        mainStatusBar.displayMessage("قبل از انجام هر کاری، لطفاً از اتصال به پایگاه داده در صفحه تنظیمات اطمینان حاصل کنید.");
    }
}
