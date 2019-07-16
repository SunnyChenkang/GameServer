#ifndef SERVER_SHARED_DBRESULT_H_
#define SERVER_SHARED_DBRESULT_H_

#include "db_def.h"

SS_NAMESPACE_BEGIN_DECL

class CDBResult
{
public:
    friend class CDBConnect;

    //      bool;
    my_bool GetBool  ( size_t sz );
    //      int8
    sint8   GetSInt8 ( size_t sz ) { return GetFieldParam<sint8>( sz );  }
    //      uint8;
    uint8   GetUint8 ( size_t sz ) { return GetFieldParam<uint8>( sz );  }
    //      int16;
    sint16  GetSInt16( size_t sz ) { return GetFieldParam<sint16>( sz ); }
    //      uint16;
    uint16  GetUint16( size_t sz ) { return GetFieldParam<uint16>( sz ); }
    //      int32;
    sint32  GetSInt32( size_t sz ) { return GetFieldParam<sint32>( sz ); }
    //      uint32;
    uint32  GetUint32( size_t sz ) { return GetFieldParam<uint32>( sz ); }
    //      int64;
    sint64  GetSInt64( size_t sz ) { return GetFieldParam<sint64>( sz ); }
    //      uint64;
    uint64  GetUint64( size_t sz ) { return GetFieldParam<uint64>( sz ); }
    //      float;
    float   GetFloat ( size_t sz ) { return GetFieldParam<float>( sz ); }
    //      double;
    double  GetDouble( size_t sz ) { return GetFieldParam<double>( sz ); }
    //      string;
    std::pair< size_t , char const* > GetString( size_t );
    //      blob;
    std::pair< size_t , void const* > GetBlob  ( size_t );
    //      next;
    bool    NextRow( void );
    //      release;
    void    Release( void ){ delete this; }
    //      count;
    size_t  GetCount ( void ) const { return m_RowCount; }

protected:
    CDBResult( void );
   ~CDBResult( void );

    // initialize;
    bool Initialize( MYSQL_STMT* , MYSQL_RES* );
    // row offset;
    uint32 GetRowOffset( void ) { return m_RowCurr < 0 ? 0 : ( m_RowCurr*m_FieldCount ); }
    // get param ;
    template< typename T >
    T GetFieldParam( size_t sz );

    SS_PROPERTY( std::vector< DBResultInfo > , Result     , private );
    SS_PROPERTY( uint32                      , RowCount   , private );
    SS_PROPERTY( sint32                      , RowCurr    , private );
    SS_PROPERTY( uint32                      , FieldCount , private );
};

#include "db_template.inl"

SS_NAMESPACE_END_DECL


#endif // SERVER_SHARED_DBINTERFACE_H_