cmake_minimum_required(VERSION 3.20)
project(qt_streaming)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
        Core
        Network
        Multimedia
        Gui
        Qml
        REQUIRED
)

add_executable(qt_streaming
        src/main.cpp

        src/video_surface.cpp
        include/video_surface.hpp
        src/camera.cpp
        include/camera.hpp

        include/images.hpp

        qml/main.qrc

)

target_link_libraries(qt_streaming
        Qt5::Core
        Qt5::Network
        Qt5::Multimedia
        Qt5::Gui
        Qt5::Qml
)

target_include_directories(qt_streaming PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)