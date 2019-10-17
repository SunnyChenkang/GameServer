#include "db_connect.h"

LSE_NAMESPACE_BEGIN_DECL

CDBConnect::CDBConnect(void)
{
    m_Random.srand( NLMISC::CTime::getSecondsSince1970() );
}

CDBConnect::~CDBConnect( void )
{

}

void CDBConnect::InitDBConnect( NLMISC::CSString Host , NLMISC::CSString User , NLMISC::CSString Password , NLMISC::CSString DBName , uint16 Port , uint16 ThreadsCount )
{
    m_DBThreads.resize( ThreadsCount );
    for ( auto& Element : m_DBThreads )
    {
        Element.Connect( Host , User , Password , DBName , Port , nullptr );
    }
}

void CDBConnect::StartDBThreads( void )
{
    for ( auto& Element : m_DBThreads )
    {
        Element.StartThreads();
    }
}

void CDBConnect::CloseDBThreads( void )
{
    for ( auto& Element : m_DBThreads )
    {
        Element.CloseThreads();
    }
}

void CDBConnect::FrameMove( void )
{
    for ( auto Element : m_DBThreads )
    {
        Element.FrameMove();
    }
}

sint8 CDBConnect::GetThreadsIdx( void )
{
    uint16 idx = m_Random.rand( m_DBThreads.size()-1 );
    return idx;
}

LSE_NAMESPACE_END_DECL