#include "rudp_msg_processor.h"
#include "rudp/rudp_interface.h"
#include "rudp/rudp_stream.h"

IOBuffer::IOBuffer( void )
    : buf_( NULL )
    , len_( 0 )
    , socket_id_( 0 )
{

}

IOBuffer::~IOBuffer( void )
{
    if ( NULL != buf_ )
    {
        delete[] buf_;
        buf_ = NULL;
        len_ = 0;
    }
}

bool IOBuffer::push( const void* data , int32_t data_len , int32_t socket_id , uint32_t addr_id )
{
    buf_ = new unsigned char[ data_len ];
    memcpy( buf_ , data , data_len );
    len_ = data_len;
    socket_id_ = socket_id;
    addr_id_   = addr_id;
    return true;
}

uint8_t* IOBuffer::buf( void ) const
{
    return buf_;
}

CSendProcessor::CSendProcessor( void )
{
    clear();
}

CSendProcessor::~CSendProcessor( void )
{

}

void CSendProcessor::clear( void )
{
    IOBuffer* buffer_ = NULL;
    while ( send_queue_.get( buffer_ ) )
    {
        if ( buffer_ != NULL )
        {
            delete buffer_;
            buffer_ = NULL;
        }
    }
}

#include "rudp/rudp_log_macro.h"

int32_t CSendProcessor::processor( void )
{
    uint32_t rudp_id = 0;

    while ( true )
    {
        rudp_id = ERROR_SEND_OBJ()->pop();
        if ( rudp_id == 0 ) { break; }
        RUDPEventHandler* socket = RUDP()->get_socket_event( rudp_id );
        if ( NULL != socket )
        {
            socket->rudp_close_event( rudp_id );
        }
    }

    IOBuffer* buffer_ = NULL;
    while ( send_queue_.get( buffer_ ) )
    {
        RUDPEventHandler* socket = RUDP()->get_socket_event( buffer_->socket_id() );
        if ( NULL != socket )
        {
            socket->send( buffer_->buf() , buffer_->len() );
        }
        delete buffer_;
        buffer_ =  NULL;
    }

    return 0;
}

bool CSendProcessor::push( const uint8_t* data_ , int32_t len_ , int32_t socket_id_ )
{
    if ( len_ <= 0 || data_ == NULL ) { return false; }
    IOBuffer* buffer_ = new IOBuffer();
    buffer_->push( data_ , len_ , socket_id_ );
    return send_queue_.put( buffer_ );
}


CRecvProcesser::CRecvProcesser( void )
{
    clear();
}

CRecvProcesser::~CRecvProcesser( void )
{

}

void CRecvProcesser::clear( void )
{
    IOBuffer* buffer_ = NULL;
    while ( recv_quque_.get( buffer_ ) )
    {
        if ( NULL == buffer_ ) { continue; }
        delete buffer_;
        buffer_ = NULL;
    }
}

bool CRecvProcesser::push( const uint8_t* data_ , int32_t len_ , int32_t scoket_id_ , uint32_t addr_id_ )
{
    if ( len_ <= 0 || NULL == data_ ) { return false; }
    IOBuffer* buffer_ = new IOBuffer();
    if ( NULL == buffer_ ) { return false; }
    buffer_->push( data_ , len_ , scoket_id_ , addr_id_ );
    return recv_quque_.put( buffer_ );
}

IOBuffer* CRecvProcesser::pop( void )
{
    IOBuffer* buffer_ = NULL;
    recv_quque_.get( buffer_ );
    return buffer_;
}

void CErrorRecvProcesser::push( int32_t socket_id )
{
    error_quque_.put( socket_id );
}

int32_t CErrorRecvProcesser::pop( void )
{
    int32_t scoket_id_ = 0;
    if ( error_quque_.get( scoket_id_ ) )
    {
        return scoket_id_;
    }

    return scoket_id_;
}

void CErrorSendProcesser::push( int32_t socket_id )
{
    error_quque_.put( socket_id );
}

int32_t CErrorSendProcesser::pop( void )
{
    int32_t scoket_id_ = 0;
    if ( error_quque_.get( scoket_id_ ) )
    {
        return scoket_id_;
    }

    return scoket_id_;
}
