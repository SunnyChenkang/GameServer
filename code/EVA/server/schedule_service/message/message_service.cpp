#include "message_service.h"
#include <schedule_service/game/game_manager.h>

SSE_NAMESPACE_BEGIN_DECL

void CallBack_GSEConnection( const std::string& ServiceName , NLNET::TServiceId ServiceId , void* )
{
    GameManager.LoadGameInfo( ServiceId );
}

void CallBack_FESConnection( const std::string& ServiceName , NLNET::TServiceId ServiceId , void* )
{

}

void CallBack_PSEConnection( const std::string& ServiceName , NLNET::TServiceId ServiceId , void* )
{

}

void CallBack_GSEDisconnection( const std::string& ServiceName , NLNET::TServiceId ServiceId , void* )
{
    GameManager.RemoveGameInfo( ServiceId );
}

void CallBack_FESDisconnection( const std::string& ServiceName , NLNET::TServiceId ServiceId , void* )
{
    
}

void CallBack_PSEDisconnection( const std::string& ServiceName , NLNET::TServiceId ServiceId , void* )
{
    
}

SSE_NAMESPACE_END_DECL