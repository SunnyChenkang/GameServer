#ifndef GAME_DEF_H
#define GAME_DEF_H

#include <nel/misc/types_nl.h>
#include "define_sys.pb.h"
#include "define_pro.pb.h"
#include "define_id_family.pb.h"
#include "define_attrib.pb.h"

namespace DEF {

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

typedef	uint32   UID;
typedef	uint64   PID;
typedef	uint32   RPC_SESSION;           ///  远程调用session;
typedef uint64   CLIENT_SESSION;        ///  客户端身份;
typedef uint32   TEMPLATE_ID;           ///  配置表使用的ID;
typedef uint32   TEMPLATE_TYPE;         ///  
typedef uint64   GAME_ID;
typedef uint64   ROOM_ID;
typedef	uint64   MAIL_ID;
typedef	uint64   HERO_ID;
typedef uint64   ZONE_ID;
typedef uint64   RECORD_ID;
typedef uint64   MATCH_ID;
typedef uint32   RUDP_ID;
typedef uint64   MOBILE_ID;
typedef uint64   TISSUE_ID;

//typedef uint32   TEMPLATE_ID;         /// 删除重复
typedef	uint64   BATTALION_ID;
typedef uint32   CHECK_SUM;
typedef sint64   MONEY;
typedef sint64   EXP;
typedef sint64   RMB;
typedef sint64   COUPON;        /// 兑换券;
typedef sint64   SCORE;		    ///	积分;
typedef sint32   ACTIVE_SCORE;
typedef uint32   ERROR_TYPE;
typedef uint64   ITEM_ID;
typedef uint64   LEGION_ID;
typedef uint32   SCENE_ID;
typedef uint8    SCENE_TYPE;
typedef uint32   MISSION_ID;
typedef uint32   SCRIPT_ID;
typedef uint32   EVENT_ID;
typedef uint64   ROOM_ID;
typedef uint32   ACHIEVE_ID;
typedef uint16   VIP_LEVEL;
typedef uint32   ACK_IDX;
typedef uint32   FRIEND_SCORE;
typedef uint32   RANKING;
typedef uint32   BUILD_EXP;
typedef uint16   BUILD_LEVEL;
typedef uint64   PROXY_ID;

#define RANDOM_SHOP_GRID_NUM        3
#define PLAYERNAME_LENGTH           (64)                ///  玩家名字最大长度
#define PLAYERNAME_LENGTH_MIN       (1)                 ///  玩家名字最小长度
#define RPC_SESSION_TCP_FLAG        0x80000000          ///  rpc_session协议标识，用于区分 tcp 和 udp协议。
//#define RPC_SESSION_PROTO_MASK      0x7fffffff          ///  
#define FLOAT_RATE                  10000               ///  万分比
#define RANDOM_CARD_ONE             1
#define RANDOM_CARD_TEN             10
#define FRIEND_FIGHT_NUM            5
//#define UDP_SEND_MAX_LEN            2048
#define BAD_CHECK_SUM               DEF::CHECK_SUM(-1)
#define ITEM_STACKING_MAX           0x7fffffff
#define MAX_VITALITY                10000

#define SYNC_ITEM_PAGE_MAX          21
#define SYNC_ACHI_PAGE_MAX          30
#define SYNC_MISSION_PAGE_MAX       30
#define SYNC_GUARD_PAGE_MAX         9
#define SYNC_HERO_PAGE_MAX          4
#define SYNC_FRIEND_PAGE_MAX        10
#define SYNC_RANKING_PAGE_MAX       10
#define SYNC_FIGHTLOG_PAGE_MAX      10
#define SYNC_GRIMOIRE_PAGE_MAX      30

#define MAX_CASTLE_MONSTER_NUM      3
#define MAX_CASTLE_GRIMONIRE_NUM    2
#define MAX_FIGHT_HERO              3
#define MAX_PVP_RANKING             5000
#define MAX_RANDOM_FRIEND_NUM       5
#define MAX_BUILD_QUEUE             4
#define MAX_UPDATE_PLAYER_MAIL_NUM  50
#define MIN_UPDATE_PLAYER_MAIL_NUM  1

#define NEW_PLAYER_FRIEND_LEVEL     5
#define NEW_PLAYER_FIGHT_LEVEL      4

#define SYNC_FRIEND_TIME    60
#define SYNC_RECOMMEND_TIME 60
#define RECOMMEND_NUM       6
#define FILL_RECOMMEND_NUM  50

#define SYNC_FIGHTINT_RECORD_COUNT 5
#define FIGHTINT_RECORD_MAX_COUNT 15

#define GRIDINFO_INVALID 0
#define INVALID_RANKING  0
#define ONE_YEAR 60*60*24*365
#define ONE_DAY  60*60*24
// 花色掩码;
#define MASK_COLOR  0xF0
// 数值掩码;
#define MASK_VALUE  0x0F
#define PLAYER_CHAT_LENGTH          64     // 玩家聊天限制长度;
#define PAOMADENG_CHAT_LENGTH       256    // 跑马灯限制长度;
// 房间最大数;
#define PRIVATE_ROOM_MAXID          1000000

//  比赛最大数

#define RFINVITEBIT 20  //  邀请码位移数
//#define  NET_UDP

struct DATA_PARAM
{
    int param_size;
    int param[16];

    DATA_PARAM( void )
    {
        param_size = 0;
    }
};

enum ErrorLogType
{
    ELOGTYPE_INVALID,
    ELOGTYPE_BUYMONEY,
};


//  获取数值;
inline uint8 getCardValue( uint8 card ) {return ( card & MASK_VALUE );}
//  获取花色;
inline uint8 getCardColor( uint8 card ) {return ( card & MASK_COLOR );}
//  获取逻辑数值;
inline uint8   getLogicValue( uint8 card )
{
    card = getCardValue( card );
    return (card==1) ? (card+13) : card;
}

///   flag(1) session(24)  sid(7)
///   flag   是tcp还是udp， 1:TCP  0:UDP
inline bool IsTCPSession( RPC_SESSION rpc_session ) {  return rpc_session&RPC_SESSION_TCP_FLAG;  }

template<class T> inline T* CloneRec(const T &val) { return new(std::nothrow) T(val); }

#define MAX_VAL( __valtype )  std::numeric_limits<__valtype>::max()

#define PROPERTY( type , name )\
	private:\
		type m_##name;\
	public:\
		inline void set_##name(type v){ \
			m_##name = v;\
		}\
		inline type get_##name(){\
			return m_##name;\
		}

#define PROP( __type, __name )\
    private:\
        __type m_##__name;\
    public:\
        inline void Set##__name(__type v){ m_##__name = v;}\
        inline __type Get##__name(){return m_##__name;}

// safe delete;
#define safe_delete( ptr ) do{ if( NULL != ptr ){ delete ptr ; ptr = NULL; } } while(0)

// safe delete array;
#define safe_delete_array( ptr ) do{ if( NULL != ptr ){ delete[] ptr; ptr = NULL; } } while(0)

const std::string  GAME_TYPE_BLACKJACK              = "BlackJack";
const std::string  GAME_TYPE_BLACKJACK_SNG          = "BJSNG";
const std::string  GAME_TYPE_CHAL_BLACKJACK         = "ChalBJ";
const std::string  GAME_TYPE_TEXASPOKER             = "TexasPoker";
const std::string  GAME_TYPE_TEXASPOKER_MTT         = "ChalTPMTT";
const std::string  GAME_TYPE_TEXASPOKER_SNG         = "ChalTPSNG";
const std::string  GAME_TYPE_SLOTS_COMMON           = "SlotsCommon";
const std::string  GAME_TYPE_CHAL_SLOTS             = "SlotsChal";
const std::string  GAME_TYPE_MAHJONG                = "MahJong";
const std::string  GAME_TYPE_HORSERACE              = "HorseComman";

static const std::string CHALLENGE_TYPE             = "chal";
}

#endif
