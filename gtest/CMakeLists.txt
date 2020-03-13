cmake_minimum_required(VERSION 2.8.12)
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
if (VERSION VERSION_GREATER_EQUAL 3.1)
    set(CMAKE_CXX_STANDARD 11)
else()
    add_compile_options(-std=c++11)
endif()

find_package(Qt5 REQUIRED Core)

set(TEST_PROGRAM prodtool_test)

set(TEST_SRC
    prodtool_test.cpp
)

include_directories(${egc_BINARY_DIR}/gtest
                    ${CMAKE_CURRENT_SOURCE_DIR}/..
                    ${CMAKE_CURRENT_SOURCE_DIR}/../drivers
                    ${CMAKE_CURRENT_SOURCE_DIR}/../drivers/gtest
                    )

add_executable(${TEST_PROGRAM} ${TEST_SRC})

target_link_libraries(${TEST_PROGRAM}
                      gtest_main
                      gmock
                      drivers
                      drivers_gtest
                      )

add_test(NAME Prodtool_Test COMMAND ${TEST_PROGRAM})
