#include "message_db_event.h"
#include <logger_service/db/db_connect.h>
#include <logger_service/db/db_sub_func.h>

LSE_NAMESPACE_BEGIN_DECL

void CallBack_DotMssage( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    CRecordStmtData RecordStmtData;
    Message.serial( RecordStmtData );
    RecordStmtData.SetThreadsIdx( DBConnect.GetThreadsIdx() );
    CDBMysql& DBMysql = DBConnect.GetDBMysql( RecordStmtData.GetThreadsIdx() );
    DBMysql.PostToMain( new CRecordStmtData( RecordStmtData ) , ( PROC_MSG )SubInsertDots );
}

LSE_NAMESPACE_END_DECL
