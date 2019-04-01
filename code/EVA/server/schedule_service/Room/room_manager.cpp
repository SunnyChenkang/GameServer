#include "room_manager.h"
#include <schedule_service/player/player.h>
#include <schedule_service/player/player_manager.h>

SSE_NAMESPACE_BEGIN_DECL

CRoomManager::CRoomManager( void )
{
    m_RandomIdAlloc = new CRandomIDAlloc( 1 , 1000000 );
}

void SSE::CRoomManager::CreateRoom( NLNET::CMessage& Message )
{
    ROLE_ID RoleID = 0;
    PB_CreateRoom PBCreateRoom;
    Message.serial( RoleID );
    Message.serial( &PBCreateRoom );

    ROOM_ID AllocId = m_RandomIdAlloc->Allocate();
    if ( AllocId == 0 ) return;

    // 分配房间服务器;
    CPlayer* pPlayer = PlayerManager.GetPlayer( RoleID );
    if ( NULL == pPlayer ) return;
    NLNET::TServiceId GameServiceId = GetRoomGameService( PBCreateRoom.room_name() );
    if ( GameServiceId == NLNET::TServiceId::InvalidId ) return;
    PBCreateRoom.set_service_id( GameServiceId.get() );
    PBCreateRoom.set_room_id( AllocId );

    NLNET::CMessage SendMessage("MSG_CREATE_ROOM");
    SendMessage.serial( RoleID );
    SendMessage.serial( &PBCreateRoom );
    SS_NETWORK->send( pPlayer->GetGameServiceId() , SendMessage );
}

void CRoomManager::RegisterRoomInfo( NLNET::CMessage& Message )
{
    NLNET::TServiceId GameServiceId = NLNET::TServiceId::InvalidId;
    PB_RoomInfoList RoomInfoList;
    Message.serial( &RoomInfoList );
    m_RoomInfo[ RoomInfoList.service_id() ] = RoomInfoList;
}

void CRoomManager::DeleteRoomInfo( NLNET::TServiceId& ServiceId )
{
    m_RoomInfo.erase( ServiceId.get() );
}

NLNET::TServiceId CRoomManager::GetLoginGamaService( void )
{
    NLNET::TServiceId GameServiceId = NLNET::TServiceId::InvalidId;
    uint32 RoleCount = std::numeric_limits< uint32 >::max();
    ROOM_INFO_TABLE::iterator it = m_RoomInfo.begin();
    for ( ; it != m_RoomInfo.end(); ++it )
    {
        if ( it->second.role_count() > RoleCount ) continue;
        RoleCount = it->second.role_count();
        GameServiceId = NLNET::TServiceId( it->first );
    }

    return GameServiceId;
}

NLNET::TServiceId CRoomManager::GetRoomGameService( NLMISC::CSString RoomName )
{
    NLNET::TServiceId GameServiceId = NLNET::TServiceId::InvalidId;
    uint32 RoomCount = std::numeric_limits< uint32 >::max();
    for ( ROOM_INFO_TABLE::iterator it = m_RoomInfo.begin(); it != m_RoomInfo.end(); ++it )
    {
        for ( uint32 idx = 0; idx < it->second.room_list_size(); idx++ )
        {
            const PB_RoomInfo& RoomInfo = it->second.room_list( idx );
            if ( RoomInfo.room_name() != RoomName ) continue;
            if ( RoomInfo.room_count() <= 0       ) continue;
            if ( RoomInfo.room_count() > RoomCount) continue;
            RoomCount = RoomInfo.room_count();
            GameServiceId = NLNET::TServiceId( it->first );
        }
    }

    return GameServiceId;
}

SSE_NAMESPACE_END_DECL
