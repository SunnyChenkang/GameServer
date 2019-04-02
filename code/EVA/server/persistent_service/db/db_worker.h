#ifndef PSE_DBWORKER_H_
#define PSE_DBWORKER_H_

#include <persistent_service/persistent_service/persistent_service_def.h>

PSE_NAMESPACE_BEGIN_DECL

//   load player entity;
bool InitLoadPlayer( CDBExecute* );

//   d_player.t_playerinfo;
bool InitPlayerInfoWoker( CDBExecute* );

//   d_player.t_item;
bool InitItemWorker( CDBExecute* );

//   d_player.t_statistics;
bool InitStatisticsWorker( CDBExecute* );

//   d_player.t_mission;
bool InitMissionWorker( CDBExecute* );

PSE_NAMESPACE_END_DECL

#endif //PSE_DBWORKER_H_


