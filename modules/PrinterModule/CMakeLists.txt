project("PrinterModule" VERSION 0.1 DESCRIPTION "This module contains the code to enable printing to a PDF file." LANGUAGES CXX)

qt_add_qml_module("${PROJECT_NAME}lib"
    STATIC
    URI "PrinterModule"
    VERSION 0.1
    SOURCES
        "./include/printer.hpp"
        "./src/printer.cpp"
)

target_include_directories("${PROJECT_NAME}lib" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries("${PROJECT_NAME}lib" PRIVATE Qt6::Core Qt6::Gui Qt6::Quick Qt6::PrintSupport Qt6::Sql DatabaseModulelib DatabaseModulelibplugin)
