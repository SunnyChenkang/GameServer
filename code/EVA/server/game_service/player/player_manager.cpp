#include "player_manager.h"
#include "player.h"

GSE_NAMESPACE_BEGIN_DECL

CPlayer* CPlayerManager::AllocPlayer( CRecordPlayer& RecordPlayer )
{
    ROLE_ID RoleID = RecordPlayer.RecordPlayerInfo.GetRoleID();
    CPlayer* pPlayer = GetPlayer( RoleID );
    if ( NULL != pPlayer ) return pPlayer;
    pPlayer = new ( std::nothrow )CPlayer( RecordPlayer );
    m_RoleTable.insert( std::make_pair( RoleID , pPlayer ) );
    return pPlayer;
}

CPlayer* CPlayerManager::AllocPlayer( ROLE_ID RoleID )
{
    CPlayer* pPlayer = GetPlayer( RoleID );
    if ( NULL != pPlayer ) return pPlayer;
    pPlayer = new ( std::nothrow )CPlayer();
    m_RoleTable.insert( std::make_pair( RoleID , pPlayer ) );
    return pPlayer;
}

void CPlayerManager::DeletePlayer( ROLE_ID RoleID )
{
    PLAYER_TABLE::iterator it = m_RoleTable.find( RoleID );
    if ( it == m_RoleTable.end() ) return;
    SS_SAFE_DELETE( it->second );
    m_RoleTable.erase( it );
}

CPlayer* CPlayerManager::GetPlayer( ROLE_ID RoleID )
{
    PLAYER_TABLE::iterator it = m_RoleTable.find( RoleID );
    if ( it == m_RoleTable.end() ) return NULL;

    return it->second;
}

uint32 CPlayerManager::GetPlayerCount( void )
{
    return m_RoleTable.size();
}

bool CPlayerManager::ChangeScenes( ROLE_ID RoleID , NLNET::TServiceId ServiceId )
{
    CPlayer* pPlayer = GetPlayer( RoleID );
    if ( NULL == pPlayer ) return false;
    NLNET::CMessage SendMessage("MSG_CHANGE_SCENES");
    SendMessage.serial( *pPlayer );
    if ( !SS_NETWORK->send( ServiceId , SendMessage ) ) return false;
    this->DeletePlayer( RoleID );
    return true;
}

GSE_NAMESPACE_END_DECL