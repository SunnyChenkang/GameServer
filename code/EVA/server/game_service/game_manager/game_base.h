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
    virtual bool JoinGame( ROLE_ID );
    /// 离开游戏;
    virtual bool LeaveGame( ROLE_ID );

    /// 游戏开始;
    virtual void StartGame( void ){ };
    /// 游戏结束;
    virtual void OwerGame( void ) { };

    /// 离线处理;
    virtual void UserOffline( ROLE_ID );
    /// 上线处理;
    virtual void UserOnline( ROLE_ID );

    /// 游戏帧数;
    virtual void FraveMove( void ) = 0;
    /// 游戏广播消息;
    virtual void BroadCasts( CSString , google::protobuf::Message* , ROLE_ID RemoveID = 0 );

    /// 获取玩家数量;
    uint32 GetRoleCount( void );

private:
    /// 是否游戏已满;
    bool IsGameFull( void );
    /// 是否游戏玩家;
    bool IsGameRole( ROLE_ID RoleID );

private:
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