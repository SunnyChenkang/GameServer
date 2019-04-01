#ifndef FRONTEND_SERVICE_DEF_H_
#define FRONTEND_SERVICE_DEF_H_

#include "rudp/rudp_wrapper.h"
#include <server_share/timer/timer.h>
#include <server_share/common/common.h>
#include <server_share/json_table/json_load.h>

FES_NAMESPACE_BEGIN_DECL

using namespace NLNET;
using namespace FES;

// SOCKET描述符定义;
typedef uint32 SOCKET_ID;

// 消息频道;
enum TChannelNet
{
    RUDP_CHANNEL = 1 ,
    WEB_CHANNEL  = 2
};

// 客户端状态;
enum TClientState
{
    CLIENT_CONNECTION_ABNORMAL = 1 ,
    CLIENT_CONNECTION_NORMAL   = 2
};

// RUDP CALLBACK FUNC;
typedef void ( *TRUDPCallback ) ( NLNET::CMessage&, uint32 );
typedef struct
{
    const char*     KeyName;
    TRUDPCallback   CallBack;
}
TRUDPCallbackItem;

// WEB CALLBACK FUNC;
typedef void ( *TWEBCallback ) ( NLNET::CMessage& , NLNET::TSockId , NLNET::CCallbackNetBase& );
typedef struct
{
    const char*     KeyName;
    TWEBCallback    CallBack;
}
TWEBCallbackItem;

// 转发内容;
enum EFormatKind
{
    ROLEID ,
    INVALID
};

// to format kind;
EFormatKind   ToForMatEnum( const std::string& );
// to fromat string;
const std::string& ToForMatString( EFormatKind );

FES_NAMESPACE_END_DECL

#endif //FRONTEND_SERVICE_DEF_H_ 