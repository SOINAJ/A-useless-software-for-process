cmake_minimum_required(VERSION 3.14)
project(ProcessWarden VERSION 1.2.4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Qt 5.14.2 — set CMAKE_PREFIX_PATH to your Qt install when configuring:
#   cmake -B build -DCMAKE_PREFIX_PATH=D:/enireonment/Qt/5.14.2/msvc2017_64
find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(ProcessWarden WIN32
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui
    src/processmanager.cpp
    src/processmanager.h
    src/processinfo.h
    src/filetools.cpp
    src/filetools.h
)

target_link_libraries(ProcessWarden PRIVATE
    Qt5::Widgets
    psapi
    advapi32
)
