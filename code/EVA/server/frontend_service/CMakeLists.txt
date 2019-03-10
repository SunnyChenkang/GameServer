FILE(GLOB SRC *.cpp *.h)
FILE(GLOB SRC_RUDP                   rudp/*.h rudp/*.cpp)
FILE(GLOB SRC_RUDP_REVOLVER   		 rudp/revolver/*.h rudp/revolver/*.cpp )
FILE(GLOB SRC_RUDP_RUDP		   		 rudp/rudp/*.h rudp/rudp/*.cpp)

SOURCE_GROUP("RUDP"   			FILES ${SRC_RUDP} )
SOURCE_GROUP("RUDP\\revolver"   FILES ${SRC_RUDP_REVOLVER} )
SOURCE_GROUP("RUDP\\rudp"   	FILES ${SRC_RUDP_RUDP} )


ADD_EXECUTABLE(frontend_service WIN32 ${SRC} ${SRC_RUDP} ${SRC_RUDP_REVOLVER} ${SRC_RUDP_RUDP} )

INCLUDE_DIRECTORIES( ${MYSQL_INCLUDE_DIR} ${LIBEVENT_INCLUDE_DIR} ${OPENSSL_INCLUDE_DIR})

TARGET_LINK_LIBRARIES(	frontend_service
						eva_adminmodules
						${PROTOBUF_LIBRARIES}
						${LIBEVENT_LIBRARY}
						nelmisc
						nelnet
						servershare )

NL_DEFAULT_PROPS(frontend_service "Services: Frontend Service ( FES )")
NL_ADD_RUNTIME_FLAGS(frontend_service)

ADD_DEFINITIONS(${LIBXML2_DEFINITIONS})

IF(WITH_PCH AND NOT MINGW) # FIXME: PCH too large (> 130MB), crashes cc1plus under MinGW
  ADD_NATIVE_PRECOMPILED_HEADER(frontend_service ${CMAKE_CURRENT_SOURCE_DIR}/stdpch.h ${CMAKE_CURRENT_SOURCE_DIR}/stdpch.cpp)
ENDIF(WITH_PCH AND NOT MINGW)

INSTALL(TARGETS frontend_service RUNTIME DESTINATION sbin COMPONENT services)
