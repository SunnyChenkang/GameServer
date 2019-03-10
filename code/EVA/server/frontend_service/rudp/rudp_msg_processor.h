#ifndef __RUDP_SEND_PROCESSOR_H_
#define __RUDP_SEND_PROCESSOR_H_

#include "revolver/base_typedef.h"
#include "revolver/base_reactor.h"
#include "revolver/base_inet_addr.h"
#include "revolver/base_queue.h"
#include "revolver/base_singleton.h"
#include "revolver/base_thread_mutex.h"

class IOBuffer
{
public:
    IOBuffer( void );
   ~IOBuffer( void );

    bool push( const void* data , int32_t data_len , int32_t socket_id , uint32_t addr_id = 0 );

    uint8_t* buf( void ) const;
    int32_t  len( void )       { return len_; }
    int32_t  socket_id( void ) { return socket_id_; }
    uint32_t addr_id( void )   { return addr_id_; }
private:
    uint8_t*        buf_;
    int32_t         len_;
    int32_t         socket_id_;
    uint32_t        addr_id_;
};


using namespace BASE;
class CSendProcessor : public IMessageProcessor
{
public:
    CSendProcessor( void );
   ~CSendProcessor( void );

public:
    void clear( void );

    bool push( const uint8_t* , int32_t , int32_t );

public:
    int32_t processor( void );
protected:
    BaseQueue_T<IOBuffer* , BaseThreadMutex , 0xFFFF > send_queue_;
};


class CRecvProcesser
{
public:
    CRecvProcesser( void );
   ~CRecvProcesser( void );

    void clear( void );

    bool push( const uint8_t* , int32_t , int32_t , uint32_t );

    IOBuffer* pop( void );

protected:
    BaseQueue_T<IOBuffer* , BaseThreadMutex ,  0xFFFF > recv_quque_;
};


class CErrorRecvProcesser
{
public:
    CErrorRecvProcesser( void ){ }
   ~CErrorRecvProcesser( void ){ }

    void push( int32_t );

    int32_t pop( void );

protected:
    BaseQueue_T<int32_t , BaseThreadMutex , 4096 > error_quque_;
};

class CErrorSendProcesser
{
public:
    CErrorSendProcesser( void ){ }
   ~CErrorSendProcesser( void ){ }

    void push( int32_t );

    int32_t pop( void );

protected:
    BaseQueue_T<int32_t , BaseThreadMutex , 4096 > error_quque_;
};


#define CREATE_SEND_OBJ         CRUDPSingleton< CSendProcessor >::instance
#define SEND_OBJ                CRUDPSingleton< CSendProcessor >::instance
#define DESTROY_SEND_OBJ        CRUDPSingleton< CSendProcessor >::destroy


#define CREATE_RECV_OBJ         CRUDPSingleton< CRecvProcesser >::instance
#define RECV_OBJ                CRUDPSingleton< CRecvProcesser >::instance
#define DESTROY_RECV_OBJ        CRUDPSingleton< CRecvProcesser >::destroy

#define CREATE_RECV_ERROR_OBJ   CRUDPSingleton< CErrorRecvProcesser >::instance
#define ERROR_RECV_OBJ          CRUDPSingleton< CErrorRecvProcesser >::instance
#define DESTROY_RECV_ERROR_OBJ  CRUDPSingleton< CErrorRecvProcesser >::destroy

#define CREATE_SEND_ERROR_OBJ   CRUDPSingleton< CErrorSendProcesser >::instance
#define ERROR_SEND_OBJ          CRUDPSingleton< CErrorSendProcesser >::instance
#define DESTROY_SEND_ERRRO_OBJ  CRUDPSingleton< CErrorSendProcesser >::destroy

#endif // __RUDP_SEND_PROCESSOR_H_;