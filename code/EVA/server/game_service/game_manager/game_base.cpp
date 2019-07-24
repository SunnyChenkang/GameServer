#include "game_base.h"
#include <game_service/event/event_define.h>
#include <game_service/player/player.h>
#include <game_service/player/player_manager.h>

GSE_NAMESPACE_BEGIN_DECL

CGameBase::CGameBase( TCtorParam& GameData , uint32 )
{
    CJsonGameCell* pGameCell = JsonGameConfig.GetJsonCell< CJsonGameCell >( m_CreateGameData.room_name() );
    if ( nullptr == pGameCell ) { return; }
    m_RoleList.resize( pGameCell->GetGameMax() );
    m_RoomID = GameData.room_id();
}

CGameBase::~CGameBase( void )
{

}

bool CGameBase::JoinGame( ROLE_ID RoleID )
{
    /// 检查进入游戏;
    if ( this->IsGameFull() )           { return false; }
    if ( this->IsGameRole( RoleID ) )   { return false; }

    /// 添加玩家列表;
    for ( auto& Element : m_RoleList )
    {
        if ( Element != 0 ) { continue; }
        Element = RoleID;
        break;
    }
    EventDefine.JoinGame( RoleID , GetRoomID() );
}

bool CGameBase::LeaveGame( ROLE_ID RoleID )
{
    /// 检查离开游戏;
    if ( !this->IsGameRole( RoleID ) ) { return false; }

    /// 删除玩家列表;
    for ( auto& Element : m_RoleList )
    {
        if ( Element != RoleID ) { continue; }
        Element = 0;
        break;
    }
    EventDefine.LeaveRoom( RoleID , GetRoomID() );
}

bool CGameBase::IsGameRole( ROLE_ID RoleID )
{
    for ( auto Element : m_RoleList )
    {
        if ( Element == RoleID ) { return true; }
    }
    return false;
}

void CGameBase::BroadCasts( CSString Name , google::protobuf::Message* pMessage , ROLE_ID RemoveID /*= 0 */ )
{
    for ( auto Element : m_RoleList )
    {
        if ( Element == RemoveID )  { continue; }
        CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( Element );
        if ( nullptr == PlayerPtr ) { continue; }
        SendToClient( Element , PlayerPtr->GetFrontendServiceID() , Name , pMessage );
    }
}

uint32 CGameBase::GetRoleCount( void )
{
    uint32 Count = 0;
    for ( auto Element : m_RoleList )
    {
        if ( Element <= 0 ) { continue; }
        Count++;
    }
    return Count;
}

void CGameBase::UserOffline( ROLE_ID RoleID )
{
    PB_UserOffline PB_Offline;
    PB_Offline.set_role_id( RoleID );
    BroadCasts( "MSG_USER_OFFLINE" , &PB_Offline );
}

void CGameBase::UserOnline( ROLE_ID RoleID )
{
    PB_UserOnline PB_Online;
    PB_Online.set_role_id( RoleID );
    BroadCasts( "MSG_USER_ONLINE" , &PB_Online );
}

bool CGameBase::IsGameFull( void )
{
    CJsonGameCell* pGameCell = JsonGameConfig.GetJsonCell<CJsonGameCell>( m_CreateGameData.room_name() );
    if ( nullptr == pGameCell ) { return false; }
    uint32 RoleCount = this->GetRoleCount();
    if ( RoleCount >= pGameCell->GetGameMax() ) {
        return true;
    }
    return false;
}




GSE_NAMESPACE_END_DECL