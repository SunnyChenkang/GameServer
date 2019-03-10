// ∂®“ÂUDP SOCKET¿‡;

#ifndef __BASE_SOCK_DGRAM_H
#define __BASE_SOCK_DGRAM_H

#include "base_socket.h"

BASE_NAMESPACE_BEGIN_DECL

class CSockDgram : public CBaseSocket
{
public:
    CSockDgram();
    virtual ~CSockDgram();

    int32_t     open(const Inet_Addr& local_addr, bool nonblocking = false,  bool resue = true, bool client = false);
private:
    int32_t     bind(Inet_Addr& local_addr);

private:
    Inet_Addr   local_addr_;
};

BASE_NAMESPACE_END_DECL

#endif