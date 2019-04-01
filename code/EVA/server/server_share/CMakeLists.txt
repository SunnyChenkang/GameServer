FILE(GLOB SRC *.cpp *.h)
FILE(GLOB SRC_JSON      	json/*.h json/*.cpp json/*.inl)
FILE(GLOB SRC_JSONTABLE 	json_table/*.h json_table/*.cpp)
FILE(GLOB SRC_TIMER     	timer/*.h timer/*.cpp)
FILE(GLOB SRC_COMMON    	common/*.h common/*.cpp)
FILE(GLOB SRC_MYSQL   		mysql/*.h mysql/*.cpp mysql/*.inl)
FILE(GLOB SRC_REDIS   		redis/*.h redis/*.cpp)
FILE(GLOB SRC_RECORD  		record/*.h record/*.cpp)
FILE(GLOB SRC_I18N      	i18n/*.h i18n/*.cpp)
FILE(GLOB SRC_UUID      	uuid/*.h uuid/*.cpp)
FILE(GLOB SRC_BUFFER    	buffer/*.h buffer/*.cpp buffer/*.inl)
FILE(GLOB SRC_PROTOBUF     	protobuf/*.h protobuf/*.cc)
FILE(GLOB SRC_FORMULA  		formula/*.h formula/*.cpp)
FILE(GLOB SRC_IDALLOCATE	id_allocate/*.h id_allocate/*.cpp)
FILE(GLOB SRC_CURL			curl/*.h curl/*.cpp)
FILE(GLOB SRC_TIMEVALUE		time_value/*.h time_value/*.cpp)

SOURCE_GROUP("json" 		FILES ${SRC_JSON})
SOURCE_GROUP("json_table" 	FILES ${SRC_JSONTABLE})
SOURCE_GROUP("timer" 		FILES ${SRC_TIMER})
SOURCE_GROUP("common" 		FILES ${SRC_COMMON})
SOURCE_GROUP("mysql"		FILES ${SRC_MYSQL})
SOURCE_GROUP("redis"		FILES ${SRC_REDIS})
SOURCE_GROUP("record" 		FILES ${SRC_RECORD})
SOURCE_GROUP("i18n" 		FILES ${SRC_I18N})
SOURCE_GROUP("uuid" 		FILES ${SRC_UUID})
SOURCE_GROUP("buffer" 		FILES ${SRC_BUFFER})
SOURCE_GROUP("protobuf" 	FILES ${SRC_PROTOBUF})
SOURCE_GROUP("formula"		FILES ${SRC_FORMULA})
SOURCE_GROUP("id_allocate"	FILES ${SRC_IDALLOCATE})
SOURCE_GROUP("curl"			FILES ${SRC_CURL})
SOURCE_GROUP("time_value"	FILES ${SRC_TIMEVALUE})

FIND_PACKAGE(CURL)
ADD_DEFINITIONS(-DCURL_STATICLIB)

NL_TARGET_LIB(servershare ${SRC} 
						  ${SRC_JSON}
						  ${SRC_COMMON} 
						  ${SRC_TIMER} 
						  ${SRC_JSONTABLE} 
						  ${SRC_MYSQL} 
						  ${SRC_RECORD} 
						  ${SRC_I18N} 
						  ${SRC_UUID} 
						  ${SRC_REDIS} 
						  ${SRC_BUFFER} 
						  ${SRC_PROTOBUF}
						  ${SRC_FORMULA}
						  ${SRC_IDALLOCATE}
						  ${SRC_CURL}
						  ${SRC_TIMEVALUE} )

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/server/src/server_share )
INCLUDE_DIRECTORIES(${MYSQL_INCLUDE_DIR} ${PROTOBUF_INCLUDE_DIR} ${CURL_INCLUDE_DIR} ${LIBHIREDIS_INCLUDE_DIR}) 

TARGET_LINK_LIBRARIES(  servershare
						nelmisc
						nelnet
						${CURL_LIBRARY}
						${MYSQL_LIBRARIES}
						${PROTOBUF_LIBRARIES}
						${LIBHIREDIS_LIBRARY})

NL_DEFAULT_PROPS(servershare "Services: Service Shared")
NL_ADD_RUNTIME_FLAGS(servershare)
NL_ADD_LIB_SUFFIX(servershare)

#ADD_DEFINITIONS(${LIBXML2_DEFINITIONS})

#IF(WITH_PCH)
#  ADD_NATIVE_PRECOMPILED_HEADER(servershare ${CMAKE_CURRENT_SOURCE_DIR}/stdpch.h ${CMAKE_CURRENT_SOURCE_DIR}/stdpch.cpp)
#ENDIF(WITH_PCH)

#INSTALL(TARGETS servershare LIBRARY DESTINATION ${EVA_LIB_PREFIX} ARCHIVE DESTINATION ${EVA_LIB_PREFIX} COMPONENT libraries)
IF((WITH_INSTALL_LIBRARIES AND WITH_STATIC) OR NOT WITH_STATIC)
  INSTALL(TARGETS servershare LIBRARY DESTINATION lib ARCHIVE DESTINATION lib COMPONENT libraries)
ENDIF((WITH_INSTALL_LIBRARIES AND WITH_STATIC) OR NOT WITH_STATIC)


