#include "id_allocate.h"

SS_NAMESPACE_BEGIN_DECL

CRandomIDAlloc::CRandomIDAlloc( uint32 MinID , uint32 MaxID ) : m_MaxID( MaxID ) , m_MinID( MinID ) , m_CurrID( m_MinID )
{
    m_Random.srand( NLMISC::CTime::getSecondsSince1970() );
    m_IDPool.clear();
    m_IDPool.resize( MaxID );
    InitIDPool();
}

void CRandomIDAlloc::InitIDPool( void )
{
    for ( uint32 idx = m_MinID; idx < m_MaxID ; idx++ )
    {
        IDState State = { idx , false };
        m_IDPool[idx] = State;
    }
    for ( uint32 idx = m_MinID; idx < m_MaxID; idx++ )
    {
        uint32 RandomID    = m_Random.rand( m_MinID , m_MaxID );
        IDState State      = m_IDPool[idx];
        m_IDPool[idx]      = m_IDPool[RandomID];
        m_IDPool[RandomID] = State;
    }
}

uint32 CRandomIDAlloc::Allocate( void )
{
    if ( m_CurrID >= m_MaxID ) m_CurrID = m_MinID;
    IDState& State = m_IDPool[ m_CurrID++ ];
    return State.ID;
}

void CRandomIDAlloc::Reclain( uint32 ID )
{
    if ( ID >= m_IDPool.size() ) return;
    m_IDPool[ID].State = false;
}

SS_NAMESPACE_END_DECL



