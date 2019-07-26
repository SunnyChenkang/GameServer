#ifndef SSE_GAME_MANAGER_H_
#define SSE_GAME_MANAGER_H_

#include <schedule_service/schedule_service/schedule_service_def.h>
#include "game.h"

SSE_NAMESPACE_BEGIN_DECL

class CGameManager : public NLMISC::CSingleton< CGameManager >
{
public:
    CGameManager( void );
   ~CGameManager( void );

    ///  加载游戏配置;
    void LoadGameInfo( TServiceId& );
    void LoadHallInfo( void );

    ///  删除游戏配置;
    void RemoveGameInfo( TServiceId& );
    void RemoveHallInfo( TServiceId& );

    //   更新游戏信息;
    void UpdateGameInfo( TServiceId& , CSString& , uint32 GameCount );
    void UpdateHallInfo( TServiceId& , CSString& , uint32 RoleCount );

    ///  获取游戏服务信息;
    CGameInfoPtr GetGameInfoPtr( CSString );
    CHallInfoPtr GetHallInfoPtr( void );

private:
    SS_PROPERTY( GAMETABLE , GameTable , private );
    SS_PROPERTY( HALLTABLE , HallTable , private );
};

SSE_NAMESPACE_END_DECL

#define GameManager CGameManager::instance()

#endif// SSE_GAME_MANAGER_H_