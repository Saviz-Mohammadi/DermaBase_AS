import QtQuick
import QtQuick.Controls.impl
import QtQuick.Controls.Basic
import QtQuick.Layouts

Item {
    id: root

    default property alias content: columnLayout.data
    property bool contentEnabled: true
    property bool startCollapsed: false
    property string title: "Section"
    property real titleFontSizeScalar: 1.3
    property real separatorHeight: 2
    property real titleRightMargin: 0
    property real titleLeftMargin: 10
    property real contentTopMargin: 10
    property real contentBottomMargin: 10
    property real contentRightMargin: 10
    property real contentLeftMargin: 10
    property real spacing: 7
    readonly property int collapsedHeight: rectangleTitleBackground.implicitHeight
    readonly property int expandedHeight: rectangleTitleBackground.implicitHeight + rectangleSeparator.implicitHeight + rectangleContentBackground.implicitHeight + root.contentTopMargin + root.contentBottomMargin
    property color sectionTitleBackground: AppTheme.getColor(AppTheme.Colors.SectionTitleBackground)
    property color sectionTitleText: AppTheme.getColor(AppTheme.Colors.SectionTitleText)
    property color sectionSeparator: AppTheme.getColor(AppTheme.Colors.SectionTitleSeparator)
    property color sectionContentBackground: AppTheme.getColor(AppTheme.Colors.SectionContentBackground)

    implicitWidth: 200
    implicitHeight: buttonExpand.checked ? expandedHeight : collapsedHeight

    Rectangle {
        id: rectangleTitleBackground

        anchors.top: root.top
        anchors.right: root.right
        anchors.left: root.left

        implicitHeight: 40

        color: root.sectionTitleBackground

        RowLayout {
            anchors.fill: parent

            spacing: 10

            Text {
                id: textTitle

                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.rightMargin: root.titleRightMargin
                Layout.leftMargin: root.titleLeftMargin

                text: root.title
                color: root.sectionTitleText
                elide: Text.ElideRight
                font.pixelSize: Qt.application.font.pixelSize * root.titleFontSizeScalar
                wrapMode: Text.NoWrap
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
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
        color: root.sectionSeparator
    }

    Rectangle {
        id: rectangleContentBackground

        anchors.top: rectangleSeparator.bottom
        anchors.bottom: root.bottom
        anchors.right: root.right
        anchors.left: root.left

        implicitHeight: columnLayout.implicitHeight

        radius: 0
        visible: buttonExpand.checked
        color: root.sectionContentBackground

        Item {
            anchors.fill: parent
            anchors.topMargin: root.contentTopMargin
            anchors.bottomMargin: root.contentBottomMargin
            anchors.rightMargin: root.contentRightMargin
            anchors.leftMargin: root.contentLeftMargin

            ColumnLayout {
                id: columnLayout

                width: parent.width

                clip: false
                spacing: root.spacing
                enabled: root.contentEnabled
            }
        }
    }
}
