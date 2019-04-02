#include "message_login.h"
#include <game_service/player/player.h>
#include <game_service/event/event_define.h>

GSE_NAMESPACE_BEGIN_DECL

void CallBack_UserLoad( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    CRecordPlayer RecordPlayer;
    Message.serial( RecordPlayer );
    EventDefine.EventUserLoad( RecordPlayer );
}

void CallBack_UserLogin( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    PB_UserLogin UserLogin;
    Message.serial( &UserLogin );
    EventDefine.EventUserLogin( UserLogin );
}

void CallBack_UserOffline( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    ROLE_ID RoleID;
    Message.serial( RoleID );
    EventDefine.EventUserOffline( RoleID );
}

void CallBack_ChangeScenes( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    CPlayer pPlayer;
    Message.serial( pPlayer );
    EventDefine.EventChangeScenes( pPlayer );
}

GSE_NAMESPACE_END_DECL