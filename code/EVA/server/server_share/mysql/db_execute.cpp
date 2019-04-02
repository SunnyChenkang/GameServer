#include "db_execute.h"

SS::CDBExecute::CDBExecute( void )
{
    m_StmtTable.resize( 512 , NULL );
}

SS::CDBExecute::~CDBExecute( void )
{
    Close();
}

bool SS::CDBExecute::Connect( NLMISC::CSString Host , NLMISC::CSString User , NLMISC::CSString Password , NLMISC::CSString DBName , uint16 Port )
{
    return m_Connect.Connect( Host , User , Password , DBName , Port );
}

void SS::CDBExecute::Close( void )
{
    for ( sint32 idx = 0; idx < 512; idx++ )
    {
        if ( NULL == m_StmtTable[idx] ) continue;
        m_StmtTable[idx]->Release();
        m_StmtTable[idx] =  NULL;
    }
    m_StmtTable.clear();
    m_Connect.Close();
}

void SS::CDBExecute::Execute( CDBStatement* pStmt )
{
    if ( NULL == pStmt ) return;
    m_Connect.Execute( pStmt );
}

void SS::CDBExecute::Query( CDBStatement* pStmt , CDBResult** pResult )
{
    if ( NULL == pStmt   ) return;
    if ( NULL == pResult ) return;
    m_Connect.Query( pStmt , pResult );
}

void SS::CDBExecute::AddStmt( size_t sz , char const* sql )
{
    if ( NULL == sql ) return;
    CDBStatement* pStmt = m_Connect.CreateStmt( sql , strlen( sql ) );
    if ( NULL == pStmt ) return;
    if ( m_StmtTable[ sz ] != NULL )
    {
        m_StmtTable[ sz ]->Release();
        m_StmtTable[ sz ] = NULL;
    }
    m_StmtTable[ sz ] = pStmt;
}

SS::CDBStatement* SS::CDBExecute::GetStmt( size_t sz )
{
    return m_StmtTable[ sz ];
}
