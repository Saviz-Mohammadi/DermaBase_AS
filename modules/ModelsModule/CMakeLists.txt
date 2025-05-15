project("ModelsModule" VERSION 1.0 LANGUAGES CXX DESCRIPTION "This module contains models that can help manage lists and delegates.")

qt_add_library("ModelsModuleLib" STATIC)

target_sources("ModelsModuleLib"
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/search_model.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/starred_patients_model.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/diagnoses_list_model.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/patient_diagnoses_model.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/treatments_list_model.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/patient_treatments_model.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/procedures_list_model.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/patient_procedures_model.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/consultants_list_model.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/patient_consultations_model.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/patient_images_model.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/labs_list_model.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/patient_lab_tests_model.hpp

  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/search_model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/starred_patients_model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/diagnoses_list_model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/patient_diagnoses_model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/treatments_list_model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/patient_treatments_model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/procedures_list_model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/patient_procedures_model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/consultants_list_model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/patient_consultations_model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/patient_images_model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/labs_list_model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/patient_lab_tests_model.cpp
)

target_include_directories("ModelsModuleLib"
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries("ModelsModuleLib"
    PRIVATE
    Qt6::Core
    Qt6::Quick
    Qt6::Sql
    ContainersModuleLib
    DatabaseModuleLib)
