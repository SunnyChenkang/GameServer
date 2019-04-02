#include "db_sub_func.h"
#include <logger_service/db/db_connect.h>

LSE_NAMESPACE_BEGIN_DECL

bool SubInsertDots( void* data )
{
    CRecordStmtData* pStmt = (CRecordStmtData*)data;
    if ( NULL == pStmt ) return false;

    CDBExecute* pWorker = DBThreads.GetDBExecute();
    if ( NULL == pWorker ) return false;

    pWorker->Execute( &pStmt->m_Stmt );
    return true;
}

LSE_NAMESPACE_END_DECL