cmake_minimum_required(VERSION 3.7)
project(HAMOOPI)

# Add custom CMake modules path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Option to choose backend
option(USE_SDL2 "Use SDL2 backend instead of Allegro 4" OFF)

if(USE_SDL2)
    # SDL2 Backend
    add_definitions(-DUSE_SDL2)
    add_executable(HAMOOPI src/HAMOOPI.c src/platform_sdl2.c)
    
    # Find SDL2 packages
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_mixer REQUIRED)
    find_package(SDL2_ttf REQUIRED)

    # inih
    # sudo apt install libinih-dev
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(INIH REQUIRED inih)

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
        SDL2
        SDL2_image
        SDL2_mixer
        SDL2_ttf
        m
        ${INIH_LIBRARIES}
    )
else()
    # Allegro 4 Backend (default)
    add_definitions(-DUSE_ALLEGRO4)
    add_executable(HAMOOPI src/HAMOOPI.c src/platform_allegro.c)
    
    # Find Allegro
    find_package(Alleg4 4)
    
    # Add directories to the include search path
    target_include_directories(HAMOOPI PRIVATE ${ALLEGRO_INCLUDE_DIR})
    
    # Link with dependencies
    target_link_libraries(HAMOOPI alleg m)
endif()

# Copy executable to parent folder after build
add_custom_command(TARGET HAMOOPI POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:HAMOOPI> ${CMAKE_SOURCE_DIR}
    COMMENT "Copying executable to parent folder..."
)