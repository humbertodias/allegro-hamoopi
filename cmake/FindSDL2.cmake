# FindSDL2.cmake
# Locate SDL2 library
#
# This module defines:
#  SDL2_FOUND - system has SDL2
#  SDL2_INCLUDE_DIRS - the SDL2 include directories
#  SDL2_LIBRARIES - the libraries needed to use SDL2
#  SDL2_VERSION - the version of SDL2 found

# Find the SDL2 include directory
find_path(SDL2_INCLUDE_DIR
    NAMES SDL.h
    PATHS
        /usr/local/include/SDL2
        /usr/include/SDL2
        /opt/homebrew/include/SDL2
        /usr/local/opt/sdl2/include/SDL2
        $ENV{SDL2DIR}/include/SDL2
    PATH_SUFFIXES SDL2
)

# Find the SDL2 library
find_library(SDL2_LIBRARY
    NAMES SDL2
    PATHS
        /usr/local/lib
        /usr/lib
        /opt/homebrew/lib
        /usr/local/opt/sdl2/lib
        $ENV{SDL2DIR}/lib
)

# Handle the QUIETLY and REQUIRED arguments
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL2
    REQUIRED_VARS SDL2_LIBRARY SDL2_INCLUDE_DIR
    VERSION_VAR SDL2_VERSION
)

if(SDL2_FOUND)
    set(SDL2_LIBRARIES ${SDL2_LIBRARY})
    set(SDL2_INCLUDE_DIRS ${SDL2_INCLUDE_DIR})
    
    # Create imported target
    if(NOT TARGET SDL2::SDL2)
        add_library(SDL2::SDL2 UNKNOWN IMPORTED)
        set_target_properties(SDL2::SDL2 PROPERTIES
            IMPORTED_LOCATION "${SDL2_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${SDL2_INCLUDE_DIR}"
        )
    endif()
endif()

mark_as_advanced(SDL2_INCLUDE_DIR SDL2_LIBRARY)
