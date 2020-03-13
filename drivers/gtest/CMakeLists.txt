cmake_minimum_required(VERSION 2.8.12)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
if (VERSION VERSION_GREATER_EQUAL 3.1)
    set(CMAKE_CXX_STANDARD 11)
else()
    add_compile_options(-std=c++11)
endif()

find_package(Qt5 REQUIRED Core Network)

set(DRIVERS_GTEST_SRC
    hmp4040driver_test.cpp
)

set(DRIVERS_GMOCK_H
    mocktcpsocket.h
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..
                    ${egc_SOURCE_DIR}/ebird_fw/Birds/common
)

add_library (drivers_gtest ${DRIVERS_GTEST_SRC} ${DRIVERS_GMOCK_H})
target_link_libraries(drivers_gtest
    drivers
    gtest_main
    gmock
    Qt5::Core
    Qt5::Network
    ebird_common
)
