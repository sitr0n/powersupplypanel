add_subdirectory( ui )
add_subdirectory(drivers)
add_subdirectory(gtest)
find_package(Qt5Widgets)


cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)


qt5_wrap_ui(uis
            ui/mainwindow.ui
            ui/bodyfunctionaltestdialog.ui
            ui/streamerconfigurationdialog.ui
            ui/powerstatusdialog.ui
            ui/streamerpower.ui
            ui/rollcalibrationdialog.ui
            ui/ultimapsudialog.ui
            ui/testdescriptiondialog.ui
            ui/digiquarzdialog.ui
            ui/birdstatustemperatureform.ui
            ui/temperaturecalibrationdialog.ui
)

set (RESOURCES
    icons.qrc
)

qt5_add_resources(RES_SOURCES ${RESOURCES})


set (PRODTOOL_SRC
     main.cpp
     prodtoolsapi.cpp
     bodyfunctionaltest.cpp
     birdcomserverif.cpp
     ebirdconfig.cpp
     statusbitwidget.cpp
     bodyrotatewidget.cpp
     rollcalibration.cpp
     drawingarea.cpp
     ultimapsuif.cpp
     digiquarzif.cpp
     temperaturecalibration.cpp
     prodtoolsmath.cpp
     ui/mainwindow.cpp
     ui/bodyfunctionaltestdialog.cpp
     ui/streamerconfigurationdialog.cpp
     ui/powerstatusdialog.cpp
     ui/streamerpower.cpp
     ui/rollcalibrationdialog.cpp
     ui/ultimapsudialog.cpp
     ui/configurationdialog.cpp
     ui/testdescriptiondialog.cpp
     ui/digiquarzdialog.cpp
     ui/birdstatustemperatureform.cpp
     ui/temperaturecalibrationdialog.cpp
     ui/qpsupanel.cpp

)

include_directories(${egc_SOURCE_DIR}/swlib/src/C/Incl 
                    ${egc_SOURCE_DIR}/libs/corbautils
                    ${egc_SOURCE_DIR}/libs/ebird_common
                    ${egc_SOURCE_DIR}/libs/ebird_qwt
                    ${egc_BINARY_DIR}/corba/idl/ebird
                    ${egc_SOURCE_DIR}/dynamica
                    ${egc_SOURCE_DIR}/ebird_fw/Birds/common
                    ui/
                    ${egc_SOURCE_DIR}/drivers
                    )

add_executable(prodtool ${uis} ${PRODTOOL_SRC} ${RES_SOURCES})

target_link_libraries(prodtool 
                      drivers
                      ebird_common
                      corbautils
                      swlib
                      Qt5::Widgets
                      dynamica
                      ebird_qwt
                      rt)



install(TARGETS prodtool
        RUNTIME
        DESTINATION ebird
        )

install(TARGETS prodtool
        RUNTIME
        DESTINATION bin
        COMPONENT vendor
        )
