#ifndef SERVER_WWW_TASK_H_
#define SERVER_WWW_TASK_H_

#include <server_share/common/common.h>

SS_NAMESPACE_BEGIN_DECL

class curl_slist;

class CWWWTask
{
public:
    CWWWTask( void ){ };
   ~CWWWTask( void ){ };

public:
    virtual bool TaskStart( void ) = 0;
    virtual bool TaskEnd  ( void );
    virtual bool TaskPostUrl( NLMISC::CSString , NLMISC::CSString , curl_slist* );
    virtual bool TaskGetUrl ( NLMISC::CSString );

protected:
    static size_t WriteDataFromCurl( char* pBuffer , size_t BufferSize , size_t Member , NLMISC::CSString* WriterData )
    {
        if ( NULL == pBuffer )
            return 0;
        WriterData->append( pBuffer , BufferSize * Member );
        return BufferSize * Member;
    }

    SS_PROPERTY( NLMISC::CSString , WriteData , protected );
};

SS_NAMESPACE_END_DECL

#endif//SERVER_WWW_TASK_H_