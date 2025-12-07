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
    src/main.cpp
    src/mainwindow.cpp
    src/character_qt.cpp
    src/previewwidget.cpp
)

set(HEADERS
    src/mainwindow.h
    src/character_qt.h
    src/previewwidget.h
)

# Create executable
add_executable(ttf2pcx-qt ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(ttf2pcx-qt PRIVATE src)

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

# Optional: Build test executable
option(BUILD_TESTS "Build test executables" ON)
if(BUILD_TESTS)
    add_executable(test_core tests/test_core.cpp src/character_qt.cpp)
    target_include_directories(test_core PRIVATE src)
    target_link_libraries(test_core Qt6::Core Qt6::Gui Qt6::Widgets)
endif()
