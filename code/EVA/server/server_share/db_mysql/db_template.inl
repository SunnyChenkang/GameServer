#include "db_result.h"

template< typename T >
T SS::CDBResult::GetFieldParam( size_t sz )
{
    uint32 CurrIdx = GetRowOffset() + sz;
    DBResultInfo& ResultInfo = m_Result[ CurrIdx ];
    if ( ResultInfo.IsNull ) return T(0);

    switch ( ResultInfo.Field )
    {
    case MYSQL_TYPE_TINY:       return ( T )( *(uint8*) ResultInfo.Buffer.c_str() );
    case MYSQL_TYPE_SHORT:      return ( T )( *(uint16*)ResultInfo.Buffer.c_str() );
    case MYSQL_TYPE_INT24:      return ( T )( *(uint32*)ResultInfo.Buffer.c_str() );
    case MYSQL_TYPE_LONG:       return ( T )( *(uint32*)ResultInfo.Buffer.c_str() );
    case MYSQL_TYPE_LONGLONG:   return ( T )( *(uint64*)ResultInfo.Buffer.c_str() );
    case MYSQL_TYPE_FLOAT:      return ( T )( *(float*) ResultInfo.Buffer.c_str() );
    case MYSQL_TYPE_DOUBLE:     return ( T )( *(double*)ResultInfo.Buffer.c_str() );
    default:
        break;
    }
    return T(0);
}