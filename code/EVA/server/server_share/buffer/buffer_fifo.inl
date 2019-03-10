#include "buffer_fifo.h"

template< typename T >
void SS::CBufferFifoAnnular<T>::InitPool( uint32 Size )
{
    for ( uint32 idx = 0; idx < 32; idx++ )
    {
        m_MaxSize = ( m_MaxSize << 1 );
        if ( m_MaxSize >= Size ) break;
    }
    m_Mask = m_MaxSize - 1;
    m_Data.resize( m_MaxSize );
}

template< typename T >
bool SS::CBufferFifoAnnular<T>::PushBack( T* pData )
{
    bool res = false;
    m_Mutex.enter();
    if ( m_Writer - m_Reads < m_MaxSize )
    {
        uint32 Writer = m_Writer++;
        m_Data[ Writer & m_Mask ] = pData;
        res = true;
    }
    m_Mutex.leave();
    return res;
}

template< typename T >
T* SS::CBufferFifoAnnular<T>::BackFront( void )
{
    T res = NULL;
    m_Mutex.enter();
    if ( m_Reads != m_Writer )
    {
        uint32 Read = m_Reads++;
        res = m_Data[ Read & m_Mask ];
    }
    m_Mutex.leave();
    return res;
}

template< typename T >
uint32 SS::CBufferFifoAnnular<T>::GetSize( void )
{
    m_Mutex.enter();
    uint32 size = m_Writer - m_Reads;
    m_Mutex.leave();
}

template< typename T >
bool SS::CBufferFifoAnnular<T>::IsEmpty( void )
{
    return ( this->GetSize() == 0 );
}

template< typename T >
bool SS::CDoubleBufferFifo<T>::PushBack( T* pData )
{
    m_WriterMutex.enter();
    m_WriterQueue.push( pData );
    m_WriterCount = m_WriterQueue.size();
    m_WriterMutex.leave();
    return true;
}

template< typename T >
T* SS::CDoubleBufferFifo<T>::BackFront( void )
{
    if ( m_ReadsCount <= 0 )
    {
        ExchangeQueue();
    }
    if ( m_ReadsCount <= 0 ) return NULL;

    m_ReadsMutex.enter();
    T* pRes = m_ReadsQueue.front();
    m_ReadsQueue.pop();
    m_ReadsCount = m_ReadsQueue.size();
    m_ReadsMutex.leave();
    return pRes;
}

template< typename T >
void SS::CDoubleBufferFifo<T>::ExchangeQueue( void )
{
    if ( m_WriterCount <= 0 ) return;
    m_ReadsMutex.enter();
    m_WriterMutex.enter();

    std::queue<T*> pTestBuffer = m_ReadsQueue;
    m_ReadsQueue  = m_WriterQueue;
    m_WriterQueue = pTestBuffer;

    m_ReadsCount  = m_ReadsQueue.size();
    m_WriterCount = m_WriterQueue.size();

    m_WriterMutex.leave();
    m_ReadsMutex.leave();
}