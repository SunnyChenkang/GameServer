IF(LIBUUID_LIBRARY AND LIBUUID_INCLUDE_DIR)
  # in cache already
  SET(LIBUUID_FIND_QUIETLY TRUE)
ENDIF(LIBUUID_LIBRARY AND LIBUUID_INCLUDE_DIR)

FIND_PATH(LIBUUID_INCLUDE_DIR uuid.h
  PATH_SUFFIXES uuid
  $ENV{LIBUUID_DIR}/include
  /usr/local/include
  /usr/include
  /sw/include
  /opt/local/include
  /opt/csw/include
  /opt/include
  /usr/local/include/libuuid
  /mingw/include
)

SET(LIBRARY_UUIDSCORE_NAME_RELEASE libuuid uuid)
SET(LIBRARY_UUIDSCORE_NAME_DEBUG libuuid uuid)

FIND_LIBRARY(LIBUUID_LIBRARY_RELEASE
  NAMES ${LIBRARY_UUIDSCORE_NAME_RELEASE}
  PATHS
  $ENV{LIBUUID_DIR}/lib
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
  /usr/local/lib/libuuid
  /mingw/lib
)

FIND_LIBRARY(LIBUUID_LIBRARY_DEBUG
  NAMES ${LIBRARY_UUIDSCORE_NAME_DEBUG}
  PATHS
  $ENV{LIBUUID_DIR}/lib
  /usr/local/lib
  /usr/lib
  /usr/local/X11R6/lib
  /usr/X11R6/lib
  /sw/lib
  /opt/local/lib
  /opt/csw/lib
  /opt/lib
  /usr/freeware/lib64
  /usr/local/lib/libuuid
  /mingw/lib
)

IF(LIBUUID_INCLUDE_DIR)
  IF(LIBUUID_LIBRARY_RELEASE AND LIBUUID_LIBRARY_DEBUG)
    # Case where both Release and Debug versions are provided
    SET(LIBUUID_FOUND TRUE)
    SET(LIBUUID_LIBRARY optimized ${LIBUUID_LIBRARY_RELEASE} debug ${LIBUUID_LIBRARY_DEBUG})
  ELSEIF(LIBUUID_LIBRARY_RELEASE)
    # Normal case
    SET(LIBUUID_FOUND TRUE)
    SET(LIBUUID_LIBRARY ${LIBUUID_LIBRARY_RELEASE})
  ELSEIF(LIBUUID_LIBRARY_DEBUG)
    # Case where LibUUID is compiled from sources (debug version is compiled by default)
    SET(LIBUUID_FOUND TRUE)
    SET(LIBUUID_LIBRARY ${LIBUUID_LIBRARY_DEBUG})
  ENDIF(LIBUUID_LIBRARY_RELEASE AND LIBUUID_LIBRARY_DEBUG)
ENDIF(LIBUUID_INCLUDE_DIR)

IF(LIBUUID_FOUND)
  IF(NOT LIBUUID_FIND_QUIETLY)
    MESSAGE(STATUS "Found LibUUID: ${LIBUUID_INCLUDE_DIR} ${LIBUUID_LIBRARY}")
  ENDIF(NOT LIBUUID_FIND_QUIETLY)
ELSE(LIBUUID_FOUND)
  IF(NOT LIBUUID_FIND_QUIETLY)
    MESSAGE(STATUS "Warning: Unable to find Libuuid! INCLUDE: ${LIBUUID_INCLUDE_DIR}  LIB: ${LIBUUID_LIBRARY}  ")
  ENDIF(NOT LIBUUID_FIND_QUIETLY)
ENDIF(LIBUUID_FOUND)

MARK_AS_ADVANCED(LIBUUID_LIBRARY_RELEASE LIBUUID_LIBRARY_DEBUG)

