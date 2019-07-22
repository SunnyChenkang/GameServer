FILE(GLOB SRC_SCHEDULE 	schedule_service/*.cpp schedule_service/*.h)
FILE(GLOB SRC_MESSAGE  	message/*.h message/*.cpp )
FILE(GLOB SRC_PLAYER   		player/*.h player/*.cpp )
FILE(GLOB SRC_LOGIN   		login/*.h login/*.cpp )
FILE(GLOB SRC_GAME     		game/*.h game/*.cpp )

SOURCE_GROUP("schedule_service" 	FILES ${SRC_SCHEDULE})
SOURCE_GROUP("message"  				FILES ${SRC_MESSAGE})
SOURCE_GROUP("player"   					FILES ${SRC_PLAYER} )
SOURCE_GROUP("login"    					FILES ${SRC_LOGIN} )
SOURCE_GROUP("game"    					FILES ${SRC_GAME} )

ADD_EXECUTABLE(schedule_service WIN32 ${SRC_SCHEDULE} ${SRC_MESSAGE} ${SRC_PLAYER} ${SRC_LOGIN} ${SRC_GAME} )

#INCLUDE_DIRECTORIES(${LIBXML2_INCLUDE_DIR} ${LUA_INCLUDE_DIR})

TARGET_LINK_LIBRARIES(	schedule_service
						eva_adminmodules
						${PROTOBUF_LIBRARIES}
						nelmisc
						nelnet
						servershare)

NL_DEFAULT_PROPS(schedule_service "Services: Schedule Service ( SSE )")
NL_ADD_RUNTIME_FLAGS(schedule_service)

#ADD_DEFINITIONS(${LIBXML2_DEFINITIONS})

INSTALL(TARGETS schedule_service RUNTIME DESTINATION sbin COMPONENT services)
