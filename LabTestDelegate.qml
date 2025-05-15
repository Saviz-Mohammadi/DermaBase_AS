import QtQuick
import QtQuick.Controls.impl
import QtQuick.Controls.Basic
import QtQuick.Layouts

Item {
    id: root

    signal updateClicked(labTestD: int,
                         newDate: string,
                         newOutcome: string,
                         int  CBC,
                         int  WBC,
                         int  Hgb,
                         int  Ferritin,
                         int  ESR,
                         int  Na,
                         int  K,
                         int  Mg,
                         int  VitaminD,
                         int  FBS,
                         int  TG,
                         int  Cholestrol,
                         int  AST,
                         int  ALT,
                         int  ALKPh,
                         int  BUN,
                         int  Cr,
                         int  UA,
                         int  SE_OB,
                         int  SE_OP,
                         int  H_Pylori_Ab,
                         int  H_Pylori_Ag_SE,
                         int  Tuberculin_test,
                         int  Pathergy_test,
                         int  Sonography,
                         int  TSH,
                         int  LH,
                         int  FSH,
                         int  DHEAS,
                         int  OH_P_17,
                         int  Prolactine,
                         int  Testosterone,
                         int  Hepatitis_Ag,
                         int  Hepatitis_Ab,
                         int  ANA,
                         int  Anti_DS_Ab,
                         int  Anti_SCL70_Ab,
                         int  IgE,
                         row: int);
    signal deleteClicked(row: int);

    property bool startCollapsed: true
    property real titleFontSizeScalar: 1.0
    property real separatorHeight: 2
    property real titleRightMargin: 0
    property real titleLeftMargin: 10
    property real contentTopMargin: 10
    property real contentBottomMargin: 10
    property real contentRightMargin: 10
    property real contentLeftMargin: 10
    readonly property int collapsedHeight: rectangleTitleBackground.implicitHeight
    readonly property int expandedHeight: rectangleTitleBackground.implicitHeight + rectangleSeparator.implicitHeight + rectangleContentBackground.implicitHeight + root.contentTopMargin + root.contentBottomMargin
    property color delegateTitleBackground: AppTheme.getColor(AppTheme.Colors.DelegateTitleBackground)
    property color delegateTitleTextColor: AppTheme.getColor(AppTheme.Colors.DelegateTitleText)
    property color delegateSeparatorColor: AppTheme.getColor(AppTheme.Colors.DelegateTitleSeparator)
    property color delegateContentBackgroundColor: AppTheme.getColor(AppTheme.Colors.DelegateContentBackground)

    implicitWidth: 200
    implicitHeight: buttonExpand.checked ? expandedHeight : collapsedHeight

    Rectangle {
        id: rectangleTitleBackground

        anchors.top: root.top
        anchors.right: root.right
        anchors.left: root.left

        implicitHeight: 35

        color: root.delegateTitleBackground

        RowLayout {
            anchors.fill: parent

            spacing: 0

            Item {
                Layout.preferredWidth: 10
            }

            Text {
                Layout.fillWidth: true
                Layout.fillHeight: true

                text: model.name + " (" + model.specialization + ")"
                color: root.delegateTitleTextColor
                elide: Text.ElideRight
                font.pixelSize: Qt.application.font.pixelSize
                wrapMode: Text.NoWrap
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
            }

            Item {
                Layout.preferredWidth: 5
            }

            UFOButton {
                id: buttonDelete

                Layout.preferredWidth: 120
                Layout.fillHeight: true

                display: AbstractButton.TextBesideIcon
                text: qsTr("حذف")
                icon.source: "qrc:/resources/icons/material/delete.svg"

                onClicked: {
                    root.deleteClicked(model.row);
                }
            }

            Item {
                Layout.preferredWidth: 5
            }

            UFOButton {
                id: buttonExpand

                Layout.preferredWidth: 50
                Layout.fillHeight: true

                display: AbstractButton.IconOnly
                checkable: true
                checked: !root.startCollapsed
                icon.source: checked ? "qrc:/resources/icons/material/keyboard_arrow_up.svg" : "qrc:/resources/icons/material/keyboard_arrow_down.svg"
            }
        }
    }

    Rectangle {
        id: rectangleSeparator

        anchors.top: rectangleTitleBackground.bottom
        anchors.right: root.right
        anchors.left: root.left

        implicitHeight: root.separatorHeight

        visible: buttonExpand.checked
        color: root.delegateSeparatorColor
    }

    Rectangle {
        id: rectangleContentBackground

        anchors.top: rectangleTitleBackground.bottom
        anchors.bottom: root.bottom
        anchors.right: root.right
        anchors.left: root.left

        implicitHeight: columnLayout.implicitHeight

        radius: 0
        visible: buttonExpand.checked
        color: root.delegateContentBackgroundColor

        Item {
            anchors.fill: parent
            anchors.topMargin: root.contentTopMargin
            anchors.bottomMargin: root.contentBottomMargin
            anchors.rightMargin: root.contentRightMargin
            anchors.leftMargin: root.contentLeftMargin

            // TODO (SAVIZ): In future you can add a colmun to the database that explains the diagnosis and show a 'Text' for it here.

            ColumnLayout {
                id: columnLayout

                width: parent.width

                clip: false
                spacing: 5

                Text {
                    Layout.fillWidth: true

                    color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                    elide: Text.ElideRight
                    text: qsTr("تاریخ تکمیل آزمایش")
                    textFormat: Text.PlainText
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.NoWrap
                }

                UFOTextField {
                    id: textFieldConsultationDate

                    Layout.preferredWidth: 250
                    Layout.preferredHeight: 35

                    horizontalAlignment: TextInput.AlignLeft
                    validator: RegularExpressionValidator {
                        regularExpression: /^[0-9]{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])$/
                    }

                    text: model.date
                }


                Flow {
                    Layout.fillWidth: true
                    Layout.topMargin: 20
                    Layout.bottomMargin: 20

                    LayoutMirroring.enabled: false
                    LayoutMirroring.childrenInherit: true

                    padding: 5
                    spacing: 5

                    // CBC
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("CBC")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldCBC
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.CBC
                        }
                    }

                    // WBC
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("WBC")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldWBC
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.WBC
                        }
                    }

                    // Hgb
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("Hgb")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldHgb
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.Hgb
                        }
                    }

                    // Ferritin
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("Ferritin")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldFerritin
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.Ferritin
                        }
                    }

                    // ESR
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("ESR")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldESR
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.ESR
                        }
                    }

                    // Na
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("Na")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldNa
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.Na
                        }
                    }

                    // K
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("K")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldK
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.K
                        }
                    }

                    // Mg
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("Mg")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldMg
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.Mg
                        }
                    }

                    // VitaminD
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("VitaminD")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldVitaminD
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.VitaminD
                        }
                    }

                    // FBS
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("FBS")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldFBS
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.FBS
                        }
                    }

                    // TG
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("TG")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldTG
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.TG
                        }
                    }

                    // Cholestrol
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("Cholestrol")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldCholestrol
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.Cholestrol
                        }
                    }

                    // AST
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("AST")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldAST
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.AST
                        }
                    }

                    // ALT
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("ALT")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldALT
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.ALT
                        }
                    }

                    // ALKPh
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("ALKPh")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldALKPh
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.ALKPh
                        }
                    }

                    // BUN
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("BUN")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldBUN
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.BUN
                        }
                    }

                    // Cr
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("Cr")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldCr
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.Cr
                        }
                    }

                    // UA
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("UA")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldUA
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.UA
                        }
                    }

                    // SE_OB
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("SE_OB")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldSE_OB
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.SE_OB
                        }
                    }

                    // SE_OP
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("SE_OP")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldSE_OP
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.SE_OP
                        }
                    }

                    // H_Pylori_Ab
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("H_Pylori_Ab")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldH_Pylori_Ab
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.H_Pylori_Ab
                        }
                    }

                    // H_Pylori_Ag_SE
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("H_Pylori_Ag_SE")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldH_Pylori_Ag_SE
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.H_Pylori_Ag_SE
                        }
                    }

                    // Tuberculin_test
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("Tuberculin_test")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldTuberculin_test
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.Tuberculin_test
                        }
                    }

                    // Pathergy_test
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("Pathergy_test")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldPathergy_test
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.Pathergy_test
                        }
                    }

                    // Sonography
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("Sonography")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldSonography
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.Sonography
                        }
                    }

                    // TSH
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("TSH")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldTSH
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.TSH
                        }
                    }

                    // LH
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("LH")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldLH
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.LH
                        }
                    }

                    // FSH
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("FSH")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldFSH
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.FSH
                        }
                    }

                    // DHEAS
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("DHEAS")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldDHEAS
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.DHEAS
                        }
                    }

                    // OH_P_17
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("17_OH_P")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldOH_P_17
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.OH_P_17
                        }
                    }

                    // Prolactine
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("Prolactine")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldProlactine
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.Prolactine
                        }
                    }

                    // Testosterone
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("Testosterone")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldTestosterone
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.Testosterone
                        }
                    }

                    // Hepatitis_Ag
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("Hepatitis_Ag")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldHepatitis_Ag
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.Hepatitis_Ag
                        }
                    }

                    // Hepatitis_Ab
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("Hepatitis_Ab")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldHepatitis_Ab
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.Hepatitis_Ab
                        }
                    }

                    // ANA
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("ANA")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldANA
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.ANA
                        }
                    }

                    // Anti_DS_Ab
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("Anti_DS_Ab")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldAnti_DS_Ab
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.Anti_DS_Ab
                        }
                    }

                    // Anti_SCL70_Ab
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("Anti_SCL70_Ab")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldAnti_SCL70_Ab
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.Anti_SCL70_Ab
                        }
                    }

                    // IgE
                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            Layout.preferredWidth: 100
                            color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                            elide: Text.ElideRight
                            text: qsTr("IgE")
                            textFormat: Text.PlainText
                            verticalAlignment: Text.AlignVCenter
                            wrapMode: Text.NoWrap
                        }

                        UFOTextField {
                            id: textFieldIgE
                            Layout.preferredWidth: 40
                            Layout.preferredHeight: 35
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator { bottom: 0; top: 9999 }
                            text: model.IgE
                        }
                    }
                }

                Text {
                    Layout.fillWidth: true

                    color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                    elide: Text.ElideRight
                    text: qsTr("نتیجه آزمایش")
                    textFormat: Text.PlainText
                    verticalAlignment: Text.AlignVCenter
                    wrapMode: Text.NoWrap
                }

                ScrollView {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 100

                    UFOTextArea {
                        id: textAreaConsultationOutcome

                        text: model.outcome
                    }
                }

                UFOButton {
                    id: buttonUpdate

                    Layout.preferredWidth: 120
                    Layout.preferredHeight: 35
                    Layout.topMargin: 20

                    display: AbstractButton.TextBesideIcon
                    text: qsTr("آپدیت")
                    icon.source: "qrc:/resources/icons/material/autorenew.svg"

                    onClicked: {
                        if (!textFieldConsultationDate.acceptableInput) {
                            mainDialog.title = qsTr("ورودی ارائه شده به قسمت تاریخ تکمیل مشاوره صحیح نیست.") + "\n" + qsTr("لطفاً قبل از ادامه تاریخ صحیح را وارد کنید.");
                            mainDialog.identifier = "Search";
                            mainDialog.standardButtons = Dialog.Ok;
                            mainDialog.modal = true;
                            mainDialog.open();

                            return;
                        }

                        let newDate = textFieldConsultationDate.text;
                        let newOutcome = textAreaConsultationOutcome.text;
                        let CBC               = parseInt(textFieldCBC.text, 10);
                        let WBC               = parseInt(textFieldWBC.text, 10);
                        let Hgb               = parseInt(textFieldHgb.text, 10);
                        let Ferritin          = parseInt(textFieldFerritin.text, 10);
                        let ESR               = parseInt(textFieldESR.text, 10);
                        let Na                = parseInt(textFieldNa.text, 10);
                        let K                 = parseInt(textFieldK.text, 10);
                        let Mg                = parseInt(textFieldMg.text, 10);
                        let VitaminD          = parseInt(textFieldVitaminD.text, 10);
                        let FBS               = parseInt(textFieldFBS.text, 10);
                        let TG                = parseInt(textFieldTG.text, 10);
                        let Cholestrol        = parseInt(textFieldCholestrol.text, 10);
                        let AST               = parseInt(textFieldAST.text, 10);
                        let ALT               = parseInt(textFieldALT.text, 10);
                        let ALKPh             = parseInt(textFieldALKPh.text, 10);
                        let BUN               = parseInt(textFieldBUN.text, 10);
                        let Cr                = parseInt(textFieldCr.text, 10);
                        let UA                = parseInt(textFieldUA.text, 10);
                        let SE_OB             = parseInt(textFieldSE_OB.text, 10);
                        let SE_OP             = parseInt(textFieldSE_OP.text, 10);
                        let H_Pylori_Ab       = parseInt(textFieldH_Pylori_Ab.text, 10);
                        let H_Pylori_Ag_SE    = parseInt(textFieldH_Pylori_Ag_SE.text, 10);
                        let Tuberculin_test   = parseInt(textFieldTuberculin_test.text, 10);
                        let Pathergy_test     = parseInt(textFieldPathergy_test.text, 10);
                        let Sonography        = parseInt(textFieldSonography.text, 10);
                        let TSH               = parseInt(textFieldTSH.text, 10);;
                        let LH                = parseInt(textFieldLH.text, 10);
                        let FSH               = parseInt(textFieldFSH.text, 10);
                        let DHEAS             = parseInt(textFieldDHEAS.text, 10);
                        let OH_P_17           = parseInt(textFieldOH_P_17.text, 10);
                        let Prolactine        = parseInt(textFieldProlactine.text, 10);
                        let Testosterone      = parseInt(textFieldTestosterone.text, 10);
                        let Hepatitis_Ag      = parseInt(textFieldHepatitis_Ag.text, 10);
                        let Hepatitis_Ab      = parseInt(textFieldHepatitis_Ab.text, 10);
                        let ANA               = parseInt(textFieldANA.text, 10);
                        let Anti_DS_Ab        = parseInt(textFieldAnti_DS_Ab.text, 10);
                        let Anti_SCL70_Ab     = parseInt(textFieldAnti_SCL70_Ab.text, 10);
                        let IgE               = parseInt(textFieldIgE.text, 10);

                        root.updateClicked(model.labTestID, newDate, newOutcome,
                                           CBC, WBC, Hgb, Ferritin, ESR,
                                                           Na, K, Mg, VitaminD, FBS,
                                                           TG, Cholestrol, AST, ALT,
                                                           ALKPh, BUN, Cr, UA,
                                                           SE_OB, SE_OP, H_Pylori_Ab,
                                                           H_Pylori_Ag_SE, Tuberculin_test,
                                                           Pathergy_test, Sonography,
                                                           TSH, LH, FSH, DHEAS,
                                                           OH_P_17, Prolactine, Testosterone,
                                                           Hepatitis_Ag, Hepatitis_Ab,
                                                           ANA, Anti_DS_Ab, Anti_SCL70_Ab,
                                                           IgE,
                                           model.row);
                    }
                }
            }
        }
    }
}
