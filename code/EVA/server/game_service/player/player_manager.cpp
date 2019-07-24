#include "player_manager.h"

GSE_NAMESPACE_BEGIN_DECL

CPlayerManager::CPlayerManager( void )
{
    m_PlayerTable.clear();
}

CPlayerManager::~CPlayerManager( void )
{
    m_PlayerTable.clear();
}

CPlayerPtr CPlayerManager::AllocPlayer( CRecordPlayer& RecordPlayer )
{
    CPlayerPtr PlayerPtr = AllocPlayer( RecordPlayer.GetRecordBasePlayer().GetRoleID() );
    if ( nullptr == PlayerPtr ) {
        return nullptr;
    }
    PlayerPtr->SetRecordPlayer( RecordPlayer );
    return PlayerPtr;
}

CPlayerPtr CPlayerManager::AllocPlayer( ROLE_ID RoleID )
{
    CPlayerPtr PlayerPtr = std::make_shared< CPlayer >();
    if ( nullptr == PlayerPtr ) {
        return nullptr;
    }
    auto res = m_PlayerTable.insert( std::make_pair( RoleID , PlayerPtr ) );
    return res.first->second;
}

CPlayerPtr CPlayerManager::GetPlayer( ROLE_ID RoleID )
{
    auto It = m_PlayerTable.find( RoleID );
    if ( It == m_PlayerTable.end() ) {
        return nullptr;
    }
    return It->second;
}

void CPlayerManager::DeletePlayer( ROLE_ID RoleID )
{
    auto It = m_PlayerTable.find( RoleID );
    if ( It == m_PlayerTable.end() ) {
        return;
    }
    m_PlayerTable.erase( It );
}

bool CPlayerManager::ChangeScenes( ROLE_ID RoleID , TServiceId& ServiceID )
{
    CPlayerPtr PlayerPtr = this->GetPlayer( RoleID );
    if ( nullptr == PlayerPtr ) {
        return false;
    }

    /// 检查目标服务是否运行;
    if ( !SS_NETWORK->isConnectionConnected( ServiceID ) ) {
        return false;
    }

    /// 数据投递到目标服务器;
    NLNET::CMessage SendMessage( "MSG_CHANGE_SCENES" );
    SendMessage.serial( *PlayerPtr );
    SS_NETWORK->send  ( ServiceID , SendMessage );

    /// 删除玩家数据;
    this->DeletePlayer( RoleID );
    return true;
}

GSE_NAMESPACE_END_DECL