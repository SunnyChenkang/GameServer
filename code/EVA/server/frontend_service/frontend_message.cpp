#include "frontend_message.h"
#include "client_manager.h"
#include "client.h"
#include "frontend_network.h"

extern NLMISC::CVariable< std::string > VAR_FES_AUTH_SECRET;

FES_NAMESPACE_BEGIN_DECL

void CallBack_S2C( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceID )
{
    ROLE_ID RoleID = 0;
    Message.serial( RoleID );
    CClientPtr ClientPtr = ClientManager.FindClientRole( RoleID );
    if ( nullptr == ClientPtr ) { return; }

    uint32 BufferLen = 0;
    Message.serial( BufferLen );
    Message.lockSubMessage( BufferLen );
    NLNET::CMessage SendMessage;
    SendMessage.assignFromSubMessage( Message );
    Message.unlockSubMessage();
    ClientPtr->SendToClient( SendMessage );
}

void CallBack_LoginSucceed( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceID )
{
    ROLE_ID RoleID = 0;
    NLNET::TServiceId GameServiceId = NLNET::TServiceId::InvalidId;
    Message.serial( RoleID );
    Message.serial( GameServiceId );
    CClientPtr ClientPtr = ClientManager.FindClientRole( RoleID );
    if ( nullptr == ClientPtr ) { return; }

    ClientPtr->SetRoleID( RoleID );
    ClientPtr->SetGameServiceId( GameServiceId );
}

void CallBack_ClientDelete( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    ROLE_ID RoleID = 0;
    NLNET::TServiceId FesServiceId = NLNET::TServiceId::InvalidId;
    Message.serial( RoleID );
    Message.serial( FesServiceId );
    if ( FesServiceId == NLNET::IService::getInstance()->getServiceId() ) { return; }

    CClientPtr ClientPtr = ClientManager.FindClientRole( RoleID );
    if ( nullptr == ClientPtr ) { return; }
    ClientManager.DeleteClient( ClientPtr );
}

void CallBack_RUDPLogin(NLNET::CMessage& Message , SOCKET_ID SocketID )
{
    /// 验证客户端登录;
    PB_LoginAuthUser PBLoginAuthUser;
    Message.serial( &PBLoginAuthUser );
    NLMISC::CSString    AuthMD5 = NLMISC::toString( PBLoginAuthUser.role_id() ) + PBLoginAuthUser.client_host() + NLMISC::toString( PBLoginAuthUser.role_kind() ) + VAR_FES_AUTH_SECRET.get();
    AuthMD5 = NLMISC::toUpper( NLMISC::getMD5( (const uint8*)AuthMD5.c_str() , AuthMD5.length() ).toString() );
    if ( !AuthMD5.icompare( PBLoginAuthUser.client_token() ))
    {
        nlinfo( " client login auth fails ... " );
        return;
    }

    ROLE_ID    RoleID       = PBLoginAuthUser.role_id();
    uint32     RoleKind     = PBLoginAuthUser.role_kind();
    CSString   ClientHost   = PBLoginAuthUser.client_host();
    TServiceId FesServiceID = IService::getInstance()->getServiceId();

    // 其它服务关闭客户端;
    NLNET::CMessage SendMessage1("MSG_CLIENT_DELETE");
    SendMessage1.serial( RoleID );
    SendMessage1.serial( FesServiceID );
    SS_NETWORK->send( "FES" , SendMessage1 );

    /// 产生客户端实体;
    CClientPtr ClientPtr = ClientManager.AllocUDPClient( PBLoginAuthUser.role_id() , SocketID );
    if ( nullptr == ClientPtr ) { return; }
    ClientPtr->SetRoleID( RoleID );
    ClientPtr->SetHost( ClientHost );

    // 登录游戏;
    PB_UserLogin PBUserLogin;
    PBUserLogin.set_role_id( RoleID );
    PBUserLogin.set_role_kind( RoleKind );
    PBUserLogin.set_client_host( ClientHost );
    PBUserLogin.set_frontend_service_id( FesServiceID.get() );
    NLNET::CMessage SendMessage2("MSG_LOGIN");
    SendMessage2.serial( &PBUserLogin );
    SS_NETWORK->send( "SSE" , SendMessage2 );
}

void CallBack_WebLogin(NLNET::CMessage& Message , NLNET::TSockId SocketID )
{

}

void CallBack_SSEDisconnection( const std::string& , NLNET::TServiceId , void* )
{

}

void CallBack_GSEDisconnection( const std::string& , NLNET::TServiceId , void* )
{

}

void CallBack_PSEDisconnection( const std::string& , NLNET::TServiceId , void* )
{

}

FES_NAMESPACE_END_DECL
