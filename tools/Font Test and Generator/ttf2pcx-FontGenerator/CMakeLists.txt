cmake_minimum_required(VERSION 3.16)
project(ttf2pcx-qt VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 packages
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Enable automoc for Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Source files
set(SOURCES
    main.cpp
    mainwindow.cpp
    character_qt.cpp
    previewwidget.cpp
)

set(HEADERS
    mainwindow.h
    character_qt.h
    previewwidget.h
)

# Create executable
add_executable(ttf2pcx-qt ${SOURCES} ${HEADERS})

# Link Qt libraries
target_link_libraries(ttf2pcx-qt
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

# Install target
install(TARGETS ttf2pcx-qt
    RUNTIME DESTINATION bin
)
