#include "message_game.h"
#include <schedule_service/game/game_manager.h>

SSE_NAMESPACE_BEGIN_DECL

void CallBack_RegisterGameInfo( NLNET::CMessage& Message , const std::string& ServiceName, NLNET::TServiceId ServiceId )
{
    RecordGameList GameList;
    Message.serialCont( GameList );
    GameManager.UpdateGameList( ServiceId , GameList );
}

SSE_NAMESPACE_END_DECL