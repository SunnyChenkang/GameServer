FILE(GLOB SRC_PERSISTENT  persistent_service/*.cpp persistent_service/*.h)
FILE(GLOB SRC_MYSQL		  db/*.cpp db/*.h)
FILE(GLOB SRC_MESSAGE 	  message/*.cpp message/*.h)
FILE(GLOB SRC_LOGIN 	  login/*.cpp login/*.h)

SOURCE_GROUP("PersistentService" 	FILES ${SRC_PERSISTENT} )
SOURCE_GROUP("Message" 				FILES ${SRC_MESSAGE} )
SOURCE_GROUP("DB"					FILES ${SRC_MYSQL} )
SOURCE_GROUP("Login" 				FILES ${SRC_LOGIN} )

ADD_EXECUTABLE(persistent_service WIN32 ${SRC_PERSISTENT} ${SRC_MYSQL} ${SRC_MESSAGE} ${SRC_LOGIN} )

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
