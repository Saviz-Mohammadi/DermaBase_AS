pragma Singleton

import QtQuick
import QtCore

Item {
    id: root

    property alias currentTheme: themeSettings.currentTheme
    property alias ipAddress: credentialSettings.ipAddress
    property alias portNumber: credentialSettings.portNumber
    property alias schema: credentialSettings.schema
    property alias username: credentialSettings.username

    Settings {
        id: themeSettings

        property int currentTheme: AppTheme.Themes.UFOLight

        category: "Theme"
    }

    Settings {
        id: credentialSettings

        property string ipAddress: ""
        property int portNumber: 0
        property string schema: ""
        property string username: ""

        category: "Credential"
    }
}
