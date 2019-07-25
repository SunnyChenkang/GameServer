#ifndef SERVER_SHARED_DBDOTDATA_H_
#define SERVER_SHARED_DBDOTDATA_H_

#include "db_record_base.h"
#include <server_share/db/mysql/db_statement.h>

SS_NAMESPACE_BEGIN_DECL

class CRecordStmtData : public CRecordBase
{
    SS_PROPERTY_QUOTE( CDBStatement , DBStmt      , private );
    SS_PROPERTY_QUOTE( sint8        , ThreadsIdx  , private );

public:

    /// serial;
    void serial( NLMISC::IStream &s )
    {
        s.serial( m_DBStmt );
        s.serial( m_ThreadsIdx );
    }

    /// ave;
    void SaveDB( void )
    {
        CRecordStmtData& RecordStmtData( *this );
        NLNET::CMessage SendMessage("MSG_DOT");
        SendMessage.serial( RecordStmtData );
        SS_NETWORK->send( "LSE" , SendMessage );
    }
};

SS_NAMESPACE_END_DECL

#endif//SERVER_SHARED_DBDOTDATA_H_