pragma Singleton

import QtQuick

Item {
    id: root

    readonly property alias titilliumBlackFont: titilliumBlack.font
    readonly property alias titilliumBoldFont: titilliumBold.font
    readonly property alias titilliumBoldItalicFont: titilliumBoldItalic.font
    readonly property alias titilliumExtraLightFont: titilliumExtraLight.font
    readonly property alias titilliumExtraLightItalicFont: titilliumExtraLightItalic.font
    readonly property alias titilliumItalicFont: titilliumItalic.font
    readonly property alias titilliumLightFont: titilliumLight.font
    readonly property alias titilliumLightItalicFont: titilliumLightItalic.font
    readonly property alias titilliumRegularFont: titilliumRegular.font
    readonly property alias titilliumSemiBoldFont: titilliumSemiBold.font
    readonly property alias titilliumSemiBoldItalicFont: titilliumSemiBoldItalic.font

    FontLoader {
        id: titilliumBlack
        source: "qrc:/resources/fonts/Titillium_Web/TitilliumWeb-Black.ttf"
    }

    FontLoader {
        id: titilliumBold
        source: "qrc:/resources/fonts/Titillium_Web/TitilliumWeb-Bold.ttf"
    }

    FontLoader {
        id: titilliumBoldItalic
        source: "qrc:/resources/fonts/Titillium_Web/TitilliumWeb-BoldItalic.ttf"
    }

    FontLoader {
        id: titilliumExtraLight
        source: "qrc:/resources/fonts/Titillium_Web/TitilliumWeb-ExtraLight.ttf"
    }

    FontLoader {
        id: titilliumExtraLightItalic
        source: "qrc:/resources/fonts/Titillium_Web/TitilliumWeb-ExtraLightItalic.ttf"
    }

    FontLoader {
        id: titilliumItalic
        source: "qrc:/resources/fonts/Titillium_Web/TitilliumWeb-Italic.ttf"
    }

    FontLoader {
        id: titilliumLight
        source: "qrc:/resources/fonts/Titillium_Web/TitilliumWeb-Light.ttf"
    }

    FontLoader {
        id: titilliumLightItalic
        source: "qrc:/resources/fonts/Titillium_Web/TitilliumWeb-LightItalic.ttf"
    }

    FontLoader {
        id: titilliumRegular
        source: "qrc:/resources/fonts/Titillium_Web/TitilliumWeb-Regular.ttf"
    }

    FontLoader {
        id: titilliumSemiBold
        source: "qrc:/resources/fonts/Titillium_Web/TitilliumWeb-SemiBold.ttf"
    }

    FontLoader {
        id: titilliumSemiBoldItalic
        source: "qrc:/resources/fonts/Titillium_Web/TitilliumWeb-SemiBoldItalic.ttf"
    }
}
