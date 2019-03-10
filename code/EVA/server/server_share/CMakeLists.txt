FILE(GLOB SRC *.cpp *.h)
FILE(GLOB SRC_JSON      	json/*.h json/*.cpp json/*.inl)
FILE(GLOB SRC_JSONTABLE 	json_table/*.h json_table/*.cpp)
FILE(GLOB SRC_TIMER     	timer/*.h timer/*.cpp)
FILE(GLOB SRC_COMMON    	common/*.h common/*.cpp)
FILE(GLOB SRC_DBMYSQL   	db_mysql/*.h db_mysql/*.cpp db_mysql/*.inl)
FILE(GLOB SRC_DBREDIS   	db_redis/*.h db_redis/*.cpp)
FILE(GLOB SRC_DBRECORD  	db_record/*.h db_record/*.cpp)
FILE(GLOB SRC_I18N      	i18n/*.h i18n/*.cpp)
FILE(GLOB SRC_UUID      	uuid/*.h uuid/*.cpp)
FILE(GLOB SRC_BUFFER    	buffer/*.h buffer/*.cpp buffer/*.inl)
FILE(GLOB SRC_PROTOBUF     	protobuf/*.h protobuf/*.cc)
FILE(GLOB SRC_FORMULA  		formula/*.h formula/*.cpp)


SOURCE_GROUP("json" 		FILES ${SRC_JSON})
SOURCE_GROUP("json_table" 	FILES ${SRC_JSONTABLE})
SOURCE_GROUP("timer" 		FILES ${SRC_TIMER})
SOURCE_GROUP("common" 		FILES ${SRC_COMMON})
SOURCE_GROUP("db_mysql"		FILES ${SRC_DBMYSQL})
SOURCE_GROUP("db_redis"		FILES ${SRC_DBREDIS})
SOURCE_GROUP("db_record" 	FILES ${SRC_DBRECORD})
SOURCE_GROUP("i18n" 		FILES ${SRC_I18N})
SOURCE_GROUP("uuid" 		FILES ${SRC_UUID})
SOURCE_GROUP("buffer" 		FILES ${SRC_BUFFER})
SOURCE_GROUP("protobuf" 	FILES ${SRC_PROTOBUF})
SOURCE_GROUP("formula"		FILES ${SRC_FORMULA})

FIND_PACKAGE(CURL)
ADD_DEFINITIONS(-DCURL_STATICLIB)

NL_TARGET_LIB(servershare ${SRC} 
						  ${SRC_JSON}
						  ${SRC_COMMON} 
						  ${SRC_TIMER} 
						  ${SRC_JSONTABLE} 
						  ${SRC_DBMYSQL} 
						  ${SRC_DBRECORD} 
						  ${SRC_I18N} 
						  ${SRC_UUID} 
						  ${SRC_DBREDIS} 
						  ${SRC_BUFFER} 
						  ${SRC_PROTOBUF}
						  ${SRC_FORMULA})

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/server/src/server_share )
INCLUDE_DIRECTORIES(${MYSQL_INCLUDE_DIR} ${PROTOBUF_INCLUDE_DIR} ${CURL_INCLUDE_DIR} ${LIBHIREDIS_INCLUDE_DIR}) 

TARGET_LINK_LIBRARIES(  servershare
						nelmisc
						nelnet
						${MYSQL_LIBRARIES}
						${PROTOBUF_LIBRARIES}
						${LIBHIREDIS_LIBRARY})

NL_DEFAULT_PROPS(servershare "Services: Library: Service Shared")
NL_ADD_RUNTIME_FLAGS(servershare)
NL_ADD_LIB_SUFFIX(servershare)

ADD_DEFINITIONS(${LIBXML2_DEFINITIONS})

#IF(WITH_PCH)
#  ADD_NATIVE_PRECOMPILED_HEADER(servershare ${CMAKE_CURRENT_SOURCE_DIR}/stdpch.h ${CMAKE_CURRENT_SOURCE_DIR}/stdpch.cpp)
#ENDIF(WITH_PCH)

#INSTALL(TARGETS servershare LIBRARY DESTINATION ${EVA_LIB_PREFIX} ARCHIVE DESTINATION ${EVA_LIB_PREFIX} COMPONENT libraries)
IF((WITH_INSTALL_LIBRARIES AND WITH_STATIC) OR NOT WITH_STATIC)
  INSTALL(TARGETS servershare LIBRARY DESTINATION lib ARCHIVE DESTINATION lib COMPONENT libraries)
ENDIF((WITH_INSTALL_LIBRARIES AND WITH_STATIC) OR NOT WITH_STATIC)


