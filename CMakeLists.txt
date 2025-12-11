cmake_minimum_required(VERSION 3.10)
project(HAMOOPI)

# Add custom CMake modules path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Option to choose backend
option(USE_SDL2 "Use SDL2 backend instead of Allegro 4" OFF)

if (USE_SDL2)
    # SDL2 Backend
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
                src/backend/platform_sdl2.c)
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
                src/backend/platform_sdl2.c)
    endif ()

    # Find SDL2 packages
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_mixer REQUIRED)
    find_package(SDL2_ttf REQUIRED)

    # inih - configuration library
    # Try custom Find module first, fallback to pkg-config
    find_package(INIH QUIET)
    if (NOT INIH_FOUND)
        find_package(PkgConfig REQUIRED)
        pkg_check_modules(INIH REQUIRED inih)
    endif ()

    # Include directories for SDL2
    target_include_directories(HAMOOPI PRIVATE
            ${SDL2_INCLUDE_DIRS}
            ${SDL2_IMAGE_INCLUDE_DIRS}
            ${SDL2_MIXER_INCLUDE_DIRS}
            ${SDL2_TTF_INCLUDE_DIRS}
            ${INIH_INCLUDE_DIRS}
    )

    # Link SDL2 libraries
    target_link_libraries(HAMOOPI
            ${SDL2_LIBRARIES}
            ${SDL2_IMAGE_LIBRARIES}
            ${SDL2_MIXER_LIBRARIES}
            ${SDL2_TTF_LIBRARIES}
            ${INIH_LIBRARIES}
    )

    # Link math library on Unix-like systems (not needed on Windows)
    if (UNIX)
        target_link_libraries(HAMOOPI m)
    endif ()
else ()
    # Allegro 4 Backend (default)
    add_definitions(-DUSE_ALLEGRO4)

    # On Windows, Allegro 4 requires WIN32 executable type
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
                src/backend/platform_allegro.c)
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
                src/backend/platform_allegro.c)
    endif ()

    # Find Allegro 4 using custom Find module
    find_package(Allegro4 REQUIRED)
    
    # Find PNG library for PNG support in Allegro 4 backend
    find_package(PNG REQUIRED)

    # Add directories to the include search path
    target_include_directories(HAMOOPI PRIVATE ${ALLEGRO4_INCLUDE_DIRS} ${PNG_INCLUDE_DIRS})

    # Link with dependencies
    target_link_libraries(HAMOOPI ${ALLEGRO4_LIBRARIES} ${PNG_LIBRARIES})

    # On Windows, disable SAFESEH for compatibility with Allegro 4
    # Allegro 4 was compiled without SAFESEH support
    if (WIN32 AND MSVC)
        target_link_options(HAMOOPI PRIVATE /SAFESEH:NO)
        set_target_properties(HAMOOPI PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
    endif ()

    # Link math library on Unix-like systems (not needed on Windows)
    if (UNIX)
        target_link_libraries(HAMOOPI m)
    endif ()
    target_link_options(HAMOOPI PRIVATE -Wl,--wrap=load_bitmap,--wrap=load_font)
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

    # Palette generator uses the same SDL2 as main project when USE_SDL2 is ON
    # or can use Allegro 4 when USE_SDL2 is OFF
    # Pass the backend choice to the palette generator
    if (USE_SDL2)
        message(STATUS "Building pallete-generator tool (SDL2 backend)")
        add_subdirectory(tools/pallete-generator)
    else ()
        message(STATUS "Building pallete-generator tool (Allegro backend)")
        # Set USE_ALLEGRO for the subdirectory
        set(USE_ALLEGRO ON CACHE BOOL "Use Allegro for pallete-generator" FORCE)
        add_subdirectory(tools/pallete-generator)
        unset(USE_ALLEGRO CACHE)
    endif ()
endif ()