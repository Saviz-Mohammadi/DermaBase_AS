import QtQuick
import QtQuick.Controls.impl
import QtQuick.Controls.Basic

CheckBox {
    id: control

    property color checkBoxIndicatorBackgroundNormal: AppTheme.getColor(AppTheme.Colors.CheckBoxIndicatorBackgroundNormal)
    property color checkBoxIndicatorBackgroundDown: AppTheme.getColor(AppTheme.Colors.CheckBoxIndicatorBackgroundDown)
    property color checkBoxIndicatorBorderNormal: AppTheme.getColor(AppTheme.Colors.CheckBoxIndicatorBorderNormal)
    property color checkBoxIndicatorBorderFocused: AppTheme.getColor(AppTheme.Colors.CheckBoxIndicatorBorderFocused)
    property color checkBoxIndicatorFiller: AppTheme.getColor(AppTheme.Colors.CheckBoxIndicatorFiller)
    property color checkBoxText: AppTheme.getColor(AppTheme.Colors.CheckBoxText)

    opacity: enabled ? 1.0 : 0.5

    indicator: Rectangle {
        anchors.fill: parent

        radius: 0
        color: control.down ? control.checkBoxIndicatorBackgroundDown : control.checkBoxIndicatorBackgroundNormal

        border.width: control.visualFocus ? 2 : 1
        border.color: control.visualFocus ? control.checkBoxIndicatorBorderFocused : control.checkBoxIndicatorBorderNormal

        Rectangle {
            anchors.centerIn: parent

            width: parent.width / 2
            height: parent.height /2

            radius: 0
            color: control.checkBoxIndicatorFiller
            visible: control.checked
        }
    }

    contentItem: Text {
        id: textContent

        text: control.text
        font: control.font
        color: control.checkBoxText
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }
}
