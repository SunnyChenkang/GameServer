#ifndef GES_PLAYER_MANAGER_H_
#define GES_PLAYER_MANAGER_H_

#include <game_service/game_service/game_service_def.h>

GSE_NAMESPACE_BEGIN_DECL

class CPlayer;

class CPlayerManager : public NLMISC::CSingleton< CPlayerManager >
{
public:
    CPlayerManager( void ) { };
   ~CPlayerManager( void ) { };

public:
    //       分配角色实体;
    CPlayer* AllocPlayer( CRecordPlayer& RecordPlayer );
    CPlayer* AllocPlayer( ROLE_ID );

    //       获取角色实体;
    CPlayer* GetPlayer( ROLE_ID );
    //       删除玩家实体;
    void     DeletePlayer( ROLE_ID );
    //       获取实体数量;
    uint32   GetPlayerCount( void );
    //       切换场景;
    bool     ChangeScenes( ROLE_ID , NLNET::TServiceId );

private:
    PLAYER_TABLE m_RoleTable;
};

#define PlayerManager CPlayerManager::instance()

GSE_NAMESPACE_END_DECL

#endif// GES_PLAYER_MANAGER_H_