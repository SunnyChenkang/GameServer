#ifndef CRobotTimer_h__
#define CRobotTimer_h__
#include <game_share/timer.h>

class CConnect;
class CClient;

class ClientEventTimer : public CTimerEvent
{
    NL_INSTANCE_COUNTER_DECL( ClientEventTimer );
public:
    ClientEventTimer( CClient* pClient , std::string LuaName , std::string FunName , int Time )
        : m_Client( pClient )
        , m_Time( Time )
        , m_UseFunName( FunName )
        , m_UseLuaName( LuaName )
    {
    }

    void timerCallback( CTimer* owner );

private:
    int             m_Time;
    std::string     m_UseLuaName;
    std::string     m_UseFunName;
    CClient*        m_Client;
};


class ClientBlackJackEventTimer : public CTimerEvent
{
    NL_INSTANCE_COUNTER_DECL( ClientBlackJackEventTimer );
public:
    ClientBlackJackEventTimer( CClient* pClient , std::string LuaName , std::string FunName , int Time )
        : m_Client( pClient )
        , m_Time( Time )
        , m_UseFunName( FunName )
        , m_UseLuaName( LuaName )
    {
    }

    void timerCallback( CTimer* owner );

private:
    int             m_Time;
    std::string     m_UseLuaName;
    std::string     m_UseFunName;
    CClient*        m_Client;
};


class ClientSlotEventTimer : public CTimerEvent
{
    NL_INSTANCE_COUNTER_DECL( ClientSlotEventTimer );
public:
    ClientSlotEventTimer( CClient* pClient , std::string LuaName , std::string FunName , int Time )
        : m_Client( pClient )
        , m_Time( Time )
        , m_UseFunName( FunName )
        , m_UseLuaName( LuaName )
    {
    }

    void timerCallback( CTimer* owner );

private:
    int             m_Time;
    std::string     m_UseLuaName;
    std::string     m_UseFunName;
    CClient*        m_Client;
};

class ClientTexaspokerEventTimer : public CTimerEvent
{
    NL_INSTANCE_COUNTER_DECL( ClientTexaspokerEventTimer );
public:
    ClientTexaspokerEventTimer( CClient* pClient , std::string LuaName , std::string FunName , int Time )
        : m_Client( pClient )
        , m_Time( Time )
        , m_UseFunName( FunName )
        , m_UseLuaName( LuaName )
    {
    }

    void timerCallback( CTimer* owner );

private:
    int             m_Time;
    std::string     m_UseLuaName;
    std::string     m_UseFunName;
    CClient*        m_Client;
};

class ClientMahJongEventTimer : public CTimerEvent
{
    NL_INSTANCE_COUNTER_DECL( ClientMahJongEventTimer );
public:
    ClientMahJongEventTimer( CClient* pClient , std::string LuaName , std::string FunName , int Time )
        : m_Client( pClient )
        , m_Time( Time )
        , m_UseFunName( FunName )
        , m_UseLuaName( LuaName )
    {
    }

    void timerCallback( CTimer* owner );

private:
    int             m_Time;
    std::string     m_UseLuaName;
    std::string     m_UseFunName;
    CClient*        m_Client;
};

class ClientAutoTimer : public CTimerEvent
{
    NL_INSTANCE_COUNTER_DECL( ClientAutoTimer );

public:
    ClientAutoTimer(void){};

    void timerCallback( CTimer* owner );
};

class ClientTMailTimer : public CTimerEvent
{
    NL_INSTANCE_COUNTER_DECL( ClientTMailTimer );

public:
    ClientTMailTimer(void){};

    void timerCallback( CTimer* owner );
};

class ClientMsgTimer : public CTimerEvent
{
    NL_INSTANCE_COUNTER_DECL( ClientMsgTimer );

public:
    ClientMsgTimer(void){};

    void timerCallback( CTimer* owner );
};

#endif // CRobotTimer_h__