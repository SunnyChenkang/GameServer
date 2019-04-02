#include "db_record_base.h"

SS_NAMESPACE_BEGIN_DECL

CRecordBase::CRecordBase( void )
{
    m_DBState.resetEnumValue( DB_EVENT_NULL );
}

CRecordBase::~CRecordBase( void )
{
    
}

SS_NAMESPACE_END_DECL