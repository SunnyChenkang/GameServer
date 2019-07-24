#include "game_base.h"
#include <game_service/event/event_define.h>
#include <game_service/player/player.h>
#include <game_service/player/player_manager.h>

GSE_NAMESPACE_BEGIN_DECL

CGameBase::CGameBase( TCtorParam& GameData , uint32 )
{
    CJsonRoomCell* pGameCell = JsonRoomConfig.GetJsonCell< CJsonRoomCell >( m_CreateGameData.room_name() );
    if ( nullptr == pGameCell ) { return; }
    m_RoleList.resize( pGameCell->GetRoomMax() );
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

    /// 触发加入游戏事件;
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

    /// 触发离开游戏事件;
    EventDefine.LeaveRoom( RoleID , GetRoomID() );
}

void CGameBase::StartGame( void )
{
    /// 触发游戏开始;
    for ( auto Element : m_RoleList )
    {
        EventDefine.GameStart( Element , GetRoomID() );
    }
}

void CGameBase::OwerGame( void )
{
    /// 触发游戏结束;
    for ( auto Element : m_RoleList )
    {
        EventDefine.GameOwer( Element , GetRoomID() );
    }
}

bool CGameBase::IsGameFull( void )
{
    CJsonRoomCell* pGameCell = JsonRoomConfig.GetJsonCell< CJsonRoomCell >( m_CreateGameData.room_name() );
    if ( nullptr == pGameCell ) { return false; }
    return ( GetRoleCount() >= pGameCell->GetRoomMax() );
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
        if ( Element == RemoveID ) { continue; }
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

GSE_NAMESPACE_END_DECL