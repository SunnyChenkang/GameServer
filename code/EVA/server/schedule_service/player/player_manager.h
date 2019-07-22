#ifndef SSE_PLAYER_MANAGER_H_
#define SSE_PLAYER_MANAGER_H_

#include <schedule_service/schedule_service/schedule_service_def.h>
#include "player.h"

SSE_NAMESPACE_BEGIN_DECL

class CPlayerManager : public CSingleton< CPlayerManager >
{
public:
    CPlayerManager( void );
   ~CPlayerManager( void );

    /// 分配玩家实例;
    CPlayerPtr AllocPlayer( ROLE_ID );
    /// 获取玩家数据;
    CPlayerPtr GetPlayer  ( ROLE_ID );

    SS_PROPERTY( PLAYER_TABLE , PlayerTable , private );
};

#define PlayerManager CPlayerManager::getInstance()

SSE_NAMESPACE_END_DECL

#endif // SSE_PLAYER_MANAGER_H_;