#ifndef __RUDP_CONNECTION_H_
#define __RUDP_CONNECTION_H_

#include "revolver/base_event_handler.h"
#include "rudp/rudp_stream.h"
#include "rudp/rudp_interface.h"
#include "revolver/base_block_buffer.h"
#include "revolver/base_bin_stream.h"
#include "revolver/base_packet.h"

using namespace BASE;

typedef CReciverBuffer_T<BinStream , RUDPStream , 1024*8>  RUDPRBuffer;
typedef CSenderBuffer_T<BinStream, RUDPStream, 1024 * 16>   RUDPSBuffer;

enum RUDPConnState
{
    RUDP_CONN_IDLE,         //平静状态,有可能是未连接;
    RUDP_CONN_CONNECTING,   //连接状态;
    RUDP_CONN_CONNECTED,    //连接状态;
};

class RUDPConnection : public CEventHandler , public RUDPEventHandler
{
public:
    RUDPConnection( void );
    virtual ~RUDPConnection( void );

public:
    RUDPStream&         get_rudp_stream( void ) { return rudp_sock_; }

    int32_t             handle_timeout( const void* act , uint32_t timer_id );
    int32_t             rudp_accept_event(int32_t rudp_id);
    int32_t             rudp_input_event(int32_t rudp_id);
    int32_t             rudp_output_event(int32_t rudp_id);
    int32_t             rudp_close_event(int32_t rudp_id);
    int32_t             rudp_exception_event(int32_t rudp_id);

public:
    int32_t             connect( const Inet_Addr& scr_addr , const Inet_Addr& dst_addr );
    void                close( void );
    int32_t             send( const uint8_t *data, uint32_t data_len );

    void                reset( void );
    void                set_timer( uint32_t delay );
    void                cancel_timer( void );

    void                set_state( uint8_t state ) { state_ = state; }
    uint8_t             get_state( void ) { return state_; }

protected:
    RUDPStream          rudp_sock_;

    uint32_t            timer_id_;

    RUDPRBuffer         rbuffer_;
    RUDPSBuffer         sbuffer_;

    BinStream           istrm_;

    uint8_t             state_;
};
#endif // __RUDP_CONNECTION_H_;