# FindSDL2_mixer.cmake
# Locate SDL2_mixer library
#
# This module defines:
#  SDL2_MIXER_FOUND - system has SDL2_mixer
#  SDL2_MIXER_INCLUDE_DIRS - the SDL2_mixer include directories
#  SDL2_MIXER_LIBRARIES - the libraries needed to use SDL2_mixer

# Find the SDL2_mixer include directory
find_path(SDL2_MIXER_INCLUDE_DIR
    NAMES SDL_mixer.h
    PATHS
        /usr/local/include/SDL2
        /usr/include/SDL2
        /opt/homebrew/include/SDL2
        /usr/local/opt/sdl2_mixer/include/SDL2
        $ENV{SDL2MIXERDIR}/include/SDL2
    PATH_SUFFIXES SDL2
)

# Find the SDL2_mixer library
find_library(SDL2_MIXER_LIBRARY
    NAMES SDL2_mixer
    PATHS
        /usr/local/lib
        /usr/lib
        /opt/homebrew/lib
        /usr/local/opt/sdl2_mixer/lib
        $ENV{SDL2MIXERDIR}/lib
)

# Handle the QUIETLY and REQUIRED arguments
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL2_mixer
    REQUIRED_VARS SDL2_MIXER_LIBRARY SDL2_MIXER_INCLUDE_DIR
)

if(SDL2_MIXER_FOUND)
    set(SDL2_MIXER_LIBRARIES ${SDL2_MIXER_LIBRARY})
    # Set SDL2_MIXER_INCLUDE_DIRS to the parent directory so <SDL2/SDL_mixer.h> works
    get_filename_component(SDL2_MIXER_INCLUDE_PARENT "${SDL2_MIXER_INCLUDE_DIR}" DIRECTORY)
    set(SDL2_MIXER_INCLUDE_DIRS ${SDL2_MIXER_INCLUDE_PARENT})
    
    # Create imported target
    if(NOT TARGET SDL2::SDL2_mixer)
        add_library(SDL2::SDL2_mixer UNKNOWN IMPORTED)
        set_target_properties(SDL2::SDL2_mixer PROPERTIES
            IMPORTED_LOCATION "${SDL2_MIXER_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${SDL2_MIXER_INCLUDE_PARENT}"
        )
    endif()
endif()

mark_as_advanced(SDL2_MIXER_INCLUDE_DIR SDL2_MIXER_LIBRARY)

