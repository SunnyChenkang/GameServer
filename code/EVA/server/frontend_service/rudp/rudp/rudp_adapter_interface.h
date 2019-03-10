// RUDPÊÊÅäÆ÷½Ó¿Ú;

#ifndef __RUDP_ADAPTER_INTERFACE_H_
#define __RUDP_ADAPTER_INTERFACE_H_

#include "../revolver/base_typedef.h"
#include "../revolver/base_namespace.h"
#include "../revolver/base_bin_stream.h"
#include "../revolver/base_inet_addr.h"

BASE_NAMESPACE_BEGIN_DECL

class IRUDPAdapter
{
public:
    IRUDPAdapter( void ){ index_ = 0; };
    virtual ~IRUDPAdapter( void ) { };

    uint8_t             get_index() const { return index_; };
    void                set_index( uint8_t index ) { index_ = index; };

    virtual void        on_data( BinStream& strm , const Inet_Addr& remote_addr ) = 0;
    virtual void        send( BinStream& strm , const Inet_Addr& remote_addr )    = 0;

protected:
    uint8_t             index_;
};

BASE_NAMESPACE_END_DECL

#endif
