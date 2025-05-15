import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts

Window {
    id: root

    property url imageUrl;

    flags: Qt.Window | Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint
    modality: Qt.ApplicationModal
    color: "transparent"

    Component.onCompleted: {
        imageView.source = root.imageUrl;

        root.showFullScreen()
    }

    Rectangle {
        anchors.fill: parent

        color: "black"
        focus: true

        Keys.onPressed: (event)=> {
            if (event.key === Qt.Key_Escape) {
                event.accepted = true

                root.close()
            }
        }

        Image {
            id: imageView

            anchors.centerIn: parent

            fillMode: Image.PreserveAspectFit
            smooth: true
            cache: false
        }
    }
}
