# FindAllegro4.cmake
# Locate Allegro 4 library
#
# This module defines:
#  ALLEGRO4_FOUND - system has Allegro 4
#  ALLEGRO4_INCLUDE_DIRS - the Allegro 4 include directories
#  ALLEGRO4_LIBRARIES - the libraries needed to use Allegro 4

# Find the Allegro 4 include directory
find_path(ALLEGRO4_INCLUDE_DIR
    NAMES allegro.h
    PATHS
        /usr/local/include
        /usr/include
        /opt/homebrew/include
        /usr/local/opt/allegro@4/include
        C:/allegro/include
        C:/allegro-temp/include
        $ENV{ALLEGRO_ROOT}/include
        $ENV{ALLEGRODIR}/include
        $ENV{CMAKE_PREFIX_PATH}/include
    PATH_SUFFIXES allegro
    DOC "Allegro 4 include directory"
)

# Find the Allegro 4 library
# Windows may use different naming: alleg44.lib, alleg.lib, liballeg.a, etc.
find_library(ALLEGRO4_LIBRARY
    NAMES alleg44 alleg allegro allegro-4.4 allegro-4.4.2 liballeg
    PATHS
        /usr/local/lib
        /usr/lib
        /opt/homebrew/lib
        /usr/local/opt/allegro@4/lib
        C:/allegro/lib
        C:/allegro/lib/msvc
        C:/allegro/lib/mingw
        C:/allegro-temp/lib
        $ENV{ALLEGRO_ROOT}/lib
        $ENV{ALLEGRODIR}/lib
        $ENV{CMAKE_PREFIX_PATH}/lib
    PATH_SUFFIXES lib
    DOC "Allegro 4 library"
)

# Handle the QUIETLY and REQUIRED arguments
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Allegro4
    REQUIRED_VARS ALLEGRO4_LIBRARY ALLEGRO4_INCLUDE_DIR
)

if(ALLEGRO4_FOUND)
    set(ALLEGRO4_LIBRARIES ${ALLEGRO4_LIBRARY})
    set(ALLEGRO4_INCLUDE_DIRS ${ALLEGRO4_INCLUDE_DIR})
    
    # Create imported target
    if(NOT TARGET Allegro4::Allegro4)
        add_library(Allegro4::Allegro4 UNKNOWN IMPORTED)
        set_target_properties(Allegro4::Allegro4 PROPERTIES
            IMPORTED_LOCATION "${ALLEGRO4_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${ALLEGRO4_INCLUDE_DIR}"
        )
    endif()
    
    # Provide legacy variables for backward compatibility
    set(ALLEGRO_FOUND ${ALLEGRO4_FOUND})
    set(ALLEGRO_LIBRARIES ${ALLEGRO4_LIBRARIES})
    set(ALLEGRO_INCLUDE_DIR ${ALLEGRO4_INCLUDE_DIR})
else()
    # Debugging: show what paths were searched
    message(STATUS "Allegro4 not found.")
    if(ALLEGRO4_INCLUDE_DIR)
        message(STATUS "  Include dir found: ${ALLEGRO4_INCLUDE_DIR}")
    else()
        message(STATUS "  Include dir: NOT FOUND")
    endif()
    if(ALLEGRO4_LIBRARY)
        message(STATUS "  Library found: ${ALLEGRO4_LIBRARY}")
    else()
        message(STATUS "  Library: NOT FOUND")
    endif()
    if(DEFINED ENV{ALLEGRO_ROOT})
        message(STATUS "  ALLEGRO_ROOT env: $ENV{ALLEGRO_ROOT}")
    endif()
    if(DEFINED ENV{CMAKE_PREFIX_PATH})
        message(STATUS "  CMAKE_PREFIX_PATH env: $ENV{CMAKE_PREFIX_PATH}")
    endif()
endif()

mark_as_advanced(ALLEGRO4_INCLUDE_DIR ALLEGRO4_LIBRARY)

