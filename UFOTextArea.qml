import QtQuick
import QtQuick.Controls.impl
import QtQuick.Controls.Basic
import QtQuick.Layouts

TextArea {
    id: control

    property real radius: 0
    property color textAreaBackground: AppTheme.getColor(AppTheme.Colors.TextAreaBackground)
    property color textAreaPlaceHolderText: AppTheme.getColor(AppTheme.Colors.TextAreaPlaceHolderText)
    property color textAreaTextSelectedBackground: control.palette.highlight
    property color textAreaTextSelected: control.palette.highlightedText
    property color textAreaTextNormal: control.palette.text
    property color textAreaBorderNormal: AppTheme.getColor(AppTheme.Colors.TextAreaBorderNormal)
    property color textAreaBorderFocused: AppTheme.getColor(AppTheme.Colors.TextAreaBorderFocused)

    implicitWidth: Math.max(contentWidth + leftPadding + rightPadding,
                            implicitBackgroundWidth + leftInset + rightInset,
                            placeholder.implicitWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(contentHeight + topPadding + bottomPadding,
                             implicitBackgroundHeight + topInset + bottomInset,
                             placeholder.implicitHeight + topPadding + bottomPadding)

    padding: 6
    leftPadding: padding + 4

    color: control.textAreaTextNormal
    placeholderTextColor: control.textAreaPlaceHolderText
    selectionColor: control.textAreaTextSelectedBackground
    selectedTextColor: control.textAreaTextSelected

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
        color: control.textAreaBackground
        border.color: control.activeFocus ? control.textAreaBorderFocused : control.textAreaBorderNormal
    }
}
