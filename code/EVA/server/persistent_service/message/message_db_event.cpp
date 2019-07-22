#include "message_db_event.h"
#include <persistent_service/db/db_manager.h>

PSE_NAMESPACE_BEGIN_DECL

void CallBack_Player( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    CRecordPlayerInfo RecordPlayer;
    Message.serial( RecordPlayer );
    DBManager.RefreshDBPlayer( RecordPlayer );
}

void CallBack_Item( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    CRecordItem RecordItem;
    Message.serial( RecordItem );
    DBManager.RefreshDBItem( RecordItem );
}

void CallBack_Statistics( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    CRecordStatistics RecordStatistics;
    Message.serial( RecordStatistics );
    DBManager.RefreshDBStatistics( RecordStatistics );
}

void CallBack_Mission( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    CRecordMission RecordMission;
    Message.serial( RecordMission );
    DBManager.RefreshDBMission( RecordMission );
}

PSE_NAMESPACE_END_DECL