# FindINIH.cmake
# Locate inih library
#
# This module defines:
#  INIH_FOUND - system has inih
#  INIH_INCLUDE_DIRS - the inih include directories
#  INIH_LIBRARIES - the libraries needed to use inih

# Find the inih include directory
find_path(INIH_INCLUDE_DIR
    NAMES ini.h
    PATHS
        /usr/local/include
        /usr/include
        /opt/homebrew/include
        /usr/local/opt/inih/include
        $ENV{INIHDIR}/include
)

# Find the inih library
find_library(INIH_LIBRARY
    NAMES inih
    PATHS
        /usr/local/lib
        /usr/lib
        /opt/homebrew/lib
        /usr/local/opt/inih/lib
        $ENV{INIHDIR}/lib
)

# Handle the QUIETLY and REQUIRED arguments
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(INIH
    REQUIRED_VARS INIH_LIBRARY INIH_INCLUDE_DIR
)

if(INIH_FOUND)
    set(INIH_LIBRARIES ${INIH_LIBRARY})
    set(INIH_INCLUDE_DIRS ${INIH_INCLUDE_DIR})
    
    # Create imported target
    if(NOT TARGET INIH::INIH)
        add_library(INIH::INIH UNKNOWN IMPORTED)
        set_target_properties(INIH::INIH PROPERTIES
            IMPORTED_LOCATION "${INIH_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${INIH_INCLUDE_DIR}"
        )
    endif()
endif()

mark_as_advanced(INIH_INCLUDE_DIR INIH_LIBRARY)

