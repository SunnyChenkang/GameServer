#include "player_manager.h"
#include "player.h"

SSE_NAMESPACE_BEGIN_DECL

CPlayer* CPlayerManager::AllocPlayer( ROLE_ID RoleID )
{
    PLAYER_TABLE::iterator it = m_PlayerTable.find( RoleID );
    if ( it != m_PlayerTable.end() ) return it->second;
    CPlayer* pPlayer = new ( std::nothrow ) CPlayer();
    if ( NULL == pPlayer )           return NULL;
    m_PlayerTable.insert( std::make_pair( RoleID , pPlayer ) );
    return pPlayer;
}

CPlayer* CPlayerManager::GetPlayer( ROLE_ID RoleID )
{
    PLAYER_TABLE::iterator it = m_PlayerTable.find( RoleID );
    if ( it != m_PlayerTable.end() ) return it->second;
    return NULL;
}

SSE_NAMESPACE_END_DECL

