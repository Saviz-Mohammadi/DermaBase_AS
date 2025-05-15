import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import QtQuick.Dialogs
import QtCore

// Local QML:
import "./../basic"
import "./../custom"

// Custom CPP Registered Types
import AppTheme 1.0
import Database 1.0
import Printer 1.0

UFO_Page {
    id: root

    title: qsTr("چاپ")
    contentSpacing: 25

    UFO_GroupBox {
        Layout.fillWidth: true
        // NOTE (SAVIZ): No point using "Layout.fillHeight" as "UFO_Page" ignores height to enable vertical scrolling.

        title: qsTr("بیمار")
        contentSpacing: 0

        Text {
            Layout.fillWidth: true
            Layout.margins: 15

            text: qsTr("توجه داشته باشید که جدیدترین داده‌ها مستقیماً از پایگاه داده بازیابی می‌شوند. بنابراین، هر تغییری باید قبل از چاپ به پایگاه داده ارسال شود.")
            elide: Text.ElideRight
            wrapMode: Text.NoWrap
            verticalAlignment: Text.AlignVCenter
            color: Qt.color(AppTheme.colors["UFO_GroupBox_Content_Text"])
            font.pixelSize: Qt.application.font.pixelSize * 1
        }

        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 15

            Text {
                Layout.fillWidth: true

                text: qsTr("شماره پرونده")
                elide: Text.ElideRight
                wrapMode: Text.NoWrap
                verticalAlignment: Text.AlignBottom
                color: Qt.color(AppTheme.colors["UFO_GroupBox_Content_Text"])
                font.pixelSize: Qt.application.font.pixelSize * 1
            }

            UFO_TextField {
                id: textField_PatientID

                Layout.fillWidth: true
                Layout.preferredHeight: 35

                enabled: (Database.connectionStatus === true) ? true : false
                horizontalAlignment: Text.AlignRight
                validator: RegularExpressionValidator {
                    regularExpression: /^\p{Nd}+$/
                }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 1

                Layout.topMargin: 30
                Layout.bottomMargin: 25

                color: Qt.color(AppTheme.colors["UFO_GroupBox_Content_Separator"])
            }

            Text {
                Layout.fillWidth: true

                text: qsTr("لطفاً محل خروجی فایل را انتخاب کنید")
                elide: Text.ElideRight
                wrapMode: Text.NoWrap
                verticalAlignment: Text.AlignVCenter
                color: Qt.color(AppTheme.colors["UFO_GroupBox_Content_Text"])
                font.pixelSize: Qt.application.font.pixelSize * 1
            }

            RowLayout {
                Layout.fillWidth: true

                UFO_Button {
                    id: ufo_Button_SelectPath

                    Layout.preferredWidth: 120
                    Layout.preferredHeight: 35

                    enabled: (Database.connectionStatus === true) ? true : false
                    text: qsTr("انتخاب")
                    onClicked: {
                        folderDialog.open();
                    }
                }

                UFO_TextField {
                    id: textField_OutputDirectoryPath

                    Layout.fillWidth: true
                    Layout.preferredHeight: 35

                    enabled: (Database.connectionStatus === true) ? true : false
                    text: Printer.outputDirectoryUrl
                    readOnly: true
                }

                FolderDialog {
                    id: folderDialog

                    title: "Select Folder"
                    currentFolder: Printer.outputDirectoryUrl

                    onAccepted: {
                        Printer.outputDirectoryUrl = folderDialog.selectedFolder;
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true

                Layout.topMargin: 15

                Item {
                    Layout.fillWidth: true
                }

                UFO_Button {
                    id: ufo_Button_Print

                    Layout.preferredWidth: 120
                    Layout.preferredHeight: 35

                    enabled: (Database.connectionStatus === true) ? true : false
                    text: qsTr("چاپ")
                    icon.source: "qrc:/resources/icons/print.svg"

                    onClicked: {
                        let id = parseInt(textField_PatientID.text.trim(), 10);

                        if(isNaN(id)) {

                            return;
                        }

                        Printer.setPatientID(id);
                        Printer.printPatientData();
                    }
                }
            }
        }
    }

    UFO_OperationResult {
        id: ufo_OperationResult

        Layout.fillWidth: true
        // NOTE (SAVIZ): No point using "Layout.fillHeight" as "UFO_Page" ignores height to enable vertical scrolling.

        Connections {
            target: Printer

            function onPrintStatusChanged(resultMap) {

                ufo_OperationResult.displayMessage(resultMap["status"], resultMap["message"], 8000);
            }
        }
    }
}
