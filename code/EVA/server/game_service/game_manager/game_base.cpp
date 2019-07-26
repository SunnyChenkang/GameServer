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

bool CGameBase::GameJoin( ROLE_ID RoleID )
{
    /// 检查进入游戏;
    if ( this->GameIsFull() )           { return false; }
    if ( this->GameIsRole( RoleID ) )   { return false; }

    /// 添加玩家列表;
    for ( auto It = m_RoleList.begin(); It != m_RoleList.end(); ++It )
    {
        if ( *It != 0 ) { continue; }
        *It = RoleID;
        break;
    }
    /// 加入房间事件;
    EventDefine.JoinGame( RoleID , GetRoomID() );
    return true;
}

bool CGameBase::GameLeave( ROLE_ID RoleID )
{
    /// 检查离开游戏;
    if ( !this->GameIsRole( RoleID ) ) { return false; }

    /// 删除玩家列表;
    for ( auto It = m_RoleList.begin(); It != m_RoleList.end(); ++It )
    {
        if ( *It != RoleID ) { continue; }
        *It = 0;
        break;
    }
    /// 离开房间事件;
    EventDefine.LeaveRoom( RoleID , GetRoomID() );
    return true;
}

void CGameBase::GameStart( void )
{
    /// 游戏开始事件;
    for ( auto It = m_RoleList.begin(); It != m_RoleList.end(); ++It )
    {
        EventDefine.GameStart( *It , GetRoomID() );
    }
}

void CGameBase::GameOwer( void )
{
    /// 游戏结束事件;
    for ( auto It = m_RoleList.begin(); It != m_RoleList.end(); ++It )
    {
        EventDefine.GameOwer( *It , GetRoomID() );
    }
}

bool CGameBase::GameIsRole( ROLE_ID RoleID )
{
    for ( auto It = m_RoleList.begin(); It != m_RoleList.end(); ++It )
    {
        if ( *It == RoleID ) { return true; }
    }
    return false;
}

bool CGameBase::GameIsFull( void )
{
    CJsonGameCell* pGameCell = JsonGameConfig.GetJsonCell<CJsonGameCell>( m_CreateGameData.room_name() );
    if ( nullptr == pGameCell ) { return false; }
    if ( this->GetRoleCount() >= pGameCell->GetGameMax() ) {
        return true;
    }
    return false;
}

void CGameBase::GameBroadCasts( CSString Name , google::protobuf::Message* pMessage , ROLE_ID RemoveID /*= 0 */ )
{
    for ( auto It = m_RoleList.begin(); It != m_RoleList.end(); ++It )
    {
        if ( *It == RemoveID ) { continue; }
        CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( *It );
        if ( nullptr == PlayerPtr ) { continue; }
        SendToClient( *It , PlayerPtr->GetFrontendServiceID() , Name , pMessage );
    }
}

uint32 CGameBase::GetRoleCount( void )
{
    uint32 Count = 0;
    for ( auto It = m_RoleList.begin(); It != m_RoleList.end(); ++It )
    {
        if ( *It < 0 ) { continue; }
        Count++;
    }
    return Count;
}

void CGameBase::GameOffline( ROLE_ID RoleID )
{
    PB_UserOffline PB_Offline;
    PB_Offline.set_role_id( RoleID );
    GameBroadCasts( "MSG_USER_OFFLINE" , &PB_Offline );
}

void CGameBase::GameOnline( ROLE_ID RoleID )
{
    PB_UserOnline PB_Online;
    PB_Online.set_role_id( RoleID );
    GameBroadCasts( "MSG_USER_ONLINE" , &PB_Online );
}

GSE_NAMESPACE_END_DECL