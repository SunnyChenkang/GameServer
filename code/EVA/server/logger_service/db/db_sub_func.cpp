#include "db_sub_func.h"
#include <logger_service/db/db_connect.h>

LSE_NAMESPACE_BEGIN_DECL

bool SubInsertDots( void* data )
{
    CRecordStmtData* pStmt = (CRecordStmtData*)data;
    if ( NULL == pStmt ) return false;

    CDBMysql& DBMysql = DBConnect.GetDBMysql( pStmt->GetThreadsIdx() );
    CDBExecute* pWorker = DBMysql.GetDBExecute();
    if ( NULL == pWorker ) return false;

    pWorker->Execute( &pStmt->GetDBStmt() );
    return true;
}

LSE_NAMESPACE_END_DECL