#ifndef __RUDP_LISTENER_HANDLER_H_
#define __RUDP_LISTENER_HANDLER_H_

#include "rudp/rudp_interface.h"
#include "revolver/base_singleton.h"

using namespace BASE;

class RUDPListenHandler : public RUDPEventHandler
{
public:
    RUDPListenHandler( void );
   ~RUDPListenHandler( void );

   virtual  int32_t rudp_accept_event( int32_t rudp_id );
   virtual  int32_t	rudp_input_event ( int32_t rudp_id );
   virtual  int32_t rudp_output_event( int32_t rudp_id );
   virtual  int32_t rudp_close_event ( int32_t rudp_id );
   virtual  int32_t rudp_exception_event( int32_t rudp_id );
};

#define CREATE_RUDP_LISTEN  CRUDPSingleton<RUDPListenHandler>::instance
#define RUDP_LISTEN         CRUDPSingleton<RUDPListenHandler>::instance
#define DESTROY_RUDP_LISTEN CRUDPSingleton<RUDPListenHandler>::destroy


#endif // __RUDP_LISTENER_HANDLER_H_;