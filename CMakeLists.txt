cmake_minimum_required(VERSION 3.20)
project(qtgstreamer)

set(CMAKE_CXX_STANDARD 17)

include(ExternalProject)

macro (generate_qt_libs)
    set(options)
    set(oneValueArgs VAR VERSION)
    set(multiValueArgs COMPONENTS)
    cmake_parse_arguments(GENERATE_QT_LIBS "${options}" "${oneValueArgs}"
            "${multiValueArgs}" ${ARGN})

    # Qualified names
    set(REQUIRED_COMPONENTS)
    foreach (QT_LIB IN LISTS GENERATE_QT_LIBS_COMPONENTS)
        list(APPEND ${GENERATE_QT_LIBS_VAR} Qt${GENERATE_QT_LIBS_VERSION}::${QT_LIB})
        list(APPEND REQUIRED_COMPONENTS ${QT_LIB})
    endforeach ()

    find_package(QT NAMES Qt6 Qt5 COMPONENTS ${REQUIRED_COMPONENTS} REQUIRED)
    find_package(Qt${GENERATE_QT_LIBS_VERSION} COMPONENTS ${REQUIRED_COMPONENTS} REQUIRED)
endmacro ()

set(QT_VERSION_MAJOR 5)
set(TARGET_QT_MODULES Core Quick Qml Multimedia Network)

generate_qt_libs(
        VAR TARGET_QT_DEPS
        COMPONENTS ${TARGET_QT_MODULES}
        VERSION ${QT_VERSION_MAJOR}
)

message(STATUS "Qt dependencies: ${TARGET_QT_DEPS}")
set(LOCAL_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/deps)

ExternalProject_Add(libqt5gstreamer
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/deps/qt5gstreamer
        GIT_REPOSITORY https://github.com/GStreamer/qt-gstreamer
        GIT_TAG master
        GIT_PROGRESS ON
        CMAKE_ARGS
        -DQT_VERSION=${QT_VERSION_MAJOR}
        -DQTGSTREAMER_CODEGEN=OFF
        -DQTGSTREAMER_EXAMPLES=OFF
        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
        -DCMAKE_CXX_FLAGS="-w"
        -Wno-dev
        -DCMAKE_INSTALL_PREFIX=${LOCAL_INSTALL_PREFIX}
        -DUSE_GST_PLUGIN_DIR=OFF

        INSTALL_DIR ${LOCAL_INSTALL_PREFIX}
        )

add_executable(qtgstreamer
        src/main.cpp
        src/camera.cpp
        src/video_surface.cpp

        include/camera.hpp
        include/video_surface.hpp

        qml/main.qrc
)

add_dependencies(qtgstreamer libqt5gstreamer)
target_link_directories(qtgstreamer PRIVATE ${LOCAL_INSTALL_PREFIX}/lib)
target_link_libraries(qtgstreamer PRIVATE ${TARGET_QT_DEPS} Qt5GStreamer-1.0 Qt5GLib-2.0)
target_include_directories(qtgstreamer PRIVATE ${LOCAL_INSTALL_PREFIX}/include/Qt5GStreamer)