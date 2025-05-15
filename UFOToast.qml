import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import QtQuick.Controls.impl

Item {
    id: root

    enum Status {
        Info,
        Warning,
        Success,
        Error
    }

    property int iconSize: 32
    property int borderRadius: 0

    implicitWidth: 200
    implicitHeight: root.iconSize + 20

    function displayMessage(status, message: string, duration: int) {
        switch (status) {
        case UFOToast.Status.Info:
            rectangleBackground.color = AppTheme.getColor(AppTheme.Colors.ToastBackgroundInfo);
            iconLabel.icon.source = "qrc:/resources/icons/material/info.svg";
            iconLabel.icon.color = AppTheme.getColor(AppTheme.Colors.ToastIconInfo);
            textDisplayMessage.color = AppTheme.getColor(AppTheme.Colors.ToastTextInfo);
            break;
        case UFOToast.Status.Warning:
            rectangleBackground.color = AppTheme.getColor(AppTheme.Colors.ToastBackgroundWarning);
            iconLabel.icon.source = "qrc:/resources/icons/material/warning.svg";
            iconLabel.icon.color = AppTheme.getColor(AppTheme.Colors.ToastIconWarning);
            textDisplayMessage.color = AppTheme.getColor(AppTheme.Colors.ToastTextWarning);
            break;
        case UFOToast.Status.Success:
            rectangleBackground.color = AppTheme.getColor(AppTheme.Colors.ToastBackgroundSuccess);
            iconLabel.icon.source = "qrc:/resources/icons/material/check_circle.svg";
            iconLabel.icon.color = AppTheme.getColor(AppTheme.Colors.ToastIconSuccess);
            textDisplayMessage.color = AppTheme.getColor(AppTheme.Colors.ToastTextSuccess);
            break;
        case UFOToast.Status.Error:
            rectangleBackground.color = AppTheme.getColor(AppTheme.Colors.ToastBackgroundError);
            iconLabel.icon.source = "qrc:/resources/icons/material/error.svg";
            iconLabel.icon.color = AppTheme.getColor(AppTheme.Colors.ToastIconError);
            textDisplayMessage.color = AppTheme.getColor(AppTheme.Colors.ToastTextError);
            break;
        default:
            break;
        }

        textDisplayMessage.text = qsTr(message);
        rectangleBackground.visible = true;

        if (duration === undefined) {
            return;
        }

        timer.interval = duration;
        timer.restart();
    }

    function hideToast() {
        rectangleBackground.visible = false;
    }

    Timer {
        id: timer

        onTriggered: {
            root.hideToast();
        }
    }

    Rectangle {
        id: rectangleBackground

        anchors.fill: parent

        radius: root.borderRadius
        visible: false

        RowLayout {
            anchors.fill: parent
            anchors.margins: 10

            spacing: 10

            IconLabel {
                id: iconLabel

                Layout.preferredWidth: root.iconSize
                Layout.preferredHeight: root.iconSize

                icon.width: root.iconSize
                icon.height: root.iconSize
            }

            Text {
                id: textDisplayMessage

                Layout.fillWidth: true
                Layout.fillHeight: true

                elide: Text.ElideRight
                wrapMode: Text.Wrap
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        MouseArea {
            id: mouseAreaClose

            anchors.fill: parent

            hoverEnabled: true

            onEntered: {
                cursorShape = Qt.PointingHandCursor;
            }

            onClicked: {
                root.hideToast();
            }
        }
    }
}
