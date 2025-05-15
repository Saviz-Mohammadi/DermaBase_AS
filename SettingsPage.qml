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

    QtObject {
        id: qtObjectProperties

        property string ipAddress: ""
        property int portNumber: 0
        property string schema: ""
        property string username: ""
        property string password: ""
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
                        icon.source: "qrc:/resources/icons/material/settings.svg"
                        icon.color: AppTheme.getColor(AppTheme.Colors.PageIcon)
                    }

                    Text {
                        Layout.preferredHeight: 40

                        color: AppTheme.getColor(AppTheme.Colors.PageText)
                        elide: Text.ElideRight
                        font.pixelSize: Qt.application.font.pixelSize * root.titleFontSizeScalar
                        text: qsTr("تنظیمات برنامه")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignTop
                        wrapMode: Text.NoWrap
                    }
                }

                UFOSection {
                    Layout.fillWidth: true

                    title: qsTr("ظاهر")

                    Text {
                        Layout.fillWidth: true
                        Layout.bottomMargin: 20

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("جدیدترین تم انتخاب شده به طور خودکار در راه اندازی برنامه ذخیره و بارگذاری می شود.")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.Wrap
                    }

                    UFOComboBox {
                        id: comboBoxTheme

                        Layout.preferredWidth: 250
                        Layout.preferredHeight: 35

                        model: ListModel {
                            id: listModel

                            ListElement {name: "UFOLight"}
                            ListElement {name: "UFODark"}
                        }

                        textRole: "name"

                        onCurrentIndexChanged: {
                            let currentElement = listModel.get(comboBoxTheme.currentIndex);

                            if (currentElement.name === "UFOLight") {
                                AppTheme.setTheme(AppTheme.Themes.UFOLight);
                                return;
                            }

                            if (currentElement.name === "UFODark") {
                                AppTheme.setTheme(AppTheme.Themes.UFODark);
                                return;
                            }
                        }

                        Component.onCompleted: {
                            if(AppSettings.currentTheme === undefined) {
                                comboBoxTheme.current = 0;
                                return;
                            }

                            switch(AppSettings.currentTheme) {
                            case AppTheme.Themes.UFOLight:
                                comboBoxTheme.currentIndex = 0;
                                break;
                            case AppTheme.Themes.UFODark:
                                comboBoxTheme.currentIndex = 1;
                                break;
                            default:
                                break;
                            }
                        }
                    }
                }

                UFOSection {
                    Layout.fillWidth: true

                    title: qsTr("پایگاه داده")

                    Text {
                        Layout.fillWidth: true
                        Layout.bottomMargin: 20

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("برنامه برای تعامل با پایگاه داده به اطلاعات اولیه نیاز دارد. برای ارائه اطلاعات لازم از فیلدهای ورودی زیر استفاده کنید. جدیدترین اطلاعات توسط برنامه ذخیره می شود.")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.Wrap
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("آدرس آی پی")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.NoWrap
                    }

                    UFOTextField {
                        id: textFieldIP

                        Layout.preferredWidth: 250
                        Layout.preferredHeight: 35

                        text: qtObjectProperties.ipAddress
                        horizontalAlignment: TextInput.AlignLeft
                        validator: RegularExpressionValidator {
                            regularExpression: /^((25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])\.){3}(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])$/
                        }
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("شماره پورت")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.NoWrap
                    }

                    UFOTextField {
                        id: textFieldPort

                        Layout.preferredWidth: 250
                        Layout.preferredHeight: 35

                        text: qtObjectProperties.portNumber
                        horizontalAlignment: TextInput.AlignLeft
                        validator: IntValidator {
                            top: 65535
                            bottom: 0
                        }
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("نام پایگاه داده")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.NoWrap
                    }

                    UFOTextField {
                        id: textFieldSchema

                        Layout.preferredWidth: 250
                        Layout.preferredHeight: 35

                        text: qtObjectProperties.schema
                        horizontalAlignment: TextInput.AlignLeft
                        validator: RegularExpressionValidator {
                            regularExpression: /^[A-Za-z]+$/
                        }
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("نام کاربری")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.NoWrap
                    }

                    UFOTextField {
                        id: textFieldUsername

                        Layout.preferredWidth: 250
                        Layout.preferredHeight: 35

                        text: qtObjectProperties.username
                        horizontalAlignment: TextInput.AlignLeft
                        validator: RegularExpressionValidator {
                            regularExpression: /^[A-Za-z]+$/
                        }
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("رمز عبور")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.NoWrap
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        UFOTextField {
                            id: textFieldPassword

                            Layout.preferredWidth: 250
                            Layout.preferredHeight: 35

                            text: qtObjectProperties.password
                            horizontalAlignment: TextInput.AlignLeft
                            echoMode: TextInput.Password
                        }

                        UFOButton {
                            id: buttonTogglePassword

                            Layout.preferredWidth: 120
                            Layout.preferredHeight: 35

                            checkable: true
                            checked: false
                            display: AbstractButton.TextBesideIcon
                            text: checked ? qsTr("پنهان کردن") : qsTr("نشان دادن")
                            icon.source: checked ? "qrc:/resources/icons/material/visibility_off.svg" : "qrc:/resources/icons/material/visibility.svg"
                            onCheckedChanged: {
                                buttonTogglePassword.checked ? textFieldPassword.echoMode = TextInput.Normal : textFieldPassword.echoMode = TextInput.Password
                            }
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        Layout.topMargin: 10

                        UFOButton {
                            id: buttonConnect

                            Layout.preferredWidth: 120
                            Layout.preferredHeight: 35
                            Layout.topMargin: 20

                            display: AbstractButton.TextBesideIcon
                            text: qsTr("تجدید اتصال")
                            icon.source: "qrc:/resources/icons/material/autorenew.svg"

                            onClicked: {
                                if (!textFieldIP.acceptableInput) {
                                    mainDialog.title = qsTr("ورودی ارائه شده به فیلد آدرس IP صحیح نیست.") + "\n" + qsTr("لطفاً قبل از ادامه یک آدرس IP کاملاً صحیح ارائه دهید.");
                                    mainDialog.identifier = "Settings";
                                    mainDialog.standardButtons = Dialog.Ok;
                                    mainDialog.modal = true;
                                    mainDialog.open();

                                    return;
                                }

                                if (!textFieldPort.acceptableInput) {
                                    mainDialog.title = qsTr("ورودی ارائه شده به قسمت شماره پورت صحیح نیست.") + "\n" + qsTr("لطفاً قبل از ادامه، یک شماره پورت کاملاً صحیح ارائه دهید.") + "\n" + qsTr("Max: 65535 | Min: 0");
                                    mainDialog.identifier = "Settings";
                                    mainDialog.standardButtons = Dialog.Ok;
                                    mainDialog.modal = true;
                                    mainDialog.open();

                                    return;
                                }

                                if (!textFieldSchema.acceptableInput) {
                                    mainDialog.title = qsTr("ورودی ارائه شده به فیلد نام پایگاه داده صحیح نیست.") + "\n" + qsTr("لطفاً قبل از ادامه نام پایگاه داده کاملاً صحیح را وارد کنید.");
                                    mainDialog.identifier = "Settings";
                                    mainDialog.standardButtons = Dialog.Ok;
                                    mainDialog.modal = true;
                                    mainDialog.open();

                                    return;
                                }

                                if (!textFieldUsername.acceptableInput) {
                                    mainDialog.title = qsTr("ورودی ارائه شده به قسمت نام کاربری صحیح نیست.") + "\n" + qsTr("لطفاً قبل از ادامه یک نام کاربری کاملاً صحیح وارد کنید.");
                                    mainDialog.identifier = "Settings";
                                    mainDialog.standardButtons = Dialog.Ok;
                                    mainDialog.modal = true;
                                    mainDialog.open();

                                    return;
                                }

                                if (textFieldPassword.text === "") {
                                    mainDialog.title = qsTr("ورودی ارائه شده به قسمت رمز عبور صحیح نیست.") + "\n" + qsTr("لطفا قبل از ادامه یک رمز عبور کاملاً صحیح وارد کنید.");
                                    mainDialog.identifier = "Settings";
                                    mainDialog.standardButtons = Dialog.Ok;
                                    mainDialog.modal = true;
                                    mainDialog.open();

                                    return;
                                }

                                qtObjectProperties.ipAddress = textFieldIP.text;
                                qtObjectProperties.portNumber = parseInt(textFieldPort.text, 10);
                                qtObjectProperties.schema = textFieldSchema.text;
                                qtObjectProperties.username = textFieldUsername.text;
                                qtObjectProperties.password = textFieldPassword.text.trim();

                                mainDatabase.establishConnection(
                                    qtObjectProperties.ipAddress,
                                    qtObjectProperties.portNumber,
                                    qtObjectProperties.schema,
                                    qtObjectProperties.username,
                                    qtObjectProperties.password
                                );
                            }

                            Connections {
                                target: mainDatabase

                                function onStartedConnecting() {
                                    buttonConnect.enabled = false;
                                }

                                function onFinishedConnecting(status: int, message: string) {
                                    buttonConnect.enabled = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        qtObjectProperties.ipAddress = AppSettings.ipAddress;
        qtObjectProperties.portNumber = AppSettings.portNumber;
        qtObjectProperties.schema = AppSettings.schema;
        qtObjectProperties.username = AppSettings.username;
    }

    Component.onDestruction: {
        AppSettings.ipAddress = qtObjectProperties.ipAddress
        AppSettings.portNumber = qtObjectProperties.portNumber
        AppSettings.schema = qtObjectProperties.schema
        AppSettings.username = qtObjectProperties.username
    }
}
