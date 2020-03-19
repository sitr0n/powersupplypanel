cmake_minimum_required(VERSION 2.8.12)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
if (VERSION VERSION_GREATER_EQUAL 3.1)
    set(CMAKE_CXX_STANDARD 11)
else()
    add_compile_options(-std=c++11)
endif()

find_package(
    Qt5 REQUIRED
    Core
    Network
    Widgets
)

set(
    UI_GTEST_SRC
    powersupplypanel_test.cpp
    psuchannelpanel_test.cpp
)

set(
    UI_GMOCK_H
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}..
    ${CMAKE_CURRENT_SOURCE_DIR}drivers
    ${CMAKE_CURRENT_SOURCE_DIR}drivers/gtest
    ${CURRENT_SOURCE_DIR}../
    ${CURRENT_SOURCE_DIR}../drivers
    ${CURRENT_SOURCE_DIR}../drivers/gtest
)

add_library(
    ui_gtest
    ${UI_GTEST_SRC}
    ${UI_GMOCK_H}
)

target_link_libraries(
    ui_gtest
    ui
    drivers_gtest
    drivers
    gtest_main
    gmock
    Qt5::Core
    Qt5::Network
    Qt5::Widgets
)
