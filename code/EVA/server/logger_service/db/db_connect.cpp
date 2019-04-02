#include "db_connect.h"

LSE_NAMESPACE_BEGIN_DECL

void CDBConnect::InitDBConnect( NLMISC::CSString Host , NLMISC::CSString User , NLMISC::CSString Password , NLMISC::CSString DBName , uint16 Port )
{
    DBThreads.Connect( Host , User , Password , DBName , Port , NULL );
}

void CDBConnect::StartDBThreads( void )
{
    DBThreads.StartThreads();
}

void CDBConnect::CloseDBThreads( void )
{
    DBThreads.CloseThreads();
}

void CDBConnect::FrameMove( void )
{
    DBThreads.FrameMove();
}

LSE_NAMESPACE_END_DECL