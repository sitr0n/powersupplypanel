add_subdirectory(gtest)
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
    Widgets
)

set(TEST_PROGRAM powersupplypanel_test)
set(TEST_SRC main_test.cpp)

include_directories(
    ./gtest
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../drivers
    ${CMAKE_CURRENT_SOURCE_DIR}/../drivers/gtest
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui
    ${CMAKE_CURRENT_SOURCE_DIR}/../ui/gtest
)

add_executable(
    ${TEST_PROGRAM}
    ${TEST_SRC}
)

target_link_libraries(
    ${TEST_PROGRAM}
    gtest_main
    gmock
    drivers
    drivers_gtest
    ui
    ui_gtest
    Qt5::Core
    Qt5::Widgets
)

add_test(NAME Psu_Test COMMAND ${TEST_PROGRAM})
