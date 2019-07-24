#include "message_login.h"
#include <game_service/player/player.h>
#include <game_service/event/event_define.h>

GSE_NAMESPACE_BEGIN_DECL

void CallBack_PlayerLoadFinish( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    CRecordPlayer RecordPlayer;
    Message.serial( RecordPlayer );
    EventDefine.PlayerLoadFinish( RecordPlayer );
}

void CallBack_PlayerLoginFinish( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    PB_UserLogin UserLogin;
    Message.serial( &UserLogin );
    EventDefine.PlayerLoginFinish( UserLogin );
}

void CallBack_PlayerOffline( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    ROLE_ID RoleID;
    Message.serial( RoleID );
    EventDefine.PlayerOffline( RoleID );
}

void CallBack_ChangeScenes( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    CPlayerPtr PlayerPtr;
    Message.serial( *PlayerPtr );
    EventDefine.ChangeScenes( PlayerPtr );
}

GSE_NAMESPACE_END_DECL