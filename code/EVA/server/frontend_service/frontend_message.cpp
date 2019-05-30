#include "frontend_message.h"
#include "client_manager.h"
#include "client.h"
#include "frontend_network.h"

extern NLMISC::CVariable< std::string > VAR_FES_AUTH_SECRET;

FES_NAMESPACE_BEGIN_DECL

bool CallBack_AuthAccount( NLNET::CMessage& Message , CClient* pClient )
{
    // 验证账号;
    NLMISC::CSString AuthSecret = VAR_FES_AUTH_SECRET.get();
    PB_LoginAuthUser LoginAuthUser;
    Message.serial( &LoginAuthUser );
    NLMISC::CSString    AuthMd5 = NLMISC::toString( LoginAuthUser.role_id() ) + LoginAuthUser.client_host() + AuthSecret;
    NLMISC::CHashKeyMD5 Md5     = NLMISC::getMD5( (const uint8*)AuthMd5.c_str() , AuthMd5.length() );
    if ( Md5.toString() != LoginAuthUser.client_token() ) return false;

    pClient->SetRoleID( LoginAuthUser.role_id() );
    pClient->SetHost  ( LoginAuthUser.client_host() );

    // 登录游戏;
    PB_UserLogin UserLogin;
    ROLE_ID RoleID              = pClient->GetRoleID();
    NLMISC::CSString ClientHost = pClient->GetHost();

    UserLogin.set_role_id( RoleID );
    UserLogin.set_client_host( ClientHost );
    UserLogin.set_frontend_service_id( NLNET::IService::getInstance()->getServiceId().get() );
    NLNET::CMessage SendMessage("MSG_LOGIN");
    SendMessage.serial( &UserLogin );
    SS_NETWORK->send( "SSE" , SendMessage );
    return true;
}

void CallBack_S2C( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceID )
{
    ROLE_ID RoleID = 0;
    Message.serial( RoleID );
    CClient* pClient = ClientManager.FindClientRoleID( RoleID );
    if ( NULL == pClient ) return;

    uint32 BufferLen = 0;
    Message.serial( BufferLen );
    Message.lockSubMessage( BufferLen );
    NLNET::CMessage SendMessage;
    SendMessage.assignFromSubMessage( Message );
    Message.unlockSubMessage();
    pClient->SendToClient( SendMessage );
}

void CallBack_LoginSucceed( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceID )
{
    ROLE_ID RoleID = 0;
    NLNET::TServiceId GameServiceId = NLNET::TServiceId::InvalidId;
    Message.serial( RoleID );
    Message.serial( GameServiceId );
    CClient* pClient = ClientManager.FindClientRoleID( RoleID );
    if ( NULL == pClient ) return;

    pClient->SetRoleID( RoleID );
    pClient->SetGameServiceId( GameServiceId );
}

void CallBack_ClientDelete( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceId )
{
    ROLE_ID RoleID = 0;
    NLNET::TServiceId FesServiceId = NLNET::TServiceId::InvalidId;
    Message.serial( RoleID );
    Message.serial( FesServiceId );

    //忽律自己服务器;
    if ( FesServiceId == NLNET::IService::getInstance()->getServiceId() ) return;
    CClient* pClient = ClientManager.FindClientRoleID( RoleID );
    if ( NULL == pClient ) return;
    ClientManager.DeleteClient( pClient );
}

void CallBack_RUDPLogin(NLNET::CMessage& Message , SOCKET_ID SocketID )
{
    PB_LoginAuthUser PBLoginAuthUser;
    Message.serial( &PBLoginAuthUser );
    NLMISC::CSString    strAuthMD5 = NLMISC::toString( PBLoginAuthUser.role_id() ) + PBLoginAuthUser.client_host() + NLMISC::toString( PBLoginAuthUser.role_kind() ) + VAR_FES_AUTH_SECRET.get();
    NLMISC::CHashKeyMD5 strMD5     = NLMISC::getMD5( (const uint8*)strAuthMD5.c_str() , strAuthMD5.length() );
    strAuthMD5 = NLMISC::toUpper( strMD5.toString() );
    if ( strAuthMD5 != PBLoginAuthUser.client_token() )
        return;

    CClient* pClient = ClientManager.AllocClient( PBLoginAuthUser.role_id() , SocketID );
    if ( NULL == pClient )  return;
    pClient->SetRoleID( PBLoginAuthUser.role_id() );
    pClient->SetHost( PBLoginAuthUser.client_host() );

    PB_UserLogin PBUserLogin;
    ROLE_ID RoleID                  = pClient->GetRoleID();
    NLMISC::CSString ClientHost     = pClient->GetHost();
    NLNET::TServiceId FesServiceId  = NLNET::IService::getInstance()->getServiceId();
    PBUserLogin.set_role_id( RoleID );
    PBUserLogin.set_role_kind( PBLoginAuthUser.role_kind() );
    PBUserLogin.set_client_host( ClientHost );
    PBUserLogin.set_frontend_service_id( FesServiceId.get() );

    // 其它服务关闭客户端;
    NLNET::CMessage SendMessage1("MSG_CLIENT_DELETE");
    SendMessage1.serial( RoleID );
    SendMessage1.serial( FesServiceId );
    SS_NETWORK->send( "FES" , SendMessage1 );

    // 登录游戏;
    NLNET::CMessage SendMessage2("MSG_LOGIN");
    SendMessage2.serial( &PBUserLogin );
    SS_NETWORK->send( "SSE" , SendMessage2 );
}

void CallBack_WebLogin(NLNET::CMessage& Message , NLNET::TSockId SocketID , NLNET::CCallbackNetBase&)
{
    CClient* pClient = ClientManager.FindClient( SocketID );
    if ( NULL == pClient ){ return; }

    if ( !CallBack_AuthAccount( Message , pClient ) )
    {
        FrontendNetWork.CloseClientNet( SocketID );
        return;
    }
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
