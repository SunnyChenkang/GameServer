#ifndef SERVER_SHARED_DBRECORDBASE_H_
#define SERVER_SHARED_DBRECORDBASE_H_

#include "db_record_def.h"

SS_NAMESPACE_BEGIN_DECL

class CRecordBase
{
public:
    CRecordBase( void );
    virtual ~CRecordBase( void );

    //   serial;
    virtual void serial(NLMISC::IStream &s)
    {
        s.serial( m_DBState );
    }

    //   重置标记;
    void ResetState( void )     { m_DBState.resetEnumValue( DB_EVENT_NULL ); }

    //   插入标记;
    void SetInsert ( void )     { m_DBState.resetEnumValue( DB_EVENT_INSERT ); }
    //   更新标记;
    void SetUpdate ( void )     { m_DBState.resetEnumValue( DB_EVENT_DELETE ); }
    //   删除标记;
    void SetDelete ( void )     { m_DBState.resetEnumValue( DB_EVENT_DELETE ); }

    //   是否存在插入;
    bool IsInsertState( void )  { return ( m_DBState.checkEnumValue( DB_EVENT_INSERT ) ); }
    //   是否存在更新;
    bool IsUpdateState( void )  { return ( m_DBState.checkEnumValue( DB_EVENT_UPDATE ) );  }
    //   是否存在删除;
    bool IsDeleteState( void )  { return ( m_DBState.checkEnumValue( DB_EVENT_DELETE ) );  }

public:
    NLMISC::CEnumBitset< DBEventEnum , uint32 >  m_DBState;
};

SS_NAMESPACE_END_DECL

#endif // SERVER_SHARED_DBRECORDBASE_H_;