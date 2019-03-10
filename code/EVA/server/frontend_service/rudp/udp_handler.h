#ifndef __RECIVER_UDP_HANDLER_H_
#define __RECIVER_UDP_HANDLER_H_

#include "revolver/base_event_handler.h"
#include "revolver/base_sock_dgram.h"
#include "revolver/base_bin_stream.h"
#include "revolver/base_singleton.h"
#include "reciver_adapter.h"

using namespace BASE;

class RecvUDPHandler : public CEventHandler
{
public:
    RecvUDPHandler( void );
    virtual ~RecvUDPHandler( void );

    bool            is_open( void ) const;

    int32_t         open( const Inet_Addr& local_addr );
    int32_t         close( void );
    int32_t         send( BinStream& bin_strm , const Inet_Addr& remote_addr );

    BASE_HANDLER    get_handle( void ) const;

    virtual         int32_t handle_input ( BASE_HANDLER handle );
    virtual         int32_t handle_output( BASE_HANDLER handle );
    virtual         int32_t handle_close ( BASE_HANDLER handle );
    virtual         int32_t handle_exception( BASE_HANDLER handle );

protected:
    BinStream       bin_strm_;
    CSockDgram      sock_dgram_;
    ReciverAdapter  adapter_;
};

#define CREATE_RECV_UDP         CRUDPSingleton<RecvUDPHandler>::instance
#define RECV_UDP                CRUDPSingleton<RecvUDPHandler>::instance
#define DESTROY_RECV_UDP        CRUDPSingleton<RecvUDPHandler>::destroy

#endif // __RECIVER_UDP_HANDLER_H_;