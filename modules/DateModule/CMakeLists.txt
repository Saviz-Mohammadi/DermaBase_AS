project("DateModule" VERSION 1.0 LANGUAGES CXX DESCRIPTION "This module contains the code to transform Gregorian dates to Jalali dates and vice versa.")

qt_add_qml_module("DateModuleLib"
    STATIC
    URI "DateModule"
    VERSION 1.0
    SOURCES
        "./include/date.hpp"
        "./src/date.cpp"
)

target_include_directories("DateModuleLib" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries("DateModuleLib"
    PRIVATE
    Qt6::Core
    Qt6::Quick)
