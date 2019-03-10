#ifndef SERVICE_SHARED_COMMON_H_
#define SERVICE_SHARED_COMMON_H_

#include <nel/misc/types_nl.h>
#include <nel/net/message.h>
#include <nel/net/unified_network.h>
#include <nel/net/callback_server.h>
#include <nel/net/service.h>
#include <nel/misc/debug.h>
#include <nel/misc/types_nl.h>
#include <nel/misc/singleton.h>
#include <nel/misc/stop_watch.h>
#include <nel/misc/sstring.h>
#include <nel/misc/enum_bitset.h>
#include <nel/net/service.h>
#include <nel/net/callback_server_websocket.h>
#include <nel/misc/string_conversion.h>
#include <nel/misc/utils.h>
#include <nel/misc/md5.h>
#include <nel/misc/file.h>
#include <nel/misc/path.h>
#include <nel/misc/eval_num_expr.h>
#include <nel/misc/sstring.h>
#include <nel/misc/string_common.h>

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

#include "../protobuf/msg_login.pb.h"
#include "../protobuf/msg_error_id.pb.h"
#include "../protobuf/msg_player.pb.h"

using namespace std;
using namespace PROTOBUF;

typedef uint32      ROLE_ID;
typedef uint32      ITEM_ID;
typedef uint32      MISSION_ID;
typedef uint32      STATISTICS_ID;
typedef sint64      MONEY;

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
#define SS_ARRAYSIZE( a ) ( sizeof( a ) / sizeof(a[0]) )
// 释放指针;
#define SS_SAFE_DELETE( Ptr ) do { if ( NULL != Ptr ) { delete Ptr; Ptr = NULL; } } while ( 0 )
// 释放数组指针;
#define SS_SAFE_DELETE_ARRAY( Ptr ) do { if ( NULL != Ptr ) { delete[] Ptr ; Ptr = NULL; } } while( 0 )

// 消息注册;
static uint32 NetCallBackFuncSize = 0;
static NLNET::TUnifiedCallbackItem CallBackFunItems[512] = { };
#define REGISTER_MAIN_FUNCITEM( SCR_CALLBACK ) \
{ \
    uint32 ArraySize = SS_ARRAYSIZE( SCR_CALLBACK ); \
    for ( sint32 idx = 0; idx < ArraySize; idx++ )  \
{ \
    CallBackFunItems[ NetCallBackFuncSize + idx ] = SCR_CALLBACK[idx]; \
} \
    NetCallBackFuncSize += ArraySize; \
} \

#endif // SERVICE_SHARED_COMMON_H_;