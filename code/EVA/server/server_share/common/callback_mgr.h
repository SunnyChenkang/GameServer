#ifndef SERVICE_CALLBACK_MGR_H_
#define SERVICE_CALLBACK_MGR_H_

/*
* CCallBackMgr< std::tr1::function<void( float, double, int )> > CALLBACK_MGR;
* CALLBACK_MGR call_back;
* void func( float, double, int ){ }
* call_back.PushCallBack( &func , 1000 );
*/

#include "common.h"

SS_NAMESPACE_BEGIN_DECL

template<typename T>
class CCallBackMgr
{
public:
    typedef std::map< CALLBACK_ID , std::pair< T , uint32 > > CALLBACKS;
    CCallBackMgr( void );
   ~CCallBackMgr( void );

    // 添加一个回调;
    CALLBACK_ID PushCallBack( T callback , uint32 timeout = 0 );
    // 取走一个回调;
    T TakeCallBack( CALLBACK_ID );
    // 检查回调超时;
    void TimeOutCallBack( void );

    SS_PROPERTY( CALLBACKS           , CallBack , private );
    SS_PROPERTY( CIDAllocate<uint64> , AllockID , private );
};

template< typename T >
CALLBACK_ID CCallBackMgr::PushCallBack( T callback , uint32 timeout /* = 0 */ )
{
    // 检查超时回调;
    this->TimeOutCallBack();

    if ( timeout == 0 )
    {
        timeout = 0x93A80 + NLMISC::CTime::getSecondsSince1970();
    }
    CALLBACK_ID id = m_AllockID.Allocate();
    m_CallBack.insert( typename CALLBACKS::value_type( id , std::pair< T , uint32 >( callback , timeout ) ) );
    return id;
}

template< typename T >
T CCallBackMgr::TakeCallBack( CALLBACK_ID id )
{
    // 回调超时检查;
    this->TimeOutCallBack();

    typename CALLBACKS::iterator it = m_CallBack.find( id );
    if ( it == m_CallBack.end() ) {
        return NULL;
    }

    T t = it->second.first;
    m_AllockID.Reclaim(it->first);
    m_CallBack.erase( it );
    return t;
}

template< typename T >
void CCallBackMgr::TimeOutCallBack( void )
{
    uint32 curr_time = NLMISC::CTime::getSecondsSince1970();
    typename CALLBACKS::iterator it = m_CallBack.begin();
    for( ; it != m_CallBack.end(); )
    {
        if ( curr_time < it->second.second ) {
            ++it;
            continue;
        }
        m_AllockID.Reclaim( it->first );
        m_CallBack.erase( it++ );
    }
}

SS_NAMESPACE_END_DECL


#endif //SERVICE_CALLBACK_MGR_H_