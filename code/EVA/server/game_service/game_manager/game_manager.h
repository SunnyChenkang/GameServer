#ifndef GSE_GAME_MANAGER_H_
#define GSE_GAME_MANAGER_H_

#include <game_service/game_service/game_service_def.h>
#include "game_base.h"

GSE_NAMESPACE_BEGIN_DECL

class CGameManager : public CSingleton< CGameManager >
{
public:
    CGameManager( void );
   ~CGameManager( void );

    ///  加入游戏;
    bool JoinGame( ROLE_ID , ROOM_ID );
    ///  离开游戏;
    bool LeaveGame( ROLE_ID );
    ///  删除游戏;
    bool DeleteGame( ROOM_ID );

    ///  创建游戏;
    bool CreateGame( ROLE_ID , PB_CreateRoom& );
    bool CreateGameChangeScenes( ROLE_ID , PB_CreateRoom& );

    /// 获取游戏实体;
    CGameBasePtr GetGameBasePtr( ROOM_ID );

    /// 房间列表;
    SS_PROPERTY( GameList , GameList , private );
};

#define GameManager CGameManager::getInstance()

GSE_NAMESPACE_END_DECL

#endif//GSE_GAME_MANAGER_H_