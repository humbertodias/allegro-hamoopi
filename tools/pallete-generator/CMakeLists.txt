cmake_minimum_required(VERSION 3.7)
project(PALLETEGEN)
add_executable(PALLETEGEN PalleteGenerator.c)

# Find Allegro
find_package(Alleg4 4)

# Add directories to the include search path
target_include_directories(PALLETEGEN PRIVATE ${ALLEGRO_INCLUDE_DIR})

# Link with dependencies
target_link_libraries(PALLETEGEN alleg m)

# Copy executable to parent folder after build
add_custom_command(TARGET PALLETEGEN POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:PALLETEGEN> ${CMAKE_SOURCE_DIR}
    COMMENT "Copying executable to parent folder..."
)