#ifndef SSE_PLAYER_MANAGER_H_
#define SSE_PLAYER_MANAGER_H_

#include <schedule_service/schedule_service/schedule_service_def.h>

SSE_NAMESPACE_BEGIN_DECL

class CPlayer;

class CPlayerManager : public NLMISC::CSingleton< CPlayerManager >
{
public:
    CPlayerManager( void ){ };
   ~CPlayerManager( void ){ };

    // 分配玩家实例;
    CPlayer* AllocPlayer( ROLE_ID );
    // 获取玩家数据;
    CPlayer* GetPlayer  ( ROLE_ID );

    // 玩家列表;
    SS_PROPERTY( PLAYER_TABLE , PlayerTable , private );
};

SSE_NAMESPACE_END_DECL

#define PlayerManager SSE::CPlayerManager::instance()

#endif // SSE_PLAYER_MANAGER_H_;