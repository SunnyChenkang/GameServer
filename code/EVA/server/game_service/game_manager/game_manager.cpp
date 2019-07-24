#include "game_manager.h"
#include <game_service/player/player.h>
#include <game_service/player/player_manager.h>

GSE_NAMESPACE_BEGIN_DECL

CGameManager::CGameManager( void )
{
    m_GameList.clear();
}

CGameManager::~CGameManager( void )
{

}

bool CGameManager::CreateGame( ROLE_ID RoleID , PB_CreateRoom& GameData )
{
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( RoleID );
    if ( nullptr == PlayerPtr ) {
        return false;
    }

    /// 检查游戏静态数据;
    CJsonGameCell* pGameCell = JsonGameConfig.GetJsonCell< CJsonGameCell >( GameData.room_name() );
    if ( nullptr == pGameCell ) {
        return false;
    }

    /// 检查跳转服务器;
    if( CreateGameChangeScenes( RoleID , GameData ) ) {
        return true;
    }

    /// 创建游戏实体;
    CGameBasePtr GameBasePtr( NLMISC_GET_FACTORY( CGameBase , NLMISC::CSString ).createObject( pGameCell->GetGameName() , GameData ) );
    if ( nullptr == GameBasePtr ) {
        return false;
    }

    /// 保存游戏实体;
    auto Res = m_GameList.insert( std::make_pair( GameData.room_id() , GameBasePtr ));
    if ( !Res.second ) {
        return false;
    }

    /// 加入游戏;
    GameBasePtr->SetOwnerID( RoleID );
    GameBasePtr->JoinGame( RoleID );
    return true;
}

bool CGameManager::CreateGameChangeScenes( ROLE_ID RoleID , PB_CreateRoom& GameData )
{
    /// 检查是否需要切服务器;
    uint16 LocalServiceID = NLNET::IService::getInstance()->getServiceId().get();
    if ( LocalServiceID == GameData.service_id() ) {
        return false;
    }

    /// 目标服务器是否存在连接;
    if ( !SS_NETWORK->isConnectionConnected( TServiceId( GameData.service_id() ))) {
        return true;
    }

    bool Res = false;
    Res = PlayerManager.ChangeScenes( RoleID , TServiceId( GameData.service_id() ));
    if ( !Res ) return true;

    /// 同步游戏数据;
    CMessage SendMessage( "MSG_CREATE_ROOM" );
    SendMessage.serial( RoleID );
    SendMessage.serial( &GameData );
    SS_NETWORK->send( TServiceId( GameData.service_id()) , SendMessage );
    return true;
}

bool CGameManager::JoinGame( ROLE_ID RoleID , ROOM_ID RoomID )
{
    CGameBasePtr GameBasePtr = GetGameBasePtr( RoomID );
    if ( nullptr == GameBasePtr ) { return false; }

    /// 加入游戏;
    return GameBasePtr->JoinGame( RoleID );
}

bool CGameManager::LeaveGame( ROLE_ID RoleID )
{
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( RoleID );
    if ( nullptr == PlayerPtr )   { return false; }
    CGameBasePtr GameBasePtr = GetGameBasePtr( PlayerPtr->GetRoomID() );
    if ( nullptr == GameBasePtr ) { return false; }

    /// 离开游戏;
    return GameBasePtr->LeaveGame( RoleID );
}

bool CGameManager::DeleteGame( ROOM_ID RoomID )
{
    auto It = m_GameList.find( RoomID );
    if ( It == m_GameList.end() ) { return false; }

    /// 删除游戏实体;
    m_GameList.erase( It );
    return true;
}

CGameBasePtr CGameManager::GetGameBasePtr( ROOM_ID RoomID )
{
    auto It = m_GameList.find( RoomID );
    if ( It == m_GameList.end() ) { return nullptr; }
    return It->second;
}

GSE_NAMESPACE_END_DECL