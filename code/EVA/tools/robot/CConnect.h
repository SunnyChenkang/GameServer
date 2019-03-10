#ifndef CConnect_h__
#define CConnect_h__
#include <game_share/game_def.h>
#include <game_share/udp_msg.h>
#include <game_share/timer.h>
#include <nel/net/callback_client.h>
#include <nel/net/udp_sim_sock.h>
#include <nel/misc/random.h>

class RecvLogic;
class SendLogic;

class CConnect
{
public:
    CConnect( void );
    virtual ~CConnect( void );

    // 发送消息;
    virtual bool SendMsg( std::string Name , google::protobuf::Message* Msg = NULL );

    // 发送玩家心跳;
    virtual void SendHeartbeatMsg( void );

    // 获取TCP连接;
    //NLNET::CCallbackClient& GetTCPConnect( void ) {
    //    return m_TcpConnect;
    //}

    // 获取UDP连接;
     NLNET::CUdpSimSock&   GetUDPConnect( void ) {
         return m_UdpConnect;
     }

    // 接受端;
    RecvLogic* GetRecvLogic( void ){
        return m_RecvLogic;
    }

    // 发送端;
    SendLogic* GetSendLogic( void ){
        return m_SendLogic;
    }

    // 断开TCP;
    void TCPDisconnect( void );

    // 回话ID;
    PROPERTY( DEF::CLIENT_SESSION , session );

    // 种子;
    void SetRandomSeed( uint seed );


    uint GetBuffIndex(){
        return m_BuffIndex++;
    }

    uint32 GetSendMsgLimitTime() { return m_Limitiem; }

protected:
    // 更新UDP;
    void OnUDPUpdate( void );
    // 更新TCP;
    void OnTCPUpdate( void );

private:
    bool TCPConnect( void );
    bool TCPConnect( std::string , short );
    bool IsTCPProtocol( std::string& name );
    bool IsUDPProtocol( std::string& name );

private:
    //NLNET::CCallbackClient m_TcpConnect;
    NLNET::CUdpSimSock     m_UdpConnect;
    RecvLogic*             m_RecvLogic;
    SendLogic*             m_SendLogic;
    std::deque< uint32 >   m_AckPool;
    CTimer                 m_HeartBeat;
    uint32                 m_MsgCountTime;
    uint                   m_BuffIndex;
    uint32                 m_Limitiem;
    NLMISC::CRandom        m_Random;

};

#endif // CConnect_h__