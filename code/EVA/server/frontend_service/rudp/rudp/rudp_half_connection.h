// 定义RUDP半开连接数据接口

#ifndef __RUDP_HALF_CONNECTION_H_
#define __RUDP_HALF_CONNECTION_H_

#include "../revolver/base_typedef.h"
#include "../revolver/base_namespace.h"
#include "../revolver/base_inet_addr.h"

#include <map>

using namespace std;

BASE_NAMESPACE_BEGIN_DECL
typedef struct __RUDPPeerInfo
{
    int32_t     rudp_id;
    Inet_Addr   addr;

    __RUDPPeerInfo( int32_t id, const Inet_Addr& peer_addr ) : rudp_id(id), addr(peer_addr)
    {

    };

    bool    operator==( const __RUDPPeerInfo& info ) const
    {
        if( rudp_id == info.rudp_id && addr == info.addr )
            return true;
        else
            return false;
    };

    bool    operator!=( const __RUDPPeerInfo& info ) const
    {
        if( rudp_id != info.rudp_id || addr == info.addr )
            return true;
        else
            return false;
    };

    bool    operator>( const __RUDPPeerInfo& info ) const
    {
        if( rudp_id > info.rudp_id )            { return true;  }
        else if( rudp_id < info.rudp_id )       { return false; }
        else if(addr > info.addr)               { return true;  }
        else return false;
    };

    bool    operator<( const __RUDPPeerInfo& info ) const
    {
        if( rudp_id < info.rudp_id )        { return true;  }
        else if( rudp_id > info.rudp_id )   { return false; }
        else if(addr < info.addr)           { return true;  }
        else return false;
    };

}RUDPPeerInfo;

typedef map< RUDPPeerInfo, int32_t >    RUDPHandleMap;

BASE_NAMESPACE_END_DECL

#endif