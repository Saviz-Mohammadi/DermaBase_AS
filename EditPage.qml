import QtCore
import QtQuick
import QtQuick.Controls.impl
import QtQuick.Controls.Basic
import QtQuick.Layouts
import QtQuick.Dialogs

Item {
    id: root

    signal startedLoadingPatientForEditing();
    signal finishedLoadingPatientForEditing(isSuccessful: bool);

    property int topMargin: 15
    property int bottomMargin: 15
    property int rightMargin: 15
    property int leftMargin: 15
    property int spacing: 10
    property real titleFontSizeScalar: 2

    function loadPatient(patientID: int) {
        root.startedLoadingPatientForEditing();

        mainDatabase.getPatientBasicInformation(patientID);

        qtObjectEditInformation.patientID = patientID;
    }

    function performEvaluation() {
        let totalCallsRequired = 1;
        let totalSuccessesRequired = 1;

        if(qtObjectEditInformation.countOfCallsCompleted !== totalCallsRequired) {
            return;
        }

        // If all calls are successful:
        if(qtObjectEditInformation.countOfCallsSucceeded === totalSuccessesRequired) {
            root.resetCounters();

            root.finishedLoadingPatientForEditing(true);

            return;
        }

        // Reset:
        root.resetCounters();

        root.finishedLoadingPatientForEditing(false);
    }

    function resetCounters() {
        qtObjectEditInformation.countOfCallsCompleted = 0;
        qtObjectEditInformation.countOfCallsSucceeded = 0;
    }

    QtObject {
        id: qtObjectEditInformation

        property int countOfCallsCompleted: 0
        property int countOfCallsSucceeded: 0
        property int patientID: -1
    }

    // NOTE (SAVIZ): In my opinnion, when it comes to loading the data we don't really need to notify the start of every retrieval since that would be insane. I think the best approach is to only notify the user if something went wrong that requires us to note about.
    Connections {
        target: mainDatabase

        // NOTE (SAVIZ): We do not require any additional parameters for checking the outcome:
        function onFinishedGettingPatientBasicInformation(status: int, message: string, firstName: string, lastName: string, birthYear: int, phoneNumber: string, email: string, gender: string, maritalStatus: string) {
            qtObjectEditInformation.countOfCallsCompleted += 1;

            if(status === 1) {
                qtObjectEditInformation.countOfCallsSucceeded += 1;
            }

            root.performEvaluation();
        }
    }

    ScrollView {
        id: scrollView

        anchors.fill: parent

        contentWidth: -1
        contentHeight: columnLayout.implicitHeight + root.topMargin + root.bottomMargin
        ScrollBar.horizontal.policy: ScrollBar.AsNeeded
        ScrollBar.vertical.policy: ScrollBar.AsNeeded

        background: Rectangle {
            id: rectangleBackground

            radius: 0
            color: AppTheme.getColor(AppTheme.Colors.PageBackground)
        }

        Item {
            anchors.fill: parent
            anchors.topMargin: root.topMargin
            anchors.bottomMargin: root.bottomMargin
            anchors.rightMargin: root.rightMargin
            anchors.leftMargin: root.leftMargin

            ColumnLayout {
                id: columnLayout

                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left

                clip: false
                spacing: root.spacing

                RowLayout {
                    Layout.fillWidth: true
                    Layout.bottomMargin: 40

                    spacing: 10

                    IconLabel {
                        Layout.preferredHeight: 40

                        icon.width: 32
                        icon.height: 32
                        icon.source: "qrc:/resources/icons/material/person_edit.svg"
                        icon.color: AppTheme.getColor(AppTheme.Colors.PageIcon)
                    }

                    Text {
                        Layout.preferredHeight: 40

                        color: AppTheme.getColor(AppTheme.Colors.PageText)
                        elide: Text.ElideRight
                        font.pixelSize: Qt.application.font.pixelSize * root.titleFontSizeScalar
                        text: qsTr("ویرایش بیمار")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignTop
                        wrapMode: Text.NoWrap
                    }
                }

                RowLayout {
                    Layout.fillWidth: true
                    Layout.bottomMargin: 40

                    Text {
                        id: textPatientTitle

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        font.pixelSize: Qt.application.font.pixelSize * 1.3
                        text: qsTr("هیچ بیماری انتخاب نشده است")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.Wrap
                    }

                    Item {
                        Layout.fillWidth: true
                    }

                    Connections {
                        target: mainDatabase

                        function onFinishedGettingPatientBasicInformation(status: int, message: string, firstName: string, lastName: string, birthYear: int, phoneNumber: string, email: string, gender: string, maritalStatus: string) {
                            if(status === 1) {
                                textPatientTitle.text = qtObjectEditInformation.patientID + " | " + firstName + " " + lastName;
                            }
                        }

                        function onFinishedUpdatingPatientBasicInformation(status: int, message: string) {
                            if(status === 1) {
                                textPatientTitle.text = qtObjectEditInformation.patientID + " | " + textFieldFirstName.text + " " + textFieldLastName.text;
                            }
                        }
                    }
                }

                UFOSection {
                    id: sectionPatientBasicInformation

                    Layout.fillWidth: true

                    startCollapsed: true
                    enabled: false
                    title: qsTr("اطلاعات پایه بیمار")

                    Connections {
                        target: root

                        function onFinishedLoadingPatientForEditing(isSuccessful: bool) {
                            sectionPatientBasicInformation.enabled = isSuccessful;
                        }
                    }

                    Text {
                        Layout.fillWidth: true
                        Layout.bottomMargin: 20

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("برای ویرایش اطلاعات پایه بیمار می‌توان از فیلدهای زیر استفاده کرد.")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.Wrap
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("نام")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.NoWrap
                    }

                    UFOTextField {
                        id: textFieldFirstName

                        Layout.preferredWidth: 250
                        Layout.preferredHeight: 35

                        horizontalAlignment: TextInput.AlignLeft
                        validator: RegularExpressionValidator {
                            regularExpression: /^[\p{L}]+(?:[ '\-][\p{L}]+)*$/u
                        }

                        Connections {
                            target: mainDatabase

                            function onFinishedGettingPatientBasicInformation(status: int, message: string, firstName: string, lastName: string, birthYear: int, phoneNumber: string, email: string, gender: string, maritalStatus: string) {
                                if(status === 1) {
                                    textFieldFirstName.text = firstName;
                                }
                            }
                        }
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("نام خانوادگی")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.NoWrap
                    }

                    UFOTextField {
                        id: textFieldLastName

                        Layout.preferredWidth: 250
                        Layout.preferredHeight: 35

                        horizontalAlignment: TextInput.AlignLeft
                        validator: RegularExpressionValidator {
                            regularExpression: /^[\p{L}]+(?: [\p{L}]+)*$/u
                        }

                        Connections {
                            target: mainDatabase

                            function onFinishedGettingPatientBasicInformation(status: int, message: string, firstName: string, lastName: string, birthYear: int, phoneNumber: string, email: string, gender: string, maritalStatus: string) {
                                if(status === 1) {
                                    textFieldLastName.text = lastName;
                                }
                            }
                        }
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("سال تولد")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.NoWrap
                    }

                    UFOTextField {
                        id: textFieldBirthYear

                        Layout.preferredWidth: 250
                        Layout.preferredHeight: 35

                        horizontalAlignment: TextInput.AlignLeft
                        validator: IntValidator {
                            top: 9999
                            bottom: 0
                        }

                        Connections {
                            target: mainDatabase

                            function onFinishedGettingPatientBasicInformation(status: int, message: string, firstName: string, lastName: string, birthYear: int, phoneNumber: string, email: string, gender: string, maritalStatus: string) {
                                if(status === 1) {
                                    textFieldBirthYear.text = birthYear;
                                }
                            }
                        }
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("شماره تلفن")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.NoWrap
                    }

                    UFOTextField {
                        id: textFieldPhoneNumber

                        Layout.preferredWidth: 250
                        Layout.preferredHeight: 35

                        horizontalAlignment: TextInput.AlignLeft
                        validator: RegularExpressionValidator {
                            regularExpression: /^[0-9][0-9]{1,14}$/
                        }

                        Connections {
                            target: mainDatabase

                            function onFinishedGettingPatientBasicInformation(status: int, message: string, firstName: string, lastName: string, birthYear: int, phoneNumber: string, email: string, gender: string, maritalStatus: string) {
                                if(status === 1) {
                                    textFieldPhoneNumber.text = phoneNumber;
                                }
                            }
                        }
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("آدرس ایمیل")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.NoWrap
                    }

                    UFOTextField {
                        id: textFieldEmail

                        Layout.preferredWidth: 250
                        Layout.preferredHeight: 35

                        horizontalAlignment: TextInput.AlignLeft
                        validator: RegularExpressionValidator {
                            regularExpression: /^[^\s@]+@[^\s@]+\.com$/
                        }

                        Connections {
                            target: mainDatabase

                            function onFinishedGettingPatientBasicInformation(status: int, message: string, firstName: string, lastName: string, birthYear: int, phoneNumber: string, email: string, gender: string, maritalStatus: string) {
                                if(status === 1) {
                                    textFieldEmail.text = email;
                                }
                            }
                        }
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("جنسیت")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.NoWrap
                    }

                    UFOComboBox {
                        id: comboBoxGender

                        Layout.preferredWidth: 250
                        Layout.preferredHeight: 35

                        currentIndex: 0
                        model: ["نامشخص", "مرد", "زن"]

                        Connections {
                            target: mainDatabase

                            function onFinishedGettingPatientBasicInformation(status: int, message: string, firstName: string, lastName: string, birthYear: int, phoneNumber: string, email: string, gender: string, maritalStatus: string) {
                                if(status === 1) {
                                    switch (gender) {
                                    case "نامشخص":
                                        comboBoxGender.currentIndex = 0;
                                        break;
                                    case "مرد":
                                        comboBoxGender.currentIndex = 1;
                                        break;
                                    case "زن":
                                        comboBoxGender.currentIndex = 2;
                                        break;
                                    default:
                                        break;
                                    };
                                }
                            }
                        }
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("وضعیت تاهل")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.NoWrap
                    }

                    UFOComboBox {
                        id: comboBoxMaritalStatus

                        Layout.preferredWidth: 250
                        Layout.preferredHeight: 35

                        currentIndex: 0
                        model: ["نامشخص", "مجرد", "متاهل"]

                        Connections {
                            target: mainDatabase

                            function onFinishedGettingPatientBasicInformation(status: int, message: string, firstName: string, lastName: string, birthYear: int, phoneNumber: string, email: string, gender: string, maritalStatus: string) {
                                if(status === 1) {
                                    switch (gender) {
                                    case "نامشخص":
                                        comboBoxMaritalStatus.currentIndex = 0;
                                        break;
                                    case "مجرد":
                                        comboBoxMaritalStatus.currentIndex = 1;
                                        break;
                                    case "متاهل":
                                        comboBoxMaritalStatus.currentIndex = 2;
                                        break;
                                    default:
                                        break;
                                    };
                                }
                            }
                        }
                    }

                    UFOButton {
                        id: buttonUpdatePatientBasicInformation

                        Layout.preferredWidth: 120
                        Layout.preferredHeight: 35
                        Layout.topMargin: 20

                        display: AbstractButton.TextBesideIcon
                        text: qsTr("ذخیره کردن")
                        icon.source: "qrc:/resources/icons/material/save.svg"

                        onClicked: {
                            if (!textFieldFirstName.acceptableInput) {
                                mainDialog.title = qsTr("ورودی ارائه شده به قسمت ورودی نام صحیح نیست.") + "\n" + qsTr("لطفاً قبل از ادامه نام صحیح را وارد کنید.");
                                mainDialog.identifier = "Edit";
                                mainDialog.standardButtons = Dialog.Ok;
                                mainDialog.modal = true;
                                mainDialog.open();

                                return;
                            }

                            if (!textFieldLastName.acceptableInput) {
                                mainDialog.title = qsTr("ورودی ارائه شده به قسمت ورودی نام خانوادگی صحیح نیست.") + "\n" + qsTr("لطفاً قبل از ادامه نام خانوادگی صحیح را وارد کنید.");
                                mainDialog.identifier = "Edit";
                                mainDialog.standardButtons = Dialog.Ok;
                                mainDialog.modal = true;
                                mainDialog.open();

                                return;
                            }

                            if (!textFieldBirthYear.acceptableInput) {
                                mainDialog.title = qsTr("ورودی ارائه شده به فیلد ورودی سال تولد صحیح نیست.") + "\n" + qsTr("لطفاً قبل از ادامه، سال تولد صحیح را ارائه دهید.");
                                mainDialog.identifier = "Edit";
                                mainDialog.standardButtons = Dialog.Ok;
                                mainDialog.modal = true;
                                mainDialog.open();

                                return;
                            }

                            if (!textFieldPhoneNumber.acceptableInput) {
                                mainDialog.title = qsTr("ورودی ارائه شده به قسمت ورودی شماره تلفن صحیح نیست.") + "\n" + qsTr("لطفاً قبل از ادامه یک شماره تلفن صحیح ارائه دهید.");
                                mainDialog.identifier = "Edit";
                                mainDialog.standardButtons = Dialog.Ok;
                                mainDialog.modal = true;
                                mainDialog.open();

                                return;
                            }

                            if (textFieldEmail.text !== "" && !textFieldEmail.acceptableInput) {
                                mainDialog.title = qsTr("ورودی ارائه شده به قسمت ورودی آدرس ایمیل صحیح نیست.") + "\n" + qsTr("لطفا قبل از ادامه یک آدرس ایمیل صحیح وارد کنید.");
                                mainDialog.identifier = "Edit";
                                mainDialog.standardButtons = Dialog.Ok;
                                mainDialog.modal = true;
                                mainDialog.open();

                                return;
                            }

                            let newFirstName = textFieldFirstName.text;
                            let newLastName = textFieldLastName.text;
                            let newBirthYear = parseInt(textFieldBirthYear.text, 10);
                            let newPhoneNumber = textFieldPhoneNumber.text;
                            let newEmail = textFieldEmail.text;
                            let newGender = comboBoxGender.currentText;
                            let newMaritalStatus = comboBoxMaritalStatus.currentText;

                            mainDatabase.updatePatientBasicInformation(
                                qtObjectEditInformation.patientID,
                                newFirstName,
                                newLastName,
                                newBirthYear,
                                newPhoneNumber,
                                newEmail,
                                newGender,
                                newMaritalStatus
                            );
                        }

                        Connections {
                            target: mainDatabase

                            function onStartedUpdatingPatientBasicInformation() {
                                buttonUpdatePatientBasicInformation.enabled = false;
                            }

                            function onFinishedUpdatingPatientBasicInformation(status: int, message: string) {
                                buttonUpdatePatientBasicInformation.enabled = true;
                            }
                        }
                    }
                }
            }
        }
    }
}
