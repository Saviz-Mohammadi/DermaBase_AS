project("ContainersModule" VERSION 1.0 DESCRIPTION "This module provides some basic containers to help transfer data between database and models." LANGUAGES CXX)

qt_add_library("ContainersModuleLib" STATIC)

target_sources("ContainersModuleLib"
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/search_result.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/starred_patient.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/diagnosis.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/treatment.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/procedure.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/consultant.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/consultation.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/image.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/lab.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/lab_test.hpp

  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/search_result.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/starred_patient.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/diagnosis.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/treatment.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/procedure.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/consultant.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/consultation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/image.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lab.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lab_test.cpp
)

target_include_directories("ContainersModuleLib"
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries("ContainersModuleLib"
    PRIVATE
    Qt6::Core)

