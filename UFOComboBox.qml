pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls.impl
import QtQuick.Controls.Basic
import QtQuick.Layouts

ComboBox {
    id: control

    property bool canFilter: false
    property string filterText: ""
    property real popupHeight: 250
    property color comboBoxDropDownBackgroundNormal: AppTheme.getColor(AppTheme.Colors.ComboBoxDropDownBackgroundNormal)
    property color comboBoxDropDownBackgroundDown: AppTheme.getColor(AppTheme.Colors.ComboBoxDropDownBackgroundDown)
    property color comboBoxDropDownTextNormal: AppTheme.getColor(AppTheme.Colors.ComboBoxDropDownTextNormal)
    property color comboBoxDropDownTextPressed: AppTheme.getColor(AppTheme.Colors.ComboBoxDropDownTextPressed)
    property color comboBoxDropDownBorder: AppTheme.getColor(AppTheme.Colors.ComboBoxDropDownBorder)
    property color comboBoxIndicatorNormal: AppTheme.getColor(AppTheme.Colors.ComboBoxIndicatorNormal)
    property color comboBoxIndicatorPressed: AppTheme.getColor(AppTheme.Colors.ComboBoxIndicatorPressed)
    property color comboBoxPopupBorder: AppTheme.getColor(AppTheme.Colors.ComboBoxPopupBorder)
    property color comboBoxTextInputBackground: AppTheme.getColor(AppTheme.Colors.ComboBoxTextInputBackground)
    property color comboBoxTextInputBorder: AppTheme.getColor(AppTheme.Colors.ComboBoxTextInputBorder)
    property color comboBoxTextInputText: AppTheme.getColor(AppTheme.Colors.ComboBoxTextInputText)
    property color comboBoxDelegateBackgroundNormal: AppTheme.getColor(AppTheme.Colors.ComboBoxDelegateBackgroundNormal)
    property color comboBoxDelegateBackgroundHighlighted: AppTheme.getColor(AppTheme.Colors.ComboBoxDelegateBackgroundHighlighted)
    property color comboBoxDelegateTextNormal: AppTheme.getColor(AppTheme.Colors.ComboBoxDelegateTextNormal)
    property color comboBoxDelegateTextHighlighted: AppTheme.getColor(AppTheme.Colors.ComboBoxDelegateTextHighlighted)

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding,
                             implicitIndicatorHeight + topPadding + bottomPadding)

    leftPadding: padding + (!control.mirrored || !indicator || !indicator.visible ? 0 : indicator.width + spacing)
    rightPadding: padding + (control.mirrored || !indicator || !indicator.visible ? 0 : indicator.width + spacing)
    opacity: enabled ? 1.0 : 0.5

    spacing: 5

    delegate: ItemDelegate {
        id: delegate

        required property var model
        required property int index

        width: control.width
        contentItem: Text {
            text: delegate.model[control.textRole]
            color: delegate.highlighted ? control.comboBoxDelegateTextHighlighted : control.comboBoxDelegateTextNormal
            font: control.font
            elide: Text.ElideRight
        }

        background: Rectangle {
            width: control.width
            radius: 0
            color: delegate.highlighted ? control.comboBoxDelegateBackgroundHighlighted : control.comboBoxDelegateBackgroundNormal
        }

        highlighted: control.highlightedIndex === index
    }

    indicator: Canvas {
        id: canvas
        x: control.mirrored ? control.padding + 10 : control.width - width - control.padding - 10
        y: control.topPadding + (control.availableHeight - height) / 2
        width: 12
        height: 8
        contextType: "2d"

        Connections {
            target: control
            function onPressedChanged() { canvas.requestPaint(); }
        }

        onPaint: {
            context.reset();
            context.moveTo(0, 0);
            context.lineTo(width, 0);
            context.lineTo(width / 2, height);
            context.closePath();
            context.fillStyle = control.pressed ? control.comboBoxIndicatorPressed : control.comboBoxIndicatorNormal;
            context.fill();
        }
    }

    contentItem: Text {
        leftPadding: control.indicator.width + control.spacing
        rightPadding: control.indicator.width + control.spacing

        text: control.displayText
        font: control.font
        color: control.pressed ? control.comboBoxDropDownTextPressed : control.comboBoxDropDownTextNormal
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 140
        implicitHeight: 40

        color: control.down ? control.comboBoxDropDownBackgroundDown : control.comboBoxDropDownBackgroundNormal
        border.color: control.comboBoxDropDownBorder
        border.width: 1
    }

    popup: Popup {
        y: control.height + 2
        width: control.width
        height: Math.min(contentItem.implicitHeight, control.Window.height - topMargin - bottomMargin)
        padding: 0

        contentItem: ColumnLayout {

            spacing: 0

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: 35
                Layout.topMargin: 1
                Layout.rightMargin: 1
                Layout.leftMargin: 1

                border.width: 1
                border.color: control.comboBoxTextInputBorder
                color: control.comboBoxTextInputBackground
                visible: control.canFilter

                TextInput {
                    id: textInputFilterText

                    anchors.fill: parent
                    anchors.margins: 10

                    color: control.comboBoxTextInputText

                    onTextEdited: {
                        control.filterText = textInputFilterText.text.trim();
                    }
                }
            }

            ListView {
                id: listView

                Layout.fillWidth: true
                Layout.preferredHeight: Math.min(contentHeight, control.popupHeight)
                Layout.topMargin: control.canFilter ? 0 : 1
                Layout.bottomMargin: 1
                Layout.rightMargin: 1
                Layout.leftMargin: 1

                clip: true
                model: control.popup.visible ? control.delegateModel : null
                currentIndex: control.highlightedIndex
            }
        }

        background: Rectangle {
            border.width: 1
            border.color: control.comboBoxPopupBorder
        }
    }
}
