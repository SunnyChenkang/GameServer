#include "revolver/base_reactor_instance.h"
#include "udp_handler.h"
#include "rudp/rudp_interface.h"

#define MAX_UDP_PACKET 1500

RecvUDPHandler::RecvUDPHandler()
{
    bin_strm_.resize(MAX_UDP_PACKET);
}

RecvUDPHandler::~RecvUDPHandler()
{
    this->close();
}

BASE_HANDLER RecvUDPHandler::get_handle() const
{
    return sock_dgram_.get_handler();
}

bool RecvUDPHandler::is_open() const 
{
    return ( get_handle() != INVALID_HANDLER );
}

int32_t RecvUDPHandler::open( const Inet_Addr& local_addr )
{
    int32_t res = sock_dgram_.open( local_addr , true );
    if ( res != 0 ) { return -1; }

    // 设置缓存区大小;
    int32_t bufsize = 20*1024*1024;
    sock_dgram_.set_option( SOL_SOCKET , SO_RCVBUF , (void*)&bufsize , sizeof( int32_t ) );
    sock_dgram_.set_option( SOL_SOCKET , SO_SNDBUF , (void*)&bufsize , sizeof( int32_t ) );
    // 本地UDP桥接;
    adapter_.set_title( 0 );
    adapter_.set_local_addr( local_addr );

    RUDP()->attach( &adapter_ );

    return REACTOR_INSTANCE()->register_handler( this , MASK_READ );
}

int32_t RecvUDPHandler::close( void )
{
    REACTOR_INSTANCE()->delete_handler( this );
    sock_dgram_.close();
    RUDP()->unattach( &adapter_ );

    return 0;
}

int32_t RecvUDPHandler::send( BinStream& bin_strm , const Inet_Addr& remote_addr )
{
    int32_t rc = sock_dgram_.send( bin_strm.get_rptr() , bin_strm.data_size() , remote_addr );
    if ( rc >= 0 ) { return rc; }

    // 插入一个写事件,防止套接字异常;
    if ( XEAGAIN == error_no() || XEINPROGRESS == error_no() )
    {
        REACTOR_INSTANCE()->register_handler( this , MASK_WRITE );
        return 0;
    }
    return -1;
}

int32_t RecvUDPHandler::handle_input( BASE_HANDLER handle )
{
    Inet_Addr remote_addr;

    while ( true )
    {
        bin_strm_.rewind( true );
        int32_t rc = sock_dgram_.recv( bin_strm_.get_wptr() , MAX_UDP_PACKET , remote_addr );
        if ( rc > 0 )
        {
            bin_strm_.set_used_size( rc );
            adapter_.on_data( bin_strm_ , remote_addr );
        }
        else
        {
			if ( XEAGAIN == error_no() ) { return 0; }
            else { return -1;}
        }
    }

    return 0;
}

int32_t RecvUDPHandler::handle_output( BASE_HANDLER handle )
{
    REACTOR_INSTANCE()->remove_handler( this , MASK_WRITE );
    return 0;
}

int32_t RecvUDPHandler::handle_close( BASE_HANDLER handle )
{
    return 0;
}

int32_t RecvUDPHandler::handle_exception( BASE_HANDLER handle )
{
    return 0;
}