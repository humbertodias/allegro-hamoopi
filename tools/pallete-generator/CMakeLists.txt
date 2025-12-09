cmake_minimum_required(VERSION 3.7)
project(PALLETEGEN)

# Option to choose backend
option(USE_SDL2 "Use SDL2 backend instead of Allegro 4" ON)

if(USE_SDL2)
    # SDL2 Backend
    add_definitions(-DUSE_SDL2)
    add_executable(PALLETEGEN PalleteGenerator_SDL2.c ../../src/platform_sdl2.c)
    
    # Find SDL2 packages
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_mixer REQUIRED)
    find_package(SDL2_ttf REQUIRED)

    # inih - configuration library
    # Try custom Find module first, fallback to pkg-config
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../cmake")
    find_package(INIH QUIET)
    if(NOT INIH_FOUND)
        find_package(PkgConfig REQUIRED)
        pkg_check_modules(INIH REQUIRED inih)
    endif()

    # Include directories for SDL2
    target_include_directories(PALLETEGEN PRIVATE 
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${INIH_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/../../src
    )
    
    # Link SDL2 libraries
    target_link_libraries(PALLETEGEN 
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${INIH_LIBRARIES}
    )
    
    # Link math library on Unix-like systems (not needed on Windows)
    if(UNIX)
        target_link_libraries(PALLETEGEN m)
    endif()
else()
    # Allegro 4 Backend (original)
    add_executable(PALLETEGEN PalleteGenerator.c)
    
    # Find Allegro
    find_package(Alleg4 4)
    
    # Add directories to the include search path
    target_include_directories(PALLETEGEN PRIVATE ${ALLEGRO_INCLUDE_DIR})
    
    # Link with dependencies
    target_link_libraries(PALLETEGEN alleg m)
endif()

# Copy executable to parent folder after build
add_custom_command(TARGET PALLETEGEN POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:PALLETEGEN> ${CMAKE_SOURCE_DIR}
    COMMENT "Copying executable to parent folder..."
)