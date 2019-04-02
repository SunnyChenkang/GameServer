#include "room_register.h"
#include "room_manager.h"
#include "room_timer.h"

#include <game_service/player/player_manager.h>
GSE_NAMESPACE_BEGIN_DECL

CRoomRegister::CRoomRegister( void )
{
    m_RoomInfoTimer.setRemaining( 3000 , new CRoomSyncInfoTimer() );
}

void CRoomRegister::LoadRoomInfo( void )
{
    m_Roomlist.clear_room_list();
    NLMISC::CConfigFile::CVar* pRoomConfig = NLNET::IService::getInstance()->ConfigFile.getVarPtr( "RoomList" );
    if ( NULL == pRoomConfig ) return;
    for ( uint32 idx = 0; idx < pRoomConfig->size(); idx++ )
    {
        NLNET::TParsedCommandLine ParseCommand;
        ParseCommand.parseParamList( pRoomConfig->asString( idx ) );
        PB_RoomInfo* pRoomInfo = m_Roomlist.add_room_list();
        NLMISC::CSString RoomName  = ParseCommand.getParam( "RoomName" )->ParamValue;
        NLMISC::CSString RoomCount = ParseCommand.getParam( "RoomCount" )->ParamValue;
        pRoomInfo->set_room_name ( RoomName );
        pRoomInfo->set_room_count( RoomCount.atosi() );
    }
}

void CRoomRegister::UpdateRoomInfo( void )
{
    PB_RoomInfoList SendRoomList;
    SendRoomList.set_service_id( NLNET::IService::getInstance()->getServiceId().get() );
    SendRoomList.set_role_count( PlayerManager.GetPlayerCount() );

    // 计算剩余房间数量;
    for ( uint32 idx = 0; idx < m_Roomlist.room_list_size(); idx++ )
    {
        const PB_RoomInfo& RoomInfo = m_Roomlist.room_list( idx );
        NLMISC::CSString RoomName = RoomInfo.room_name();
        sint32 RoomCount = RoomManager.GetRoomCount( RoomName );
        RoomCount = RoomInfo.room_count() - RoomCount;
        PB_RoomInfo* pRoomInfo = SendRoomList.add_room_list();
        pRoomInfo->set_room_name ( RoomName );
        pRoomInfo->set_room_count( RoomCount < 0 ? 0 : RoomCount );
    }

    // 同步调度服务器;
    {
        NLNET::CMessage SendMessage( "MSG_REGISTER_ROOM" );
        SendMessage.serial( &SendRoomList );
        SS_NETWORK->send( "SSE" , SendMessage );
    }
}

GSE_NAMESPACE_END_DECL