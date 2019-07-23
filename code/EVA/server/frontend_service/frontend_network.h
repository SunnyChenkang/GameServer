#ifndef FRONTEND_SERVICE_NETHANDLER_H_
#define FRONTEND_SERVICE_NETHANDLER_H_

#include "frontend_def.h"
#include "client.h"
#include "client_manager.h"

FES_NAMESPACE_BEGIN_DECL

typedef std::map< std::string , TWEBCallback >  WEBCALLBACKTABLE;
typedef std::map< std::string , TRUDPCallback>  RUDPCALLBACKTABLE;

class CClient;

class CFrontendNetWork : public NLMISC::CSingleton< CFrontendNetWork >
{
public:
    CFrontendNetWork( void );
   ~CFrontendNetWork( void ){ };

    // 初始化网络库;
    void InitNetHandler( uint16 , uint16 );
    // 更新网络库;
    void UpdateNetHandler( void );
    // 释放网络库;
    void DestroyNetHandler( void );
    // 关闭客户端连接;
    void CloseClientNet( NLNET::TSockId SocketID ) { m_WebCallBackNetBase->disconnect( SocketID ); }
    void CloseClientNet( SOCKET_ID SocketID )      { ERROR_SEND_OBJ()->push( SocketID ); }

    // 获取WEB连接实例;
    NLNET::CCallbackNetBase* GetWebNetBase( void ) { return m_WebCallBackNetBase; }

    /**************************************WEB连接处理*****************************************/;
private:
    // 处理连接;
    static void CallBackWebConnection( NLNET::TSockId, void* );
    // 处理消息;
    static void CallBackWebMessage( NLNET::CMessage&, NLNET::TSockId , NLNET::CCallbackNetBase& );
    // 处理断开;
    static void CallBackWebDisConnection( NLNET::TSockId , void* );

    /**************************************UDP连接处理*****************************************/;
private:
    // 处理连接;
    void CallBackRUDPConnection( void ) { };
    // 处理消息;
    void CallBackRUDPMessage( void );


private:
    // 转发消息;
    static void HandlerForwardMessage( NLNET::CMessage& , CClientPtr );

private:
    NLNET::CCallbackNetBase*    m_WebCallBackNetBase;       // WEB接口;
    static WEBCALLBACKTABLE     m_WebCallBackFuncTable;     // WEB本地消息回调;
    static RUDPCALLBACKTABLE    m_RUDPCallBackFuncTable;    // RUDP本地消息回调;
};

#define FrontendNetWork FES::CFrontendNetWork::instance()

FES_NAMESPACE_END_DECL

#endif // FRONTEND_SERVICE_NETHANDLER_H_