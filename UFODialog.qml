import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import QtQuick.Controls.impl

Dialog {
    id: control

    property string identifier: ""
    property color dialogBackground: AppTheme.getColor(AppTheme.Colors.DialogBackground)
    property color dialogBorder: AppTheme.getColor(AppTheme.Colors.DialogBorder)
    property color dialogButtonBackground: AppTheme.getColor(AppTheme.Colors.DialogButtonBackground)
    property color dialogTextBackground: AppTheme.getColor(AppTheme.Colors.DialogTextBackground)
    property color dialogText: AppTheme.getColor(AppTheme.Colors.DialogText)

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            contentWidth + leftPadding + rightPadding,
                            implicitHeaderWidth,
                            implicitFooterWidth)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             contentHeight + topPadding + bottomPadding
                             + (implicitHeaderHeight > 0 ? implicitHeaderHeight + spacing : 0)
                             + (implicitFooterHeight > 0 ? implicitFooterHeight + spacing : 0))

    padding: 12

    background: Rectangle {
        color: control.dialogBackground
        border.color: control.dialogBorder
    }

    header: Label {
        color: control.dialogText
        text: control.title
        visible: parent?.parent === Overlay.overlay && control.title
        elide: Label.ElideRight
        font.bold: true
        padding: 12
        background: Rectangle {
            x: 1; y: 1
            width: parent.width - 2
            height: parent.height - 1
            color: control.dialogTextBackground
        }
    }

    footer: DialogButtonBox {
        visible: count > 0
        spacing: control.spacing

        delegate: UFOButton {
            width: control.count === 1 ? control.availableWidth / 2 : undefined
        }

        background: Rectangle {
            implicitHeight: 40
            x: 1; y: 1
            width: parent.width - 2
            height: parent.height - 2
            color: control.dialogButtonBackground
        }
    }

    Overlay.modal: Rectangle {
        color: Color.transparent(control.palette.shadow, 0.5)
    }

    Overlay.modeless: Rectangle {
        color: Color.transparent(control.palette.shadow, 0.12)
    }
}
