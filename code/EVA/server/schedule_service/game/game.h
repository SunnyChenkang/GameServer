#ifndef SSE_GAME_H_
#define SSE_GAME_H_

#include <schedule_service/schedule_service/schedule_service_def.h>

class CGameInfo
{
    SS_PROPERTY( NLMISC::CSString , GameName      , private );
    SS_PROPERTY( uint32           , GameMaxCount  , private );
    SS_PROPERTY( NLNET::TServiceId, GameServiceID , private );
    SS_PROPERTY( uint32           , GameCurrCount , private );

    ///  游戏是否已满;
    bool IsRoleFull( void ) { return this->GetGameCurrCount() >= this->GetGameMaxCount(); }
};

class CHallInfo
{
    SS_PROPERTY( NLMISC::CSString , HallName      , private );
    SS_PROPERTY( uint32           , RoleMaxCount  , private );
    SS_PROPERTY( NLNET::TServiceId, HallServiceID , private );
    SS_PROPERTY( uint32           , RoleCurrCount , private );

    /// 大厅是否已满;
    bool IsHallFull( void ) { return this->GetRoleCurrCount() >= this->GetRoleMaxCount(); }
};

// game;
typedef std::shared_ptr< CGameInfo > CGameInfoPtr;
typedef std::shared_ptr< CHallInfo > CHallInfoPtr;

// hall;
typedef std::vector< CGameInfoPtr >  GAMETABLE;
typedef std::vector< CHallInfoPtr >  HALLTABLE;

#endif//SSE_GAME_H_