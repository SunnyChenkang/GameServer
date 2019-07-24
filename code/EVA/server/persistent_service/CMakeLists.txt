FILE(GLOB SRC_PERSISTENT  persistent_service/*.h persistent_service/*.cpp)
FILE(GLOB SRC_MYSQL		  db/*.h db/*.cpp)
FILE(GLOB SRC_MESSAGE 	  message/*.h message/*.cpp)
FILE(GLOB SRC_LOGIN 	  login/*.h login/*.cpp)
FILE(GLOB SRC_PLAYER  player/*.h player/*.cpp)

SOURCE_GROUP("persistent_service" 	FILES ${SRC_PERSISTENT} )
SOURCE_GROUP("message" 				FILES ${SRC_MESSAGE} )
SOURCE_GROUP("db"							FILES ${SRC_MYSQL} )
SOURCE_GROUP("login" 						FILES ${SRC_LOGIN} )
SOURCE_GROUP("player"						FILES ${SRC_PLAYER} )

ADD_EXECUTABLE(persistent_service WIN32 ${SRC_PERSISTENT} ${SRC_MYSQL} ${SRC_MESSAGE} ${SRC_LOGIN} ${SRC_PLAYER} )

INCLUDE_DIRECTORIES(${MYSQL_INCLUDE_DIR})

#IF(FREEBSD)
#ADD_PLATFORM_FLAGS("-lz")
#ENDIF(FREEBSD)

TARGET_LINK_LIBRARIES(  persistent_service
						eva_adminmodules
						servershare
						${PROTOBUF_LIBRARIES}
						nelmisc
						nelnet)

NL_DEFAULT_PROPS(persistent_service "Services: Persistent Service ( PSE )")
NL_ADD_RUNTIME_FLAGS(persistent_service)

#ADD_DEFINITIONS(${LIBXML2_DEFINITIONS})

INSTALL(TARGETS persistent_service RUNTIME DESTINATION sbin COMPONENT services)
