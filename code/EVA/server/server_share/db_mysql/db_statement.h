#ifndef SERVER_SHARED_DBSTATEMENT_H_
#define SERVER_SHARED_DBSTATEMENT_H_

#include "db_def.h"

SS_NAMESPACE_BEGIN_DECL

class CDBStatement
{
public:
    friend class CDBConnect;

    //   bool;
    void SetBool  ( size_t , my_bool);
    //   int8;
    void SetInt8  ( size_t , sint8  );
    //   uint8;
    void SetUInt8 ( size_t , uint8  );
    //   int16;
    void SetInt16 ( size_t , sint16 );
    //   uint16;
    void SetUint16( size_t , uint16 );
    //   int32;
    void SetInt32 ( size_t , sint32 );
    //   uint32;
    void SetUint32( size_t , uint32 );
    //   int64;
    void SetInt64 ( size_t , sint64 );
    //   uint64;
    void SetUint64( size_t , uint64 );
    //   float;
    void SetFloat ( size_t , float  );
    //   double;
    void SetDouble( size_t , double );
    //   string;
    void SetString( size_t , char const* );
    void SetString( size_t , char const* , size_t );
    //   bolb;
    void SetBlob( size_t , void const* , size_t );
    void SetBlobTiny( size_t , void const* , size_t );
    //   release;
    void Release( void ) { delete this; }

    //   to string;
    NLMISC::CSString ToString( void );

protected:
    CDBStatement( void );
   ~CDBStatement( void );

    //   Bind;
    void Bind( size_t );

    SS_PROPERTY( MYSQL_BIND*                    , Bind   , private );
    SS_PROPERTY( size_t                         , Count  , private );
    SS_PROPERTY( std::vector< DBStatementInfo > , Param  , private );
    SS_PROPERTY( NLMISC::CSString               , Sql    , private );
};

SS_NAMESPACE_END_DECL

#endif // SERVER_SHARED_DBSTATEMENT_H_