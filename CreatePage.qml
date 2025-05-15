import QtQuick
import QtQuick.Controls.impl
import QtQuick.Controls.Basic
import QtQuick.Layouts

Item {
    id: root

    property int topMargin: 15
    property int bottomMargin: 15
    property int rightMargin: 15
    property int leftMargin: 15
    property int spacing: 10
    property real titleFontSizeScalar: 2

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
                        icon.source: "qrc:/resources/icons/material/person_add.svg"
                        icon.color: AppTheme.getColor(AppTheme.Colors.PageIcon)
                    }

                    Text {
                        Layout.preferredHeight: 40

                        color: AppTheme.getColor(AppTheme.Colors.PageText)
                        elide: Text.ElideRight
                        font.pixelSize: Qt.application.font.pixelSize * root.titleFontSizeScalar
                        text: qsTr("ایجاد بیمار")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignTop
                        wrapMode: Text.NoWrap
                    }
                }

                UFOSection {
                    Layout.fillWidth: true

                    title: qsTr("اطلاعات بیمار")

                    Text {
                        Layout.fillWidth: true
                        Layout.bottomMargin: 20

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("فیلدهایی که با علامت ستاره مشخص شده اند اجباری هستند. لطفاً توجه داشته باشید که اگر سیستم تشخیص دهد که بیمار دیگری با همان نام، نام خانوادگی و تاریخ تولد قبلاً وجود دارد، از ایجاد یک بیمار جدید در پایگاه داده جلوگیری می کند.")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.Wrap
                    }

                    UFOButton {
                        id: buttonClear

                        Layout.preferredWidth: 120
                        Layout.preferredHeight: 35
                        Layout.bottomMargin: 20

                        display: AbstractButton.TextBesideIcon
                        text: qsTr("پاک کردن")
                        icon.source: "qrc:/resources/icons/material/delete.svg"
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("نام*")
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
                            target: buttonClear

                            function onClicked() {
                                textFieldFirstName.clear();
                            }
                        }
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("نام خانوادگی*")
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
                            target: buttonClear

                            function onClicked() {
                                textFieldLastName.clear();
                            }
                        }
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("سال تولد*")
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
                            target: buttonClear

                            function onClicked() {
                                textFieldBirthYear.clear();
                            }
                        }
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("شماره تلفن*")
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
                            target: buttonClear

                            function onClicked() {
                                textFieldPhoneNumber.clear();
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
                            target: buttonClear

                            function onClicked() {
                                textFieldEmail.clear();
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
                            target: buttonClear

                            function onClicked() {
                                comboBoxGender.currentIndex = 0;
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
                            target: buttonClear

                            function onClicked() {
                                comboBoxMaritalStatus.currentIndex = 0;
                            }
                        }
                    }

                    UFOButton {
                        id: buttonCreatePatient

                        Layout.preferredWidth: 120
                        Layout.preferredHeight: 35
                        Layout.topMargin: 20

                        display: AbstractButton.TextBesideIcon
                        text: qsTr("ایجاد بیمار")
                        icon.source: "qrc:/resources/icons/material/person_add.svg"

                        onClicked: {
                            if (!textFieldFirstName.acceptableInput) {
                                mainDialog.title = qsTr("ورودی ارائه شده به قسمت ورودی نام صحیح نیست.") + "\n" + qsTr("لطفاً قبل از ادامه نام صحیح را وارد کنید.");
                                mainDialog.identifier = "Create";
                                mainDialog.standardButtons = Dialog.Ok;
                                mainDialog.modal = true;
                                mainDialog.open();

                                return;
                            }

                            if (!textFieldLastName.acceptableInput) {
                                mainDialog.title = qsTr("ورودی ارائه شده به قسمت ورودی نام خانوادگی صحیح نیست.") + "\n" + qsTr("لطفاً قبل از ادامه نام خانوادگی صحیح را وارد کنید.");
                                mainDialog.identifier = "Create";
                                mainDialog.standardButtons = Dialog.Ok;
                                mainDialog.modal = true;
                                mainDialog.open();

                                return;
                            }

                            if (!textFieldBirthYear.acceptableInput) {
                                mainDialog.title = qsTr("ورودی ارائه شده به فیلد ورودی سال تولد صحیح نیست.") + "\n" + qsTr("لطفاً قبل از ادامه، سال تولد صحیح را ارائه دهید.");
                                mainDialog.identifier = "Create";
                                mainDialog.standardButtons = Dialog.Ok;
                                mainDialog.modal = true;
                                mainDialog.open();

                                return;
                            }

                            if (!textFieldPhoneNumber.acceptableInput) {
                                mainDialog.title = qsTr("ورودی ارائه شده به قسمت ورودی شماره تلفن صحیح نیست.") + "\n" + qsTr("لطفاً قبل از ادامه یک شماره تلفن صحیح ارائه دهید.");
                                mainDialog.identifier = "Create";
                                mainDialog.standardButtons = Dialog.Ok;
                                mainDialog.modal = true;
                                mainDialog.open();

                                return;
                            }

                            if (textFieldEmail.text !== "" && !textFieldEmail.acceptableInput) {
                                mainDialog.title = qsTr("ورودی ارائه شده به قسمت ورودی آدرس ایمیل صحیح نیست.") + "\n" + qsTr("لطفا قبل از ادامه یک آدرس ایمیل صحیح وارد کنید.");
                                mainDialog.identifier = "Create";
                                mainDialog.standardButtons = Dialog.Ok;
                                mainDialog.modal = true;
                                mainDialog.open();

                                return;
                            }

                            let firstName = textFieldFirstName.text;
                            let lastName = textFieldLastName.text;
                            let birthYear = parseInt(textFieldBirthYear.text, 10);
                            let phoneNumber = textFieldPhoneNumber.text;
                            let email = textFieldEmail.text;
                            let gender = comboBoxGender.currentText;
                            let maritalStatus = comboBoxMaritalStatus.currentText;

                            mainDatabase.createPatient(
                                firstName,
                                lastName,
                                birthYear,
                                phoneNumber,
                                email,
                                gender,
                                maritalStatus
                            );
                        }

                        Connections {
                            target: mainDatabase

                            function onStartedCreatingPatient() {
                                buttonCreatePatient.enabled = false;
                            }

                            function onFinishedCreatingPatient(status: int, message: string) {
                                buttonCreatePatient.enabled = true;
                            }
                        }
                    }
                }
            }
        }
    }
}
