#ifndef SERVER_SHARED_DBEXECUTE_H_
#define SERVER_SHARED_DBEXECUTE_H_

#include <server_share/common/common.h>
#include "db_statement.h"
#include "db_connect.h"

SS_NAMESPACE_BEGIN_DECL

class CDBExecute
{
public:
    CDBExecute( void );
   ~CDBExecute( void );

    //   connect;
    bool Connect( NLMISC::CSString , NLMISC::CSString , NLMISC::CSString , NLMISC::CSString , uint16 );
    //   close;
    void Close( void );
    //   execute;
    void Execute( CDBStatement* );
    //   query;
    void Query( CDBStatement* , CDBResult** );

    //   add stmt;
    void AddStmt( size_t , char const* );
    //   get stmt;
    CDBStatement* GetStmt( size_t );

    SS_PROPERTY( CDBConnect                 , Connect    , private );
    SS_PROPERTY( std::vector<CDBStatement*> , StmtTable  , private );
};

SS_NAMESPACE_END_DECL

#endif // SERVER_SHARED_DBEXECUTE_H_;