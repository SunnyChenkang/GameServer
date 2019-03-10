#ifndef MyRobotHelper_h__
#define MyRobotHelper_h__
#include <nel/net/callback_net_base.h>
#include "msg/recv_logic.h"
#include <game_share/game_def.h>

//class CClient;
#define PLAYER_COMMON                  "CMD"               // GM指令;
#define PLAYER_ERROR                   "ERR"               // 错误处理;
#define PLAYER_INFO                    "SyncData"          // 请求角色信息;
#define LOGIN                          "LOGIN"             // 登陆;
#define PLAYER_SYNCLOGINPLAYER         "LPLY"              // 同步玩家基本信息;
#define PLAYER_CREATE                  "CT_PLY"            // 角色名字;
#define PLAYER_NULL                    "PLY_NULL"          // 需要创建角色;
#define PLAYER_ENTER_GAME              "EG"                // 进入房间;
#define PLAYER_BLACKJACKROOMINFO       "BJ_GI"             // 所有玩家以及房间数据;
#define PLAYER_LEAVE_ROOM              "LR"                // 离开房间;
#define PLAYER_SYNCPLAYERINFO          "SPLY"              // 请求同步玩家信息;
#define PLAYER_RANKINGMONEYOP10        "RMT"               // Ranking Money Top 10;
#define PLAYER_BLACKJACKADDPOUR        "BJ_P"              // 请求下注;
#define PLAYER_BLACKJACKASKCARD        "BJ_AC"             // 请求要牌;
#define PLAYER_BLACKJACKSPLITCARD      "BJ_SC"             // 请求要牌;
#define PLAYER_BLACKJACKSTANDCARD      "BJ_STD"            // 请求停牌;
#define PLAYER_BLACKJACKBUYSURRENDER   "BJ_BS"             // 购买保险;
#define PLAYER_BLACKJACKSKIPSURRENDER  "BJ_BSC"            // 跳过保险;
#define PLAYER_BLACKJACKDOUBLECARD     "BJ_DB"             // 双倍;
#define PLAYER_BROADCAST_PLY_INFO      "BJ_PI"             // 广播玩家信息;
#define PLAYER_BLACKJACKCLEARPOUR      "BJ_CL"             // 清除下注;
#define PLAYER_ADDMONEY                "AM"                // 添加金钱;
#define PLAYER_SUBMONEY                "SM"                // 减少金钱;
#define PLAYER_GETREWARD               "TRD"               // 领取奖励;
#define PLAYER_GETCHAMPIONSHIP         "SC"                // 请求获取比赛数据;
#define PLAYER_REQUESTPRIZEPOOL        "RP"                // 请求比赛奖池;
#define PLAYER_RANKINGROOMTOP          "RRT"               // ranking room top;
#define PLAYER_RANKINGMYDATA           "RMy"               // 请求自己的排行榜数据;
#define PLAYER_SENDCOMMMONMAIL         "SCM"               // 请求发送普通邮件;
#define PLAYER_REQUESTMAILDATA         "RMAIL"             // 请求邮件数据;
#define PLAYER_RECEIVECOMMONMAIL       "RCM"               // 收到普通邮件;
#define PLAYER_SYSTEM_REWARD           "SRAD"              // 请求系统邮件奖励;
#define PLAYER_COMMON_REWARD           "CRAD"              // 请求普通邮件奖励;
#define PLAYER_DELETE_SYSTEMMAIL       "DSM"               // 请求删除系统邮件;
#define PLAYER_DELETE_COMMONMAIL       "DCM"               // 请求删除普通邮件;
#define PLAYER_LOOK_COMMONMAIL         "LCM"               // 请求查看普通邮件;
#define PLAYER_SYNCHFRIENDLIST         "FL"                // 请求同步好友列表;
#define PLAYER_SYNCHAPPLYLIST          "AL"                // 请求同步好友申请列表;
#define PLAYER_ADDFRIENDAPPLY          "APF"               // 好友申请;
#define PLAYER_ADDFRIEND               "AF"                // 好友添加;
#define PLAYER_DELETEFRIEND            "DF"                // 删除好友;
#define PLAYER_DELETEAPPLYFRIEND       "DA"                // 删除好友申请;
#define PLAYER_FRIENDDETAIL            "FD"                // 请求好友详细信息;
#define PLAYER_APPLYDETAIL             "AD"                // 请求申请好友详细信息;
#define PLAYER_REWARDFRIEND            "GF"                // 请求奖励好友;
#define PLAYER_CHAT_ROOM               "CR"                // 房间内聊天;
#define PLAYER_RKPI                    "RKPI"              // 返回玩家统计数据
#define PLAYER_GIVETIP                 "BJ_Tip"            // 牌桌上打赏;
#define PLAYER_ROOMPLAYERINFO          "RPI"               // 请求同局其他玩家详细信息;
#define PLAYER_INVITEFRIEND            "IVF"               // 好友邀请;
#define PLAYER_INVITEENTER             "IVE"               // 邀请进入;
#define PLAYER_SENDTEMPLATEMAIL        "SSM"               // 发送系统模板邮件;
#define PLAYER_BIND_FACEBOOK           "BF"                // 绑定Facebook;
#define PLAYER_PULLROULETTEMONEY       "PRM"               // 大转盘;
#define PLAYER_PULLROULETTERATE        "PRR"               // 转倍率;
#define PLAYER_PULLROULETTERATERMB     "PRRR"              // 美金转倍率;
#define PLAYER_ROULETTEGETMONEY        "RGM"               // 获取转盘奖励;
#define PLAYER_REQUESTSHOPINFO         "SHOP"              // 请求商店信息;
#define PLAYER_SHOPBUYMONEY            "SBUY"              // 商店购买金币;
#define PLAYER_REQUESTRENAME           "RN"                // 请求换名字;
#define PLAYER_REQOTHERPLAYERINFO      "ROPI"              // 请求其他玩家详细信息;
#define PLAYER_REQSELFPLAYERINFO       "RSPI"              // 请求自己详细信息;
#define PLAYER_REQPLAYERKPI            "DRKPI"             // 请求其他玩家统计信息;
#define PLAYER_HALLADSDRAWAWARD        "HALL_ADS"          // 大厅看广告领取奖励;
#define PLAYER_ROOMADSDRAWAWARD        "ROOM_ADS"          // 房间看广告领取奖励;
#define PLAYER_TP_CALLPOUR             "TP_CP"             // 玩家跟注;
#define PLAYER_TP_RAISEPOUR            "TP_RP"             // 玩家加注;
#define PLAYER_TP_FOLDCARD             "TP_AD"             // 玩家弃牌;
#define PLAYER_TP_CHECKCARD            "TP_CC"             // 玩家让牌;
#define PLAYER_TP_RESETCOINS           "TP_RC"             // 重置筹码;
#define PLAYER_GOBACKGAME              "GoBackGame"        // 返回游戏;
#define PLAYER_SLOTSSPIN               "SL_SP"             // 老虎机拉杆;
#define PLAYER_CHECKMAILSTATE          "MFG"               // 请求查看邮件状态;
#define PLAYER_RANKPLAYERNUM           "RF"                // 请求比赛参数人数;
#define PLAYER_SYNCHACHIEVEMENT        "SAD"               // 请求成就信息;
#define PLAYER_SYNCHCOMACHIEVEMENT     "SCAD"              // 请求已完成成就信息;
#define PLAYER_ACHIEVEMENTDRAWREWARD   "ADR"               // 请求领取成就奖励;
#define PLAYER_BLACKJACKRESETPOUR      "BJ_RP"             // 21点重新下注;
#define PLAYER_SLOTSBONUSGAMESELECT    "SL_BGS"            // 老虎机小游戏;
#define PLAYER_RECOMMENDFRIEND         "RDF"               // 请求推荐好友;
#define PLAYER_SYNCHSTATISTICSDATA     "SSD"               // 请求同步统计信息;
#define PLAYER_BROAD_JOINTEXASPOKER    "TP_GI"             // 德州扑克广播进入房间消息;
#define PLAYER_UPDATEDYNAMICMSG        "UDM"               // 更新个性签名;
#define PLAYER_REHEADPORTRAIT          "RHP"               // 修改头像;
#define PLAYER_SLOTSJACKPOTS           "SL_JP"             // Slots请求奖池数据;
#define PLAYER_SLOTSBROADCASTGAMEINFO  "SL_GI"             // Slots进入房间，广播房间消息;
#define PLAYER_TPCHALLAPPLYGAME        "TP_CAG"            // 德州竞技场报名;
#define PLAYER_TPCHALLCANCELAPPLYGAME  "TP_CCG"            // 取消德州竞技场报名;
#define PLAYER_TPCHALLROOMDATA         "TP_RDG"            // 德州竞技场房间信息;
#define PLAYER_TPCHALLREQUESTQUIT      "TP_RQ"             // 德州竞技场请求退出;
#define PLAYER_GETBONUSMONEY           "GB"                // 获取bonus money;
#define PLAYER_VIEWPIGINFO             "VPig"              // 查询小猪存钱罐信息;
#define PLAYER_PRIVATECHAT             "PC"                // 玩家私聊;
#define PLAYER_MAHJONGGAMEINFO         "MJ_GI"             // 南京麻将游戏信息;
#define PLAYER_MAHJONGUSEROPERATE      "MJ_SP"             // 南京麻将玩家操作权限;
#define PLAYER_MAHJONGOUTCARD          "MJ_OC"             // 南京麻将玩家出牌;
#define PLAYER_MAHJONGSTARTREADY       "MJ_SR"             // 南京麻将用户开始准备;
#define PLAYER_MAHJONGCANCEREADY       "MJ_CR"             // 南京麻将用户取消准备;
#define PLAYER_MAHJONGSHOWDOWN         "MJ_SD"             // 南京麻将结算;
#define PLAYER_SYNCHITEMDATA           "SICU"              // 同步道具数据;
#define PLAYER_USE_ITEM                "UseItem"           // 使用道具;
#define PLAYER_SELL_ITEM               "SellItem"          // 出售道具;
#define PLAYER_STOREBUYITEM            "BSI"               // 购买商城道具;
#define PLAYER_BINDMOBILENUMBER        "BMNC"              // Bind Mobile Number Check Random Code.;
#define PLAYER_CHATPAOMADENG           "CPMD"              // 跑马灯喊话;
#define PLAYER_SEARCHPID               "SPID"              // 搜索PID;
#define PLAYER_GETSENDMONEYLIMIT       "SML"               // 获取Send Money Limit;
#define PLAYER_SYNCBLACKLIST           "SBL"               // 同步屏蔽列表数据;
#define PLAYER_DELETEBLACKLIST         "DBL"               // 移除屏蔽列表;
#define PLAYER_ADDBLACKLIST            "ABL"               // 添加屏蔽列表;
#define PLAYER_SYNCHMISSIONDATA        "SMD"               // 同步任务数据;
#define PLAYER_RESTORESCOREDATA        "RSD"               // 清空统计积分数据;
#define PLAYER_MISSIONREWARD           "MDR"               // 任务领取奖励;


#define ROBOT_UDP_TIME   1000
#define ITEM_RANDOM_NUM 50
#define ROBOT_START_MISSION 16001001
#define ROBOT_START_ACHIEVEMENT 7000001
#define CLIENT_RANDOM_NUM 10
#define LIMIT_SEND_TIME 1
#define USERNAMELENGTH 20
#define SENDMSGLIMITTIME (LIMIT_SEND_TIME + 2)
#define MOBILENUMBERSIZE  14          

#define DYNAMIC_CLIENT( data ) \
    if( !data ) \
    return; \
    CClient* pClient = dynamic_cast< CClient* >( data ); \
    if( !pClient )\
    return;

enum ClientState
{
    client_state_null  ,        
    client_state_authaccount,   // 验证账号;
    client_state_login ,        // 登陆中;
    client_state_createrole,    // 创建角色;
    client_state_loadplayer,    // 加载玩家数据;
    client_state_online,        // 登陆成功;
};

enum SyncLoginFlag
{
    login_sync_succeed      = 0x0000,
    login_sync_item_can_use = 0x0001,
    login_sync_item_stuff   = 0x0002,
    login_sync_item_guard   = 0x0004,
    login_sync_item_limit   = 0x0008,
    login_sync_dup          = 0x0010,
    login_sync_guard        = 0x0020,
    login_sync_hero         = 0x0040,
    login_sync_castle       = 0x0080,
    login_sync_achievement  = 0x0100,
	login_sync_mission      = 0x0200,
};

enum PlayerState
{
    InTheHallState = 0,
    InTheRoomState = 1,

};

enum MountLuaType
{
    MountLua_Invalid    = 0,
    MountLua_Hall       = 1,
    MountLua_BlackJack  = 2,
    MountLua_TexasPoker = 3,
    MountLua_Slots      = 4,
    MountLua_MahJong    = 5,
};

// bytes to int'
inline uint bytesTouint( uint8* ArrBytes )
{
    uint resVal  = ( uint )ArrBytes[ 0 ] & 0xff;
    resVal      |= ( ( ( uint )ArrBytes[ 1 ] << 8) & 0xff00 );
    resVal      |= ( ( ( uint )ArrBytes[ 2 ] << 16 & 0xff0000 ) );
    resVal      |= ( ( ( uint )ArrBytes[ 3 ] << 24 & 0xff000000 ) );

    return resVal;
}

// int to bytes;
inline void uintTobytes( uint Value , uint8* ArrBytes )
{
    memset( ArrBytes , 0 , sizeof( uint8 ) * 4 );
    ArrBytes[ 0 ] = ( uint8 )( Value & 0xff );
    ArrBytes[ 1 ] = ( uint8 )( ( Value >> 8 )  & 0xff00 );
    ArrBytes[ 2 ] = ( uint8 )( ( Value >> 16 ) & 0xff0000 );
    ArrBytes[ 3 ] = ( uint8 )( ( Value >> 24 ) & 0xff000000 );
}

// long long to byte;
inline void llongtobyte( uint64 Value , uint8* ArrBytes )
{
    memset( ArrBytes , 0 , sizeof( uint8 ) * 8 );
    ArrBytes[ 0 ] = ( uint8 )( Value & 0xff );
    ArrBytes[ 1 ] = ( uint8 )( ( Value >> 8 ) & 0xff00 );
    ArrBytes[ 2 ] = ( uint8 )( ( Value >> 16 ) & 0xff0000 );
    ArrBytes[ 3 ] = ( uint8 )( ( Value >> 24 ) & 0xff000000 );
    ArrBytes[ 4 ] = ( uint8 )( ( Value >> 32 ) & 0xff00000000 );
    ArrBytes[ 5 ] = ( uint8 )( ( Value >> 40 ) & 0xff0000000000 );
    ArrBytes[ 6 ] = ( uint8 )( ( Value >> 48 ) & 0xff000000000000 );
    ArrBytes[ 7 ] = ( uint8 )( ( Value >> 56 ) & 0xff00000000000000 );
}

// byte to long long 
inline uint64 byteTolonglong( uint8* ArrBytes )
{
    uint64 resVal = ( uint64 )ArrBytes[ 0 ] & 0xff;
    resVal |= ( ( ( uint64 )ArrBytes[ 1 ] << 8 ) & 0xff00 );
    resVal |= ( ( ( uint64 )ArrBytes[ 2 ] << 16 ) & 0xff0000 );
    resVal |= ( ( ( uint64 )ArrBytes[ 3 ] << 24 ) & 0xff000000 );
    resVal |= ( ( ( uint64 )ArrBytes[ 4 ] << 32 ) & 0xff00000000 );
    resVal |= ( ( ( uint64 )ArrBytes[ 5 ] << 40 ) & 0xff000000000 );
    resVal |= ( ( ( uint64 )ArrBytes[ 6 ] << 48 ) & 0xff00000000000 );
    resVal |= ( ( ( uint64 )ArrBytes[ 7 ] << 56 ) & 0xff0000000000000 );

	return resVal;
}

static const char UserNameTable[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

#endif // MyRobotHelper_h__