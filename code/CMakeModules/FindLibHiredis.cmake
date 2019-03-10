# - Locate LibHiredis library
# This module defines
# LIBHIREDIS_INCLUDE_DIRS   - where to find libhiredis/hiredis.h, etc.
# LIBHIREDIS_LIBRARIES      - List of libraries when using libhiredis.
# LIBHIREDIS_FOUND          - True if libhiredis found.
# LIBHIREDIS_VERSION_STRING - the version of libhiredis found (since CMake 2.8.8)

IF(LIBHIREDIS_LIBRARY AND LIBHIREDIS_INCLUDE_DIR)
  # in cache already
  SET(LIBHIREDIS_FIND_QUIETLY TRUE)
ENDIF(LIBHIREDIS_LIBRARY AND LIBHIREDIS_INCLUDE_DIR)

FIND_PATH(LIBHIREDIS_INCLUDE_DIR hiredis.h
  PATH_SUFFIXES hiredis
  $ENV{LIBHIREDIS_DIR}/include
  /usr/local/include
  /usr/include
  /sw/include
  /opt/local/include
  /opt/csw/include
  /opt/include
  /usr/local/include/libhiredis
  /mingw/include
)

SET(LIBRARY_HIREDISCORE_NAME_RELEASE libhiredis hiredis)
SET(LIBRARY_HIREDISCORE_NAME_DEBUG libhiredis hiredis)

FIND_LIBRARY(LIBHIREDIS_LIBRARY_RELEASE
  NAMES ${LIBRARY_HIREDISCORE_NAME_RELEASE}
  PATHS
  $ENV{LIBHIREDIS_DIR}/lib
  /usr/local/lib
  /usr/lib
  /usr/lib64
  /usr/local/X11R6/lib
  /usr/X11R6/lib
  /sw/lib
  /opt/local/lib
  /opt/csw/lib
  /opt/lib
  /usr/freeware/lib64
  /usr/local/lib/libhiredis
  /mingw/lib
)

FIND_LIBRARY(LIBHIREDIS_LIBRARY_DEBUG
  NAMES ${LIBRARY_HIREDISCORE_NAME_DEBUG}
  PATHS
  $ENV{LIBHIREDIS_DIR}/lib
  /usr/local/lib
  /usr/lib
  /usr/local/X11R6/lib
  /usr/X11R6/lib
  /sw/lib
  /opt/local/lib
  /opt/csw/lib
  /opt/lib
  /usr/freeware/lib64
  /usr/local/lib/libhiredis
  /mingw/lib
)

IF(LIBHIREDIS_INCLUDE_DIR)
  IF(LIBHIREDIS_LIBRARY_RELEASE AND LIBHIREDIS_LIBRARY_DEBUG)
    # Case where both Release and Debug versions are provided
    SET(LIBHIREDIS_FOUND TRUE)
    SET(LIBHIREDIS_LIBRARY optimized ${LIBHIREDIS_LIBRARY_RELEASE} debug ${LIBHIREDIS_LIBRARY_DEBUG})
  ELSEIF(LIBHIREDIS_LIBRARY_RELEASE)
    # Normal case
    SET(LIBHIREDIS_FOUND TRUE)
    SET(LIBHIREDIS_LIBRARY ${LIBHIREDIS_LIBRARY_RELEASE})
  ELSEIF(LIBHIREDIS_LIBRARY_DEBUG)
    # Case where LibHirredis is compiled from sources (debug version is compiled by default)
    SET(LIBHIREDIS_FOUND TRUE)
    SET(LIBHIREDIS_LIBRARY ${LIBHIREDIS_LIBRARY_DEBUG})
  ENDIF(LIBHIREDIS_LIBRARY_RELEASE AND LIBHIREDIS_LIBRARY_DEBUG)
ENDIF(LIBHIREDIS_INCLUDE_DIR)

IF(LIBHIREDIS_FOUND)
  IF(NOT LIBHIREDIS_FIND_QUIETLY)
    MESSAGE(STATUS "Found LibHiredis: ${LIBHIREDIS_INCLUDE_DIR} ${LIBHIREDIS_LIBRARY}")
  ENDIF(NOT LIBHIREDIS_FIND_QUIETLY)
ELSE(LIBHIREDIS_FOUND)
  IF(NOT LIBHIREDIS_FIND_QUIETLY)
    MESSAGE(STATUS "Warning: Unable to find LibHiredis! INCLUDE: ${LIBHIREDIS_INCLUDE_DIR}  LIB: ${LIBHIREDIS_LIBRARY}  ")
  ENDIF(NOT LIBHIREDIS_FIND_QUIETLY)
ENDIF(LIBHIREDIS_FOUND)

MARK_AS_ADVANCED(LIBHIREDIS_LIBRARY_RELEASE LIBHIREDIS_LIBRARY_DEBUG)

