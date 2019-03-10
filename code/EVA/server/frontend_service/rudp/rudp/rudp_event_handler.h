// RUDP的event handler，用于应用层的事件监听和处理的接口;

#ifndef __RUDP_EVENT_HANDLER_H_
#define __RUDP_EVENT_HANDLER_H_

#define INVALID_RUDP_HANDLE -1

BASE_NAMESPACE_BEGIN_DECL

class RUDPEventHandler
{
public:
    RUDPEventHandler( void ) { };
    virtual ~RUDPEventHandler( void ) { };

    virtual	int32_t rudp_accept_event( int32_t rudp_id )    { return 0; };
    virtual	int32_t	rudp_input_event ( int32_t rudp_id )    { return 0; };
    virtual int32_t rudp_output_event( int32_t rudp_id )    { return 0; };
    virtual	int32_t rudp_close_event ( int32_t rudp_id )    { return 0; };
    virtual int32_t rudp_exception_event( int32_t rudp_id ) { return 0; };
    virtual int32_t rudp_exist_keeplive( int32_t rudp_id )  { return 0; };

    // test;
    virtual int32_t send( const uint8_t *data, uint32_t data_len ) { return 0; }
};

BASE_NAMESPACE_END_DECL

#endif

