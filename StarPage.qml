import QtQuick
import QtQuick.Controls.impl
import QtQuick.Controls.Basic
import QtQuick.Layouts

// Custom CPP:
import StarredPatientsModel 1.0

Item {
    id: root

    signal patientSelectedForEdit(patientID: int);

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
                        icon.source: "qrc:/resources/icons/material/star.svg"
                        icon.color: AppTheme.getColor(AppTheme.Colors.PageIcon)
                    }

                    Text {
                        Layout.preferredHeight: 40

                        color: AppTheme.getColor(AppTheme.Colors.PageText)
                        elide: Text.ElideRight
                        font.pixelSize: Qt.application.font.pixelSize * root.titleFontSizeScalar
                        text: qsTr("بیماران ستاره‌دار")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignTop
                        wrapMode: Text.NoWrap
                    }
                }

                UFOSection {
                    Layout.fillWidth: true

                    startCollapsed: true
                    title: qsTr("ستاره دار کردن با شماره پرونده")

                    Text {
                        Layout.fillWidth: true
                        Layout.bottomMargin: 20

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("از فیلدهای زیر برای ستاره دار کردن بیمار با شماره پرونده استفاده کنید.")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.Wrap
                    }

                    UFOButton {
                        id: buttonClearIDSection

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
                        text: qsTr("شماره پرونده")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.NoWrap
                    }

                    UFOTextField {
                        id: textFieldPatientID

                        Layout.preferredWidth: 250
                        Layout.preferredHeight: 35

                        horizontalAlignment: TextInput.AlignLeft
                        validator: IntValidator {
                            bottom: 0
                        }

                        Connections {
                            target: buttonClearIDSection

                            function onClicked() {
                                textFieldPatientID.clear();
                            }
                        }
                    }

                    UFOButton {
                        id: buttonStarringID

                        Layout.preferredWidth: 120
                        Layout.preferredHeight: 35
                        Layout.topMargin: 20

                        display: AbstractButton.TextBesideIcon
                        text: qsTr("ستاره")
                        icon.source: "qrc:/resources/icons/material/star.svg"

                        onClicked: {
                            if (!textFieldPatientID.acceptableInput) {
                                mainDialog.title = qsTr("ورودی ارائه شده به قسمت ورودی شماره پرونده صحیح نیست.") + "\n" + qsTr("لطفاً قبل از ادامه شماره پرونده صحیح را وارد کنید.");
                                mainDialog.identifier = "Search";
                                mainDialog.standardButtons = Dialog.Ok;
                                mainDialog.modal = true;
                                mainDialog.open();

                                return;
                            }

                            let patientID = parseInt(textFieldPatientID.text, 10);

                            starredPatientsModel.requestCreateStarredPatient(patientID);
                        }
                    }
                }

                UFOSection {
                    Layout.fillWidth: true

                    title: qsTr("لیست بیماران ستاره‌دار")

                    Text {
                        Layout.fillWidth: true
                        Layout.bottomMargin: 20

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("لیست زیر نشان دهنده تمام بیماران ستاره دار است که برای مراجعه سریع در دسترس هستند.")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.Wrap
                    }

                    Text {
                        Layout.fillWidth: true
                        Layout.bottomMargin: 20

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("بیماران ویزیت شده: ") + starredPatientsModel.rowCount() + " (" + qsTr("کل") + ")" + " | " + starredPatientsModel.visitedCount + " (" + qsTr("ویزیت شده") + ")"
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.Wrap
                    }

                    ListView {
                        id: listViewStar

                        Layout.fillWidth: true
                        Layout.preferredHeight: 400

                        anchors.margins: 12

                        clip: true
                        enabled: !starredPatientsModel.operationIsInProgress
                        spacing: 7

                        StarredPatientsModel {
                            id: starredPatientsModel

                            database: mainDatabase
                        }

                        model: starredPatientsModel

                        delegate: StarDelegate {
                            width: listViewStar.width

                            onEditClicked: function(patientID) {
                                root.patientSelectedForEdit(patientID)
                            }
                        }
                    }

                    UFOButton {
                        id: buttonRefreshListStar

                        Layout.preferredWidth: 120
                        Layout.preferredHeight: 35
                        Layout.topMargin: 20

                        display: AbstractButton.TextBesideIcon
                        text: qsTr("آپدیت لیست")
                        icon.source: "qrc:/resources/icons/material/autorenew.svg"

                        onClicked: {
                            starredPatientsModel.requestGetAllStarredPatients();
                        }
                    }
                }
            }
        }
    }
}
