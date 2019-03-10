#include "CConnect.h"
#include <nel/net/inet_address.h>
#include <nel/misc/common.h>

#include <server_share/client_msg_desc.h>
#include <game_share/define_pro.pb.h>
#include <google/protobuf/message.h>
#include "msg/recv_logic.h"
#include "msg/send_logic.h"
#include "CClient.h"
#include "CRobotHelper.h"
#include "CRobotTimer.h"
#include "CCommonLine.h"
#include "CClientMgr.h"


#ifdef NL_OS_WINDOWS
#	define _WIN32_WINDOWS   0x0410
#	ifndef NL_COMP_MINGW
#		define WINVER       0x0400
#		define NOMINMAX
#	endif
#	include <winsock2.h>
#	include <windows.h>
#endif

#ifdef NL_OS_UNIX
#include <sys/ioctl.h>
#endif

using namespace NLNET;
using namespace NLMISC;
using namespace std;

#define SEND_ACK_CMD   1
#define SEND_ACK_PRO   1
#define SEND_ACK_INDEX 4
#define SEND_ACK_LEN ( SEND_ACK_CMD+SEND_ACK_PRO+SEND_ACK_INDEX )
#define ACK_QUEUE_POOL 50
#define UDP_HEARTBETE_TIME ( 1*1000 )
#define UDP_HEARTBETE_LEN ( 8+1+1 )

#define SIO_UDP_CONNRESET _WSAIOW(IOC_VENDOR,12)


CConnect::CConnect( void )
    : m_session( 0 )
    , m_Limitiem( 0 )
    , m_BuffIndex( 0 )
{
    m_AckPool.clear();

    std::string LoginHost = CCommonLine::GetInstance()->GetServerHost();
    short       LoginPort = CCommonLine::GetInstance()->GetServerPort();

    m_UdpConnect.connect( CInetAddress( LoginHost , LoginPort ) );

#ifdef NL_OS_UNIX
    u_long mode = 1;
    ioctl( m_UdpConnect.UdpSock.descriptor() ,FIONBIO , &mode);
#endif

#ifdef NL_OS_WINDOWS
    u_long mode = 1;
    ioctlsocket( m_UdpConnect.UdpSock.descriptor() , FIONBIO , &mode );
#endif

    m_MsgCountTime = CTime::getSecondsSince1970();
    m_Random.srand( m_MsgCountTime );

    m_RecvLogic = new( std::nothrow ) RecvLogic( this );
    m_SendLogic = new( std::nothrow ) SendLogic( this );
}

CConnect::~CConnect( void )
{
    m_HeartBeat.reset();
}

bool CConnect::SendMsg( string Name , google::protobuf::Message* Msg )
{
    CClient* pClient = dynamic_cast< CClient* >( this );
    if ( NULL == pClient ) {
        return false;
    }
    uint check_random = 0;
    sint nCurTime = NLMISC::CTime::getSecondsSince1970();

    bool b_state = pClient->IsOnlineState();
    if ( pClient->GetRoleUID() == CommonLine->m_RobotUID )
    {
        nlwarning( " Start robot send msg uid = %d, name:%s",pClient->GetRoleUID(), Name.c_str() );
    }

    if ( nCurTime - m_Limitiem < LIMIT_SEND_TIME && pClient->IsOnlineState() ) {
        return false;
    }

    if ( pClient->GetRoleUID() == CommonLine->m_RobotUID )
    {
        nlwarning( " -------------------End robot send msg uid = %d, name:%s",pClient->GetRoleUID(),Name.c_str() );
    }

    if ( NULL != Msg ) 
    {
        string strBuff = Msg->SerializeAsString();
        uint32 len  = strBuff.length();
        uint8* data = new uint8[4];
        uintTobytes(len , data );
        DEF::CHECK_SUM crc= crc32( 0 , (const uint8*)data , sizeof(int)  );
        safe_delete_array( data );
        if (len  > 0 )
        {
            crc = crc32( crc , (const uint8 *)strBuff.c_str(), strBuff.length() );
        }
        check_random = m_Random.rand() + crc;
     }
    else
    {
        int* msgBuffer = new int;
        memset( msgBuffer , 0 , sizeof( int ) );
        DEF::CHECK_SUM crc = crc32( 0, (const uint8 *)msgBuffer, sizeof(int) );
        check_random = m_Random.rand() + crc;
    }

    NLNET::CMessage MsgOut( Name );
    MsgSession Session;
    Session.set_index( GetBuffIndex() );
    Session.set_check( check_random );
    Session.set_session( m_session );

    MsgOut.serial( &Session );

    if ( NULL != Msg ) {
        MsgOut.serial( Msg );
    }
    else {
        int test = 0;
        MsgOut.serial(test);
    }


    try
    {
        if ( IsTCPProtocol( Name ) )
        {
            if ( !TCPConnect() ) {
                return false;
            }

            //m_TcpConnect.send( MsgOut );
        }
        else
        {
            UDPToServerMsg ToServerBuff;
            uint8* buff = const_cast< uint8* >( MsgOut.buffer() ) ;
            ToServerBuff.AddBuffer( buff , MsgOut.length() );

            uint32 len  = ToServerBuff.length();
            m_UdpConnect.send( ToServerBuff.buffer() , len );
            //VAR_SECOND_MSG.set( VAR_SECOND_MSG.get()+1 );
            ClientMgr->SetSecondSendMsgCount();
        }

        m_Limitiem = nCurTime;
    }
    catch( std::exception what )
    {

    }

    OnUDPUpdate();

    return false;
}

bool CConnect::TCPConnect( void )
{
    std::string LoginHost = CCommonLine::GetInstance()->GetServerHost();
    short       LoginPort = CCommonLine::GetInstance()->GetServerPort();

    // 连接TCP网络;
    return TCPConnect( LoginHost , LoginPort );
}

bool CConnect::TCPConnect( std::string Host , short Port )
{
    try
    {
        CInetAddress Address( Host , Port );
        //m_TcpConnect.disconnect();
        //m_TcpConnect.connect( Address );

        return false;//.connected();
    }
    catch( std::exception what )
    {
        nlwarning( "connect tcp exception %s;" , what.what() );
    }

    return false;
}

void CConnect::TCPDisconnect( void )
{
    try
    {
        //if ( m_TcpConnect.connected() )
        //{
        //    m_TcpConnect.disconnect();
        //}
    }
    catch( std::exception what )
    {
        nlwarning( " disconnect tcp socket %s " , what.what() );
    }
}

void CConnect::SendHeartbeatMsg( void )
{
    uint32 bufflen = UDP_HEARTBETE_LEN;
    uint8* buff    = new( std::nothrow ) uint8[ bufflen ];
    if( NULL == buff )
        return;

    buff[ 0 ] = PROTO_CMD;
    buff[ 1 ] = PROTO_CMD_HEARTBEAT;

    llongtobyte( m_session , buff + 2 );

    try
    {
        m_UdpConnect.send( buff , bufflen );
    }
    catch( std::exception what )
    {

    }

    safe_delete_array( buff );
}

void CConnect::OnUDPUpdate( void )
{
    //uint32 curr_time = CTime::getSecondsSince1970();
    //if ( m_Limitiem + SENDMSGLIMITTIME > curr_time )
    //{
    //    m_SendLogic->PlayerAddMoney();
    //    m_Limitiem = curr_time;
    //    return;
    //}

    uint32 Len = 2*1024;
    uint8 *Packet = new( std::nothrow ) uint8[ Len ];

    try
    {
        m_UdpConnect.receive( Packet , Len );
    }
    catch( std::exception what )
    {
        safe_delete_array( Packet );
        return;
    }

    if ( Len < 5 )
    {
        safe_delete_array( Packet );
        return;
    }

    int CurrReadSize = 0;
    // 解析长度;
    uint8* headBytes = new( std::nothrow ) uint8[ sizeof(uint32) ];
    if( NULL == headBytes ) {
        return;
    }

    memcpy( headBytes , Packet , sizeof( uint32 ) );
    uint32 headLen = bytesTouint( headBytes );
    CurrReadSize += sizeof( uint32 );
    if ( (Len-CurrReadSize) < sizeof( uint32 ) ) 
    {
        safe_delete_array( headBytes );
        return;
    }

    uint8* headDataBytes = new ( std::nothrow )uint8[ headLen ];
    if ( NULL == headDataBytes ) {
        return;
    }

    uint8* OffPacket = Packet + CurrReadSize;
    memcpy( headDataBytes, OffPacket, headLen );

    MsgDataHead msg_head;
    msg_head.ParseFromArray( headDataBytes, headLen );

    // 检查ACK重复;
    if ( std::find( m_AckPool.begin() , m_AckPool.end() , msg_head.ack_idx() ) != m_AckPool.end() )
    {
        safe_delete_array( headBytes );
        safe_delete_array( Packet );
        safe_delete_array( headDataBytes );
        return;
    }

    if ( m_AckPool.size() >= ACK_QUEUE_POOL )
    {
        m_AckPool.pop_front();
    }

    m_AckPool.push_back( msg_head.ack_idx() );

    CurrReadSize += headLen;

    // 解析数据包;
    OffPacket = Packet + CurrReadSize;
    uint32 CurrMsgLen = 0;
    NLNET::CMessage UdpMemStream;

    while ( CurrReadSize<Len )
    {
        /// 解析消息体 长度
        memcpy( headBytes , OffPacket , sizeof( uint32 ) );
        CurrMsgLen = htonl(bytesTouint( headBytes ));
        CurrReadSize += sizeof( uint32 );
        OffPacket += sizeof( uint32 );


        /// 填充消息数据
        UdpMemStream.fill( OffPacket, CurrMsgLen );
        CurrReadSize += CurrMsgLen;
        OffPacket += CurrMsgLen;

        UdpMemStream.invert();
        GetRecvLogic()->HandleMessage( UdpMemStream );
    }

    safe_delete_array( Packet );
}

void CConnect::OnTCPUpdate( void )
{
    //// RECV TCP;
    //if ( !m_TcpConnect.connected() )
    //    return;

    //if( !m_TcpConnect.IsAvailable() )
    //    return;

    //NLNET::TSockId  TcpSocketID;
    //NLNET::CMessage TcpMemStream("" , true);
    //m_TcpConnect.ReceiveBuff( TcpMemStream , TcpSocketID );

    //GetRecvLogic()->HandleMessage( TcpMemStream );
}

bool CConnect::IsTCPProtocol( std::string& name )
{
    return ( false /*NULL != MsgDesc.GetTCPMsgLeaf(  name )*/ ) ;
}

bool CConnect::IsUDPProtocol( std::string& name )
{
    return ( NULL != MsgDesc.GetUDPMsgLeaf( name ) );
}

void CConnect::SetRandomSeed( uint seed )
{
    m_BuffIndex = 0;
    m_Random.srand( seed );
}

