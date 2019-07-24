FILE(GLOB SRC_GAME_SERVICE					game_service/*.h game_service/*.cpp)
FILE(GLOB SRC_MESSAGE		   						message/*.h message/*.cpp)
FILE(GLOB SRC_PLAYER									player/*.h player/*.cpp)
FILE(GLOB SRC_ITEM										item/*.h item/*.cpp)
FILE(GLOB SRC_MISSION		   						mission/*.h mission/*.cpp)
FILE(GLOB SRC_STATISTICS							statistics/*.h statistics/*.cpp)
FILE(GLOB SRC_EVENT			   						event/*.h event/*.cpp)
FILE(GLOB SRC_GAME_MANAGER    			game_manager/*.h game_manager/*.cpp )
FILE(GLOB SRC_GAME			   						game/*.h game/*.cpp)
FILE(GLOB SRC_GAME_RECORD					game/record/*.h game/record/*.cpp			)
FILE(GLOB SRC_GAME_MAHJONG				game/mahjong/*.h game/mahjong/*.cpp			)
FILE(GLOB SRC_GAME_MAHJONG_BASE		game/mahjong/base/*.h game/mahjong/base/*.cpp	)


SOURCE_GROUP("game_service"					FILES ${SRC_GAME_SERVICE})
SOURCE_GROUP("message"							FILES ${SRC_MESSAGE})
SOURCE_GROUP("player" 								FILES ${SRC_PLAYER})
SOURCE_GROUP("item" 								FILES ${SRC_ITEM})
SOURCE_GROUP("mission" 							FILES ${SRC_MISSION})
SOURCE_GROUP("statistics"							FILES ${SRC_STATISTICS})
SOURCE_GROUP("event" 								FILES ${SRC_EVENT})
SOURCE_GROUP("game_manager"				FILES ${SRC_GAME_MANAGER})
SOURCE_GROUP("game" 								FILES ${SRC_GAME})
SOURCE_GROUP("game\\record"					FILES ${SRC_GAME_RECORD})
SOURCE_GROUP("game\\mahjong"				FILES ${SRC_GAME_MAHJONG})
SOURCE_GROUP("game\\mahjong\\base"	FILES ${SRC_GAME_MAHJONG_BASE})

ADD_EXECUTABLE(game_service WIN32 ${SRC_GAME_SERVICE} 
								  ${SRC_MESSAGE} 
								  ${SRC_PLAYER}
								  ${SRC_ITEM}
								  ${SRC_MISSION}
								  ${SRC_STATISTICS}
								  ${SRC_EVENT} 
								  ${SRC_ROOM}
								  ${SRC_REDIS}
								  ${SRC_GAME}
								  ${SRC_GAME_MANAGER}
								  ${SRC_GAME_RECORD}
								  ${SRC_GAME_MAHJONG}
								  ${SRC_GAME_MAHJONG_BASE})

INCLUDE_DIRECTORIES(${CURL_INCLUDE_DIR} ${MYSQL_INCLUDE_DIR})

TARGET_LINK_LIBRARIES(	game_service
						eva_adminmodules
						${PROTOBUF_LIBRARIES}
						${CURL_LIBRARY}
						nelmisc
						nelnet
						servershare)

NL_DEFAULT_PROPS(game_service "Services: Game Service ( GSE )")
NL_ADD_RUNTIME_FLAGS(game_service)

#ADD_DEFINITIONS(${LIBXML2_DEFINITIONS})

INSTALL(TARGETS game_service RUNTIME DESTINATION sbin COMPONENT services)
