#include "frontend_network.h"
#include "client.h"
#include "client_manager.h"
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
    // 更新RUDP
    CallBackRUDPMessage();
    // 更新WEB;
    m_WebCallBackNetBase->update();
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
    CClient* pClient = ClientManager.AllocClient( from );
    if ( NULL != pClient ) return;

    // 数据异常断开连接;
    FrontendNetWork.CloseClientNet( from );
}

void CFrontendNetWork::CallBackWebMessage( NLNET::CMessage& message , NLNET::TSockId from , NLNET::CCallbackNetBase& args )
{
    CClient* pClient = ClientManager.FindClient( from );
    if ( NULL == pClient )
    {
        FrontendNetWork.CloseClientNet( from );
        return;
    }
    // 本地消息;
    WEBCALLBACKTABLE::iterator it = m_WebCallBackFuncTable.find( message.getName() );
    if ( it != m_WebCallBackFuncTable.end() )
    {
        it->second( message , from , args );
        return;
    }
    // 转发消息;
    HandlerForwardMessage( message , pClient );
}

void CFrontendNetWork::CallBackWebDisConnection( NLNET::TSockId from , void* args )
{
    ClientManager.DeleteClient( from );
}

void CFrontendNetWork::CallBackRUDPMessage( void )
{
    do // 处理异常客户端;
    {
        SOCKET_ID SocketID = ERROR_RECV_OBJ()->pop();
        if ( SocketID <= 0 ) break;
        ClientManager.DeleteClient( SocketID );
    }
    while ( true );

    do // 处理客户端消息;
    {
        IOBuffer* pIOBuffer = RECV_OBJ()->pop();
        if ( NULL == pIOBuffer ) break;
        NLNET::CMessage IOMessage;
        IOMessage.fill( pIOBuffer->buf() , pIOBuffer->len() );
        IOMessage.invert();
        SOCKET_ID SocketID = pIOBuffer->socket_id();
        SS_SAFE_DELETE( pIOBuffer );
        RUDPCALLBACKTABLE::iterator it = m_RUDPCallBackFuncTable.find( IOMessage.getName() );
        if ( it != m_RUDPCallBackFuncTable.end() )
        {
            it->second( IOMessage , SocketID );
        }
        else
        {
            HandlerForwardMessage( IOMessage , ClientManager.FindClient( SocketID ) );
        }
    }
    while( true );
}

void CFrontendNetWork::HandlerForwardMessage( NLNET::CMessage& RevcMessage , CClient* pClient )
{
    if ( NULL == pClient ) return;

    SS::CJsonFesMessageCell* pJsonCell = JsonFesMessage.GetJsonCell< SS::CJsonFesMessageCell >( RevcMessage.getName() );
    if ( NULL == pJsonCell )
    {
        ClientManager.DeleteClient( pClient );
        return;
    }

    ROLE_ID RoleID = pClient->GetRoleID();
    NLNET::CMessage SendMessage;

    // 填充数据结构;
    std::vector< NLMISC::CSString >& JsonArray = pJsonCell->GetFormat().GetJsonArray();
    for ( std::vector<NLMISC::CSString>::iterator It = JsonArray.begin(); It != JsonArray.end(); ++It )
    {
        EFormatKind format = ToForMatEnum( *It );
        switch ( format )
        {
        case FORMAT_PID:
            SendMessage.serial( RoleID );
            break;
        case FORMAT_INVALID:
            const google::protobuf::Descriptor* pDescriptor = google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName( *It );
            if ( NULL == pDescriptor ) return;
            const google::protobuf::Message* pProtoBuffer = google::protobuf::MessageFactory::generated_factory()->GetPrototype( pDescriptor );
            if ( NULL == pProtoBuffer ) return;
            google::protobuf::Message* pMessage = pProtoBuffer->New();
            RevcMessage.serial( pMessage );
            SendMessage.serial( pMessage );
            break;
        }
    }
    // 转发消息;
    JsonArray = pJsonCell->GetSendToService().GetJsonArray();
    for ( std::vector< NLMISC::CSString >::iterator It = JsonArray.begin(); It != JsonArray.end(); ++It )
    {
         SS_NETWORK->send( *It , SendMessage );
    }
}

FES_NAMESPACE_END_DECL