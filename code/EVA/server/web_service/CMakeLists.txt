FILE(GLOB SRC_WEB_SERVICE  web_service/*.cpp web_service/*.h)
FILE(GLOB SRC_MESSAGE 	   message/*.cpp message/*.h)
FILE(GLOB SRC_MODULE 	   module/*.cpp module/*.h)

SOURCE_GROUP("WebService" 		FILES ${SRC_WEB_SERVICE} )
SOURCE_GROUP("Message"			FILES ${SRC_MESSAGE} )
SOURCE_GROUP("Module"			FILES ${SRC_MODULE} )

ADD_EXECUTABLE(web_service WIN32 ${SRC_WEB_SERVICE} ${SRC_MESSAGE} ${SRC_MODULE} )

TARGET_LINK_LIBRARIES(  web_service
						eva_adminmodules
						servershare
						${PROTOBUF_LIBRARIES}
						nelmisc
						nelnet)

NL_DEFAULT_PROPS(web_service "Services: Web Service ( WSE )")
NL_ADD_RUNTIME_FLAGS(web_service)

#ADD_DEFINITIONS(${LIBXML2_DEFINITIONS})

INSTALL(TARGETS web_service RUNTIME DESTINATION sbin COMPONENT services)
