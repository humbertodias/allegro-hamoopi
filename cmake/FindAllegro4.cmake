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
        $ENV{ALLEGRO_ROOT}/include
        $ENV{ALLEGRODIR}/include
    PATH_SUFFIXES allegro
)

# Find the Allegro 4 library
find_library(ALLEGRO4_LIBRARY
    NAMES alleg allegro allegro-4.4
    PATHS
        /usr/local/lib
        /usr/lib
        /opt/homebrew/lib
        /usr/local/opt/allegro@4/lib
        C:/allegro/lib
        $ENV{ALLEGRO_ROOT}/lib
        $ENV{ALLEGRODIR}/lib
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
endif()

mark_as_advanced(ALLEGRO4_INCLUDE_DIR ALLEGRO4_LIBRARY)
