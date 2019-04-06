#ifndef SERVICE_SHARED_COMMON_H_
#define SERVICE_SHARED_COMMON_H_

#include <nel/misc/types_nl.h>
#include <nel/net/message.h>
#include <nel/net/unified_network.h>
#include <nel/net/callback_server.h>
#include <nel/net/callback_net_base.h>
#include <nel/net/service.h>
#include <nel/net/module_common.h>
#include <nel/misc/debug.h>
#include <nel/misc/singleton.h>
#include <nel/misc/stop_watch.h>
#include <nel/misc/sstring.h>
#include <nel/misc/enum_bitset.h>
#include <nel/misc/hierarchical_timer.h>
#include <nel/net/service.h>
#include <nel/net/callback_server_websocket.h>
#include <nel/net/module.h>
#include <nel/misc/string_conversion.h>
#include <nel/misc/utils.h>
#include <nel/misc/md5.h>
#include <nel/misc/file.h>
#include <nel/misc/path.h>
#include <nel/misc/eval_num_expr.h>
#include <nel/misc/sstring.h>
#include <nel/misc/string_common.h>
#include <nel/misc/i18n.h>
#include <nel/misc/factory.h>
#include <nel/misc/random.h>
#include <nel/misc/callback_adaptor.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h> 
#include <math.h>
#include <assert.h> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <deque>
#include <queue>
#include <limits>
#include <algorithm>
#include <utility>
#include <functional>
#include <cctype>
#include <iterator>

#include "base_namespace.h"

#include <server_share/protobuf/msg_enum_id.pb.h>
#include <server_share/protobuf/msg_login.pb.h>
#include <server_share/protobuf/msg_player.pb.h>
#include <server_share/protobuf/msg_room.pb.h>
#include <server_share/protobuf/msg_item.pb.h>
#include <server_share/protobuf/msg_mission.pb.h>
#include <server_share/protobuf/msg_statistics.pb.h>

using namespace std;
using namespace PROTOBUF;

typedef uint32      ROLE_ID;
typedef uint32      ITEM_ID;
typedef uint32      MISSION_ID;
typedef uint32      STATISTICS_ID;
typedef sint32      MONEY;
typedef uint32      ROOM_ID;

// 网络接口;
#define SS_NETWORK NLNET::CUnifiedNetwork::getInstance()

// 定义变量属性;
#define SS_PROPERTY( __type, __name , __protected ) \
__protected:\
__type m_##__name;\
public:\
inline void Set##__name(__type v){ m_##__name = v;}\
inline __type Get##__name(){return m_##__name;}

// 获取数组长度;
#define SS_ARRAYSIZE( a ) (sizeof(a) / sizeof((a)[0]))
// 释放指针;
#define SS_SAFE_DELETE( Ptr ) do { if ( NULL != Ptr ) { delete Ptr; Ptr = NULL; } } while ( 0 )
// 释放数组指针;
#define SS_SAFE_DELETE_ARRAY( Ptr ) do { if ( NULL != Ptr ) { delete[] Ptr ; Ptr = NULL; } } while( 0 )

// 通过反射动态生成MESSAGE;
inline google::protobuf::Message* GetProtoBufMessage( NLMISC::CSString ProtobufName )
{
    const google::protobuf::Descriptor* pDescriptor = google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName( ProtobufName );
    if ( NULL == pDescriptor )  return NULL;
    const google::protobuf::Message* pProtoBuffer = google::protobuf::MessageFactory::generated_factory()->GetPrototype( pDescriptor );
    if ( NULL == pProtoBuffer ) return NULL;
    google::protobuf::Message* pMessage = pProtoBuffer->New();
    return pMessage;
}

// 发送消息到客户端;
inline void SendToClient( ROLE_ID RoleID, NLNET::TServiceId ServiceId , NLNET::CMessage& Message )
{
    if ( ServiceId == NLNET::TServiceId::InvalidId ) return;
    NLNET::CMessage SendMessage( "S2C" );
    SendMessage.serial( RoleID );
    SendMessage.serialMessage( Message );
    SS_NETWORK->send( ServiceId , SendMessage );
}

inline void SendToClient( ROLE_ID RoleID , NLNET::TServiceId ServiceId , NLMISC::CSString MessageName , google::protobuf::Message* pMessage )
{
    if ( ServiceId == NLNET::TServiceId::InvalidId ) return;
    NLNET::CMessage SendMessage1( MessageName );
    SendMessage1.serial( pMessage );
    NLNET::CMessage SendMessage2( "S2C" );
    SendMessage2.serial( RoleID );
    SendMessage2.serialMessage( SendMessage1 );
    SS_NETWORK->send( ServiceId , SendMessage2 );
}


#endif // SERVICE_SHARED_COMMON_H_;