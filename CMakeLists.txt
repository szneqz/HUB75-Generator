cmake_minimum_required(VERSION 3.16)

project(HUB75_Generator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2 Core Widgets)

qt_standard_project_setup(REQUIRES 6.10)

set(SOURCES
    main.cpp
    imagereader.cpp
    imagereader.h
)

qt_add_executable(appHUB75_Generator
    ${SOURCES}
)

qt_add_qml_module(appHUB75_Generator
    URI HUB75_Generator
    QML_FILES
        Main.qml
        SOURCES filedialoghelper.h filedialoghelper.cpp
)

set_target_properties(appHUB75_Generator PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appHUB75_Generator
    PRIVATE Qt6::Quick Qt6::QuickControls2 Qt6::Core Qt6::Widgets
)