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
ADD_SUBDIRECTORY(persistant_service)


#ADD_SUBDIRECTORY(player_logic_service)
#ADD_SUBDIRECTORY(ranking_service)
#ADD_SUBDIRECTORY(admin_service)
#ADD_SUBDIRECTORY(mail_service)
#ADD_SUBDIRECTORY(logger_service)
#ADD_SUBDIRECTORY(data_center_service)

#ADD_SUBDIRECTORY(login_center)
#ADD_SUBDIRECTORY(login_fes)

#INSTALL(FILES common.cfg DESTINATION ~/service COMPONENT services)
