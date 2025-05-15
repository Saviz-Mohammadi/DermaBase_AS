project("DatabaseModule" VERSION 1.0 LANGUAGES CXX DESCRIPTION "This module contains the code to interact with the MySQL database.")

qt_add_library("DatabaseModuleLib" STATIC)

target_sources("DatabaseModuleLib"
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/database.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/database_worker.hpp

  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/database.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/database_worker.cpp
)

target_include_directories("DatabaseModuleLib"
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries("DatabaseModuleLib"
    PRIVATE
    Qt6::Core
    Qt6::Concurrent
    Qt6::Quick
    Qt6::Sql
    ContainersModuleLib
    DateModuleLib
    DateModuleLibplugin)
