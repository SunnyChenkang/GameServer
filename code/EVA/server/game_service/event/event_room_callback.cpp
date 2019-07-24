#include "event_room_callback.h"
#include "event_define.h"

#include <game_service/player/player.h>
#include <game_service/player/player_manager.h>
#include <game_service/room/room_base.h>
#include <game_service/room/room_manager.h>

GSE_NAMESPACE_BEGIN_DECL

void CEventRoomCallBack::InitEventCallBack( void )
{
    EventDefine.PlayerLoginFinish.connect  ( &EventRoomCallBack , &CEventRoomCallBack::CallBackPlyaerLoginFinish     );
    EventDefine.PlayerOffline.connect      ( &EventRoomCallBack , &CEventRoomCallBack::CallBackPlayerOffline   );
    EventDefine.JoinGame.connect           ( &EventRoomCallBack , &CEventRoomCallBack::CallBackJoinRoom        );
    EventDefine.LeaveRoom.connect          ( &EventRoomCallBack , &CEventRoomCallBack::CallBackLeaveRoom       );
    EventDefine.DeleteRoom.connect         ( &EventRoomCallBack , &CEventRoomCallBack::CallBackDeleteRoom      );
    EventDefine.GameStart.connect          ( &EventRoomCallBack , &CEventRoomCallBack::CallBackGameStart       );
    EventDefine.GameOwer.connect           ( &EventRoomCallBack , &CEventRoomCallBack::CallBackGameOwer        );
}

void CEventRoomCallBack::CallBackPlyaerLoginFinish( PB_UserLogin& UserLogin )
{
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( UserLogin.role_id() );
    if ( nullptr == PlayerPtr ) { return; }

    CRoomBase* pRoomBase = RoomManager.GetRoomInfo( 0 );
    if ( nullptr != pRoomBase )
    pRoomBase->UserOnline( UserLogin.role_id() );
}

void CEventRoomCallBack::CallBackPlayerOffline( ROLE_ID RoleID )
{
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( RoleID );
    if ( nullptr == PlayerPtr ) { return; }

    CRoomBase* pRoomBase = RoomManager.GetRoomInfo( 0 );
    if ( nullptr != pRoomBase )
    pRoomBase->UserOffline( RoleID );
}

void CEventRoomCallBack::CallBackJoinRoom( ROLE_ID RoleID , ROOM_ID RoomID )
{

}

void CEventRoomCallBack::CallBackLeaveRoom( ROLE_ID RoleID , ROOM_ID RoomID )
{

}

void CEventRoomCallBack::CallBackDeleteRoom( ROOM_ID RoomID , std::vector<ROLE_ID>& Rolelist )
{

}

void CEventRoomCallBack::CallBackGameStart( ROLE_ID RoleID , ROOM_ID RoomID )
{
    
}

void CEventRoomCallBack::CallBackGameOwer( ROLE_ID , ROOM_ID RoomID )
{
    
}


GSE_NAMESPACE_END_DECL