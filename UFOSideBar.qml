import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Item {
    id: root

    signal tabSelected(int index)

    implicitWidth: 200
    implicitHeight: 200

    ButtonGroup {
        id: buttonGroup
    }

    Rectangle {
        anchors.fill: parent

        color: AppTheme.predefinedColors.grey800

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 15

            spacing: 5

            ListView {
                id: listView

                Layout.fillWidth: true
                Layout.fillHeight: true

                clip: true
                spacing: 5

                model: ListModel {
                    id: listModel

                    ListElement {
                        tabName: "بیماران ستاره‌دار"
                        tabIcon: "qrc:/resources/icons/material/star.svg"
                        tabIndex: 0
                    }

                    ListElement {
                        tabName: "جستجو بیمار"
                        tabIcon: "qrc:/resources/icons/material/person_search.svg"
                        tabIndex: 1
                    }

                    ListElement {
                        tabName: "ویرایش بیمار"
                        tabIcon: "qrc:/resources/icons/material/person_edit.svg"
                        tabIndex: 2
                    }

                    ListElement {
                        tabName: "ایجاد بیمار"
                        tabIcon: "qrc:/resources/icons/material/person_add.svg"
                        tabIndex: 3
                    }
                }

                delegate: UFOButton {
                    width: listView.width
                    height: 40

                    alignment: mirrored ? Qt.AlignLeft : Qt.AlignRight
                    autoExclusive: true
                    ButtonGroup.group: buttonGroup
                    checkable: true
                    icon.source: model.tabIcon
                    spacing: 10
                    text: model.tabName

                    onCheckedChanged: {
                        root.tabSelected(model.tabIndex)
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 1
                Layout.topMargin: 10
                Layout.bottomMargin: 10

                color: AppTheme.predefinedColors.grey500
            }

            UFOButton {
                id: buttonSettings

                Layout.fillWidth: true
                Layout.preferredHeight: 40

                alignment: mirrored ? Qt.AlignLeft : Qt.AlignRight
                autoExclusive: true
                ButtonGroup.group: buttonGroup
                checkable: true
                checked: true
                icon.source: "qrc:/resources/icons/material/settings.svg"
                spacing: 10
                text: qsTr("تنظیمات برنامه")

                onCheckedChanged: {
                    root.tabSelected(4)
                }
            }

            UFOButton {
                id: buttonAbout

                Layout.fillWidth: true
                Layout.preferredHeight: 40

                alignment: mirrored ? Qt.AlignLeft : Qt.AlignRight
                autoExclusive: true
                ButtonGroup.group: buttonGroup
                checkable: true
                checked: false
                icon.source: "qrc:/resources/icons/material/help.svg"
                spacing: 10
                text: qsTr("درباره برنامه")

                onCheckedChanged: {
                    root.tabSelected(5)
                }
            }
        }
    }
}
