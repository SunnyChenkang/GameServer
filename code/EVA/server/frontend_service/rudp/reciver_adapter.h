#ifndef __RECIVER_ADAPTER_H_
#define __RECIVER_ADAPTER_H_

#include "rudp/rudp_adapter.h"

using namespace BASE;

class ReciverAdapter : public IRUDPAdapter
{
public:
    ReciverAdapter( void );
    virtual ~ReciverAdapter( void );

    virtual void send( BinStream& strm , const Inet_Addr& remote_addr );
};

#endif // __RECIVER_ADAPTER_H_;