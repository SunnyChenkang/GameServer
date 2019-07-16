#include "db_result.h"

SS::CDBResult::CDBResult( void ) : m_RowCount( 0 )
                                 , m_RowCurr( -1 )
                                 , m_FieldCount( 0 )
{
    
}

SS::CDBResult::~CDBResult( void )
{
    
}

my_bool SS::CDBResult::GetBool( size_t sz )
{
    uint32 Idx = GetRowOffset() + sz;
    DBResultInfo& ResultInfo = m_Result[ Idx ];
    if ( ResultInfo.IsNull ) return false;
    switch ( ResultInfo.Field )
    {
    case MYSQL_TYPE_TINY:       return ( 0 != ( *(uint8*) ResultInfo.Buffer.c_str() ) );
    case MYSQL_TYPE_SHORT:      return ( 0 != ( *(uint16*)ResultInfo.Buffer.c_str() ) );
    case MYSQL_TYPE_INT24:      return ( 0 != ( *(uint32*)ResultInfo.Buffer.c_str() ) );
    case MYSQL_TYPE_LONG:       return ( 0 != ( *(uint32*)ResultInfo.Buffer.c_str() ) );
    case MYSQL_TYPE_LONGLONG:   return ( 0 != ( *(uint64*)ResultInfo.Buffer.c_str() ) );
    case MYSQL_TYPE_FLOAT:      return ( 0 != ( *(uint32*)ResultInfo.Buffer.c_str() ) );
    case MYSQL_TYPE_DOUBLE:     return ( 0 != ( *(uint64*)ResultInfo.Buffer.c_str() ) );
    default:
        break;
    }
    return false;
}

std::pair< size_t , char const* > SS::CDBResult::GetString(size_t sz )
{
    std::pair< size_t , char const* > PairResult( 0 , "" );
    uint32 CurrIdx = GetRowOffset() + sz;
    DBResultInfo& ResultInfo = m_Result[ CurrIdx ];
    if ( ResultInfo.IsNull ) return PairResult;
    if ( ResultInfo.BufferSize <= 0 ) return PairResult;
    if ( ResultInfo.Buffer.c_str() == NULL ) return PairResult;

    PairResult.first  = ResultInfo.BufferSize;
    PairResult.second = ResultInfo.Buffer.c_str();
    *(((char*)PairResult.second) + PairResult.first ) = '\0';

    return PairResult;
}

std::pair< size_t , void const* > SS::CDBResult::GetBlob(size_t sz )
{
    std::pair< size_t , char const* > PairResult( 0 , "" );
    uint32 CurrIdx = GetRowOffset() + sz;
    DBResultInfo& ResultInfo = m_Result[ CurrIdx ];
    if ( ResultInfo.IsNull ) return PairResult;
    PairResult.first    = ResultInfo.BufferSize;
    PairResult.second   = ResultInfo.Buffer.c_str();

    return PairResult;
}

bool SS::CDBResult::NextRow( void )
{
    bool ret = false;
    if ( m_RowCurr+1 < m_RowCount )
    {
        ++m_RowCurr;
        ret = true;
    }
    return ret;
}

bool SS::CDBResult::Initialize( MYSQL_STMT* pStmt , MYSQL_RES* pResult )
{
    if ( NULL == pStmt || NULL == pResult ) return false;
    size_t Row = mysql_stmt_num_rows( pStmt );
    if ( Row <= 0 ) return false;

    MYSQL_BIND* pBind = NULL;
    size_t Count = mysql_stmt_field_count( pStmt );
    if ( Count > 0 )
    {
        m_FieldCount = Count;
        pBind = ( MYSQL_BIND* )malloc( Count* sizeof( MYSQL_BIND ) );
        memset( pBind , 0 , Count*sizeof( MYSQL_BIND ) );
    }
    if ( NULL == pBind ) return false;

    std::vector< DBResultInfo > ResultArray;
    ResultArray.resize( Count );
    size_t idx = 0;
    size_t buffer_max_len = 0;
    MYSQL_FIELD* pField = mysql_fetch_field( pResult );

    while ( NULL != pField )
    {
        size_t sz = 0;
        switch ( pField->type )
        {
        case MYSQL_TYPE_TINY:       sz = 1; break;
        case MYSQL_TYPE_SHORT:      sz = 2; break;
        case MYSQL_TYPE_INT24:      sz = 4; break;
        case MYSQL_TYPE_LONG:       sz = 4; break;
        case MYSQL_TYPE_LONGLONG:   sz = 8; break;
        case MYSQL_TYPE_FLOAT:      sz = 4; break;
        case MYSQL_TYPE_DOUBLE:     sz = 8; break;
        case MYSQL_TYPE_STRING:
        case MYSQL_TYPE_VAR_STRING:
        case MYSQL_TYPE_BLOB:
        case MYSQL_TYPE_TINY_BLOB:
        case MYSQL_TYPE_MEDIUM_BLOB:
        case MYSQL_TYPE_LONG_BLOB:  sz = pField->max_length; break;
        default: nlassert( false ); break;
        }

        DBResultInfo& res = ResultArray[ idx ];
        res.Buffer.assign( sz , '\0' );
        res.BufferSize = sz;
        res.Field      = pField->type;
        res.IsNull     = 0;

        pBind[ idx ].buffer_type    = pField->type;
        pBind[ idx ].buffer         = (void*)res.Buffer.c_str();
        pBind[ idx ].buffer_length  =  res.BufferSize;
        pBind[ idx ].length         = &res.BufferSize;
        pBind[ idx ].is_unsigned    = pField->flags & UNSIGNED_FLAG;
        pBind[ idx ].is_null        = &res.IsNull;
        buffer_max_len             += res.BufferSize;
        idx = idx+1;
        pField = mysql_fetch_field( pResult );
    }

    if ( buffer_max_len >= 0 && 0 == mysql_stmt_bind_result( pStmt , pBind ) )
    {
        m_Result.resize( Row * Count );
        m_RowCount = Row;
        uint32 RetIdx = 0;
        while ( Row > 0 )
        {
            int Val = mysql_stmt_fetch( pStmt );
            -- Row;
            if ( 0 == Val || MYSQL_DATA_TRUNCATED == Val )
            {
                uint32 RowOffset = RetIdx * Count;
                for ( size_t idx = 0; idx < Count; ++idx )
                {
                    DBResultInfo& ScrInfo = ResultArray[idx];
                    DBResultInfo& DescInfo= m_Result[RowOffset+idx];
                    DescInfo.Buffer.assign( ScrInfo.Buffer.c_str() , ScrInfo.BufferSize );
                    DescInfo.BufferSize = ScrInfo.BufferSize;
                    DescInfo.Field      = ScrInfo.Field;
                    DescInfo.IsNull     = ScrInfo.IsNull;
                }
                ++RetIdx;
            }
            else
            {
                m_RowCount = m_RowCount - Row;
                m_Result.resize( m_RowCount * m_FieldCount );
                Row = 0;
            }
        }
    }

    free( pBind );
    ResultArray.clear();
    return true;
}
