cmake_minimum_required(VERSION 3.16)

project(EarthquakeDashboard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2 Network)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appEarthquakeDashboard
    main.cpp
    earthquake.h
)

qt_add_qml_module(appEarthquakeDashboard
    URI EarthquakeDashboard
    VERSION 1.0
    QML_FILES
        Main.qml
)

set_target_properties(appEarthquakeDashboard PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appEarthquakeDashboard PRIVATE
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Network
)

include(GNUInstallDirs)
install(TARGETS appEarthquakeDashboard
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
