#ifndef SERVICE_SHARED_BUFFERFIFO_RING_H_
#define SERVICE_SHARED_BUFFERFIFO_RING_H_

#include <server_share/common/common.h>

SS_NAMESPACE_BEGIN_DECL

// 环形队列;
template< typename T >
class CBufferFifoAnnular
{
public:
    CBufferFifoAnnular( void ) : m_Reads( 0 )
                               , m_Writer( 0 )
                               , m_MaxSize( 1 )
                               , m_Mask( 0 )
    {
        m_Data.clear();
    }

   ~CBufferFifoAnnular( void ){ };

    //   初始化环形队列;
    void InitPool( uint32 size );
    //   添加元素;
    bool PushBack( T* data );
    //   获取元素;
    T*   BackFront( void );
    //   环形队列是否为空;
    bool IsEmpty( void );
    //   获取队列大小;
    uint32 GetSize( void );

    SS_PROPERTY( NLMISC::CMutex  , Mutex      , private );
    SS_PROPERTY( uint32          , Reads      , private  );
    SS_PROPERTY( uint32          , Writer     , private  );
    SS_PROPERTY( uint32          , MaxSize    , private  );
    SS_PROPERTY( uint32          , Mask       , private  );
    SS_PROPERTY( std::vector<T*> , Data       , private  );
};

// 双缓冲队列;
template< typename T >
class CDoubleBufferFifo
{
public:
    CDoubleBufferFifo( void ) : m_ReadsCount ( 0 )
                              , m_WriterCount( 0 )
    {
        
    }

   ~CDoubleBufferFifo( void ) { }

    //   添加元素;
    bool PushBack( T* data );
    //   获取元素;
    T*   BackFront( void );

    //   元素数量;
    uint32 Size( void ) { return m_ReadsCount + m_WriterCount ;}

private:
    //   交换队列;
    void ExchangeQueue( void );

    SS_PROPERTY( volatile uint32  , ReadsCount      , private );
    SS_PROPERTY( volatile uint32  , WriterCount     , private );

    SS_PROPERTY( NLMISC::CMutex   , WriterMutex     , private );
    SS_PROPERTY( NLMISC::CMutex   , ReadsMutex      , private );

    SS_PROPERTY( std::queue<T*>   , WriterQueue     , private );
    SS_PROPERTY( std::queue<T*>   , ReadsQueue      , private );
};

#include "buffer_fifo.inl"

SS_NAMESPACE_END_DECL

#endif // SERVICE_SHARED_BUFFERFIFO_RING_H_;