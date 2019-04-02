#ifndef SERVER_ID_ALLOCAATE_H_
#define SERVER_ID_ALLOCAATE_H_

#include <server_share/common/common.h>

SS_NAMESPACE_BEGIN_DECL

class CRandomIDAlloc
{
public:
    CRandomIDAlloc( uint32 MinID , uint32 MaxID );
   ~CRandomIDAlloc( void ) { }

    uint32 Allocate( void );
    void   Reclain ( uint32 );

private:
    void   InitIDPool( void );

    struct IDState
    {
        uint32 ID;
        bool   State;
    };
    SS_PROPERTY( std::vector<IDState>   , IDPool    , private );
    SS_PROPERTY( uint32                 , MaxID     , private );
    SS_PROPERTY( uint32                 , MinID     , private );
    SS_PROPERTY( uint32                 , CurrID    , private );
    SS_PROPERTY( NLMISC::CRandom        , Random    , private );
};


template< typename T >
class CIDAllocate
{
public:
    CIDAllocate( void ) : m_LastID( 0 ) { }

    T Allocate( void )
    {
        T t = ++m_LastID;
        if ( t == 0 )
        t = ++m_LastID;
        return t;
    }
    virtual void Reclaim( T id ) { }
    SS_PROPERTY( T , LastID , protected );
};

template< typename T >
class CIDAllocateFromList : public CIDAllocate< T >
{
public:
    CIDAllocateFromList( void ) : CIDAllocate<T>() { }
   ~CIDAllocateFromList( void ) { }

    T Alloc( void )
    {
        if ( m_IdLast.size() > 0 ) {
        T n = m_IdLast.front();
        m_IdLast.pop_front();
        return n;
        }
        T t = ++CIDAllocate<T>::m_LastID;
        if ( t == 0 )
        t = ++CIDAllocate<T>::m_LastID;
        return t;
    }

    void Reclain( T ID )
    {
        m_IdLast.push( ID );
    }

    SS_PROPERTY( std::queue< T > , IdLast , protected );
};

SS_NAMESPACE_END_DECL

#endif//SERVER_ID_ALLOCAATE_H_
