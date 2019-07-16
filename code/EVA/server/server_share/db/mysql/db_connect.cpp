#include "db_connect.h"
#include "db_result.h"
#include "db_statement.h"

SS::CDBConnect::CDBConnect( void ) : m_Mysql( NULL )
                                   , m_Port ( 3306 )
                                   , m_Errno( 0 )
                                   , m_Error( "" )
                                   , m_User( "" )
                                   , m_Password( "" )
                                   , m_DBName( "" )
{
    
}

SS::CDBConnect::~CDBConnect( void )
{
    
}

bool SS::CDBConnect::Connect( NLMISC::CSString Host, NLMISC::CSString User , NLMISC::CSString Password, NLMISC::CSString DBName, uint16 Port )
{
    // close;
    this->Close();

    // connect;
    m_Mysql = mysql_init( NULL );
    if ( NULL == m_Mysql )
    {
        nlwarning( " connect mysql init failed !" );
        return false;
    }

    // set character;
    mysql_options( m_Mysql , MYSQL_SET_CHARSET_NAME , DB_NAMES );

    MYSQL* pMysql = mysql_real_connect( m_Mysql , Host.c_str() , User.c_str() , Password.c_str() , DBName.c_str() , Port , NULL , CLIENT_FOUND_ROWS );
    if ( NULL == pMysql )
    {
        m_Errno = mysql_errno( m_Mysql );
        m_Error = mysql_error( m_Mysql );
        nlwarning( " connect mysql failed error = %d" , m_Errno );
        return false;
    }

    m_Host     = Host;
    m_User     = User;
    m_DBName   = DBName;
    m_Password = Password;
    m_Port     = Port;

    // set autocommit;
    mysql_autocommit( m_Mysql , 1 );
    // set character set;
    mysql_set_character_set( m_Mysql , DB_NAMES );
    // set query;
    mysql_query( m_Mysql , "SET character_set_client=binary" );

    nlinfo( " connect mysql succeed !" );
    nlinfo( " mysql client library : %s" , mysql_get_client_info() );
    nlinfo( " mysql server library : %s" , mysql_get_server_info( m_Mysql ) );

    return true;
}

void SS::CDBConnect::Close(void)
{
    if ( NULL == m_Mysql ) return;
    mysql_close( m_Mysql );
    m_Mysql = NULL;
}

SS::CDBStatement* SS::CDBConnect::CreateStmt( char const* sql , size_t sz )
{
    CDBStatement* pStmt = NULL;
    if ( NULL == m_Mysql ) return pStmt;
    if ( sz   <= 0       ) return pStmt;
    if ( NULL == sql     ) return pStmt;

    pStmt = new ( std::nothrow ) CDBStatement;
    if ( NULL == pStmt ) return pStmt;
    NLMISC::CSString str = "";
    str.append( sql , sz );
    pStmt->SetSQL( str );
    return pStmt;
}

sint32 SS::CDBConnect::Execute( CDBStatement* pStmt )
{
    sint32 ret= -1;
    if ( NULL == pStmt )    return ret;
    if ( NULL == m_Mysql )  return ret;

    MYSQL_STMT* pMysqlStmt = mysql_stmt_init( m_Mysql );
    if ( NULL != pMysqlStmt )
    {
        if ( 0 == mysql_stmt_prepare( pMysqlStmt , pStmt->GetSQL().c_str() , pStmt->GetSQL().size() ) )
        {
            my_bool bl = 1;
            mysql_stmt_attr_set( pMysqlStmt , STMT_ATTR_UPDATE_MAX_LENGTH , &bl );
            pStmt->Bind( mysql_stmt_param_count( pMysqlStmt ) );
            if ( NULL != pStmt->GetBind() )
            {
                if ( 0 != mysql_stmt_bind_param( pMysqlStmt , pStmt->GetBind() ) )
                {
                    m_Errno = mysql_errno( m_Mysql );
                    m_Error = mysql_error( m_Mysql );
                    mysql_stmt_close( pMysqlStmt );
                    if ( Procerror( pStmt , "mysql_stmt_bind_param" ) )
                    {
                        ret = Execute( pStmt );
                    }
                }
            }
            if ( NULL != pStmt )
            {
                if ( 0 == mysql_stmt_execute( pMysqlStmt ) )
                {
                    ret = ( sint32 )mysql_stmt_affected_rows( pMysqlStmt );
                    MYSQL_RES* pMysqlRes = mysql_stmt_result_metadata( pMysqlStmt );
                    if ( NULL != pMysqlRes )
                    {
                        uint32 ServerStatus = m_Mysql->server_status;
                        if ( ServerStatus & SERVER_PS_OUT_PARAMS )
                        {
                            nlwarning( "此调用存储存在返回参数值，请检查SQL语句和存储过程实现!" );
                            mysql_stmt_store_result( pMysqlStmt );
                            mysql_free_result( pMysqlRes );
                            mysql_stmt_free_result( pMysqlStmt );
                        }
                        else
                        {
                            nlwarning( "执行产讯操作不应该返回任何结果集,请检查SQL语句和存储过程实现" );
                            mysql_stmt_store_result( pMysqlStmt );
                            mysql_free_result( pMysqlRes );
                            mysql_stmt_free_result( pMysqlStmt );
                            while ( 0 == mysql_stmt_next_result( pMysqlStmt ) )
                            {
                                pMysqlRes = mysql_stmt_result_metadata( pMysqlStmt );
                                if ( NULL != pMysqlRes )
                                {
                                    ServerStatus = m_Mysql->server_status;
                                    mysql_stmt_store_result( pMysqlStmt );
                                    mysql_free_result( pMysqlRes );
                                    mysql_stmt_free_result( pMysqlStmt );
                                    if ( ServerStatus & SERVER_PS_OUT_PARAMS )
                                    {
                                        nlwarning( "此调用存储存在返回参数值,请检查SQL语句和存储过程实现" );
                                        break;
                                    }
                                    else
                                    {
                                        nlwarning( "执行查询操作不应该返回任何结果集,请检查SQL语句和存储过程实现" );
                                    }
                                }
                            }
                        }
                    }
                    mysql_stmt_close( pMysqlStmt );
                    pMysqlStmt = NULL;
                    pMysqlRes  = NULL;
                }
                else
                {
                    m_Errno = mysql_errno( m_Mysql );
                    m_Error = mysql_error( m_Mysql );
                    mysql_stmt_close( pMysqlStmt );
                    pMysqlStmt = NULL;
                    if ( Procerror( pStmt , "mysql_stmt_execute") )
                    {
                        ret = Execute( pStmt );
                    }
                }
            }
        }
        else
        {
            m_Errno = mysql_errno( m_Mysql );
            m_Error = mysql_error( m_Mysql );
            mysql_stmt_close( pMysqlStmt );
            pStmt = NULL;
            if ( Procerror( pStmt , "mysql_stmt_prepare" ) )
            {
                ret = Execute( pStmt );
            }
        }
    }
    else
    {
        m_Errno = mysql_errno( m_Mysql );
        m_Error = mysql_error( m_Mysql );
        if ( Procerror( pStmt , "mysql_stmt_init" ) )
        {
            ret = Execute( pStmt );
        }
    }

    return ret;
}

sint32 SS::CDBConnect::Query(CDBStatement* pStmt , CDBResult** pResult )
{
    sint32 ret = -1;

    if ( NULL == m_Mysql ) return ret;
    if ( NULL == pStmt   ) return ret;
    if ( NULL == pResult ) return ret;

    MYSQL_STMT* pMysqlStmt = mysql_stmt_init( m_Mysql );
    if ( NULL != pMysqlStmt )
    {
        if ( 0 == mysql_stmt_prepare( pMysqlStmt , pStmt->GetSQL().c_str() , pStmt->GetSQL().length() ) )
        {
            my_bool bl = 1;
            mysql_stmt_attr_set( pMysqlStmt , STMT_ATTR_UPDATE_MAX_LENGTH , &bl );
            pStmt->Bind( mysql_stmt_param_count( pMysqlStmt ) );
            if ( NULL != pStmt->GetBind() )
            {
                if ( 0 != mysql_stmt_bind_param( pMysqlStmt , pStmt->GetBind() ) )
                {
                    m_Errno = mysql_errno( m_Mysql );
                    m_Error = mysql_error( m_Mysql );
                    mysql_stmt_close( pMysqlStmt );
                    pMysqlStmt = NULL;
                    if ( Procerror( pStmt , "mysql_stmt_bind_param" ) )
                    {
                        ret = Query( pStmt , pResult );
                    }
                }
            }
            if ( NULL != pMysqlStmt )
            {
                if ( 0 == mysql_stmt_execute( pMysqlStmt ) )
                {
                    ret = (sint32)mysql_stmt_affected_rows( pMysqlStmt );
                    MYSQL_RES* pMysqlRes = mysql_stmt_result_metadata( pMysqlStmt );
                    if ( NULL != pMysqlRes )
                    {
                        uint32 ServerStatus = m_Mysql->server_status;
                        if ( 0 == mysql_stmt_store_result( pMysqlStmt ) )
                        {
                            CDBResult* pDBResult = *pResult;
                            if ( NULL == *pResult )
                            {
                                pDBResult = new( std::nothrow )CDBResult();
                                *pResult = pDBResult;
                            }
                            if ( ServerStatus & SERVER_PS_OUT_PARAMS )
                            {
                                ret = 0;
                                mysql_free_result( pMysqlRes );
                                mysql_stmt_free_result( pMysqlStmt );
                            }
                            else
                            {
                                ret = ( sint32 )mysql_stmt_num_rows( pMysqlStmt );
                                pDBResult->Initialize( pMysqlStmt , pMysqlRes );
                                mysql_free_result( pMysqlRes );
                                mysql_stmt_free_result( pMysqlStmt );
                                // 检查是否还有结果集;
                                while ( 0 == mysql_stmt_next_result( pMysqlStmt ) )
                                {
                                    pMysqlRes = mysql_stmt_result_metadata( pMysqlStmt );
                                    if ( NULL != pMysqlRes )
                                    {
                                        ServerStatus = m_Mysql->server_status;
                                        if ( 0 == mysql_stmt_store_result( pMysqlStmt ) )
                                        {
                                            if ( ServerStatus & SERVER_PS_OUT_PARAMS )
                                            {
                                                mysql_free_result( pMysqlRes );
                                                mysql_stmt_free_result( pMysqlStmt );
                                                break;
                                            }
                                            else
                                            {
                                                nlwarning( "执行查询操作不应该返回任何结果集,请检查SQL语句和存储过程实现！" );
                                                mysql_stmt_store_result( pMysqlStmt );
                                                mysql_free_result( pMysqlRes );
                                                mysql_stmt_free_result( pMysqlStmt );
                                            }
                                        }
                                    }
                                }
                            }
                            mysql_stmt_close( pMysqlStmt );
                            pMysqlStmt = NULL;
                        }
                        else
                        {
                            m_Errno = mysql_errno( m_Mysql );
                            m_Error = mysql_error( m_Mysql );
                            mysql_stmt_close( pMysqlStmt );
                            pMysqlStmt = NULL;
                            if ( Procerror( pStmt , "mysql_stmt_store_result" ) )
                            {
                                ret = Query( pStmt , pResult );
                            }
                            else
                            {
                                ret = -1;
                            }
                        }
                    }
                    else
                    {
                        mysql_stmt_close( pMysqlStmt );
                        pMysqlStmt = NULL;
                    }
                }
                else
                {
                    m_Errno = mysql_errno( m_Mysql );
                    m_Error = mysql_error( m_Mysql );
                    mysql_stmt_close( pMysqlStmt );
                    pMysqlStmt = NULL;
                    if ( Procerror( pStmt , "mysql_stmt_execute" ) )
                    {
                        ret = Query( pStmt , pResult );
                    }
                }
            }
        }
        else
        {
            m_Errno = mysql_errno( m_Mysql );
            m_Error = mysql_error( m_Mysql );
            mysql_stmt_close( pMysqlStmt );
            pMysqlStmt = NULL;
            if ( Procerror( pStmt , "mysql_stmt_prepare" ) )
            {
                ret = Query( pStmt , pResult );
            }
        }
    }
    else
    {
        m_Errno = mysql_errno( m_Mysql );
        m_Error = mysql_error( m_Mysql );
        if ( Procerror( pStmt , "mysql_stmt_init" ) )
        {
            ret = Query( pStmt , pResult );
        }
    }

    return ret;
}

bool SS::CDBConnect::ReConnect( void )
{
    if ( NULL != m_Mysql && 0 == mysql_ping( m_Mysql ) ) return true;

    nlwarning( " try to reconnect mysql server ...\n" );
    this->Close();
    m_Mysql = mysql_init( NULL );
    if ( NULL == m_Mysql )
    {
        nlwarning( " reconnect mysql server failed ! ");
        return false;
    }

    mysql_options( m_Mysql , MYSQL_SET_CHARSET_NAME , DB_NAMES );
    if ( NULL != mysql_real_connect( m_Mysql , 
                                     m_Host.c_str() ,
                                     m_User.c_str() ,
                                     m_Password.c_str() ,
                                     m_DBName.c_str() ,
                                     m_Port,
                                     NULL,
                                     CLIENT_FOUND_ROWS ) )
    {
        mysql_autocommit( m_Mysql , 1 );
        mysql_set_character_set( m_Mysql , DB_NAMES );
        mysql_query( m_Mysql , "SET character_set_client=binary" );
        nlinfo( " reconnect mysql server succeed !");
        nlinfo( " mysql client library %s . " , mysql_get_client_info() );
        nlinfo( " mysql server version  %s . ", mysql_get_server_info( m_Mysql ) );
        return true;
    }
    return false;
}

bool SS::CDBConnect::ReError( char const* pSql, char const* pFunc )
{
    bool ret = false;
    switch ( m_Errno )
    {
    case CR_SERVER_GONE_ERROR:
        nlwarning( "mysql server has gone away errno = %d" , m_Errno );
        while ( !( ret = ReConnect() ) )
        {
            m_Errno = mysql_errno( m_Mysql );
            m_Error = mysql_error( m_Mysql );
            nlinfo( "mysql reconnect op = %s , func = %s" , pSql , pFunc );
            NLMISC::nlSleep( ERROR_SLEEP_TIME );
        }
        break;
    case CR_SERVER_LOST:
        nlwarning( "lost the connection to mysql server , error = %d!" , m_Errno );
        while ( !( ret = ReConnect() ) )
        {
            m_Errno = mysql_errno( m_Mysql );
            m_Error = mysql_error( m_Mysql );
            nlinfo( "mysql reconnect op  = %s , func = %s." , pSql , pFunc );
            NLMISC::nlSleep( ERROR_SLEEP_TIME );
        }
        break;
    case CR_INVALID_CONN_HANDLE:
        nlwarning( "invalid connection handle , error = %d" , m_Errno );
        while ( !( ret = ReConnect() ) )
        {
            m_Errno = mysql_errno( m_Mysql );
            m_Error = mysql_error( m_Mysql );
            nlinfo( "mysql reconnect op = %s , func = %s" , pSql , pFunc );
            NLMISC::nlSleep( ERROR_SLEEP_TIME );
        }
        break;
    case CR_SERVER_LOST_EXTENDED:
        nlwarning( "lost the connection to mysql server error = %d" , m_Errno );
        while ( !( ret = ReConnect() ) )
        {
            m_Errno = mysql_errno( m_Mysql );
            m_Error = mysql_error( m_Mysql );
            nlinfo( "mysql reconnect op = %s , func = %s" , pSql , pFunc );
            NLMISC::nlSleep( ERROR_SLEEP_TIME );
        }
        break;
    default:
        nldebug( " %s error = %d" , m_Error.c_str() , m_Errno );
        break;
    }

    return ret;
}

bool SS::CDBConnect::Procerror( CDBStatement* pStmt , char const* func /*= NULL */ )
{
    bool ret = false;
    if ( NULL == pStmt ) return ret;

    if ( NULL != func )
    {
        nlinfo( "\nop = %s , param = %s , func = %s" , pStmt->GetSQL().c_str() , pStmt->ToString().c_str() , func );
    }
    else
    {
        nlinfo( "\nop = %s , param = %s." , pStmt->GetSQL().c_str() , pStmt->ToString().c_str() );
    }
    ret = ReError( pStmt->GetSQL().c_str() , func );
    return ret;
}
