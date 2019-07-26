#ifndef FRONTEND_SERVICE_CLIENTMANAGER_H_
#define FRONTEND_SERVICE_CLIENTMANAGER_H_

#include "frontend_def.h"
#include "client.h"

FES_NAMESPACE_BEGIN_DECL

class CClientManager : public NLMISC::CSingleton<CClientManager>
{
public:
    typedef std::map< ROLE_ID   , CClientPtr > ROLECLIENT;
    typedef std::map< SOCKET_ID , ROLE_ID    > UDPCLIENT;
    typedef std::map< TSockId   , ROLE_ID    > WEBCLIENT;

    CClientManager( void );
   ~CClientManager( void ) { };

    /// 分配客户端实体;
    CClientPtr AllocUDPClient( ROLE_ID , SOCKET_ID );
    CClientPtr AllocWebClient( ROLE_ID , TSockId   );

    /// 查找客户端信息;
    CClientPtr FindClientRole( ROLE_ID );
    CClientPtr FindClientWEB ( TSockId );
    CClientPtr FindClientUDP ( SOCKET_ID );

    /// 删除客户端信息;
    void DeleteClient    ( CClientPtr );
    void DeleteClientRole( ROLE_ID   );
    void DeleteClientWEB ( TSockId   );
    void DeleteClientUDP ( SOCKET_ID );

    /// 获取客户端数量;
    uint32 GetClientCount( void ) { return m_RoleClientTable.size(); }

    /// 客户端会话列表;
    SS_PROPERTY( ROLECLIENT , RoleClientTable , private );
    SS_PROPERTY( UDPCLIENT  , UDPClientTable  , private );
    SS_PROPERTY( WEBCLIENT  , WEBClientTable  , private );

private:
    // 连接超时间超;
    CTimer m_ConnectionTimer;
};

FES_NAMESPACE_END_DECL

#define ClientManager FES::CClientManager::instance()

#endif // FRONTEND_SERVICE_CLIENTMANAGER_H_