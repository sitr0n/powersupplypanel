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

set(
    UI_SRC
    powersupplypanel.cpp
    psuchannelpanel.cpp
)

set(
    UI_H
    powersupplypanel.h
    psuchannelpanel.h
)

qt5_wrap_cpp(UI_QT_HEADERS_MOC ${UI_H})

include_directories(
    ${CURRENT_SOURCE_DIR}/../
    ${CURRENT_SOURCE_DIR}/../drivers
    ${CURRENT_SOURCE_DIR}/../drivers/gtest
)

add_library(
    ui
    ${UI_SRC}
    ${UI_QT_HEADERS_MOC}
)

target_link_libraries(
    ui
    drivers
    Qt5::Core
    Qt5::Widgets
)
