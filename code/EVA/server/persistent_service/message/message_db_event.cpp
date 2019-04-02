#include "message_db_event.h"
#include <persistent_service/db/db_manager.h>

PSE_NAMESPACE_BEGIN_DECL

void CallBack_Event_Player( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    CRecordPlayerInfo RecordPlayer;
    Message.serial( RecordPlayer );
    DBManager.UpdateDBPlayer( RecordPlayer );
}

void CallBack_Event_Item( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    CRecordItem RecordItem;
    Message.serial( RecordItem );
    DBManager.UpdateDBItem( RecordItem );
}

void CallBack_Event_Statistics( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    CRecordStatistics RecordStatistics;
    Message.serial( RecordStatistics );
    DBManager.UpdateDBStatistics( RecordStatistics );
}

void CallBack_Event_Mission( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    CRecordMission RecordMission;
    Message.serial( RecordMission );
    DBManager.UpdateDBMission( RecordMission );
}

PSE_NAMESPACE_END_DECL