import QtQuick
import QtQuick.Controls.impl
import QtQuick.Controls.Basic
import QtQuick.Layouts

Item {
    id: root

    property int topMargin: 15
    property int bottomMargin: 15
    property int rightMargin: 15
    property int leftMargin: 15
    property int spacing: 10
    property real titleFontSizeScalar: 2

    ScrollView {
        id: scrollView

        anchors.fill: parent

        contentWidth: -1
        contentHeight: columnLayout.implicitHeight + root.topMargin + root.bottomMargin
        ScrollBar.horizontal.policy: ScrollBar.AsNeeded
        ScrollBar.vertical.policy: ScrollBar.AsNeeded

        background: Rectangle {
            id: rectangleBackground

            radius: 0
            color: AppTheme.getColor(AppTheme.Colors.PageBackground)
        }

        Item {
            anchors.fill: parent
            anchors.topMargin: root.topMargin
            anchors.bottomMargin: root.bottomMargin
            anchors.rightMargin: root.rightMargin
            anchors.leftMargin: root.leftMargin

            ColumnLayout {
                id: columnLayout

                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                anchors.left: parent.left

                clip: false
                spacing: root.spacing

                RowLayout {
                    Layout.fillWidth: true
                    Layout.bottomMargin: 40

                    spacing: 10

                    IconLabel {
                        Layout.preferredHeight: 40

                        icon.width: 32
                        icon.height: 32
                        icon.source: "qrc:/resources/icons/material/help.svg"
                        icon.color: AppTheme.getColor(AppTheme.Colors.PageIcon)
                    }

                    Text {
                        Layout.preferredHeight: 40

                        color: AppTheme.getColor(AppTheme.Colors.PageText)
                        elide: Text.ElideRight
                        font.pixelSize: Qt.application.font.pixelSize * root.titleFontSizeScalar
                        text: qsTr("درباره برنامه")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignTop
                        wrapMode: Text.NoWrap
                    }
                }

                UFOSection {
                    Layout.fillWidth: true

                    title: qsTr("اطلاعات کلی")

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("نسخه:") + " " + Qt.application.version
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.Wrap
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("این برنامه برای این ساخته شده است که متخصصان پوست بتوانند بدون دردسر بیماران را مدیریت کنند. این برنامه با Qt نسخه 6.8 ساخته شده است. از آخرین فناوری QtQuick استفاده می کند تا تجربه ای روان را فراهم کند. شما در حال حاضر با نسخه دستیار برنامه کار می کنید. برای نسخه پزشک برنامه، لطفاً از صفحه GitHub ما دیدن کنید تا یک بسته را دریافت کنید.")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.Wrap
                    }
                }

                UFOSection {
                    Layout.fillWidth: true

                    title: qsTr("پشتیبانی")

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("اگر این برنامه را مفید می‌دانید و می‌خواهید درباره راه‌های پشتیبانی از پروژه بیشتر بدانید، لطفاً با کلیک بر روی دکمه زیر از صفحه GitHub ما دیدن کنید.")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.Wrap
                    }

                    UFOButton {
                        id: buttonLink

                        Layout.preferredWidth: 120
                        Layout.preferredHeight: 35
                        Layout.topMargin: 20

                        display: AbstractButton.TextBesideIcon
                        text: "GitHub"
                        icon.source: "qrc:/resources/icons/material/open_in_browser.svg"

                        onClicked: {
                            Qt.openUrlExternally("https://github.com/Saviz-Mohammadi/DermaBase_DR")
                        }
                    }
                }
            }
        }
    }
}
