#ifndef GAME_SHARE_UDP_MSG_H
#define GAME_SHARE_UDP_MSG_H

#include <nel/misc/mem_stream.h>
#include "define_sys.pb.h"

class UDPToServerMsg : public NLMISC::CMemStream
{
public:
    UDPToServerMsg():m_ControlFlag(0)
    {
        clear();
        serial (m_ControlFlag);     //  协议控制位
    }

    void  SetControlFlag( TUdpControlFlag flag )
    {
        m_ControlFlag |= flag;
        poke(m_ControlFlag,0);
    }

    void ClearControlFlag( TUdpControlFlag flag )
    {
        m_ControlFlag &= ~uint8(flag);
        poke(m_ControlFlag,0);
    }

    void AddBuffer(uint8 *buf, uint len)
    {
        serialBuffer(buf,len);
    }

private:

    uint8    m_ControlFlag; 
};

class UDPToClientMsg : public NLMISC::CMemStream
{
public:
    UDPToClientMsg()
    {
        reset();
    }

    void reset()
    {
        clear();
        m_DataHead.Clear();
    }

    void SetControlFlag( TUdpControlFlag flag_idx )
    {
        m_DataHead.set_control_flag( m_DataHead.control_flag() | flag_idx );
    }

    void ClearControlFlag( TUdpControlFlag flag_idx )
    {
        uint32  flag_mask = flag_idx;
        flag_mask = ~flag_mask;

        m_DataHead.set_control_flag( m_DataHead.control_flag() & flag_mask );
    }

    void SetControlCmd( TUdpControlCmd cmd )    { m_DataHead.set_control_cmd( cmd ); }
    void SetAckIdx( uint32 ack_idx )            { m_DataHead.set_ack_idx( ack_idx );  }
    void SetClientMsgIdx( uint32 msg_idx )      { m_DataHead.set_msg_idx( msg_idx );  }
    void FillStreamHead();

    void AddBuffer(uint8 *buf, uint32 len);

private:

    MsgDataHead   m_DataHead;
};

class UDPCommand : public NLMISC::CMemStream
{
public:
    UDPCommand( TUdpControlCmd cmd ):m_ControlFlag(PROTO_CMD),m_Command(cmd)
    {
        clear();
        serial (m_ControlFlag);     //  协议控制位
        serial (m_Command);         //  命令
    }

    void  SetControlFlag( TUdpControlFlag flag )
    {
        m_ControlFlag |= flag;
        poke(m_ControlFlag, 0);
    }

    void ClearControlFlag( TUdpControlFlag flag )
    {
        m_ControlFlag &= ~uint8(flag);
        poke(m_ControlFlag, 0);
    }

    void  SetCommand( TUdpControlCmd cmd )
    {
        m_Command = cmd;
        poke(m_Command, 1);
    }

private:

    uint8    m_ControlFlag; 
    uint8    m_Command;
};



#endif
