import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Item {
    id: control

    property real radius: 0
    property real textLeftMargin: 7
    property real textRightMargin: 7
    property color statusBarBackground: AppTheme.getColor(AppTheme.Colors.StatusBarBackground)
    property color statusBarText: AppTheme.getColor(AppTheme.Colors.StatusBarText)

    function displayMessage(message: string) {
        textDisplayMessage.text = message;
    }

    implicitWidth: 200
    implicitHeight: 200

    Rectangle {
        id: rectangleBackground

        anchors.fill: parent

        radius: control.radius
        color: control.statusBarBackground

        Text {
            id: textDisplayMessage

            anchors.fill: parent
            anchors.leftMargin: control.textLeftMargin
            anchors.rightMargin: control.textRightMargin

            verticalAlignment: Text.AlignVCenter
            color: control.statusBarText
            elide: Text.ElideRight
        }
    }
}
