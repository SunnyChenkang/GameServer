#include "event_room_callback.h"
#include "event_define.h"

#include <game_service/player/player.h>
#include <game_service/player/player_manager.h>
#include <game_service/room/room_base.h>
#include <game_service/room/room_manager.h>

GSE_NAMESPACE_BEGIN_DECL

void CEventRoomCallBack::InitEventCallBack( void )
{
    EventDefine.EventUserLogin.connect  ( &EventRoomCallBack , &CEventRoomCallBack::CallBackUserLogin   );
    EventDefine.EventUserOffline.connect( &EventRoomCallBack , &CEventRoomCallBack::CallBackUserOffline );
    EventDefine.EventJoinRoom.connect   ( &EventRoomCallBack , &CEventRoomCallBack::CallBackJoinRoom    );
    EventDefine.EventLeaveRoom.connect  ( &EventRoomCallBack , &CEventRoomCallBack::CallBackLeaveRoom   );
    EventDefine.EventDeleteRoom.connect ( &EventRoomCallBack , &CEventRoomCallBack::CallBackDeleteRoom  );
    EventDefine.EventGameStart.connect  ( &EventRoomCallBack , &CEventRoomCallBack::CallBackGameStart   );
    EventDefine.EventGameOwer.connect   ( &EventRoomCallBack , &CEventRoomCallBack::CallBackGameOwer    );
}

void CEventRoomCallBack::CallBackUserLogin( PB_UserLogin& UserLogin )
{
    CPlayer* pPlayer = PlayerManager.GetPlayer( UserLogin.role_id() );
    if ( NULL == pPlayer ) return;
    CRoomBase* pRoomBase = RoomManager.GetRoomInfo( pPlayer->GetRoomID() );
    if ( NULL != pRoomBase )
    pRoomBase->UserOnline( UserLogin.role_id() );
}

void CEventRoomCallBack::CallBackUserOffline( ROLE_ID RoleID )
{
    CPlayer* pPlayer = PlayerManager.GetPlayer( RoleID );
    if ( NULL == pPlayer ) return;
    CRoomBase* pRoomBase = RoomManager.GetRoomInfo( pPlayer->GetRoomID() );
    if ( NULL != pRoomBase )
    pRoomBase->UserOffline( RoleID );
}

void CEventRoomCallBack::CallBackJoinRoom( ROLE_ID RoleID , ROOM_ID RoomID )
{
    CPlayer* pPlayer = PlayerManager.GetPlayer( RoleID );
    if ( NULL == pPlayer ) return;
    pPlayer->SetRoomID( RoomID );
}

void CEventRoomCallBack::CallBackLeaveRoom( ROLE_ID RoleID , ROOM_ID RoomID )
{
    CPlayer* pPlayer = PlayerManager.GetPlayer( RoleID );
    if ( NULL == pPlayer ) return;
    pPlayer->SetRoomID( 0 );
}

void CEventRoomCallBack::CallBackDeleteRoom( ROOM_ID RoomID , std::vector<ROLE_ID>& Rolelist )
{
    for ( std::vector< ROOM_ID >::iterator it = Rolelist.begin() ; it != Rolelist.end() ; ++it )
    {
        CPlayer* pPlayer = PlayerManager.GetPlayer( *it );
        if ( NULL == pPlayer ) continue;
        pPlayer->SetRoomID( 0 );
    }
}

void CEventRoomCallBack::CallBackGameStart( ROOM_ID RoomID )
{
    CRoomBase* pRoomBase = RoomManager.GetRoomInfo( RoomID );
    if ( NULL == pRoomBase ) return;

}

void CEventRoomCallBack::CallBackGameOwer( ROOM_ID RoomID )
{
    CRoomBase* pRoomBase = RoomManager.GetRoomInfo( RoomID );
    if ( NULL == pRoomBase ) return;

}


GSE_NAMESPACE_END_DECL