add_subdirectory(drivers)
add_subdirectory(gtest)
add_subdirectory(ui)

cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED Core Widgets Network)

include_directories(${CURRENT_SOURCE_DIR}/drivers
                    ${CURRENT_SOURCE_DIR}/ui
)

add_executable(powersupplypanel main.cpp)

target_link_libraries(powersupplypanel
                      drivers
                      ui
                      Qt5::Core
                      Qt5::Widgets
                      Qt5::Network
)
