import QtQuick
import QtQuick.Controls.impl
import QtQuick.Controls.Basic
import QtQuick.Layouts

TextField {
    id: control

    property real radius: 0
    property color textFieldBackground: AppTheme.getColor(AppTheme.Colors.TextFieldBackground)
    property color textFieldPlaceHolderText: AppTheme.getColor(AppTheme.Colors.TextFieldPlaceHolderText)
    property color textFieldTextSelectedBackground: control.palette.highlight
    property color textFieldTextSelected: control.palette.highlightedText
    property color textFieldTextNormal: control.palette.text
    property color textFieldBorderNormal: AppTheme.getColor(AppTheme.Colors.TextFieldBorderNormal)
    property color textFieldBorderFocused: AppTheme.getColor(AppTheme.Colors.TextFieldBorderFocused)

    implicitWidth: implicitBackgroundWidth + leftInset + rightInset || Math.max(contentWidth, placeholder.implicitWidth) + leftPadding + rightPadding
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, contentHeight + topPadding + bottomPadding, placeholder.implicitHeight + topPadding + bottomPadding)

    padding: 6
    leftPadding: padding + 4

    color: control.textFieldTextNormal
    selectionColor: control.textFieldTextSelectedBackground
    selectedTextColor: control.textFieldTextSelected
    placeholderTextColor: control.textFieldPlaceHolderText
    verticalAlignment: TextInput.AlignVCenter

    opacity: enabled ? 1.0 : 0.5

    PlaceholderText {
        id: placeholder
        x: control.leftPadding
        y: control.topPadding
        width: control.width - (control.leftPadding + control.rightPadding)
        height: control.height - (control.topPadding + control.bottomPadding)

        text: control.placeholderText
        font: control.font
        color: control.placeholderTextColor
        verticalAlignment: control.verticalAlignment
        visible: !control.length && !control.preeditText && (!control.activeFocus || control.horizontalAlignment !== Qt.AlignHCenter)
        elide: Text.ElideRight
        renderType: control.renderType
    }

    background: Rectangle {
        implicitWidth: 200
        implicitHeight: 40

        radius: control.radius
        border.width: control.activeFocus ? 2 : 1
        color: control.textFieldBackground
        border.color: control.activeFocus ? control.textFieldBorderFocused : control.textFieldBorderNormal
    }
}
