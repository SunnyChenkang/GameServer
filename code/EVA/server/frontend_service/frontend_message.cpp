#include "frontend_message.h"
#include "client_manager.h"
#include "client.h"
#include "frontend_network.h"

extern NLMISC::CVariable< std::string > VAR_FES_AUTH_SECRET;

FES_NAMESPACE_BEGIN_DECL

bool CallBack_AuthAccount( NLNET::CMessage& Message , CClient* pClient )
{
    try
    {
//         // ÑéÖ¤ÕËºÅ;
//         NLMISC::CSString AuthSecret = VAR_FES_AUTH_SECRET.get();
//         PB_LoginAuthUser LoginAuthUser;
//         Message.serial( &LoginAuthUser );
//         NLMISC::CSString    AuthMd5 = NLMISC::toString( LoginAuthUser.account_id() ) + LoginAuthUser.client_host() + AuthSecret;
//         NLMISC::CHashKeyMD5 Md5 = NLMISC::getMD5( AuthMd5.c_str() );
//         AuthMd5 = Md5.toString();
//         if ( AuthMd5 != LoginAuthUser.client_token() ) return false;
//         pClient->SetAccountID( LoginAuthUser.account_id() );
//         pClient->SetHost( LoginAuthUser.client_host() );
// 
//         // µÇÂ¼ÓÎÏ·;
//         NLNET::CMessage SendMessage("MSG_LOGIN");
//         uint32 AccountID            = pClient->GetAccountID();
//         NLMISC::CSString ClientHost = pClient->GetHost();
//         NLNET::TServiceId ServiceId = NLNET::IService::getInstance()->getServiceId();
//         SendMessage.serial( AccountID );
//         SendMessage.serial( ClientHost );
//         SendMessage.serial( ServiceId );
//         SS_NETWORK->send( "SSE" , SendMessage );
    }
    catch( ... )
    {
        return false;
    }

    return true;
}

void CallBack_S2C( NLNET::CMessage& Message , const std::string& ServiceName , NLNET::TServiceId ServiceID )
{
    ROLE_ID RoleID = 0;
    Message.serial( RoleID );
    CClient* pClient = ClientManager.FindClientRoleID( RoleID );
    if ( NULL == pClient )
    {
        nlinfo( " S2C %s faile ~ " , Message.getName().c_str() );
        return;
    }
    pClient->SendToClient( Message );
}

void CallBack_RUDPLogin(NLNET::CMessage& Message , SOCKET_ID SocketID )
{
    
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

void CallBack_PDSDisconnection( const std::string& , NLNET::TServiceId , void* )
{
    
}

void CallBack_PLSDisconnection( const std::string& , NLNET::TServiceId , void* )
{
    
}

void CallBack_EGSDisconnection( const std::string& , NLNET::TServiceId , void* )
{
    
}

FES_NAMESPACE_END_DECL
