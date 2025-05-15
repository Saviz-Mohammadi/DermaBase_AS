import QtQuick
import QtQuick.Controls.impl
import QtQuick.Controls.Basic
import QtQuick.Layouts
import QtQuick.Effects

Button {
    id: control

    property bool showShadow: false
    property real shadowBlur: 0.0
    property real radius: 0
    property color buttonBackgroundDown: AppTheme.getColor(AppTheme.Colors.ButtonBackgroundDown)
    property color buttonBackgroundChecked: AppTheme.getColor(AppTheme.Colors.ButtonBackgroundChecked)
    property color buttonBackgroundHovered: AppTheme.getColor(AppTheme.Colors.ButtonBackgroundHovered)
    property color buttonBackgroundNormal: AppTheme.getColor(AppTheme.Colors.ButtonBackgroundNormal)
    property color buttonIconDown: AppTheme.getColor(AppTheme.Colors.ButtonIconDown)
    property color buttonIconChecked: AppTheme.getColor(AppTheme.Colors.ButtonIconChecked)
    property color buttonIconHovered: AppTheme.getColor(AppTheme.Colors.ButtonIconHovered)
    property color buttonIconNormal: AppTheme.getColor(AppTheme.Colors.ButtonIconNormal)
    property color buttonTextDown: AppTheme.getColor(AppTheme.Colors.ButtonTextDown)
    property color buttonTextChecked: AppTheme.getColor(AppTheme.Colors.ButtonTextChecked)
    property color buttonTextHovered: AppTheme.getColor(AppTheme.Colors.ButtonTextHovered)
    property color buttonTextNormal: AppTheme.getColor(AppTheme.Colors.ButtonTextNormal)
    property color buttonBorder: AppTheme.getColor(AppTheme.Colors.ButtonBorder)
    property alias alignment: iconLabel.alignment

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding)

    opacity: control.enabled ? 1 : 0.5

    padding: 6
    spacing: 6

    icon.width: 24
    icon.height: 24

    icon.color: {
        if (control.down) {
            return control.buttonIconDown;
        }

        if (control.checked) {
            return control.buttonIconChecked;
        }

        if (control.hovered && control.enabled) {
            return control.buttonIconHovered;
        }

        return control.buttonIconNormal;
    }

    contentItem: IconLabel {
        id: iconLabel

        spacing: control.spacing
        mirrored: control.mirrored
        display: control.display

        icon: control.icon
        text: control.text
        font: control.font

        color: {
            if (control.down) {
                return control.buttonTextDown;
            }

            if (control.checked) {
                return control.buttonTextChecked;
            }

            if (control.hovered && control.enabled) {
                return control.buttonTextHovered;
            }

            return control.buttonTextNormal;
        }
    }

    background: Rectangle {
        id: rectangleBackground

        implicitWidth: 100
        implicitHeight: 35

        radius: control.radius
        visible: !control.flat

        color: {
            if (control.down) {
                return control.buttonBackgroundDown;
            }

            if (control.checked) {
                return control.buttonBackgroundChecked;
            }

            if (control.hovered && control.enabled) {
                return control.buttonBackgroundHovered;
            }

            return control.buttonBackgroundNormal;
        }

        border.color: control.buttonBorder;
        border.width: control.visualFocus ? 2 : 0

        layer.enabled: control.showShadow
        layer.effect: MultiEffect {
            source: rectangleBackground
            anchors.fill: rectangleBackground
            autoPaddingEnabled: true
            shadowBlur: control.shadowBlur
            shadowColor: "black"
            shadowEnabled: control.showShadow
            shadowVerticalOffset: 2
            shadowHorizontalOffset: 2
            opacity: control.pressed ? 0.75 : 1.0
        }
    }
}
