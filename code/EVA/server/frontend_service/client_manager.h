#ifndef FRONTEND_SERVICE_CLIENTMANAGER_H_
#define FRONTEND_SERVICE_CLIENTMANAGER_H_

#include "frontend_def.h"

FES_NAMESPACE_BEGIN_DECL

class CClient;
class CClientManager : public NLMISC::CSingleton<CClientManager>
{
public:
    typedef std::map< SOCKET_ID , CClient* >        RUDPSOCKETTABLE;
    typedef std::map< NLNET::TSockId , CClient* >   WEBSOCKETTABLE;
    typedef std::map< ROLE_ID , CClient* >          CLIENTTABLE;

    CClientManager( void );
   ~CClientManager( void ) { };

    // 分配一个客户端;
    CClient* AllocClient( ROLE_ID , SOCKET_ID );
    CClient* AllocClient( NLNET::TSockId );

    // 查找一个客户端;
    CClient* FindClient( SOCKET_ID );
    CClient* FindClient( NLNET::TSockId& );

    // 账号查询一个客户端;
    CClient* FindClientRoleID( ROLE_ID );

    // 删除一个客户端;
    void DeleteClient( CClient* );
    void DeleteClient( SOCKET_ID );
    void DeleteClient( NLNET::TSockId& );

    // 获取客户端数量;
    uint32 GetClientCount     ( void ) { return GetRUDPClientCount() + GetWEBClientCount(); }
    uint32 GetRUDPClientCount ( void ) { return m_RUDPSocketTable.size(); }
    uint32 GetWEBClientCount  ( void ) { return m_WEBSocketTable.size();  }

    // RUDP客户端列表;
    SS_PROPERTY( RUDPSOCKETTABLE , RUDPSocketTable , private );
    // WEB 客户端列表;
    SS_PROPERTY( WEBSOCKETTABLE  , WEBSocketTable  , private );
    // 账号客户端列表;
    SS_PROPERTY( CLIENTTABLE     , ClientTable     , private );

private:
    // 连接超时间超;
    CTimer m_ConnectionTimer;
};

FES_NAMESPACE_END_DECL

#define ClientManager FES::CClientManager::instance()

#endif // FRONTEND_SERVICE_CLIENTMANAGER_H_