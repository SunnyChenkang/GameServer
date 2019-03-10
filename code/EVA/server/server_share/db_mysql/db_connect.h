#ifndef SERVER_SHARED_CONNECT_H_
#define SERVER_SHARED_CONNECT_H_

#include "db_def.h"

SS_NAMESPACE_BEGIN_DECL

class CDBStatement;
class CDBResult;

class CDBConnect
{
public:
    CDBConnect( void );
   ~CDBConnect( void );

public:
    //     connect;
    bool   Connect( NLMISC::CSString , NLMISC::CSString , NLMISC::CSString , NLMISC::CSString , uint16 );
    //     close;
    void   Close( void );
    //     execute;
    sint32 Execute( CDBStatement* );
    //     query;
    sint32 Query( CDBStatement* , CDBResult** );
    //     create stmt;
    CDBStatement* CreateStmt( char const* , size_t );

protected:
    //     re connect;
    bool   ReConnect( void );
    bool   Procerror( CDBStatement* , char const* func = NULL );
    bool   ReError( char const* , char const* );

    SS_PROPERTY( MYSQL*             , Mysql     , private );
    SS_PROPERTY( NLMISC::CSString   , Host      , private );
    SS_PROPERTY( NLMISC::CSString   , User      , private );
    SS_PROPERTY( NLMISC::CSString   , Password  , private );
    SS_PROPERTY( NLMISC::CSString   , DBName    , private );
    SS_PROPERTY( uint16             , Port      , private );
    SS_PROPERTY( uint32             , Errno     , private );
    SS_PROPERTY( NLMISC::CSString   , Error     , private );
};

SS_NAMESPACE_END_DECL

#endif // SERVER_SHARED_CONNECT_H_;