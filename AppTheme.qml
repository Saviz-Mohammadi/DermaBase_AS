pragma Singleton

import QtQuick

Item {
    id: root

    // NOTE (SAVIZ): Just in case someone wants to perform experiments with colors:
    readonly property alias predefinedColors: predefinedColors

    // Theme names:
    enum Themes {
        UFOLight,
        UFODark
    }

    // Components' color:
    enum Colors {
        // Basic:
        PageBackground,
        PageIcon,
        PageText,

        // Controls:
        ButtonBackgroundNormal,
        ButtonBackgroundHovered,
        ButtonBackgroundChecked,
        ButtonBackgroundDown,
        ButtonIconNormal,
        ButtonIconHovered,
        ButtonIconChecked,
        ButtonIconDown,
        ButtonTextNormal,
        ButtonTextHovered,
        ButtonTextChecked,
        ButtonTextDown,
        ButtonBorder,
        TextFieldBackground,
        TextFieldPlaceHolderText,
        TextFieldTextSelectedBackground,
        TextFieldTextSelected,
        TextFieldTextNormal,
        TextFieldBorderNormal,
        TextFieldBorderFocused,
        TextAreaBackground,
        TextAreaPlaceHolderText,
        TextAreaTextSelectedBackground,
        TextAreaTextSelected,
        TextAreaTextNormal,
        TextAreaBorderNormal,
        TextAreaBorderFocused,
        StatusBarBackground,
        StatusBarText,
        DialogBackground,
        DialogBorder,
        DialogButtonBackground,
        DialogTextBackground,
        DialogText,
        ComboBoxDropDownBackgroundNormal,
        ComboBoxDropDownBackgroundDown,
        ComboBoxDropDownTextNormal,
        ComboBoxDropDownTextPressed,
        ComboBoxDropDownBorder,
        ComboBoxIndicatorNormal,
        ComboBoxIndicatorPressed,
        ComboBoxPopupBorder,
        ComboBoxTextInputBackground,
        ComboBoxTextInputBorder,
        ComboBoxTextInputText,
        ComboBoxDelegateBackgroundNormal,
        ComboBoxDelegateBackgroundHighlighted,
        ComboBoxDelegateTextNormal,
        ComboBoxDelegateTextHighlighted,
        CheckBoxIndicatorBackgroundNormal,
        CheckBoxIndicatorBackgroundDown,
        CheckBoxIndicatorBorderNormal,
        CheckBoxIndicatorBorderFocused,
        CheckBoxIndicatorFiller,
        CheckBoxText,

        // Delegate:
        DelegateTitleBackground,
        DelegateTitleText,
        DelegateTitleSeparator,
        DelegateContentBackground,
        DelegateContentText,

        // Custom:
        ToastBackgroundSuccess,
        ToastBackgroundInfo,
        ToastBackgroundWarning,
        ToastBackgroundError,
        ToastIconSuccess,
        ToastIconInfo,
        ToastIconWarning,
        ToastIconError,
        ToastTextSuccess,
        ToastTextInfo,
        ToastTextWarning,
        ToastTextError,
        SectionTitleBackground,
        SectionTitleText,
        SectionTitleSeparator,
        SectionContentBackground,
        SectionContentText
    }

    QtObject {
        id: qtObjectProperties

        property int currentTheme: Themes.UFOLight
    }

    QtObject {
        id: predefinedColors

        // Lime:
        readonly property color lime100: "#EFFFD6"
        readonly property color lime200: "#D3F1A7"
        readonly property color lime300: "#B3DF72"
        readonly property color lime400: "#94C748"
        readonly property color lime500: "#82B536"
        readonly property color lime600: "#6A9A23"
        readonly property color lime700: "#5B7F24"
        readonly property color lime800: "#4C6B1F"
        readonly property color lime900: "#37471F"

        // Red:
        readonly property color red100: "#FFECEB"
        readonly property color red200: "#FFD5D2"
        readonly property color red300: "#FD9891"
        readonly property color red400: "#F87168"
        readonly property color red500: "#F15B50"
        readonly property color red600: "#E2483D"
        readonly property color red700: "#C9372C"
        readonly property color red800: "#AE2E24"
        readonly property color red900: "#5D1F1A"

        // Orange:
        readonly property color orange100: "#FFF3EB"
        readonly property color orange200: "#FEDEC8"
        readonly property color orange300: "#FEC195"
        readonly property color orange400: "#FEA362"
        readonly property color orange500: "#F38A3F"
        readonly property color orange600: "#E56910"
        readonly property color orange700: "#C25100"
        readonly property color orange800: "#A54800"
        readonly property color orange900: "#702E00"

        // Yellow:
        readonly property color yellow100: "#FFF7D6"
        readonly property color yellow200: "#F8E6A0"
        readonly property color yellow300: "#F5CD47"
        readonly property color yellow400: "#E2B203"
        readonly property color yellow500: "#CF9F02"
        readonly property color yellow600: "#B38600"
        readonly property color yellow700: "#946F00"
        readonly property color yellow800: "#7F5F01"
        readonly property color yellow900: "#533F04"

        // Green colors
        readonly property color green100: "#DCFFF1"
        readonly property color green200: "#BAF3DB"
        readonly property color green300: "#7EE2B8"
        readonly property color green400: "#4BCE97"
        readonly property color green500: "#2ABB7F"
        readonly property color green600: "#22A06B"
        readonly property color green700: "#1F845A"
        readonly property color green800: "#216E4E"
        readonly property color green900: "#164B35"

        // Teal:
        readonly property color teal100: "#E7F9FF"
        readonly property color teal200: "#C6EDFB"
        readonly property color teal300: "#9DD9EE"
        readonly property color teal400: "#6CC3E0"
        readonly property color teal500: "#42B2D7"
        readonly property color teal600: "#2898BD"
        readonly property color teal700: "#227D9B"
        readonly property color teal800: "#206A83"
        readonly property color teal900: "#164555"

        // Blue:
        readonly property color blue100: "#E9F2FF"
        readonly property color blue200: "#CCE0FF"
        readonly property color blue300: "#85B8FF"
        readonly property color blue400: "#579DFF"
        readonly property color blue500: "#388BFF"
        readonly property color blue600: "#1D7AFC"
        readonly property color blue700: "#0C66E4"
        readonly property color blue800: "#0055CC"
        readonly property color blue900: "#09326C"

        // Purple:
        readonly property color purple100: "#F3F0FF"
        readonly property color purple200: "#DFD8FD"
        readonly property color purple300: "#B8ACF6"
        readonly property color purple400: "#9F8FEF"
        readonly property color purple500: "#8F7EE7"
        readonly property color purple600: "#8270DB"
        readonly property color purple700: "#6E5DC6"
        readonly property color purple800: "#5E4DB2"
        readonly property color purple900: "#352C63"

        // Grey:
        readonly property color grey100: "#F8F9FA"
        readonly property color grey200: "#E9ECEF"
        readonly property color grey300: "#DEE2E6"
        readonly property color grey400: "#CED4DA"
        readonly property color grey500: "#ADB5BD"
        readonly property color grey600: "#6C757D"
        readonly property color grey700: "#495057"
        readonly property color grey800: "#343A40"
        readonly property color grey900: "#212529"
    }

    QtObject {
        id: componentColors

        // Basic:
        property color pageBackground: "transparent"
        property color pageIcon: "transparent"
        property color pageText: "transparent"

        // Controls:
        property color buttonBackgroundNormal: "transparent"
        property color buttonBackgroundHovered: "transparent"
        property color buttonBackgroundChecked: "transparent"
        property color buttonBackgroundDown: "transparent"
        property color buttonIconNormal: "transparent"
        property color buttonIconHovered: "transparent"
        property color buttonIconChecked: "transparent"
        property color buttonIconDown: "transparent"
        property color buttonTextNormal: "transparent"
        property color buttonTextHovered: "transparent"
        property color buttonTextChecked: "transparent"
        property color buttonTextDown: "transparent"
        property color buttonBorder: "transparent"
        property color textFieldBackground: "transparent"
        property color textFieldPlaceHolderText: "transparent"
        property color textFieldTextSelectedBackground: "transparent"
        property color textFieldTextSelected: "transparent"
        property color textFieldTextNormal: "transparent"
        property color textFieldBorderNormal: "transparent"
        property color textFieldBorderFocused: "transparent"
        property color textAreaBackground: "transparent"
        property color textAreaPlaceHolderText: "transparent"
        property color textAreaTextSelectedBackground: "transparent"
        property color textAreaTextSelected: "transparent"
        property color textAreaTextNormal: "transparent"
        property color textAreaBorderNormal: "transparent"
        property color textAreaBorderFocused: "transparent"
        property color statusBarBackground: "transparent"
        property color statusBarText: "transparent"
        property color dialogBackground: "transparent"
        property color dialogBorder: "transparent"
        property color dialogButtonBackground: "transparent"
        property color dialogTextBackground: "transparent"
        property color dialogText: "transparent"
        property color comboBoxDropDownBackgroundNormal: "transparent"
        property color comboBoxDropDownBackgroundDown: "transparent"
        property color comboBoxDropDownTextNormal: "transparent"
        property color comboBoxDropDownTextPressed: "transparent"
        property color comboBoxDropDownBorder: "transparent"
        property color comboBoxIndicatorNormal: "transparent"
        property color comboBoxIndicatorPressed: "transparent"
        property color comboBoxPopupBorder: "transparent"
        property color comboBoxTextInputBackground: "transparent"
        property color comboBoxTextInputBorder: "transparent"
        property color comboBoxTextInputText: "transparent"
        property color comboBoxDelegateBackgroundNormal: "transparent"
        property color comboBoxDelegateBackgroundHighlighted: "transparent"
        property color comboBoxDelegateTextNormal: "transparent"
        property color comboBoxDelegateTextHighlighted: "transparent"
        property color checkBoxIndicatorBackgroundNormal: "transparent"
        property color checkBoxIndicatorBackgroundDown: "transparent"
        property color checkBoxIndicatorBorderNormal: "transparent"
        property color checkBoxIndicatorBorderFocused: "transparent"
        property color checkBoxIndicatorFiller: "transparent"
        property color checkBoxText: "transparent"

        // Delegate:
        property color delegateTitleBackground: "transparent"
        property color delegateTitleText: "transparent"
        property color delegateTitleSeparator: "transparent"
        property color delegateContentBackground: "transparent"
        property color delegateContentText: "transparent"

        // Custom:
        property color toastBackgroundSuccess: "transparent"
        property color toastBackgroundInfo: "transparent"
        property color toastBackgroundWarning: "transparent"
        property color toastBackgroundError: "transparent"
        property color toastIconSuccess: "transparent"
        property color toastIconInfo: "transparent"
        property color toastIconWarning: "transparent"
        property color toastIconError: "transparent"
        property color toastTextSuccess: "transparent"
        property color toastTextInfo: "transparent"
        property color toastTextWarning: "transparent"
        property color toastTextError: "transparent"
        property color sectionTitleBackground: "transparent"
        property color sectionTitleText: "transparent"
        property color sectionTitleSeparator: "transparent"
        property color sectionContentBackground: "transparent"
        property color sectionContentText: "transparent"
    }

    function setTheme(theme) {
        switch(theme) {
        case AppTheme.Themes.UFOLight:
            // Basic:
            componentColors.pageBackground = predefinedColors.grey200;
            componentColors.pageIcon = predefinedColors.grey800;
            componentColors.pageText = predefinedColors.grey800;

            // Controls:
            componentColors.buttonBackgroundNormal = predefinedColors.green500;
            componentColors.buttonBackgroundHovered = predefinedColors.green700;
            componentColors.buttonBackgroundChecked = predefinedColors.green700;
            componentColors.buttonBackgroundDown = predefinedColors.green700;
            componentColors.buttonIconNormal = predefinedColors.grey800;
            componentColors.buttonIconHovered = predefinedColors.grey200;
            componentColors.buttonIconChecked = predefinedColors.grey200;
            componentColors.buttonIconDown = predefinedColors.grey200;
            componentColors.buttonTextNormal = predefinedColors.grey800;
            componentColors.buttonTextHovered = predefinedColors.grey200;
            componentColors.buttonTextChecked = predefinedColors.grey200;
            componentColors.buttonTextDown = predefinedColors.grey200;
            componentColors.buttonBorder = predefinedColors.blue600;
            componentColors.textFieldBackground = predefinedColors.grey200;
            componentColors.textFieldPlaceHolderText = predefinedColors.grey600;
            componentColors.textFieldTextSelectedBackground = predefinedColors.green500;
            componentColors.textFieldTextSelected = predefinedColors.grey800;
            componentColors.textFieldTextNormal = predefinedColors.grey800;
            componentColors.textFieldBorderNormal = predefinedColors.grey600;
            componentColors.textFieldBorderFocused = predefinedColors.green500;
            componentColors.textAreaBackground = predefinedColors.grey200;
            componentColors.textAreaPlaceHolderText = predefinedColors.grey600;
            componentColors.textAreaTextSelectedBackground = predefinedColors.green500;
            componentColors.textAreaTextSelected = predefinedColors.grey800;
            componentColors.textAreaTextNormal = predefinedColors.grey800;
            componentColors.textAreaBorderNormal = predefinedColors.grey600;
            componentColors.textAreaBorderFocused = predefinedColors.green500;
            componentColors.statusBarBackground = predefinedColors.grey700;
            componentColors.statusBarText = predefinedColors.grey300;
            componentColors.dialogBackground = predefinedColors.grey300;
            componentColors.dialogBorder = predefinedColors.grey800;
            componentColors.dialogButtonBackground = predefinedColors.grey300;
            componentColors.dialogTextBackground = predefinedColors.grey300;
            componentColors.dialogText = predefinedColors.grey800;
            componentColors.comboBoxDropDownBackgroundNormal = predefinedColors.grey200;
            componentColors.comboBoxDropDownBackgroundDown = predefinedColors.grey200;
            componentColors.comboBoxDropDownTextNormal = predefinedColors.grey800;
            componentColors.comboBoxDropDownTextPressed = predefinedColors.grey800;
            componentColors.comboBoxDropDownBorder = predefinedColors.grey600;
            componentColors.comboBoxIndicatorNormal = predefinedColors.grey800;
            componentColors.comboBoxIndicatorPressed = predefinedColors.grey800;
            componentColors.comboBoxPopupBorder = predefinedColors.grey700;
            componentColors.comboBoxTextInputBackground = predefinedColors.grey400;
            componentColors.comboBoxTextInputBorder = "transparent";
            componentColors.comboBoxTextInputText = predefinedColors.grey800;
            componentColors.comboBoxDelegateBackgroundNormal = predefinedColors.grey200;
            componentColors.comboBoxDelegateBackgroundHighlighted = predefinedColors.green600;
            componentColors.comboBoxDelegateTextNormal = predefinedColors.grey800;
            componentColors.comboBoxDelegateTextHighlighted = predefinedColors.grey200;
            componentColors.checkBoxIndicatorBackgroundNormal = predefinedColors.grey200;
            componentColors.checkBoxIndicatorBackgroundDown = predefinedColors.grey200;
            componentColors.checkBoxIndicatorBorderNormal = predefinedColors.grey600;
            componentColors.checkBoxIndicatorBorderFocused = predefinedColors.green500;
            componentColors.checkBoxIndicatorFiller = predefinedColors.green600;
            componentColors.checkBoxText = predefinedColors.grey800;

            // Delegate:
            componentColors.delegateTitleBackground = predefinedColors.grey300;
            componentColors.delegateTitleText = predefinedColors.grey800;
            componentColors.delegateTitleSeparator = predefinedColors.grey300;
            componentColors.delegateContentBackground = predefinedColors.grey300;
            componentColors.delegateContentText = predefinedColors.grey800;

            // Custom:
            componentColors.toastBackgroundSuccess = predefinedColors.green300;
            componentColors.toastBackgroundInfo = predefinedColors.blue300;
            componentColors.toastBackgroundWarning = predefinedColors.yellow300;
            componentColors.toastBackgroundError = predefinedColors.red300;
            componentColors.toastIconSuccess = predefinedColors.grey800;
            componentColors.toastIconInfo = predefinedColors.grey800;
            componentColors.toastIconWarning = predefinedColors.grey800;
            componentColors.toastIconError = predefinedColors.grey800;
            componentColors.toastTextSuccess = predefinedColors.grey800;
            componentColors.toastTextInfo = predefinedColors.grey800;
            componentColors.toastTextWarning = predefinedColors.grey800;
            componentColors.toastTextError = predefinedColors.grey800;
            componentColors.sectionTitleBackground = predefinedColors.grey500;
            componentColors.sectionTitleText = predefinedColors.grey900;
            componentColors.sectionTitleSeparator = predefinedColors.grey400;
            componentColors.sectionContentBackground = predefinedColors.grey400;
            componentColors.sectionContentText = predefinedColors.grey800;

            qtObjectProperties.currentTheme = AppTheme.Themes.UFOLight;
            break;
        case AppTheme.Themes.UFODark:
            componentColors.pageBackground = predefinedColors.grey700;

            qtObjectProperties.currentTheme = AppTheme.Themes.UFODark;
            break;
        }
    }

    function getColor(color) {
        let result = "transparent";

        switch(color) {
        // Basic:
        case AppTheme.Colors.PageBackground:
            result = componentColors.pageBackground;
            break;
        case AppTheme.Colors.PageIcon:
            result = componentColors.pageIcon;
            break;
        case AppTheme.Colors.PageText:
            result = componentColors.pageText;
            break;

        // Controls:
        case AppTheme.Colors.ButtonBackgroundNormal:
            result = componentColors.buttonBackgroundNormal;
            break;
        case AppTheme.Colors.ButtonBackgroundHovered:
            result = componentColors.buttonBackgroundHovered;
            break;
        case AppTheme.Colors.ButtonBackgroundChecked:
            result = componentColors.buttonBackgroundChecked;
            break;
        case AppTheme.Colors.ButtonBackgroundDown:
            result = componentColors.buttonBackgroundDown;
            break;
        case AppTheme.Colors.ButtonIconNormal:
            result = componentColors.buttonIconNormal;
            break;
        case AppTheme.Colors.ButtonIconHovered:
            result = componentColors.buttonIconHovered;
            break;
        case AppTheme.Colors.ButtonIconChecked:
            result = componentColors.buttonIconChecked;
            break;
        case AppTheme.Colors.ButtonIconDown:
            result = componentColors.buttonIconDown;
            break;
        case AppTheme.Colors.ButtonTextNormal:
            result = componentColors.buttonTextNormal;
            break;
        case AppTheme.Colors.ButtonTextHovered:
            result = componentColors.buttonTextHovered;
            break;
        case AppTheme.Colors.ButtonTextChecked:
            result = componentColors.buttonTextChecked;
            break;
        case AppTheme.Colors.ButtonTextDown:
            result = componentColors.buttonTextDown;
            break;
        case AppTheme.Colors.ButtonBorder:
            result = componentColors.buttonBorder;
            break;
        case AppTheme.Colors.TextFieldBackground:
            result = componentColors.textFieldBackground;
            break;
        case AppTheme.Colors.TextFieldPlaceHolderText:
            result = componentColors.textFieldPlaceHolderText;
            break;
        case AppTheme.Colors.TextFieldTextSelectedBackground:
            result = componentColors.textFieldTextSelectedBackground;
            break;
        case AppTheme.Colors.TextFieldTextSelected:
            result = componentColors.textFieldTextSelected;
            break;
        case AppTheme.Colors.TextFieldTextNormal:
            result = componentColors.textFieldTextNormal;
            break;
        case AppTheme.Colors.TextFieldBorderNormal:
            result = componentColors.textFieldBorderNormal;
            break;
        case AppTheme.Colors.TextFieldBorderFocused:
            result = componentColors.textFieldBorderFocused;
            break;
        case AppTheme.Colors.TextAreaBackground:
            result = componentColors.textAreaBackground;
            break;
        case AppTheme.Colors.TextAreaPlaceHolderText:
            result = componentColors.textAreaPlaceHolderText;
            break;
        case AppTheme.Colors.TextAreaTextSelectedBackground:
            result = componentColors.textAreaTextSelectedBackground;
            break;
        case AppTheme.Colors.TextAreaTextSelected:
            result = componentColors.textAreaTextSelected;
            break;
        case AppTheme.Colors.TextAreaTextNormal:
            result = componentColors.textAreaTextNormal;
            break;
        case AppTheme.Colors.TextAreaBorderNormal:
            result = componentColors.textAreaBorderNormal;
            break;
        case AppTheme.Colors.TextAreaBorderFocused:
            result = componentColors.textAreaBorderFocused;
            break;
        case AppTheme.Colors.StatusBarBackground:
            result = componentColors.statusBarBackground;
            break;
        case AppTheme.Colors.StatusBarText:
            result = componentColors.statusBarText;
            break;
        case AppTheme.Colors.DialogBackground:
            result = componentColors.dialogBackground;
            break;
        case AppTheme.Colors.DialogBorder:
            result = componentColors.dialogBorder;
            break;
        case AppTheme.Colors.DialogButtonBackground:
            result = componentColors.dialogButtonBackground;
            break;
        case AppTheme.Colors.DialogTextBackground:
            result = componentColors.dialogTextBackground;
            break;
        case AppTheme.Colors.DialogText:
            result = componentColors.dialogText;
            break;
        case AppTheme.Colors.ComboBoxDropDownBackgroundNormal:
            result = componentColors.comboBoxDropDownBackgroundNormal;
            break;
        case AppTheme.Colors.ComboBoxDropDownBackgroundDown:
            result = componentColors.comboBoxDropDownBackgroundDown;
            break;
        case AppTheme.Colors.ComboBoxDropDownTextNormal:
            result = componentColors.comboBoxDropDownTextNormal;
            break;
        case AppTheme.Colors.ComboBoxDropDownTextPressed:
            result = componentColors.comboBoxDropDownTextPressed;
            break;
        case AppTheme.Colors.ComboBoxDropDownBorder:
            result = componentColors.comboBoxDropDownBorder;
            break;
        case AppTheme.Colors.ComboBoxIndicatorNormal:
            result = componentColors.comboBoxIndicatorNormal;
            break;
        case AppTheme.Colors.ComboBoxIndicatorPressed:
            result = componentColors.comboBoxIndicatorPressed;
            break;
        case AppTheme.Colors.ComboBoxPopupBorder:
            result = componentColors.comboBoxPopupBorder;
            break;
        case AppTheme.Colors.ComboBoxTextInputBackground:
            result = componentColors.comboBoxTextInputBackground;
            break;
        case AppTheme.Colors.ComboBoxTextInputBorder:
            result = componentColors.comboBoxTextInputBorder;
            break;
        case AppTheme.Colors.ComboBoxTextInputText:
            result = componentColors.comboBoxTextInputText;
            break;
        case AppTheme.Colors.ComboBoxDelegateBackgroundNormal:
            result = componentColors.comboBoxDelegateBackgroundNormal;
            break;
        case AppTheme.Colors.ComboBoxDelegateBackgroundHighlighted:
            result = componentColors.comboBoxDelegateBackgroundHighlighted;
            break;
        case AppTheme.Colors.ComboBoxDelegateTextNormal:
            result = componentColors.comboBoxDelegateTextNormal;
            break;
        case AppTheme.Colors.ComboBoxDelegateTextHighlighted:
            result = componentColors.comboBoxDelegateTextHighlighted;
            break;
        case AppTheme.Colors.CheckBoxIndicatorBackgroundNormal:
            result = componentColors.checkBoxIndicatorBackgroundNormal;
            break;
        case AppTheme.Colors.CheckBoxIndicatorBackgroundDown:
            result = componentColors.checkBoxIndicatorBackgroundDown;
            break;
        case AppTheme.Colors.CheckBoxIndicatorBorderNormal:
            result = componentColors.checkBoxIndicatorBorderNormal;
            break;
        case AppTheme.Colors.CheckBoxIndicatorBorderFocused:
            result = componentColors.checkBoxIndicatorBorderFocused;
            break;
        case AppTheme.Colors.CheckBoxIndicatorFiller:
            result = componentColors.checkBoxIndicatorFiller;
            break;
        case AppTheme.Colors.CheckBoxText:
            result = componentColors.checkBoxText;
            break;

        // Delegate:
        case AppTheme.Colors.DelegateTitleBackground:
            result = componentColors.delegateTitleBackground;
            break;
        case AppTheme.Colors.DelegateTitleText:
            result = componentColors.delegateTitleText;
            break;
        case AppTheme.Colors.DelegateTitleSeparator:
            result = componentColors.delegateTitleSeparator;
            break;
        case AppTheme.Colors.DelegateContentBackground:
            result = componentColors.delegateContentBackground;
            break;
        case AppTheme.Colors.DelegateContentText:
            result = componentColors.delegateContentText;
            break;

        // Custom:
        case AppTheme.Colors.ToastBackgroundSuccess:
            result = componentColors.toastBackgroundSuccess;
            break;
        case AppTheme.Colors.ToastBackgroundInfo:
            result = componentColors.toastBackgroundInfo;
            break;
        case AppTheme.Colors.ToastBackgroundWarning:
            result = componentColors.toastBackgroundWarning;
            break;
        case AppTheme.Colors.ToastBackgroundError:
            result = componentColors.toastBackgroundError;
            break;
        case AppTheme.Colors.ToastIconSuccess:
            result = componentColors.toastIconSuccess;
            break;
        case AppTheme.Colors.ToastIconInfo:
            result = componentColors.toastIconInfo;
            break;
        case AppTheme.Colors.ToastIconWarning:
            result = componentColors.toastIconWarning;
            break;
        case AppTheme.Colors.ToastIconError:
            result = componentColors.toastIconError;
            break;
        case AppTheme.Colors.ToastTextSuccess:
            result = componentColors.toastTextSuccess;
            break;
        case AppTheme.Colors.ToastTextInfo:
            result = componentColors.toastTextInfo;
            break;
        case AppTheme.Colors.ToastTextWarning:
            result = componentColors.toastTextWarning;
            break;
        case AppTheme.Colors.ToastTextError:
            result = componentColors.toastTextError;
            break;
        case AppTheme.Colors.SectionTitleBackground:
            result = componentColors.sectionTitleBackground;
            break;
        case AppTheme.Colors.SectionTitleText:
            result = componentColors.sectionTitleText;
            break;
        case AppTheme.Colors.SectionTitleSeparator:
            result = componentColors.sectionTitleSeparator;
            break;
        case AppTheme.Colors.SectionContentBackground:
            result = componentColors.sectionContentBackground;
            break;
        case AppTheme.Colors.SectionContentText:
            result = componentColors.sectionContentText;
            break;

        default:
            break;
        }

        return(result);
    }

    Component.onCompleted: {
        AppTheme.setTheme(AppSettings.currentTheme);
    }

    Component.onDestruction: {
        AppSettings.currentTheme = qtObjectProperties.currentTheme;
    }
}
