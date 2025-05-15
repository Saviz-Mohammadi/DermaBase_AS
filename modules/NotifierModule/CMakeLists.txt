project("NotifierModule" VERSION 0.1 DESCRIPTION "This module contains the code to enable sending notification emails via the SMTP library." LANGUAGES CXX)

qt_add_qml_module("${PROJECT_NAME}lib"
    STATIC
    URI "NotifierModule"
    VERSION 0.1
    SOURCES
        "./include/notifier.hpp"
        "./src/notifier.cpp"
)

target_include_directories("${PROJECT_NAME}lib" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

include(FetchContent)

# Fetch the SMTP library
FetchContent_Declare(
    smtpclientlibrary
    GIT_REPOSITORY https://github.com/jeremydumais/CPP-SMTPClient-library.git
    GIT_TAG master
)

FetchContent_MakeAvailable(smtpclientlibrary)

include_directories(${smtpclientlibrary_SOURCE_DIR}/src)

if(WIN32)
    include_directories($ENV{OPENSSL_INCLUDE_DIR})
    link_directories($ENV{OPENSSL_CRYPTO_LIBRARY})
endif()

target_link_libraries("${PROJECT_NAME}lib" PRIVATE Qt6::Core Qt6::Gui Qt6::Quick Qt6::Sql DatabaseModulelib DatabaseModulelibplugin smtpclient)
