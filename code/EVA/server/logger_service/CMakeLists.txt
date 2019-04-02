FILE(GLOB SRC_LOGGER_SERVICE logger_service/*.cpp logger_service/*.h)
FILE(GLOB SRC_MYSQL		  	 db/*.cpp db/*.h)
FILE(GLOB SRC_MESSAGE 	  	 message/*.cpp message/*.h)


SOURCE_GROUP("LoggerService"		FILES ${SRC_LOGGER_SERVICE} )
SOURCE_GROUP("Message"				FILES ${SRC_MESSAGE} )
SOURCE_GROUP("DB"					FILES ${SRC_MYSQL} )


ADD_EXECUTABLE(logger_service WIN32 ${SRC_LOGGER_SERVICE} ${SRC_MYSQL} ${SRC_MESSAGE} )

INCLUDE_DIRECTORIES(${MYSQL_INCLUDE_DIR})

#IF(FREEBSD)
#ADD_PLATFORM_FLAGS("-lz")
#ENDIF(FREEBSD)

TARGET_LINK_LIBRARIES(  logger_service
						eva_adminmodules
						servershare
						${PROTOBUF_LIBRARIES}
						nelmisc
						nelnet)

NL_DEFAULT_PROPS(logger_service "Services: Logger Service ( LSE )")
NL_ADD_RUNTIME_FLAGS(logger_service)

#ADD_DEFINITIONS(${LIBXML2_DEFINITIONS})

INSTALL(TARGETS logger_service RUNTIME DESTINATION sbin COMPONENT services)
