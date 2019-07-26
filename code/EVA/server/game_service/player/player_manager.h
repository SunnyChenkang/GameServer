#ifndef GES_PLAYER_MANAGER_H_
#define GES_PLAYER_MANAGER_H_

#include <game_service/game_service/game_service_def.h>
#include "player.h"

GSE_NAMESPACE_BEGIN_DECL

class CPlayerManager : public NLMISC::CSingleton< CPlayerManager >
{
public:
    CPlayerManager( void );
   ~CPlayerManager( void );

    ///  分配玩家实例;
    CPlayerPtr AllocPlayer( ROLE_ID );
    CPlayerPtr AllocPlayer( CRecordPlayer& );

    ///  获取玩家数据;
    CPlayerPtr GetPlayer( ROLE_ID );
    CPlayerPtr GetPlayer( CRecordPlayer& );

    ///  删除玩家;
    void DeletePlayer( ROLE_ID );
    void DeletePlayer( CRecordPlayer& );

    ///  切换场景;
    bool ChangeScenes( ROLE_ID , TServiceId );

private:
    SS_PROPERTY( PLAYER_TABLE , PlayerTable , private );
};

#define PlayerManager CPlayerManager::instance()

GSE_NAMESPACE_END_DECL

#endif// GES_PLAYER_MANAGER_H_