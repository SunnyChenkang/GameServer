#include "game_manager.h"

SSE_NAMESPACE_BEGIN_DECL

void CGameManager::UpdateGameList( TServiceId ServiceID , RecordGameList& GameList )
{
    m_GameList[ ServiceID ] = GameList;
}

void CGameManager::DeleteGameList( TServiceId& ServiceID )
{
    auto It = m_GameList.find( ServiceID );
    if ( It == m_GameList.end() ) {
        return;
    }
    m_GameList.erase( It );
}

TServiceId CGameManager::GetGoodServiceID( CSString& GameName )
{
    TServiceId ServiceID = TServiceId::InvalidId;
    uint32 GameCount     = std::numeric_limits<uint32>::max();
    for ( auto GameList = m_GameList.begin(); GameList != m_GameList.end(); ++GameList )
    {
        for ( auto Game : GameList->second )
        {
            if ( !Game.GetGameName().compare(GameName) ) { continue; }
            if ( GameCount < Game.GetGameCurrCount() ){ continue; }
            GameCount = Game.GetGameCurrCount();
            ServiceID = GameList->first;
        }
    }
    return ServiceID;
}

SSE_NAMESPACE_END_DECL