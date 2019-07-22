#include "player_manager.h"
#include "player.h"

SSE_NAMESPACE_BEGIN_DECL

CPlayerManager::CPlayerManager( void )
{
    m_PlayerTable.clear();
}

CPlayerManager::~CPlayerManager( void )
{
    m_PlayerTable.clear();
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
    auto it = m_PlayerTable.find( RoleID );
    if ( it == m_PlayerTable.end() ) return nullptr;
    return it->second;
}

SSE_NAMESPACE_END_DECL

