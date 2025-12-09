cmake_minimum_required(VERSION 3.10)
project(HAMOOPI)

# Add custom CMake modules path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Option to choose backend
option(USE_SDL2 "Use SDL2 backend instead of Allegro 4" OFF)

if(USE_SDL2)
    # SDL2 Backend
    add_definitions(-DUSE_SDL2)
    
    # On Windows, SDL2 requires WIN32 executable type
    if(WIN32)
        add_executable(HAMOOPI WIN32 src/HAMOOPI.c src/platform_sdl2.c)
    else()
        add_executable(HAMOOPI src/HAMOOPI.c src/platform_sdl2.c)
    endif()
    
    # Find SDL2 packages
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_mixer REQUIRED)
    find_package(SDL2_ttf REQUIRED)

    # inih - configuration library
    # Try custom Find module first, fallback to pkg-config
    find_package(INIH QUIET)
    if(NOT INIH_FOUND)
        find_package(PkgConfig REQUIRED)
        pkg_check_modules(INIH REQUIRED inih)
    endif()

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
    if(UNIX)
        target_link_libraries(HAMOOPI m)
    endif()
else()
    # Allegro 4 Backend (default)
    add_definitions(-DUSE_ALLEGRO4)
    
    # On Windows, Allegro 4 requires WIN32 executable type
    if(WIN32)
        add_executable(HAMOOPI WIN32 src/HAMOOPI.c src/platform_allegro.c)
    else()
        add_executable(HAMOOPI src/HAMOOPI.c src/platform_allegro.c)
    endif()
    
    # Find Allegro 4 using custom Find module
    find_package(Allegro4 REQUIRED)
    
    # Add directories to the include search path
    target_include_directories(HAMOOPI PRIVATE ${ALLEGRO4_INCLUDE_DIRS})
    
    # Link with dependencies
    target_link_libraries(HAMOOPI ${ALLEGRO4_LIBRARIES})
    
    # On Windows, disable SAFESEH for compatibility with Allegro 4
    # Allegro 4 was compiled without SAFESEH support
    if(WIN32 AND MSVC)
        target_link_options(HAMOOPI PRIVATE /SAFESEH:NO)
        set_target_properties(HAMOOPI PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
    endif()
    
    # Link math library on Unix-like systems (not needed on Windows)
    if(UNIX)
        target_link_libraries(HAMOOPI m)
    endif()
endif()

# Copy executable to parent folder after build
add_custom_command(TARGET HAMOOPI POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:HAMOOPI> ${CMAKE_SOURCE_DIR}
    COMMENT "Copying executable to parent folder..."
)