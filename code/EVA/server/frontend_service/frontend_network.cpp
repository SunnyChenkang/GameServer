#include "frontend_network.h"
#include "frontend_message.h"

FES_NAMESPACE_BEGIN_DECL

WEBCALLBACKTABLE  CFrontendNetWork::m_WebCallBackFuncTable;
RUDPCALLBACKTABLE CFrontendNetWork::m_RUDPCallBackFuncTable;

CFrontendNetWork::CFrontendNetWork(void)
{
    m_WebCallBackFuncTable.clear();
    m_RUDPCallBackFuncTable.clear();
}

void CFrontendNetWork::InitNetHandler( uint16 RUDPPort , uint16 WEBPort )
{
    // 初始化RUDP;
    RUDPInitNet( RUDPPort );

    // 初始化WEB;
    NLNET::CCallbackServerWebSocket* pWebServer = new ( std::nothrow )NLNET::CCallbackServerWebSocket();
    if ( NULL == pWebServer ) return;
    pWebServer->setConnectionCallback( CallBackWebConnection , this );
    pWebServer->setDisconnectionCallback( CallBackWebDisConnection , this );
    pWebServer->setDefaultCallback( CallBackWebMessage );
    pWebServer->init( WEBPort );

    m_WebCallBackNetBase = pWebServer;

    // 注册消息回调;
    for ( int idx = 0; idx < SS_ARRAYSIZE( RUDPCallBackItems ); idx++ )
    {
        m_RUDPCallBackFuncTable.insert( std::make_pair( RUDPCallBackItems[idx].KeyName  , RUDPCallBackItems[idx].CallBack ) );
    }
    for ( int idx = 0; idx < SS_ARRAYSIZE( WEBCallBackItems ); idx++ )
    {
        m_WebCallBackFuncTable.insert( std::make_pair( WEBCallBackItems[idx].KeyName , WEBCallBackItems[idx].CallBack ) );
    }
}

void CFrontendNetWork::UpdateNetHandler( void )
{
    try {
    // 更新RUDP
    CallBackRUDPMessage();
    // 更新WEB;
    m_WebCallBackNetBase->update();
    }
    catch ( ... )
    {
        
    }
}

void CFrontendNetWork::DestroyNetHandler( void )
{
    // 释放RUDP;
    RUDPDestoryNet();
    // 释放WEB;
    SS_SAFE_DELETE( m_WebCallBackNetBase );
}

void CFrontendNetWork::CallBackWebConnection( NLNET::TSockId from , void* args )
{
//     CClient* pClient = ClientManager.AllocClient( from );
//     if ( NULL != pClient ) return;
// 
//     // 数据异常断开连接;
//     FrontendNetWork.CloseClientNet( from );
}

void CFrontendNetWork::CallBackWebMessage( NLNET::CMessage& message , NLNET::TSockId from , NLNET::CCallbackNetBase& args )
{
    CClientPtr ClientPtr = ClientManager.FindClientWEB( from );
    if ( nullptr == ClientPtr )
    {
        FrontendNetWork.CloseClientNet( from );
        return;
    }
    /// 远程消息;
    HandlerForwardMessage( message , ClientPtr );
}

void CFrontendNetWork::CallBackWebDisConnection( NLNET::TSockId from , void* args )
{
    ClientManager.DeleteClientWEB( from );
}

void CFrontendNetWork::CallBackRUDPMessage( void )
{
    /// 处理异常客户端;
    while ( true )
    {
        SOCKET_ID SocketID = ERROR_RECV_OBJ()->pop();
        if ( SocketID <= 0 ) break;
        CClientPtr ClientPtr = ClientManager.FindClientUDP( SocketID );
        if ( nullptr == ClientPtr ) { break; }
        NLNET::CMessage SendMessage("MSG_OFFLINE");
        ROLE_ID RoleID = ClientPtr->GetRoleID();
        SendMessage.serial( RoleID );
        SS_NETWORK->send( "GSE" , SendMessage );
        ClientManager.DeleteClientUDP( SocketID );
    }

    /// 处理网络底层消息;
    while ( true )
    {
        IOBuffer* pIOBuffer = RECV_OBJ()->pop();
        if ( nullptr == pIOBuffer ) { break; }
        NLNET::CMessage Message;
        Message.fill( pIOBuffer->buf(), pIOBuffer->len() );
        Message.invert();
        SS_SAFE_DELETE( pIOBuffer );
        HandlerForwardMessage( Message , ClientManager.FindClientUDP( pIOBuffer->socket_id() ) );
        SS_SAFE_DELETE( pIOBuffer );
    }
}

PB_CreateRoom PB1;

void CFrontendNetWork::HandlerForwardMessage( NLNET::CMessage& RevcMessage , CClientPtr ClientPtr )
{
    if ( nullptr == ClientPtr )
        return;

    /// 处理WEB本地消息;
    if ( ClientPtr->GetChannelNet() == WEB_CHANNEL )
    {
        auto It = m_WebCallBackFuncTable.find( RevcMessage.getName() );
        if ( It != m_WebCallBackFuncTable.end() ) {
             It->second( RevcMessage , ClientPtr->GetWebSocketID() );
             return;
        }
    }

    /// 处理UDP本地消息;
    if ( ClientPtr->GetChannelNet() == RUDP_CHANNEL )
    {
        auto It = m_RUDPCallBackFuncTable.find( RevcMessage.getName() );
        if ( It != m_RUDPCallBackFuncTable.end() ) {
             It->second( RevcMessage , ClientPtr->GetUDPSocketID() );
             return;
        }
    }

    /// 处理远程消息;
    SS::CJsonMessageCell* pJsonCell = JsonMessageConfig.GetJsonCell< SS::CJsonMessageCell >( RevcMessage.getName() );
    if ( nullptr == pJsonCell ) {
    }
    if ( NULL == pJsonCell )
    {
        ClientManager.DeleteClient( ClientPtr );
        return;
    }

    ROLE_ID RoleID = ClientPtr->GetRoleID();
    NLNET::CMessage SendMessage( pJsonCell->GetName() );
    std::vector< NLMISC::CSString >& FormatList = pJsonCell->m_Format.m_JsonArray;

    /// 填充新消息;
    for ( std::vector< NLMISC::CSString >::iterator it = FormatList.begin() ; it != FormatList.end(); ++it )
    {
        EFormatKind format = ToForMatEnum( *it );
        switch ( format )
        {
        case ROLEID:
        SendMessage.serial( RoleID );
        break;
        case INVALID:
        google::protobuf::Message* pMessage = GetProtoBufMessage( *it );
        if ( NULL == pMessage ) return;
        RevcMessage.serial( pMessage );
        SendMessage.serial( pMessage );
        break;
        }
    }

    /// 转发内容;
    std::vector< NLMISC::CSString >& SendToServiceList = pJsonCell->m_SendToService.m_JsonArray;
    for ( std::vector< NLMISC::CSString >::iterator  it = SendToServiceList.begin(); it != SendToServiceList.end(); ++it )
    {
        if ( *it == "GSE" ) {
        SS_NETWORK->send( ClientPtr->GetGameServiceId() , SendMessage );
        }
        else {
        SS_NETWORK->send( *it , SendMessage );
        }
    }
}
FES_NAMESPACE_END_DECL