import QtQuick
import QtQuick.Controls.impl
import QtQuick.Controls.Basic
import QtQuick.Layouts

Item {
    id: root

    signal deleteClicked(treatmentID: int, row: int);

    property bool startCollapsed: true
    property real titleFontSizeScalar: 1.0
    property real separatorHeight: 2
    property real titleRightMargin: 0
    property real titleLeftMargin: 10
    property real contentTopMargin: 10
    property real contentBottomMargin: 10
    property real contentRightMargin: 10
    property real contentLeftMargin: 10
    readonly property int collapsedHeight: rectangleTitleBackground.implicitHeight
    readonly property int expandedHeight: rectangleTitleBackground.implicitHeight + rectangleSeparator.implicitHeight + rectangleContentBackground.implicitHeight + root.contentTopMargin + root.contentBottomMargin
    property color delegateTitleBackground: AppTheme.getColor(AppTheme.Colors.DelegateTitleBackground)
    property color delegateTitleTextColor: AppTheme.getColor(AppTheme.Colors.DelegateTitleText)
    property color delegateSeparatorColor: AppTheme.getColor(AppTheme.Colors.DelegateTitleSeparator)
    property color delegateContentBackgroundColor: AppTheme.getColor(AppTheme.Colors.DelegateContentBackground)

    implicitWidth: 200
    implicitHeight: buttonExpand.checked ? expandedHeight : collapsedHeight

    Rectangle {
        id: rectangleTitleBackground

        anchors.top: root.top
        anchors.right: root.right
        anchors.left: root.left

        implicitHeight: 35

        color: root.delegateTitleBackground

        RowLayout {
            anchors.fill: parent

            spacing: 0

            Item {
                Layout.preferredWidth: 10
            }

            Text {
                Layout.fillWidth: true
                Layout.fillHeight: true

                text: model.name
                color: root.delegateTitleTextColor
                elide: Text.ElideRight
                font.pixelSize: Qt.application.font.pixelSize
                wrapMode: Text.NoWrap
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
            }

            Item {
                Layout.preferredWidth: 5
            }

            UFOButton {
                id: buttonDelete

                Layout.preferredWidth: 120
                Layout.fillHeight: true

                display: AbstractButton.TextBesideIcon
                text: qsTr("حذف")
                icon.source: "qrc:/resources/icons/material/delete.svg"

                onClicked: {
                    root.deleteClicked(model.treatmentID, model.row);
                }
            }

            Item {
                Layout.preferredWidth: 5
            }

            UFOButton {
                id: buttonExpand

                Layout.preferredWidth: 50
                Layout.fillHeight: true

                display: AbstractButton.IconOnly
                checkable: true
                checked: !root.startCollapsed
                icon.source: checked ? "qrc:/resources/icons/material/keyboard_arrow_up.svg" : "qrc:/resources/icons/material/keyboard_arrow_down.svg"
            }
        }
    }

    Rectangle {
        id: rectangleSeparator

        anchors.top: rectangleTitleBackground.bottom
        anchors.right: root.right
        anchors.left: root.left

        implicitHeight: root.separatorHeight

        visible: buttonExpand.checked
        color: root.delegateSeparatorColor
    }

    Rectangle {
        id: rectangleContentBackground

        anchors.top: rectangleTitleBackground.bottom
        anchors.bottom: root.bottom
        anchors.right: root.right
        anchors.left: root.left

        implicitHeight: columnLayout.implicitHeight

        radius: 0
        visible: buttonExpand.checked
        color: root.delegateContentBackgroundColor

        Item {
            anchors.fill: parent
            anchors.topMargin: root.contentTopMargin
            anchors.bottomMargin: root.contentBottomMargin
            anchors.rightMargin: root.contentRightMargin
            anchors.leftMargin: root.contentLeftMargin

            // TODO (SAVIZ): In future you can add a colmun to the database that explains the diagnosis and show a 'Text' for it here.

            ColumnLayout {
                id: columnLayout

                width: parent.width

                clip: false
                spacing: 5

                // Text {
                //     Layout.fillWidth: true

                //     color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                //     elide: Text.ElideRight
                //     text: qsTr("شماره پرونده")
                //     textFormat: Text.PlainText
                //     verticalAlignment: Text.AlignVCenter
                //     wrapMode: Text.NoWrap
                // }
            }
        }
    }
}
