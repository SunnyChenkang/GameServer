#ifndef PSE_DBSUBFUNC_H_
#define PSE_DBSUBFUNC_H_

#include <persistent_service/persistent_service/persistent_service_def.h>

PSE_NAMESPACE_BEGIN_DECL

//   load player;
void SubLoadPlayerEntity ( void* );

bool SubLoadPlayer    ( CRecordPlayer& );
bool SubLoadItem      ( CRecordPlayer& );
bool SubLoadStatistics( CRecordPlayer& );
bool SubLoadMission   ( CRecordPlayer& );

//   d_player.t_playerinfo;
void SubInsertPlayer( void* );
void SubUpdatePlayer( void* );
void SubDeletePlayer( void* );

//   d_player.t_item;
void SubInsertItem( void* );
void SubUpdateItem( void* );
void SubDeleteItem( void* );

//   d_player.t_statistics;
void SubInsertStatistics( void* );
void SubUpdateStatistics( void* );
void SubDeleteStatistics( void* );

//   d_player.t_mission;
void SubInsertMission( void* );
void SubUpdateMission( void* );
void SubDeleteMission( void* );

PSE_NAMESPACE_END_DECL

#endif //PSE_DBSUBFUNC_H_;