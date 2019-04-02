FILE(GLOB SRC_GAME_SERVICE 	   				game_service/*.cpp game_service/*.h)
FILE(GLOB SRC_MESSAGE		   				message/*.cpp message/*.h)
FILE(GLOB SRC_PLAYER		   				player/*.cpp  player/*.h)
FILE(GLOB SRC_ITEM		   					item/*.cpp  item/*.h)
FILE(GLOB SRC_MISSION		   				mission/*.cpp  mission/*.h)
FILE(GLOB SRC_STATISTICS					statistics/*.cpp  statistics/*.h)
FILE(GLOB SRC_EVENT			   				event/*.cpp  event/*.h)
FILE(GLOB SRC_ROOM			   				room/*.cpp  room/*.h)
FILE(GLOB SRC_REDIS			   				redis/*.cpp  redis/*.h)
FILE(GLOB SRC_GAME			   				game/*.cpp  game/*.h)
FILE(GLOB SRC_GAME_RECORD					game/record/*.cpp  		   game/record/*.h			)
FILE(GLOB SRC_GAME_MAHJONG 	   				game/mahjong/*.cpp 		   game/mahjong/*.h			)
FILE(GLOB SRC_GAME_MAHJONG_BASE	   			game/mahjong/base/*.cpp    game/mahjong/base/*.h	)
FILE(GLOB SRC_GAME_MAHJONG_KOUDIAN 			game/mahjong/koudian/*.cpp game/mahjong/koudian/*.h )
FILE(GLOB SRC_GAME_MAHJONG_BAODING 			game/mahjong/baoding/*.cpp game/mahjong/baoding/*.h )
FILE(GLOB SRC_GAME_MAHJONG_HAINAN 			game/mahjong/hainan/*.cpp  game/mahjong/hainan/*.h  )


SOURCE_GROUP("GameService"  				FILES ${SRC_GAME_SERVICE})
SOURCE_GROUP("Message" 						FILES ${SRC_MESSAGE})
SOURCE_GROUP("Player" 						FILES ${SRC_PLAYER})
SOURCE_GROUP("Item" 						FILES ${SRC_ITEM})
SOURCE_GROUP("Mission" 						FILES ${SRC_MISSION})
SOURCE_GROUP("Statistics"					FILES ${SRC_STATISTICS})
SOURCE_GROUP("Event" 						FILES ${SRC_EVENT})
SOURCE_GROUP("Room" 						FILES ${SRC_ROOM})
SOURCE_GROUP("Redis" 						FILES ${SRC_REDIS})
SOURCE_GROUP("Game" 						FILES ${SRC_GAME})
SOURCE_GROUP("Game\\Record"					FILES ${SRC_GAME_RECORD})
SOURCE_GROUP("Game\\MahJong"				FILES ${SRC_GAME_MAHJONG})
SOURCE_GROUP("Game\\MahJong\\Base" 			FILES ${SRC_GAME_MAHJONG_BASE})
SOURCE_GROUP("Game\\MahJong\\KouDian"		FILES ${SRC_GAME_MAHJONG_KOUDIAN})
SOURCE_GROUP("Game\\MahJong\\BaoDing"		FILES ${SRC_GAME_MAHJONG_BAODING})
SOURCE_GROUP("Game\\MahJong\\HaiNan"		FILES ${SRC_GAME_MAHJONG_HAINAN})

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
								  ${SRC_GAME_RECORD}
								  ${SRC_GAME_MAHJONG}
								  ${SRC_GAME_MAHJONG_BASE}
								  ${SRC_GAME_MAHJONG_KOUDIAN}
								  ${SRC_GAME_MAHJONG_BAODING}
								  ${SRC_GAME_MAHJONG_HAINAN} )

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
