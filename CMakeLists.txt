cmake_minimum_required(VERSION 3.10)
project(HAMOOPI)

# Add custom CMake modules path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Use SDL2 backend only (Allegro support removed)
add_definitions(-DUSE_SDL2)

# On Windows, SDL2 requires WIN32 executable type
if (WIN32)
    add_executable(HAMOOPI WIN32
            src/main.c
            src/modules/input.c
            src/modules/collision.c
            src/modules/player.c
            src/modules/editor.c
            src/game_loop/donation.c
            src/game_loop/intro.c
            src/game_loop/presentation.c
            src/game_loop/play.c
            src/game_loop/stage_select.c
            src/game_loop/char_select.c
            src/game_loop/options.c
            src/game_loop/versus.c
            src/game_loop/edit.c
            src/backend/platform_sdl2.c
            src/backend/minini/minIni.c)
else ()
    add_executable(HAMOOPI
            src/main.c
            src/modules/input.c
            src/modules/collision.c
            src/modules/player.c
            src/modules/editor.c
            src/game_loop/donation.c
            src/game_loop/intro.c
            src/game_loop/presentation.c
            src/game_loop/play.c
            src/game_loop/stage_select.c
            src/game_loop/char_select.c
            src/game_loop/options.c
            src/game_loop/versus.c
            src/game_loop/edit.c
            src/backend/platform_sdl2.c
            src/backend/minini/minIni.c)
endif ()

# Find SDL2 packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

# minIni is now bundled in the source tree

# Include directories for SDL2
target_include_directories(HAMOOPI PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/src/backend/minini
)

# Link SDL2 libraries
target_link_libraries(HAMOOPI
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
)

# Link math library on Unix-like systems (not needed on Windows)
if (UNIX)
    target_link_libraries(HAMOOPI m)
endif ()

# Copy executable to parent folder after build
add_custom_command(TARGET HAMOOPI POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:HAMOOPI> ${CMAKE_SOURCE_DIR}
        COMMENT "Copying executable to parent folder..."
)

# Copy data/ folder to the build directory
add_custom_command(TARGET HAMOOPI POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:HAMOOPI>/data
        COMMENT "Copying data folder..."
)

# Copy SETUP.ini to output
add_custom_command(TARGET HAMOOPI POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/SETUP.ini
        $<TARGET_FILE_DIR:HAMOOPI>/SETUP.ini
        COMMENT "Copying SETUP.ini..."
)

# Build tools (optional)
option(BUILD_TOOLS "Build additional tools (font-generator and pallete-generator)" OFF)

if (BUILD_TOOLS)
    # Font generator requires Qt6
    find_package(Qt6 QUIET COMPONENTS Core Gui Widgets)
    if (Qt6_FOUND)
        message(STATUS "Building font-generator tool (Qt6 found)")
        add_subdirectory(tools/font-generator)
    else ()
        message(STATUS "Skipping font-generator tool (Qt6 not found)")
    endif ()

    # Palette generator uses SDL2
    message(STATUS "Building pallete-generator tool (SDL2 backend)")
    add_subdirectory(tools/pallete-generator)
endif ()