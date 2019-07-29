#ifndef SERVER_SHARED_RECORDSTATISTICS_H_
#define SERVER_SHARED_RECORDSTATISTICS_H_

#include "record_base.h"

SS_NAMESPACE_BEGIN_DECL

class CRecordStatistics : public CRecordBase
{
public:
    CRecordStatistics( void );
    virtual ~CRecordStatistics( void );

    SS_PROPERTY( ROLE_ID        , RoleID       , private );
    SS_PROPERTY( STATISTICS_ID  , StatisticsID , private );
    SS_PROPERTY( sint64         , Count        , private );

    // serial stream;
    void serial( NLMISC::IStream& s )
    {
        s.serial( m_DBState );
        s.serial( m_RoleID );
        s.serial( m_StatisticsID );
        s.serial( m_Count );
    }

    // save to database;
    void SaveDB( void )
    {
        CRecordStatistics& RecordStatistics( *this );
        NLNET::CMessage SendMessage("MSG_DB_STATISTICS");
        SendMessage.serial( RecordStatistics );
        SS_NETWORK->send( "PSE" , SendMessage );
    }
};

SS_NAMESPACE_END_DECL

#endif // SERVER_SHARED_RECORDSTATISTICS_H_