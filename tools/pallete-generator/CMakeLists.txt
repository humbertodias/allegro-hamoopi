cmake_minimum_required(VERSION 3.10)
project(PALLETEGEN)

# SDL2 Version (default)
add_executable(PALLETEGEN PalleteGenerator_SDL2.c)

# Use pkg-config to find SDL2 and SDL2_image
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

# Include directories for SDL2
target_include_directories(PALLETEGEN PRIVATE 
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
)

# Link SDL2 libraries
target_link_libraries(PALLETEGEN 
    ${SDL2_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
)

# Link math library on Unix-like systems
if(UNIX)
    target_link_libraries(PALLETEGEN m)
endif()

# Copy executable to parent folder after build
add_custom_command(TARGET PALLETEGEN POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:PALLETEGEN> ${CMAKE_CURRENT_SOURCE_DIR}/PALLETEGEN
    COMMENT "Copying executable to pallete-generator folder..."
)