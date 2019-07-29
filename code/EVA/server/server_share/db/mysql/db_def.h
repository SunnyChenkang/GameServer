#ifndef SERVER_SHARED_DBDEF_H_
#define SERVER_SHARED_DBDEF_H_

# ifdef _MSC_VER
#   if _MSC_VER < 1700
#include <my_global.h>
#endif
#endif

#include <mysql.h>
#include <errmsg.h>
#include <nel/misc/thread.h>

#include <server_share/common/common.h>
#include <server_share/buffer/buffer_fifo.h>
#include <server_share/record/record_base.h>

SS_NAMESPACE_BEGIN_DECL

class CDBExecute;

// inlitialize sql worker;
typedef void ( *INIT_SQL_WORKER )( CDBExecute* );
// db function processing msg;
typedef void* ( *PROC_MSG )( void* );

#ifdef NL_OS_WINDOWS
    static const char* DB_NAMES = "utf8";
#else
    static const char* DB_NAMES = "utf8mb4";
#endif

// 执行SQL语句时出错再次尝试执行间隔时间（毫秒）
#define ERROR_SLEEP_TIME 2000

// db execute data;
struct DBExecuteData
{
    CRecordBase*    data;
    PROC_MSG        func;
    DBExecuteData( void ) : data( NULL )
                          , func( NULL )
    {
        
    }
};

// db result struct;
struct DBResultInfo
{
    NLMISC::CSString Buffer;
    unsigned long    BufferSize;
    enum_field_types Field;
    my_bool          IsNull;

    DBResultInfo( void ) : BufferSize( 0 )
                         , Field( MYSQL_TYPE_NULL )
                         , IsNull( false )
    {
        Buffer.clear();
    }
};


// db statement struct;
struct DBStatementInfo
{
    NLMISC::CSString Buffer;
    uint32           Field;
    my_bool          IsUnsigned;
    my_bool          IsNullValue;

    DBStatementInfo( void ) : Field( MYSQL_TYPE_NULL )
                            , IsUnsigned( 0 )
                            , IsNullValue( 0 )
    {
        Buffer.clear();
    }


    // serial;
    void serial( NLMISC::IStream& s )
    {
        s.serial( Buffer );
        s.serial( Field );
        s.serial( IsUnsigned );
        s.serial( IsNullValue );
    }
};

SS_NAMESPACE_END_DECL

#endif // SERVER_SHARED_DBDEF_H_;