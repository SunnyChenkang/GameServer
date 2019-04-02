#ifndef GSE_ROOM_BASE_H_
#define GSE_ROOM_BASE_H_

#include <game_service/game_service/game_service_def.h>

GSE_NAMESPACE_BEGIN_DECL

class CRoomBase
{
public:
    typedef PB_CreateRoom TCtorParam;
    typedef std::vector< ROOM_ID > ROOM_PLAYER_TABLE;

    CRoomBase( TCtorParam& , uint32 );
    virtual ~CRoomBase( void );

    // 加入房间;
    virtual bool JoinGameRoom( ROLE_ID );
    // 离开房间;
    virtual void LeaveGameRoom( ROLE_ID );
    // 游戏开始;
    virtual void GameStart( void );
    // 游戏结束;
    virtual void GameOwer( void );
    // 游戏帧数;
    virtual void FrameMove( void ) = 0;

    // 房间已满;
    virtual bool IsRoomFull( void );
    virtual bool IsRoomRole( ROLE_ID );
    // 用户离线;
    virtual void UserOffline( ROLE_ID );
    virtual void UserOnline ( ROLE_ID );

    // 广播房间消息;
    virtual void RoomBroadCasts( NLMISC::CSString , google::protobuf::Message* , ROLE_ID RemoveId = 0 );

private:
    // 添加玩家;
    bool AddRoomPlayer( ROLE_ID );
    bool DelRoomPlayer( ROLE_ID );

    // 获取玩家数量;
    uint32 GetPlayerCount( void );

    SS_PROPERTY( ROOM_ID          , RoomID          , protected );   // 普通房间ID;
    SS_PROPERTY( NLMISC::CSString , RoomName        , protected );   // 房间名字;
    SS_PROPERTY( ROLE_ID          , OwnerID         , protected );   // 房主ID;
    SS_PROPERTY( ROOM_PLAYER_TABLE, RoomPlayer      , protected );   // 房间列表;
    SS_PROPERTY( bool             , GameStart       , protected );   // 游戏开始;
    SS_PROPERTY( uint32           , FrameMoveTime   , protected );   // 房间内帧数;
    SS_PROPERTY( TCtorParam       , CreateRoomData  , protected );   // 获取房间数据;

private:
    CTimer m_FrameMoveTimer;
};

GSE_NAMESPACE_END_DECL

#endif // GSE_ROOM_BASE_H_
