#FIND_PACKAGE(MysqlConnector)
#FIND_PACKAGE(CURL)
FIND_PACKAGE(MySQL)
FIND_PACKAGE(ToLua)
# move to server_share/CMakeLists.txt

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

ADD_SUBDIRECTORY(server_share)
ADD_SUBDIRECTORY(admin_modules)
ADD_SUBDIRECTORY(frontend_service)
ADD_SUBDIRECTORY(naming_service)
ADD_SUBDIRECTORY(schedule_service)
ADD_SUBDIRECTORY(persistent_service)
ADD_SUBDIRECTORY(game_service)
ADD_SUBDIRECTORY(logger_service)
ADD_SUBDIRECTORY(web_service)

#INSTALL(FILES common.cfg DESTINATION ~/service COMPONENT services)
