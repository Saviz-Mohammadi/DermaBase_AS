import QtQuick
import QtQuick.Controls.impl
import QtQuick.Controls.Basic
import QtQuick.Layouts

// Custom CPP:
import SearchModel 1.0

Item {
    id: root

    signal patientSelectedForEdit(patientID: int);

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
                        icon.source: "qrc:/resources/icons/material/person_search.svg"
                        icon.color: AppTheme.getColor(AppTheme.Colors.PageIcon)
                    }

                    Text {
                        Layout.preferredHeight: 40

                        color: AppTheme.getColor(AppTheme.Colors.PageText)
                        elide: Text.ElideRight
                        font.pixelSize: Qt.application.font.pixelSize * root.titleFontSizeScalar
                        text: qsTr("جستجو بیمار")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignTop
                        wrapMode: Text.NoWrap
                    }
                }

                UFOSection {
                    Layout.fillWidth: true

                    startCollapsed: true
                    title: qsTr("جستجو با شماره پرونده")

                    Text {
                        Layout.fillWidth: true
                        Layout.bottomMargin: 20

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("از فیلد ورودی زیر برای جستجوی دقیق بیمار با شماره پرونده استفاده کنید.")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.Wrap
                    }

                    UFOButton {
                        id: buttonClearIDSection

                        Layout.preferredWidth: 120
                        Layout.preferredHeight: 35
                        Layout.bottomMargin: 20

                        display: AbstractButton.TextBesideIcon
                        text: qsTr("پاک کردن")
                        icon.source: "qrc:/resources/icons/material/delete.svg"
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("شماره پرونده")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.NoWrap
                    }

                    UFOTextField {
                        id: textFieldPatientID

                        Layout.preferredWidth: 250
                        Layout.preferredHeight: 35

                        horizontalAlignment: TextInput.AlignLeft
                        validator: IntValidator {
                            bottom: 0
                        }

                        Connections {
                            target: buttonClearIDSection

                            function onClicked() {
                                textFieldPatientID.clear();
                            }
                        }
                    }

                    UFOButton {
                        id: buttonSearchID

                        Layout.preferredWidth: 120
                        Layout.preferredHeight: 35
                        Layout.topMargin: 20

                        display: AbstractButton.TextBesideIcon
                        text: qsTr("جستجو بیمار")
                        icon.source: "qrc:/resources/icons/material/person_search.svg"

                        onClicked: {
                            if (!textFieldPatientID.acceptableInput) {
                                mainDialog.title = qsTr("ورودی ارائه شده به قسمت ورودی شماره پرونده صحیح نیست.") + "\n" + qsTr("لطفاً قبل از ادامه شماره پرونده صحیح را وارد کنید.");
                                mainDialog.identifier = "Search";
                                mainDialog.standardButtons = Dialog.Ok;
                                mainDialog.modal = true;
                                mainDialog.open();

                                return;
                            }

                            let patientID = parseInt(textFieldPatientID.text, 10);

                            mainDatabase.findPatient(patientID);
                        }
                    }
                }

                UFOSection {
                    Layout.fillWidth: true

                    startCollapsed: true
                    title: qsTr("جستجوی بیماران اول/آخر با سقف دلخواه")

                    Text {
                        Layout.fillWidth: true
                        Layout.bottomMargin: 20

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("از فیلد زیر برای جستجوی اولین یا آخرین بیمارها با سقف دلخواه استفاده کنید.")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.Wrap
                    }

                    UFOButton {
                        id: buttonClearFirstOrLastNSection

                        Layout.preferredWidth: 120
                        Layout.preferredHeight: 35
                        Layout.bottomMargin: 20

                        display: AbstractButton.TextBesideIcon
                        text: qsTr("پاک کردن")
                        icon.source: "qrc:/resources/icons/material/delete.svg"
                    }

                    UFOComboBox {
                        id: comboBoxFirstOrLastN

                        Layout.preferredWidth: 250
                        Layout.preferredHeight: 35

                        model: ListModel {
                            ListElement {name: "اول"}
                            ListElement {name: "آخر"}
                        }

                        Connections {
                            target: buttonClearFirstOrLastNSection

                            function onClicked() {
                                comboBoxFirstOrLastN.currentIndex = 0;
                            }
                        }
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("تعداد رکوردها")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.NoWrap
                    }

                    UFOTextField {
                        id: textFieldFirstOrLastN

                        Layout.preferredWidth: 250
                        Layout.preferredHeight: 35

                        horizontalAlignment: TextInput.AlignLeft
                        validator: IntValidator {
                            bottom: 0
                        }

                        Connections {
                            target: buttonClearFirstOrLastNSection

                            function onClicked() {
                                textFieldFirstOrLastN.clear();
                            }
                        }
                    }

                    UFOButton {
                        id: buttonSearchFirstOrLastN

                        Layout.preferredWidth: 120
                        Layout.preferredHeight: 35
                        Layout.topMargin: 20

                        display: AbstractButton.TextBesideIcon
                        text: qsTr("جستجو بیمار")
                        icon.source: "qrc:/resources/icons/material/person_search.svg"

                        onClicked: {
                            if (!textFieldFirstOrLastN.acceptableInput) {
                                mainDialog.title = qsTr("ورودی ارائه شده به قسمت ورودی شمارش صحیح نیست.") + "\n" + qsTr("لطفاً قبل از ادامه شمارش صحیح را وارد کنید.");
                                mainDialog.identifier = "Search";
                                mainDialog.standardButtons = Dialog.Ok;
                                mainDialog.modal = true;
                                mainDialog.open();

                                return;
                            }

                            let count = parseInt(textFieldFirstOrLastN.text, 10);

                            switch(comboBoxFirstOrLastN.currentIndex) {
                            case 0:
                                mainDatabase.findFirstPatients(count);
                                break;
                            case 1:
                                mainDatabase.findLastPatients(count);
                                break;
                            default:
                                break;
                            }
                        }
                    }
                }

                UFOSection {
                    Layout.fillWidth: true

                    startCollapsed: true
                    title: qsTr("جستجو با اطلاعات دیگر")

                    Text {
                        Layout.fillWidth: true
                        Layout.bottomMargin: 20

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("برای جستجوی بیماران از فیلدهای ورودی زیر استفاده کنید. لطفاً توجه داشته باشید که هر چه فیلدهای بیشتری برای ورودی ارائه دهید، نتیجه جستجو دقیق تر خواهد بود.")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.Wrap
                    }

                    UFOButton {
                        id: buttonClearOtherSection

                        Layout.preferredWidth: 120
                        Layout.preferredHeight: 35
                        Layout.bottomMargin: 20

                        display: AbstractButton.TextBesideIcon
                        text: qsTr("پاک کردن")
                        icon.source: "qrc:/resources/icons/material/delete.svg"
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("نام")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.NoWrap
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        spacing: 5

                        UFOTextField {
                            id: textFieldFirstName

                            Layout.preferredWidth: 250
                            Layout.preferredHeight: 35

                            enabled: checkBoxFirstName.checked
                            horizontalAlignment: TextInput.AlignLeft
                            validator: RegularExpressionValidator {
                                regularExpression: /^[\p{L}]+(?:[ '\-][\p{L}]+)*$/u
                            }

                            Connections {
                                target: buttonClearOtherSection

                                function onClicked() {
                                    textFieldFirstName.clear();
                                }
                            }
                        }

                        UFOCheckBox {
                            id: checkBoxFirstName

                            Layout.preferredWidth: 35
                            Layout.preferredHeight: 35

                            checked: false

                            Connections {
                                target: buttonClearOtherSection

                                function onClicked() {
                                    checkBoxFirstName.checked = false;
                                }
                            }
                        }
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("نام خانوادگی")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.NoWrap
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        spacing: 5

                        UFOTextField {
                            id: textFieldLastName

                            Layout.preferredWidth: 250
                            Layout.preferredHeight: 35

                            enabled: checkBoxLastName.checked
                            horizontalAlignment: TextInput.AlignLeft
                            validator: RegularExpressionValidator {
                                regularExpression: /^[\p{L}]+(?: [\p{L}]+)*$/u
                            }

                            Connections {
                                target: buttonClearOtherSection

                                function onClicked() {
                                    textFieldLastName.clear();
                                }
                            }
                        }

                        UFOCheckBox {
                            id: checkBoxLastName

                            Layout.preferredWidth: 35
                            Layout.preferredHeight: 35

                            checked: false

                            Connections {
                                target: buttonClearOtherSection

                                function onClicked() {
                                    checkBoxLastName.checked = false;
                                }
                            }
                        }
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("شروع سال تولد")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.NoWrap
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        spacing: 5

                        UFOTextField {
                            id: textFieldBirthYearStart

                            Layout.preferredWidth: 250
                            Layout.preferredHeight: 35

                            enabled: checkBoxBirthYearStart.checked
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator {
                                top: 9999
                                bottom: 0
                            }

                            Connections {
                                target: buttonClearOtherSection

                                function onClicked() {
                                    textFieldBirthYearStart.clear();
                                }
                            }
                        }

                        UFOCheckBox {
                            id: checkBoxBirthYearStart

                            Layout.preferredWidth: 35
                            Layout.preferredHeight: 35

                            checked: false

                            Connections {
                                target: buttonClearOtherSection

                                function onClicked() {
                                    checkBoxBirthYearStart.checked = false;
                                }
                            }
                        }
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("پایان سال تولد")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.NoWrap
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        spacing: 5

                        UFOTextField {
                            id: textFieldBirthYearEnd

                            Layout.preferredWidth: 250
                            Layout.preferredHeight: 35

                            enabled: checkBoxBirthYearEnd.checked
                            horizontalAlignment: TextInput.AlignLeft
                            validator: IntValidator {
                                top: 9999
                                bottom: 0
                            }

                            Connections {
                                target: buttonClearOtherSection

                                function onClicked() {
                                    textFieldBirthYearEnd.clear();
                                }
                            }
                        }

                        UFOCheckBox {
                            id: checkBoxBirthYearEnd

                            Layout.preferredWidth: 35
                            Layout.preferredHeight: 35

                            checked: false

                            Connections {
                                target: buttonClearOtherSection

                                function onClicked() {
                                    checkBoxBirthYearEnd.checked = false;
                                }
                            }
                        }
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("شماره تلفن")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.NoWrap
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        spacing: 5

                        UFOTextField {
                            id: textFieldPhoneNumber

                            Layout.preferredWidth: 250
                            Layout.preferredHeight: 35

                            enabled: checkBoxPhoneNumber.checked
                            horizontalAlignment: TextInput.AlignLeft
                            validator: RegularExpressionValidator {
                                regularExpression: /^[0-9][0-9]{1,14}$/
                            }

                            Connections {
                                target: buttonClearOtherSection

                                function onClicked() {
                                    textFieldPhoneNumber.clear();
                                }
                            }
                        }

                        UFOCheckBox {
                            id: checkBoxPhoneNumber

                            Layout.preferredWidth: 35
                            Layout.preferredHeight: 35

                            checked: false

                            Connections {
                                target: buttonClearOtherSection

                                function onClicked() {
                                    checkBoxPhoneNumber.checked = false;
                                }
                            }
                        }
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("جنسیت")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.NoWrap
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        spacing: 5

                        UFOComboBox {
                            id: comboBoxGender

                            Layout.preferredWidth: 250
                            Layout.preferredHeight: 35

                            currentIndex: 0
                            enabled: checkBoxGender.checked
                            model: ["نامشخص", "مرد", "زن"]

                            Connections {
                                target: buttonClearOtherSection

                                function onClicked() {
                                    comboBoxGender.currentIndex = 0;
                                }
                            }
                        }

                        UFOCheckBox {
                            id: checkBoxGender

                            Layout.preferredWidth: 35
                            Layout.preferredHeight: 35

                            checked: false

                            Connections {
                                target: buttonClearOtherSection

                                function onClicked() {
                                    checkBoxGender.checked = false;
                                }
                            }
                        }
                    }

                    Text {
                        Layout.fillWidth: true

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("وضعیت تاهل")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.NoWrap
                    }

                    RowLayout {
                        Layout.fillWidth: true

                        spacing: 5

                        UFOComboBox {
                            id: comboBoxMaritalStatus

                            Layout.preferredWidth: 250
                            Layout.preferredHeight: 35

                            currentIndex: 0
                            enabled: checkBoxMaritalStatus.checked
                            model: ["نامشخص", "مجرد", "متاهل"]

                            Connections {
                                target: buttonClearOtherSection

                                function onClicked() {
                                    comboBoxMaritalStatus.currentIndex = 0;
                                }
                            }
                        }

                        UFOCheckBox {
                            id: checkBoxMaritalStatus

                            Layout.preferredWidth: 35
                            Layout.preferredHeight: 35

                            checked: false

                            Connections {
                                target: buttonClearOtherSection

                                function onClicked() {
                                    checkBoxMaritalStatus.checked = false;
                                }
                            }
                        }
                    }

                    UFOButton {
                        id: buttonSearchOther

                        Layout.preferredWidth: 120
                        Layout.preferredHeight: 35
                        Layout.topMargin: 20

                        display: AbstractButton.TextBesideIcon
                        enabled: textFieldFirstName.enabled || textFieldLastName.enabled || textFieldBirthYearStart.enabled || textFieldBirthYearEnd.enabled || textFieldPhoneNumber.enabled || comboBoxGender.enabled || comboBoxMaritalStatus.enabled
                        text: qsTr("جستجو بیمار")
                        icon.source: "qrc:/resources/icons/material/person_search.svg"

                        onClicked: {
                            let mask = 0;
                            let firstNameIsEnabled = textFieldFirstName.enabled;
                            let lastNameIsEnabled = textFieldLastName.enabled;
                            let birthYearStartEnabled = textFieldBirthYearStart.enabled;
                            let birthYearEndEnabled = textFieldBirthYearEnd.enabled;
                            let phoneNumberEnabled = textFieldPhoneNumber.enabled;
                            let genderEnabled = comboBoxGender.enabled;
                            let maritalStatusEnabled = comboBoxMaritalStatus.enabled;
                            let firstName = "";
                            let lastName = "";
                            let birthYearStart = 0;
                            let birthYearEnd = 0;
                            let phoneNumber = "";
                            let gender = "";
                            let maritalStatus = "";

                            if(firstNameIsEnabled) {
                                if (!textFieldFirstName.acceptableInput) {
                                    mainDialog.title = qsTr("ورودی ارائه شده به قسمت ورودی نام صحیح نیست.") + "\n" + qsTr("لطفاً قبل از ادامه نام صحیح را وارد کنید.");
                                    mainDialog.identifier = "Search";
                                    mainDialog.standardButtons = Dialog.Ok;
                                    mainDialog.modal = true;
                                    mainDialog.open();

                                    return;
                                }

                                firstName = textFieldFirstName.text;
                                mask |= 1 << 0;
                            }

                            if(lastNameIsEnabled) {
                                if (lastNameIsEnabled && !textFieldLastName.acceptableInput) {
                                    mainDialog.title = qsTr("ورودی ارائه شده به قسمت ورودی نام خانوادگی صحیح نیست.") + "\n" + qsTr("لطفاً قبل از ادامه نام خانوادگی صحیح را وارد کنید.");
                                    mainDialog.identifier = "Search";
                                    mainDialog.standardButtons = Dialog.Ok;
                                    mainDialog.modal = true;
                                    mainDialog.open();

                                    return;
                                }

                                lastName = textFieldLastName.text;
                                mask |= 1 << 1;
                            }

                            if(birthYearStartEnabled) {
                                if (!textFieldBirthYearStart.acceptableInput) {
                                    mainDialog.title = qsTr("ورودی ارائه شده به فیلد ورودی شروع سال تولد صحیح نیست.") + "\n" + qsTr("لطفاً قبل از ادامه، شروع سال تولد صحیح را ارائه دهید.");
                                    mainDialog.identifier = "Search";
                                    mainDialog.standardButtons = Dialog.Ok;
                                    mainDialog.modal = true;
                                    mainDialog.open();

                                    return;
                                }

                                birthYearStart = parseInt(textFieldBirthYearStart.text, 10);
                                mask |= 1 << 2;
                            }

                            if(birthYearEndEnabled) {
                                if (!textFieldBirthYearEnd.acceptableInput) {
                                    mainDialog.title = qsTr("ورودی ارائه شده به فیلد ورودی پایان سال تولد صحیح نیست.") + "\n" + qsTr("لطفاً قبل از ادامه، پایان سال تولد صحیح را ارائه دهید.");
                                    mainDialog.identifier = "Search";
                                    mainDialog.standardButtons = Dialog.Ok;
                                    mainDialog.modal = true;
                                    mainDialog.open();

                                    return;
                                }

                                birthYearEnd = parseInt(textFieldBirthYearEnd.text, 10);
                                mask |= 1 << 3;
                            }

                            if(phoneNumberEnabled) {
                                if (!textFieldPhoneNumber.acceptableInput) {
                                    mainDialog.title = qsTr("ورودی ارائه شده به قسمت ورودی شماره تلفن صحیح نیست.") + "\n" + qsTr("لطفاً قبل از ادامه یک شماره تلفن صحیح ارائه دهید.");
                                    mainDialog.identifier = "Search";
                                    mainDialog.standardButtons = Dialog.Ok;
                                    mainDialog.modal = true;
                                    mainDialog.open();

                                    return;
                                }

                                phoneNumber = textFieldPhoneNumber.text;
                                mask |= 1 << 4;
                            }

                            if(genderEnabled) {
                                gender = comboBoxGender.currentText;
                                mask |= 1 << 5;
                            }

                            if(maritalStatusEnabled) {
                                maritalStatus = comboBoxMaritalStatus.currentText;
                                mask |= 1 << 6;
                            }

                            mainDatabase.findPatients(
                                mask,
                                firstName,
                                lastName,
                                birthYearStart,
                                birthYearEnd,
                                phoneNumber,
                                gender,
                                maritalStatus
                            );
                        }
                    }
                }

                UFOSection {
                    Layout.fillWidth: true

                    title: qsTr("نتایج جستجو")

                    Text {
                        Layout.fillWidth: true
                        Layout.bottomMargin: 20

                        color: AppTheme.getColor(AppTheme.Colors.SectionContentText)
                        elide: Text.ElideRight
                        text: qsTr("لیست زیر تمام بیمارانی را که پایگاه داده توانسته است پیدا کند نشان می دهد.")
                        textFormat: Text.PlainText
                        verticalAlignment: Text.AlignVCenter
                        wrapMode: Text.Wrap
                    }

                    UFOButton {
                        id: buttonClearListSearch

                        Layout.preferredWidth: 120
                        Layout.preferredHeight: 35
                        Layout.bottomMargin: 20

                        display: AbstractButton.TextBesideIcon
                        text: qsTr("پاک کردن")
                        icon.source: "qrc:/resources/icons/material/delete.svg"

                        Connections {
                            target: mainDatabase

                            function onStartedFinding() {
                                buttonClearListSearch.enabled = false;
                            }

                            function onFinishedFinding(status: int, message: string, data) {
                                buttonClearListSearch.enabled = true;
                            }
                        }
                    }

                    ListView {
                        id: listViewSearch

                        Layout.fillWidth: true
                        Layout.preferredHeight: 350

                        clip: true
                        spacing: 7

                        SearchModel {
                            id: searchModel

                            database: mainDatabase
                        }

                        model: searchModel

                        delegate: SearchDelegate {
                            width: listViewSearch.width

                            onEditClicked: function(patientID) {
                                root.patientSelectedForEdit(patientID)
                            }
                        }

                        Connections {
                            target: buttonClearListSearch

                            function onClicked() {
                                searchModel.clear();
                            }
                        }

                        Connections {
                            target: mainDatabase

                            function onStartedFinding() {
                                listViewSearch.enabled = false;
                            }

                            function onFinishedFinding(status: int, message: string, data) {
                                listViewSearch.enabled = true;
                            }
                        }
                    }
                }
            }
        }
    }
}
