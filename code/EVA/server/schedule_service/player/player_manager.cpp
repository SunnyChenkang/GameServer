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

CPlayerPtr CPlayerManager::GetPlayer( ROLE_ID RoleID , bool IsAdd )
{
    auto It = m_PlayerTable.find( RoleID );
    if ( It != m_PlayerTable.end() ) {
        return It->second;
    }

    if ( !IsAdd ) { return nullptr; }
    CPlayerPtr PlayerPtr = std::make_shared< CPlayer >();
    if ( nullptr == PlayerPtr ) {
        return nullptr;
    }
    auto Res = m_PlayerTable.insert( std::make_pair( RoleID , PlayerPtr ));
    return Res.first->second;
}

SSE_NAMESPACE_END_DECL

