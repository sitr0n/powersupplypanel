add_subdirectory(drivers)
add_subdirectory(gtest)
add_subdirectory(ui)

#find_package(Qt5Widgets)
cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED Core Widgets Network)

set (POWERSUPPLYPANEL_SRC
     main.cpp
     #powersupplypanel.cpp
)

set (POWERSUPPLYPANEL_H
     #powersupplypanel.h
)


include_directories(${CURRENT_SOURCE_DIR}/drivers
                    ${CURRENT_SOURCE_DIR}/ui
                    #${CURRENT_SOURCE_DIR}/drivers/gtest
)

add_executable(powersupplypanel ${POWERSUPPLYPANEL_SRC} ${POWERSUPPLYPANEL_H})

target_link_libraries(powersupplypanel
                      drivers
                      ui
                      #drivers_gtest
                      Qt5::Core
                      Qt5::Widgets
                      Qt5::Network
)
