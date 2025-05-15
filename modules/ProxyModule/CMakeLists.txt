project("ProxyModule" VERSION 1.0 LANGUAGES CXX DESCRIPTION "A simple utility to handle filtering of a model.")

qt_add_library("ProxyModuleLib" STATIC)

target_sources("ProxyModuleLib"
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/proxy_filter.hpp

  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/proxy_filter.cpp
)

target_include_directories("ProxyModuleLib"
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries("ProxyModuleLib"
    PRIVATE
    Qt6::Core
    Qt6::Quick)
