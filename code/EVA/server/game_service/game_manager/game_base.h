#ifndef GSE_GAME_BASE_H_
#define GSE_GAME_BASE_H_

#include <game_service/game_service/game_service_def.h>

GSE_NAMESPACE_BEGIN_DECL

class CGameBase
{
public:
    typedef PB_CreateRoom        TCtorParam;
    typedef std::vector<ROLE_ID> GameRoleList;

    CGameBase( TCtorParam& , uint32 );
    virtual ~CGameBase( void );

    /// 加入游戏;
    virtual bool GameJoin( ROLE_ID );
    /// 离开游戏;
    virtual bool GameLeave( ROLE_ID );

    /// 游戏开始;
    virtual void GameStart( void );
    /// 游戏结束;
    virtual void GameOwer( void );

    /// 离线处理;
    virtual void GameOffline( ROLE_ID );
    /// 上线处理;
    virtual void GameOnline( ROLE_ID );

    /// 游戏帧数;
    virtual void GameFraveMove( void ) = 0;
    /// 游戏广播消息;
    virtual void GameBroadCasts( CSString , google::protobuf::Message* , ROLE_ID RemoveID = 0 );

    /// 是否游戏已满;
    virtual bool GameIsFull( void );
    /// 是否游戏玩家;
    virtual bool GameIsRole( ROLE_ID RoleID );

    /// 获取玩家数量;
    virtual uint32 GetRoleCount( void );

    SS_PROPERTY( ROOM_ID            , RoomID         , protected ); /// 房间ID;
    SS_PROPERTY( ROLE_ID            , OwnerID        , protected ); /// 房主ID;
    SS_PROPERTY( GameRoleList       , RoleList       , protected ); /// 角色列表;
    SS_PROPERTY( TCtorParam         , CreateGameData , protected ); /// 创建游戏属性;
    SS_PROPERTY( uint32             , FrameMoveTime  , protected ); /// 游戏帧率;
};

typedef std::shared_ptr< CGameBase >       CGameBasePtr;
typedef std::map< ROOM_ID , CGameBasePtr > GameList;

GSE_NAMESPACE_END_DECL

#endif//GSE_GAME_BASE_H_