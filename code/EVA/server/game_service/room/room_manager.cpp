#include "room_manager.h"
#include "room_base.h"
#include <game_service/player/player_manager.h>

GSE_NAMESPACE_BEGIN_DECL

CRoomManager::CRoomManager( void )
{
    m_RoomTable.clear();
}

CRoomManager::~CRoomManager( void )
{
    
}

bool CRoomManager::CreateRoom( ROLE_ID RoleID , PB_CreateRoom& RoomData )
{
    CPlayer* pPlayer = PlayerManager.GetPlayer( RoleID );
    if ( NULL == pPlayer ) return false;

    // 检查房间配置信息;
    CJsonRoomCell* pRoomCell = JsonRoomConfig.GetJsonCell< CJsonRoomCell >( RoomData.room_name() );
    if ( NULL == pRoomCell )
    {
        nlinfo( "not find room info %s " , pRoomCell->GetRoomName().c_str() );
        return false;
    }
    // 检查是否需要切换服务器;
    NLNET::TServiceId LocalServieId = NLNET::IService::getInstance()->getServiceId();
    if ( LocalServieId.get() != RoomData.service_id() )
    {
        return this->CreateRoomToScenes( RoleID , RoomData );
    }
    // 创建房间实例;
    CRoomBase* pRoomBase = NLMISC_GET_FACTORY( CRoomBase , NLMISC::CSString ).createObject( pRoomCell->GetRoomName() , RoomData );
    if ( NULL == pRoomBase )
    {
        nlinfo( " factory not alloc room entity %s " , pRoomCell->GetRoomName().c_str() );
        return false;
    }
    // 保存房间信息;
    std::pair< ROOM_TABLE::iterator , bool > res = m_RoomTable.insert( std::make_pair( pRoomBase->GetRoomID() , pRoomBase ) );
    if ( !res.second )
    {
        nlinfo( " insert room table failes room_id = %llu" , pRoomBase->GetRoomID() );
        SS_SAFE_DELETE( pRoomBase );
        return false;
    }
    // 加入房间;
    pRoomBase->SetOwnerID  ( RoleID );
    pRoomBase->JoinGameRoom( RoleID );
    return true;
}

bool CRoomManager::CreateRoomToScenes( ROLE_ID RoleID , PB_CreateRoom& RoomData )
{
    bool res = false;
    res = PlayerManager.ChangeScenes( RoleID , NLNET::TServiceId( RoomData.service_id() ) );
    if ( res == false ) return res;

    NLNET::CMessage SendMessage( "MSG_CREATE_ROOM" );
    SendMessage.serial( RoleID );
    SendMessage.serial( &RoomData );
    return SS_NETWORK->send( NLNET::TServiceId( RoomData.service_id() ) , SendMessage );
}

bool CRoomManager::JoinRoom( ROLE_ID RoleID , ROOM_ID RoomID )
{
    CPlayer* pPlayer = PlayerManager.GetPlayer( RoleID );
    if ( NULL == pPlayer )   return false;
    CRoomBase* pRoomBase = GetRoomInfo( RoomID );
    if ( NULL == pRoomBase ) return false;
    return pRoomBase->JoinGameRoom( RoomID );
}

bool CRoomManager::DeleteRoom( ROOM_ID RoomID )
{
    ROOM_TABLE::iterator it = m_RoomTable.find( RoomID );
    if ( it == m_RoomTable.end() ) return false;
    SS_SAFE_DELETE( it->second );
    m_RoomTable.erase( it );
    return true;
}

CRoomBase* CRoomManager::GetRoomInfo( ROOM_ID RoomID )
{
    ROOM_TABLE::iterator it = m_RoomTable.find( RoomID );
    if ( it == m_RoomTable.end() ) return NULL;
    return it->second;
}

uint32 CRoomManager::GetRoomCount( NLMISC::CSString RoomName )
{
    uint32 RoomCount = 0;
    ROOM_TABLE::iterator it = m_RoomTable.begin();
    for ( ; it != m_RoomTable.end() ; ++it )
    {
        if ( it->second->GetRoomName() != RoomName ) continue;
        RoomCount+=1;
    }
    return RoomCount;
}
GSE_NAMESPACE_END_DECL