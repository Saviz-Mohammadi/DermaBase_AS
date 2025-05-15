cmake_minimum_required(VERSION 3.16)

project("DermaBase_AS" VERSION 1.0 LANGUAGES CXX DESCRIPTION "A system designed for dermatologists to streamline and optimize the process of patient management.")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Concurrent Quick QuickControls2 Sql)

qt_standard_project_setup(REQUIRES 6.8)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/modules")

qt_add_executable("DermaBase_AS" main.cpp resources/resources.qrc)

set_source_files_properties(AppSettings.qml AppTheme.qml AppFont.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_qml_module("DermaBase_AS"
    URI "DermaBase_AS"
    VERSION 1.0
    QML_FILES
        Main.qml

        # Utilities:
        AppSettings.qml
        AppTheme.qml
        AppFont.qml

        # Controls:
        UFOButton.qml
        UFOTextField.qml
        UFOTextArea.qml
        UFOStatusBar.qml
        UFOComboBox.qml
        UFOCheckBox.qml
        UFODialog.qml

        # Custom:
        UFOToast.qml
        UFOSection.qml
        UFOSideBar.qml
        UFOFullScreen.qml

        # Delegate:
        SearchDelegate.qml
        StarDelegate.qml
        DiagnosisDelegate.qml
        TreatmentDelegate.qml
        ProcedureDelegate.qml
        ConsultationDelegate.qml
        LabTestDelegate.qml
        ImageDelegate.qml

        # Pages:
        StarPage.qml
        SearchPage.qml
        EditPage.qml
        CreatePage.qml
        SettingsPage.qml
        AboutPage.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties("DermaBase_AS" PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appDermaBase_AS
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries("DermaBase_AS"
    PRIVATE
    Qt6::Core
    Qt6::Concurrent
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Sql
    DatabaseModuleLib
    ContainersModuleLib
    ModelsModuleLib
    DateModuleLib
    DateModuleLibplugin
    ProxyModuleLib
    # PrinterModulelib
    # PrinterModulelibplugin
    # ModelsModulelib
    # ModelsModulelibplugin
)

include(GNUInstallDirs)
install(TARGETS DermaBase_AS
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
