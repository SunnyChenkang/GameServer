#include "static_table_mgr.h"
#include <nel/misc/file.h>
#include <nel/misc/i_xml.h>
#include <nel/net/service.h>
#include <ctime>
//#include "stdpch.h"
#include <game_share/tools.h>
#include "../eval_expression.h"
#include <game_share/game_def.h>
#include "static_table_qualifying.h"
#include "static_table_qualify_key.h"
#include "static_table_ddzpool.h"

using namespace std;
using namespace NLMISC;
using namespace ATTRIB_TYPE;
using namespace StaticData;

#define GET_STATIC_RECORD( __static_data ) \
    StaticData::RecordBase*  pRecord = NULL;\
    TStaticData::iterator iter = __static_data.find(record_id);\
    if ( iter != __static_data.end() ){\
    pRecord = iter->second;\
    }\
    return pRecord;

uint32  CStaticTableMgr::GetSeconds( CSString str )
{
    uint32 ret = 0;

    CVectorSString result_2;
    str.splitBySeparator(':',result_2);

    if ( result_2.size()==2 )
    {
        ret = result_2[0].atoi() * HOUR_SECONDS + result_2[1].atoi() * MINUTE_SECONDS;
    }

    return ret;
}

CStaticTableMgr::CStaticTableMgr()
{
    m_Random.srand( CTime::getSecondsSince1970() );
}

/// 注意清空之前的数据，CStaticTableMgr::init()可能会调用多次。
void CStaticTableMgr::init()
{
    ChangeVersion();

    load_config("AchievementPrototype",       m_AchievementData);
    load_config("StatisticsPrototype",        m_StatisticsData);
    load_config("MissionPrototype",           m_MissionData);
    load_config("ExpPrototype",               m_ExpData);
    load_config("ItemPrototype",              m_ItemData);
    load_config("StoreItemPrototype",         m_StoreItemData);
    load_config("SpendPrototype",             m_SpendItemData);
    load_config("RolePrototype",              m_WeaponData);
    load_config("BulletPrototype",            m_BulletData);
    load_config("FishPrototype",              m_FishData);

    m_GameConfig.Challenge.clear();

    load_game_config();
    load_game_blackjack_config();
    load_game_texaspoker_config();
    load_game_niuniu_config();
	load_game_gandengyan_config();

    load_vip_config();
    load_slots_config();
    load_game_horse_config();
    load_game_fish_config();
	load_fish_skill_config();
	load_robot_config();
	load_game_runfast_config();
	load_game_doushisi_config();
	load_game_penghu_config();
    load_game_doudizhu_config();
    load_game_pinsanzhang_config();
    load_game_chess_config();
    //ReloadAchievementConfigEvent();
    process_level_exp();
    GuanDanConfig.LoadConfig();
    MahJongData.LoadConfig();
    RunFastPoolConfig.LoadCardConfig();
	CreateRoomCostData.LoadConfig();
    QualifyingConfiger.LoadQualifyingXml();
    QingErData.LoadConfig();
}

void CStaticTableMgr::addToRecord( ATTRIB_TYPE::TAttribType field_attrib, NLMISC::CSString field_type, NLMISC::CSString field_val, NLMISC::CSString field_save, StaticData::RecordBase* pRecord )
{
    FieldBase* pFieldBase = NULL;

    //if ( field_type=="UpgradeItem" )
    //{
    //    pFieldBase = new(std::nothrow) FieldNeedMeta();
    //}
    //else if( field_type == "GetProps")
    //{
    //    pFieldBase = new(std::nothrow) FieldAcquireItem();
    //}
    //else if( field_type == "ActReward")
    //{
    //    pFieldBase = new(std::nothrow) FieldDupDropItem();
    //}
    //else if( field_type == "DropCurrency")
    //{
    //    pFieldBase = new(std::nothrow) FieldDupDropMoney();
    //}
    //else if ( field_type == "VipRewards")
    //{
    //    pFieldBase = new(std::nothrow) FieldRewardAdd();
    //}
    //else if ( field_type == "DropSoul" )
    //{
    //    pFieldBase = new(std::nothrow) FieldDupDropSoul();
    //}
    //else if ( field_type == "ActivateGuard" )
    //{
    //    pFieldBase = new(std::nothrow) FieldActivateGuard();
    //}
    if ( field_type == "AchCondition" )
    {
        pFieldBase = new(std::nothrow) FieldAchievementCondition();
    }
    else if ( field_type == "ItemUseEffect" )
    {
        pFieldBase = new(std::nothrow) TwoParamListComman();
    }
    else if ( field_type == "MissionStartTime" )
    {
        pFieldBase = new(std::nothrow) FieldMissionStartTime();
    }
    else if ( field_type == "ItemBuy" )
    {
        pFieldBase = new(std::nothrow) FieldItemBuyData();
    }
    else if ( field_type == "ChalRoundReward" )
    {
        pFieldBase = new(std::nothrow) FieldChalRoundReward();
    }
    else if ( field_type == "ItemSpend" )
    {
        pFieldBase = new(std::nothrow) FieldItemCommon();
    }
    else if ( field_type == "MissionReward")
    {
        pFieldBase = new(std::nothrow) FieldAcquireItem();
    }
    else if ( field_type == "DropWeight")
    {
        pFieldBase = new(std::nothrow) FieldItemCommon();
    }
    else if ( field_type == "DropRange")
    {
        pFieldBase = new(std::nothrow) FieldRangeCommon();
    }
    else
    {
        ///   class类型的默认处理
        pFieldBase = new(std::nothrow) FieldBase();
    }

    pFieldBase->set( field_attrib, field_type, field_val );
    pRecord->addAttribute( pFieldBase, field_save );
}

bool CStaticTableMgr::load_game_config()
{
    bool res = false;
    string path = NLMISC::CPath::lookup("GameConfig.xml");
    CIFile file;
    CIXml xml;

    if (file.open (path))
    {
        if (xml.init (file))
        {
            xmlNodePtr rootPtr = xml.getRootNode();

            if ( rootPtr )
            {
                m_GameConfig.rooms.clear();
                xmlNodePtr pRoomConfig = xml.getFirstChildNode( rootPtr , "room_config" );
                for ( ; pRoomConfig!=NULL; pRoomConfig= xml.getNextChildNode(pRoomConfig,"room_config") )
                {
                    RoomConfigXml   room_config;
                    room_config.template_id     = CIXml::getIntProperty( pRoomConfig, "id", 0 );
                    room_config.room_type       = CIXml::getStringProperty( pRoomConfig, "room_type", "xxxx1" );
                    room_config.game_type       = CIXml::getStringProperty( pRoomConfig, "game_type", "xxxx2" );
                    room_config.min_ver         = CIXml::getIntProperty( pRoomConfig , "min_ver" , 0 );
                    room_config.app_name        = CIXml::getStringProperty( pRoomConfig, "app_name" , "" );
                    room_config.challenge_type  = CIXml::getStringProperty( pRoomConfig, "challenge_type", "xxxx2" );
                    room_config.game_name       = CIXml::getStringProperty( pRoomConfig, "game_name", "xxxx2" );
                    room_config.robot           = CIXml::getStringProperty( pRoomConfig, "robot", "" );
                    room_config.room_max        = CIXml::getIntProperty( pRoomConfig, "room_max", 1 );
                    room_config.room_min        = CIXml::getIntProperty( pRoomConfig, "room_min", 100 );
                    room_config.viewer_max      = CIXml::getIntProperty( pRoomConfig, "viewer_max", 0 );
                    room_config.enter_score     = CIXml::getIntProperty( pRoomConfig, "enter_score", 0 );
                    room_config.icon_progress   = CIXml::getIntProperty( pRoomConfig, "icon_progress", 0 );
                    room_config.is_goback       = CIXml::getIntProperty( pRoomConfig, "is_goback" , 0 );
                    room_config.auto_return     = CIXml::getIntProperty( pRoomConfig, "auto_return" , 0 );
                    room_config.delete_room_time= CIXml::getIntProperty( pRoomConfig ,"delete_room_time" , 0 ) * 1000;
                    room_config.check_limit     = CIXml::getIntProperty( pRoomConfig ,"check_limit" , 0 );

                    uint32 total_weight = 0;
                    xmlNodePtr pIconSet = xml.getFirstChildNode( pRoomConfig , "icon_set" );
                    for ( ; pIconSet!=NULL; pIconSet= xml.getNextChildNode(pIconSet,"icon_set") )
                    {
                        IconSet data;
                        data.icon_id       = CIXml::getIntProperty( pIconSet, "icon_id", 0 );
                        data.weight        = CIXml::getIntProperty( pIconSet, "weight", 0 );
                        total_weight      += data.weight;

                        room_config.icon_set_map.insert( std::make_pair( total_weight, data ) );
                    }

                    std::pair<TRoomConfigXml::iterator , bool > _res = m_GameConfig.rooms.insert( make_pair(room_config.room_type, room_config) );
                    nlassert( _res.second );
                }

                /// 初始化数据;
                xmlNodePtr pInit = xml.getFirstChildNode( rootPtr , "init" );
                if ( NULL != pInit )
                {
                    m_GameConfig.InitConfig.player_item_list.clear();
                    m_GameConfig.InitConfig.player_init_money        = CIXml::getIntProperty( pInit, "money", 0 );
                    m_GameConfig.InitConfig.player_head_random       = CIXml::getIntProperty( pInit, "random_head", 0 );
                    m_GameConfig.InitConfig.player_fb_head           = CIXml::getIntProperty( pInit, "facebook_head", 0 );
                    m_GameConfig.InitConfig.player_sex               = CIXml::getIntProperty( pInit, "sex", 0 );
                    m_GameConfig.InitConfig.player_inti_rmb          = CIXml::getIntProperty( pInit, "rmb", 0 );
                    m_GameConfig.InitConfig.player_init_weapon_id    = CIXml::getIntProperty( pInit, "weapon_id", 0 );
                    m_GameConfig.InitConfig.player_init_bullet       = CIXml::getIntProperty( pInit, "default_unlock_bullet", 0 );
                    xmlNodePtr ItemXml = xml.getFirstChildNode( pInit , "item" );
                    for ( ; ItemXml!=NULL; ItemXml=xml.getNextChildNode(ItemXml,"item") )
                    {
                        ItemEntity Item;
                        Item.item_tid = CIXml::getIntProperty( ItemXml , "id"    , 0 );
                        Item.item_num = CIXml::getIntProperty( ItemXml , "count" , 0 );
                        m_GameConfig.InitConfig.player_item_list.push_back( Item );
                    }
                }

                /// 邮件数据;
                xmlNodePtr pMailPtr = xml.getFirstChildNode(rootPtr , "mail_config");
                if ( NULL != pMailPtr )
                {
                    m_GameConfig.MailConfig.ShowMailMaxNum      = CIXml::getIntProperty( pMailPtr , "mail_show_max_num" , 50 );
                    m_GameConfig.MailConfig.MailSaveTime        = CIXml::getIntProperty( pMailPtr , "mail_save_time" , 50 );
                    m_GameConfig.MailConfig.RewardMailSaveTime  = CIXml::getIntProperty( pMailPtr , "reward_mail_save_time" , 50 );
                }

                /// 谁观察过我的个数;
                xmlNodePtr pViewPlayers = xml.getFirstChildNode(rootPtr , "view_player_num");
                if ( NULL != pViewPlayers )
                {
                    m_GameConfig.ViewPlayersConfig.view_player_num = CIXml::getIntProperty( pViewPlayers , "value" , 0 );
                }

                /// 修改名字时间限制配置;
                xmlNodePtr pRenameTimeLimit = xml.getFirstChildNode(rootPtr , "rename_time_limit");
                if ( NULL != pRenameTimeLimit )
                {
                    m_GameConfig.RenameTimeLimitConfig.rename_time_limit = CIXml::getIntProperty( pRenameTimeLimit , "value" , 15 );
                }

                /// 好友人数限制配置;
                xmlNodePtr pFriendConfig = xml.getFirstChildNode(rootPtr , "friend_config");
                if ( NULL != pFriendConfig )
                {
                    m_GameConfig.FriendConfig.friend_init_num = CIXml::getIntProperty( pFriendConfig , "init_num" , 50 );
                    m_GameConfig.FriendConfig.friend_max_num  = CIXml::getIntProperty( pFriendConfig , "max_num" , 100 );
                }

                /// 战斗记录条目;
                xmlNodePtr pFightintConfig = xml.getFirstChildNode(rootPtr , "fightint_record_count");
                if ( NULL != pFightintConfig )
                {
                    m_GameConfig.GameRecordConfig.RecordCount   = CIXml::getIntProperty( pFightintConfig , "count" , 6 );
                    m_GameConfig.GameRecordConfig.RecordTimeOut = CIXml::getIntProperty( pFightintConfig , "timeout" , 86400 );
                    m_GameConfig.GameRecordConfig.RecordTimer   = CIXml::getIntProperty( pFightintConfig , "timer" , 3600 ) * 1000;
                }

                /// VIP事件加成;
                xmlNodePtr pVIPTimeMoneyPlus = xml.getFirstChildNode( rootPtr , "vip_time_plus" );
                if ( NULL != pVIPTimeMoneyPlus )
                {
                    m_GameConfig.VIPTimeMoneyPlus.shop_plus     = CIXml::getFloatProperty( pVIPTimeMoneyPlus , "shop_plus" , 1.0f );
                    m_GameConfig.VIPTimeMoneyPlus.bonus_plus    = CIXml::getFloatProperty( pVIPTimeMoneyPlus , "bonus_plus" , 1.0f );
                    m_GameConfig.VIPTimeMoneyPlus.signin_plus   = CIXml::getFloatProperty( pVIPTimeMoneyPlus , "signin_plus" , 1.0f );
                }

                /// 排行榜配置
                xmlNodePtr pRankingConfig = xml.getFirstChildNode(rootPtr , "ranking");
                if ( NULL != pRankingConfig )
                {
                    m_GameConfig.Ranking.win_money_refresh = CIXml::getIntProperty( pRankingConfig , "win_money_refresh" , 3 );
                }

                /// 保险箱配置;
                xmlNodePtr pSafeboxConfig = xml.getFirstChildNode(rootPtr , "safe_box");
                if ( NULL != pSafeboxConfig )
                {
                    m_GameConfig.Safebox.self_money_min         = CIXml::getIntProperty( pSafeboxConfig , "self_money_min" , 10000 );
                    m_GameConfig.Safebox.free_save_rate_money   = CIXml::getIntProperty( pSafeboxConfig , "free_save_rate_money" , 100 );
                    m_GameConfig.Safebox.max_save_rate_money    = CIXml::getIntProperty( pSafeboxConfig , "max_save_rate_money" , 100000 );
                    m_GameConfig.Safebox.save_rate              = CIXml::getFloatProperty( pSafeboxConfig , "save_rate" , 0 );
                }

                /// 修改邮件PUSH消息;
                xmlNodePtr pPushMailMsg = xml.getFirstChildNode( rootPtr , "pushmsg" );
                if ( NULL != pPushMailMsg )
                {
                    m_GameConfig.PushMailMsg.RandomFriendNum  = CIXml::getIntProperty( pPushMailMsg , "random_friend_max" , 0 );
                    m_GameConfig.PushMailMsg.PushMsgNum       = CIXml::getIntProperty( pPushMailMsg , "push_msg_num" , 0 );
                    m_GameConfig.PushMailMsg.MinMoney         = CIXml::getIntProperty( pPushMailMsg , "min_money" , 0 );
                    m_GameConfig.PushMailMsg.MaxMoney         = CIXml::getIntProperty( pPushMailMsg , "max_money" , 0 );
                }

                /// 定时奖励;
                xmlNodePtr pTimingReward = xml.getFirstChildNode( rootPtr , "timing_reward" );
                if ( NULL != pTimingReward )
                {
                    m_GameConfig.timingReward.time  = CIXml::getIntProperty( pTimingReward , "time" , 60 ) * 60;
                    m_GameConfig.timingReward.bind_facebook = CIXml::getIntProperty( pTimingReward , "bind_facebook" , 1000 );
                    m_GameConfig.timingReward.tips_max = CIXml::getIntProperty( pTimingReward , "tips_max" , 10 );

                    ///  大转盘;
                    m_GameConfig.timingReward.roulette_money_time = CIXml::getIntProperty( pTimingReward , "roulette_money_time" , 20 ) * MINUTE_SECONDS;
                    m_GameConfig.timingReward.roulette_rate_cost  = CIXml::getIntProperty( pTimingReward , "roulette_rate_cost" , 1 );
                }

                /// 定时奖励;
                xmlNodePtr pFreeMoney = xml.getFirstChildNode( rootPtr , "free_money" );
                if ( NULL != pFreeMoney )
                {
                    m_GameConfig.FreeMoney.count            = CIXml::getIntProperty( pFreeMoney, "count" , 5 );
                    m_GameConfig.FreeMoney.money            = CIXml::getIntProperty( pFreeMoney, "money" , 1000 );
                    m_GameConfig.FreeMoney.limit_give_out   = CIXml::getIntProperty( pFreeMoney, "limit_give_out" , 1000 );
                    m_GameConfig.FreeMoney.bonus_time       = CIXml::getIntProperty( pFreeMoney, "bonus_time_minute" , 30 ) * 60;
                    m_GameConfig.FreeMoney.bonus_money      = CIXml::getIntProperty( pFreeMoney, "bonus_money" , 2000 );
                    m_GameConfig.FreeMoney.bonus_day_max_cnt= CIXml::getIntProperty( pFreeMoney, "bonus_day_max_cnt" , 60 );
                }

                /// 分享奖励;
                xmlNodePtr pShareReward = xml.getFirstChildNode( rootPtr , "share_reward" );
                if ( NULL != pShareReward )
                {
                    m_GameConfig.ShareReward.share_reward_item_list.clear();
                    m_GameConfig.ShareReward.share_reward_day_max_cnt     = CIXml::getIntProperty( pShareReward, "bonus_day_max_cnt" , 1 );
                    m_GameConfig.ShareReward.share_reward_time            = CIXml::getIntProperty( pShareReward, "share_time_minute" , 30 ) * 60;
                    
                    xmlNodePtr ItemXml = xml.getFirstChildNode( pShareReward , "item" );
                    for ( ; ItemXml!=NULL; ItemXml=xml.getNextChildNode(ItemXml,"item") )
                    {
                        ItemEntity Item;
                        Item.item_tid = CIXml::getIntProperty( ItemXml , "id"    , 0 );
                        Item.item_num = CIXml::getIntProperty( ItemXml , "count" , 0 );
                        m_GameConfig.ShareReward.share_reward_item_list.push_back( Item );
                    }
                }
                
                /// 绑定好友奖励;
                xmlNodePtr pBindFriendReward = xml.getFirstChildNode( rootPtr , "bind_friend_reward" );
                if ( NULL != pBindFriendReward )
                {
                    m_GameConfig.BindFriendReward.bind_src_reward			= CIXml::getIntProperty( pBindFriendReward, "bind_other_reward" , 1 );
					m_GameConfig.BindFriendReward.play_src_reward			= CIXml::getIntProperty( pBindFriendReward, "play_other_reward" , 1 );
                    m_GameConfig.BindFriendReward.bind_max					= CIXml::getIntProperty( pBindFriendReward, "bind_max" , 0 );
                    m_GameConfig.BindFriendReward.dst_bind_reward			= CIXml::getIntProperty( pBindFriendReward, "each_bind_reward" , 1 );
                    m_GameConfig.BindFriendReward.dst_need_play_count		= CIXml::getIntProperty( pBindFriendReward, "need_game_count" , 1 );
                    m_GameConfig.BindFriendReward.dst_play_reward			= CIXml::getIntProperty( pBindFriendReward, "game_count_reward" , 1 );
                    m_GameConfig.BindFriendReward.reward_item_id			= CIXml::getIntProperty( pBindFriendReward, "reward_item_id" , 0 );
					m_GameConfig.BindFriendReward.reward_need_create_time   = CIXml::getIntProperty( pBindFriendReward, "reward_need_create_time" , 0 ) * 24 * 60 * 60;
                }

                /// 牌友圈配置;
                xmlNodePtr pFriendTissue = xml.getFirstChildNode( rootPtr , "friend_tissue" );
                if ( NULL != pFriendTissue )
                {
                    m_GameConfig.FriendTissueConfig.normal_create_limit   = CIXml::getIntProperty( pFriendTissue, "create_normal_limit" , 1 );
                    m_GameConfig.FriendTissueConfig.vip_create_limit      = CIXml::getIntProperty( pFriendTissue, "create_vip_limit" , 1 );
                    m_GameConfig.FriendTissueConfig.join_limit            = CIXml::getIntProperty( pFriendTissue, "join_limit" , 1 );
                    m_GameConfig.FriendTissueConfig.vip_default_money     = CIXml::getIntProperty( pFriendTissue, "create_vip_default_money" , 0 );
                    m_GameConfig.FriendTissueConfig.vip_default_limit     = CIXml::getIntProperty( pFriendTissue, "circle_default_limit" , 2 );
                    m_GameConfig.FriendTissueConfig.name_limit            = CIXml::getIntProperty( pFriendTissue, "circle_name_limit" , 16 );
                    m_GameConfig.FriendTissueConfig.infinit_limit_num     = CIXml::getIntProperty( pFriendTissue, "infinite_limit_num" , 9999 );

                    xmlNodePtr VipItemXml = xml.getFirstChildNode( pFriendTissue , "create_vip_cost" );
                    for ( ; VipItemXml!=NULL; VipItemXml=xml.getNextChildNode(VipItemXml,"create_vip_cost") )
                    {
                        m_GameConfig.FriendTissueConfig.create_vip_cost_item.item_tid = CIXml::getIntProperty( VipItemXml , "item_id"    , 0 );
                        m_GameConfig.FriendTissueConfig.create_vip_cost_item.item_num = CIXml::getIntProperty( VipItemXml , "num" , 0 );
                    }

                    xmlNodePtr NormalItemXml = xml.getFirstChildNode( pFriendTissue , "create_normal_cost" );
                    for ( ; NormalItemXml!=NULL; NormalItemXml=xml.getNextChildNode(NormalItemXml,"create_normal_cost") )
                    {
                        m_GameConfig.FriendTissueConfig.create_vip_cost_item.item_tid = CIXml::getIntProperty( NormalItemXml , "item_id"    , 0 );
                        m_GameConfig.FriendTissueConfig.create_vip_cost_item.item_num = CIXml::getIntProperty( NormalItemXml , "num" , 0 );
                    }
                }

                ///   礼品配置;
                m_GameConfig.CDKey.clear();
                xmlNodePtr pCDKey = xml.getFirstChildNode( rootPtr , "cdkey" );

                if ( pCDKey!=NULL )
                {
                    xmlNodePtr pCDKeyItem = xml.getFirstChildNode( pCDKey , "template" );

                    for ( ; pCDKeyItem!=NULL; pCDKeyItem= xml.getNextChildNode(pCDKeyItem,"template") )
                    {
                        CDKeyConfigXml       cdkey_item;
                        cdkey_item.id               = CIXml::getIntProperty( pCDKeyItem, "id", 1000 );
                        cdkey_item.money            = CIXml::getIntProperty( pCDKeyItem, "money", 1000 );

                        std::pair<DEF::TEMPLATE_ID, uint32>  item;
                        xmlNodePtr pItem = xml.getFirstChildNode( pCDKeyItem , "item" );
                        for ( ; pItem!=NULL; pItem= xml.getNextChildNode(pItem,"item") )
                        {
                            item.first  = CIXml::getIntProperty( pItem, "tid", 0 );
                            item.second = CIXml::getIntProperty( pItem, "num", 0 );

                            cdkey_item.items.push_back(item);
                        }

                        m_GameConfig.CDKey[cdkey_item.id] = cdkey_item;
                    }
                }

                xmlNodePtr pGift = xml.getFirstChildNode( rootPtr, "gift" );
                if ( NULL != pGift )
                {
                    m_GameConfig.GiftConfig.tip_max         = CIXml::getIntProperty( pGift, "tip_max", 0 );
                    m_GameConfig.GiftConfig.target_tip_max  = CIXml::getIntProperty( pGift, "target_tip_max", 0);
                    m_GameConfig.GiftConfig.duration_hour   = CIXml::getIntProperty( pGift, "duration_hour", 0 );
                }

                xmlNodePtr pEvelope = xml.getFirstChildNode( rootPtr, "red_envelope" );
                if ( NULL != pEvelope )
                {
                    m_GameConfig.EvelopeConfig.money_max = CIXml::getIntProperty( pEvelope, "day_limit", 0 );
                    m_GameConfig.EvelopeConfig.count     = CIXml::getIntProperty( pEvelope, "count", 0);
                    m_GameConfig.EvelopeConfig.money_min = CIXml::getIntProperty( pEvelope, "at_least", 0 );
                }

                ///////////////////////             打赏类型 金币
                //xmlNodePtr pTipsConfig = xml.getFirstChildNode( rootPtr , "tips" );
                //m_GameConfig.tips.clear();

                //for ( ; pTipsConfig!=NULL; pTipsConfig= xml.getNextChildNode(pTipsConfig,"tips") )
                //{
                //    uint32  tip_type    = CIXml::getIntProperty( pTipsConfig, "type", 1 ); 
                //    uint32  tip_money   = CIXml::getIntProperty( pTipsConfig, "money", 0 );

                //    m_GameConfig.tips.insert( std::make_pair( tip_type, tip_money ) );
                //} 

                ///////////////////////////          http test地址;

                xmlNodePtr pUrlTestConifg = xml.getFirstChildNode( rootPtr , "http_api");
                m_GameConfig.HttpTestAPIConfig.clear();
                for ( ; pUrlTestConifg != NULL ;pUrlTestConifg = xml.getNextChildNode( pUrlTestConifg , "http_api" ))
                {
                    std::string name = CIXml::getStringProperty( pUrlTestConifg,"name", "" );
                    std::string url = CIXml::getStringProperty( pUrlTestConifg,"url","" );
                    m_GameConfig.HttpTestAPIConfig.insert(pair<string,string>( name , url )); 
                }

                //   http 正式地址
                xmlNodePtr pZsUrlConifg = xml.getFirstChildNode( rootPtr , "http_api_waiwang");
                m_GameConfig.HttpWWangAPIConfig.clear();
                for ( ; pZsUrlConifg != NULL ;pZsUrlConifg = xml.getNextChildNode( pZsUrlConifg , "http_api_waiwang" ))
                {
                    std::string name = CIXml::getStringProperty( pZsUrlConifg,"name", "" );
                    std::string url = CIXml::getStringProperty( pZsUrlConifg,"url","" );
                    m_GameConfig.HttpWWangAPIConfig.insert(pair<string,string>(name , url)); 
                }

                /// 消耗道具;
                xmlNodePtr pUseScore = xml.getFirstChildNode(rootPtr , "use_item_score_clear");
                if ( NULL != pUseScore )
                {
                    m_GameConfig.UseItemConfig.score_clear_id = CIXml::getIntProperty( pUseScore , "id" , 0 );
                }
                /// 消耗道具;
                xmlNodePtr pUseHorn = xml.getFirstChildNode(rootPtr , "use_item_pao_ma_deng");
                if ( NULL != pUseHorn )
                {
                    m_GameConfig.UseItemConfig.horn_id = CIXml::getIntProperty( pUseHorn , "id" , 0 );
                }

                xmlNodePtr pAdvertisingConfig = xml.getFirstChildNode( rootPtr, "advertising" );
                if ( NULL != pAdvertisingConfig )
                { 
                    m_GameConfig.AdsConfig.ads_number       = CIXml::getIntProperty( pAdvertisingConfig, "advertising", 5 );
                    m_GameConfig.AdsConfig.interval_minute  = CIXml::getIntProperty( pAdvertisingConfig, "interval_minute", 30 );
                    m_GameConfig.AdsConfig.money            = CIXml::getIntProperty( pAdvertisingConfig, "money", 1000 );
                }

                xmlNodePtr pFormula = xml.getFirstChildNode( rootPtr , "formula" );
                if ( pFormula!=NULL )
                {
                    xmlNodePtr pField = xml.getFirstChildNode(pFormula, XML_ELEMENT_NODE);
                    for ( ; pField!=NULL; pField=xml.getNextChildNode(pField, XML_ELEMENT_NODE) )
                    {
                        std::string formula_name = (const char *)pField->name;
                        m_Formulas[formula_name] = CIXml::getStringProperty(pField, "value", "" );
                    }
                }

				/// 绑定奖励数据;
				xmlNodePtr pBindRewardPtr = xml.getFirstChildNode(rootPtr , "bind_reward");
				if ( NULL != pBindRewardPtr )
				{
					m_GameConfig.BindReward.item_id  = CIXml::getIntProperty( pBindRewardPtr , "item" , 0 );
					m_GameConfig.BindReward.mobile_reward  = CIXml::getIntProperty( pBindRewardPtr , "mobile" , 0 );
					m_GameConfig.BindReward.idcard_reward  = CIXml::getIntProperty( pBindRewardPtr , "idcard" , 0 );
					m_GameConfig.BindReward.bankcard_reward  = CIXml::getIntProperty( pBindRewardPtr , "bankcard" , 0 );
				}

				/// 老玩家回归奖励数据;
				xmlNodePtr pBackRewardPtr = xml.getFirstChildNode(rootPtr , "back_reward");
				if ( NULL != pBackRewardPtr )
				{
                    m_GameConfig.BackReward.region_list.clear();
					m_GameConfig.BackReward.start  = CIXml::getIntProperty( pBackRewardPtr , "start" , 0 );
					m_GameConfig.BackReward.end  = CIXml::getIntProperty( pBackRewardPtr , "end" , 0 );
					m_GameConfig.BackReward.last  = CIXml::getIntProperty( pBackRewardPtr , "last" , 0 );
					m_GameConfig.BackReward.itemid  = CIXml::getIntProperty( pBackRewardPtr , "itemid" , 0 );
					m_GameConfig.BackReward.count  = CIXml::getIntProperty( pBackRewardPtr , "count" , 0 );
					xmlNodePtr ItemXml = xml.getFirstChildNode( pBackRewardPtr , "region" );
					for ( ; ItemXml!=NULL; ItemXml=xml.getNextChildNode(ItemXml,"region") )
					{
						BackRewardRegion Item;
						Item.appname = CIXml::getStringProperty( ItemXml, "appname", "" );
						Item.item_id = CIXml::getIntProperty( ItemXml, "itemid", 0 );
						Item.item_count = CIXml::getIntProperty( ItemXml, "count", 0 );
						m_GameConfig.BackReward.region_list.push_back( Item );
					}
				}

				/// Http配置 0：外网 1：正式
				xmlNodePtr pHttpConfigPtr = xml.getFirstChildNode(rootPtr , "http_config");
				if ( NULL != pHttpConfigPtr )
				{
					m_GameConfig.HttpConfig.type  = CIXml::getIntProperty( pHttpConfigPtr , "type" , 0 );
				}

				/// 聚合数据配置
				xmlNodePtr pJuHeConfigPtr = xml.getFirstChildNode(rootPtr , "juhe_config");
				if ( NULL != pJuHeConfigPtr )
				{
					m_GameConfig.JuHeConfig.app_key  = CIXml::getStringProperty( pJuHeConfigPtr , "appkey" , "" );
				}

                res = true;
            }
        }

        file.close ();
    }

    return res;
}

bool CStaticTableMgr::load_config( std::string xml_name, TStaticData& static_data )
{
    bool res = false;

	if ( !NLMISC::CPath::exists( xml_name+".xml" ) )
	{
		nlwarning("load_config  file not find : %s.xml", xml_name.c_str() );
		return res;
	}
	
    string path = NLMISC::CPath::lookup(xml_name+".xml");
    CIFile file;

    if (file.open (path))
    {
        CIXml xml;
        if (xml.init (file))
        {
            xmlNodePtr rootPtr = xml.getRootNode();

            if ( rootPtr )
            {
                clear_config(static_data);

                xmlNodePtr record=xml.getFirstChildNode (rootPtr, xml_name.c_str());

                for ( ; record!=NULL; record=xml.getNextChildNode (record, xml_name.c_str()) )
                {
                    xmlNodePtr field = xml.getFirstChildNode(record,XML_ELEMENT_NODE);
                    StaticData::RecordBase*  pRecord = new(std::nothrow) StaticData::RecordBase();
                    for ( ; field!=NULL; field=xml.getNextChildNode(field,XML_ELEMENT_NODE) )
                    {
                        ATTRIB_TYPE::TAttribType   field_attrib;
                        if ( !TAttribType_Parse( string((const char *)field->name), &field_attrib ) )
                        {
                            nlwarning("TAttribType Parse Error. xmlname=%s field=%s",xml_name.c_str(),(const char *)field->name);
                            continue;
                        }

                        const CSString field_type   = xml.getStringProperty(field, "valueType", "");
                        const CSString field_val    = xml.getStringProperty(field, "value", "");
                        const CSString field_save   = xml.getStringProperty(field, "isSave", "");

                        nlassert( field_type.size()>0 );

                        if ( field_type=="int" || field_type=="string" || field_type=="bool" || field_type=="long" )
                        {
                            StaticData::FieldBase* pFieldBase = new(std::nothrow) StaticData::FieldBase();
                            pFieldBase->set( field_attrib, field_type, field_val );
                            pRecord->addAttribute( pFieldBase, field_save );
                        }
                        else
                        {
                            addToRecord( field_attrib, field_type, field_val, field_save, pRecord );
                        }
                    }
                    static_data[pRecord->getAttribute(ATTRIB_TYPE::ID)->m_int] = pRecord;
                }
                res = true;
            }
        }
        file.close ();
    }
    return res;
}

void CStaticTableMgr::clear_config( TStaticData& static_data )
{
    TStaticData::iterator iter = static_data.begin();

    while (iter!=static_data.end())
    {
        delete iter->second;
        ++iter;
    }

    static_data.clear();
}

RoomConfigXml* CStaticTableMgr::GetRoomConfigXml( std::string room_type )
{
    RoomConfigXml* pRoomConfigXml = NULL;
    TRoomConfigXml::iterator iter = m_GameConfig.rooms.find(room_type);

    if ( iter!=m_GameConfig.rooms.end() )
    {
        pRoomConfigXml = &(iter->second);
    }

    return pRoomConfigXml;
}

ChallengeConfig* CStaticTableMgr::GetChallengeConfig( std::string room_type )
{
    ChallengeConfig*  pChallengeConfig = NULL;

    TChallengeConfigXml::iterator iter = m_GameConfig.Challenge.find( room_type );

    if ( iter!=m_GameConfig.Challenge.end() )
    {
        pChallengeConfig = &(iter->second);
    }

    return pChallengeConfig;
}


BlackjackShuffle& CStaticTableMgr::GetBlackjackShuffleConfig( std::string room_type )
{
    TBlackjackShuffle::iterator iter = m_BlackjackShuffle.find( room_type );

    if ( iter!=m_BlackjackShuffle.end() )
    {
        return iter->second;
    }

    return m_DefaultBlackjackShuffle;
}

BlackJackCoinVal& CStaticTableMgr::GetBlackjackCoinValConfig( std::string room_type )
{
    TBlackJackCoinVal::iterator iter = m_BlackJackCoinVal.find( room_type );

    if ( iter!=m_BlackJackCoinVal.end() )
    {
        return iter->second;
    }

    return m_DefaultBlackJackCoinVal;
}

CDKeyConfigXml* CStaticTableMgr::GetCDKeyConfig( uint32 template_id )
{
    TCDKeyConfigXml::iterator iter = m_GameConfig.CDKey.find( template_id );

    if ( iter!=m_GameConfig.CDKey.end() )
    {
        return &(iter->second);
    }

    return NULL;
}

bool CStaticTableMgr::load_vip_config()
{
    bool res = false;
    string path;

    try
    {
        path = NLMISC::CPath::lookup("VIPConfig.xml");
    }
    catch (...)
    {
        return false;
    }

    CIFile file;
    CIXml xml;

    if (file.open (path))
    {
        if (xml.init (file))
        {
            xmlNodePtr rootPtr = xml.getRootNode();

            if ( rootPtr )
            {
                m_GameConfig.vip.clear();
                xmlNodePtr pVipConfig = xml.getFirstChildNode( rootPtr, "level_up" );

                for ( ; pVipConfig!=NULL; pVipConfig=xml.getNextChildNode(pVipConfig, "level_up") )
                {
                    VIPConfigXml   vip_config;
                    vip_config.level            = CIXml::getIntProperty( pVipConfig,   "level", 0 );
                    vip_config.level_up_exp     = CIXml::getIntProperty( pVipConfig,   "level_up_exp", 0 );
                    vip_config.buy_money        = CIXml::getFloatProperty( pVipConfig, "buy_money", 0 );
                    vip_config.bonus            = CIXml::getFloatProperty( pVipConfig, "bonus", 0 );
                    vip_config.buy_back_add_num = CIXml::getFloatProperty( pVipConfig, "buy_back_add_num", 0 );

                    m_GameConfig.vip.push_back( vip_config );
                }

                xmlNodePtr pSaleVipConfig = xml.getFirstChildNode( rootPtr, "sale_vip" );

                for ( ; pSaleVipConfig!=NULL; pSaleVipConfig=xml.getNextChildNode(pSaleVipConfig, "sale_vip") )
                {
                    SaleVipConfig   vip_config;
                    uint32 level            = CIXml::getIntProperty( pSaleVipConfig,   "level", 0 );
                    vip_config.shop_plus    = CIXml::getFloatProperty( pSaleVipConfig, "buy_money", 0 );
                    vip_config.bonus_plus   = CIXml::getFloatProperty( pSaleVipConfig, "bonus", 0 );
                    vip_config.reward_money = CIXml::getIntProperty( pSaleVipConfig, "buy_back_add_num", 0 );

                    m_GameConfig.SaleVipsConfig[level] = vip_config;
                }

                res = true;
            }
        }

        file.close ();
    }

    return res;
}

VIPConfigXml* CStaticTableMgr::GetVIPConfig( uint32 vip_level )
{
    VIPConfigXml* pConfig = NULL;

    for ( uint i=0; i<m_GameConfig.vip.size(); ++i )
    {
        if ( vip_level == m_GameConfig.vip[i].level )
        {
			return &m_GameConfig.vip[i];
        }
    }

    return pConfig;
}

PigConfigXml* CStaticTableMgr::GetPigConfig( uint32 pig_id )
{
    PigConfigXml* pConfig = NULL;

    TPigConfigXml::iterator iter = m_PigConfig.find(pig_id);

    if ( iter != m_PigConfig.end() )
    {
        pConfig = &(iter->second);
    }

    return pConfig;
}

bool CStaticTableMgr::load_game_texaspoker_config( void )
{
    bool res = false;
    string path;

    try
    {
        path = NLMISC::CPath::lookup("GameTexasPoker.xml");
    }
    catch (...)
    {
        return false;
    }

    CIFile file;
    CIXml xml;

    if ( !file.open( path ) ) {
        return false;
    }
    if ( !xml.init( file  ) ) {
        return false;
    }
    xmlNodePtr rootPtr = xml.getRootNode();
    if ( NULL == rootPtr ) {
        return false;
    }
    // texaspoker_state_wait;
    {
        xmlNodePtr statetime = xml.getFirstChildNode( rootPtr , "texaspoker_state_time" );
        if ( NULL != statetime )
        {
            GetTexaspokerConfig().TexaspokerStateWait.actionTime = CIXml::getIntProperty(statetime, "actionTime", 1);
            GetTexaspokerConfig().TexaspokerStateWait.startPer   = CIXml::getIntProperty(statetime, "startPer"  , 1);
            GetTexaspokerConfig().TexaspokerStateWait.endPer     = CIXml::getIntProperty(statetime, "endPer"    , 1);
            GetTexaspokerConfig().TexaspokerStateWait.startFlop  = CIXml::getIntProperty(statetime, "startFlop" , 1);
            GetTexaspokerConfig().TexaspokerStateWait.endFlop    = CIXml::getIntProperty(statetime, "endFlop"   , 1);
            GetTexaspokerConfig().TexaspokerStateWait.startTurn  = CIXml::getIntProperty(statetime, "startTurn" , 1);
            GetTexaspokerConfig().TexaspokerStateWait.endTurn    = CIXml::getIntProperty(statetime, "endTurn"   , 1);
            GetTexaspokerConfig().TexaspokerStateWait.startRiver = CIXml::getIntProperty(statetime, "startRiver", 1);
            GetTexaspokerConfig().TexaspokerStateWait.endRiver   = CIXml::getIntProperty(statetime, "endRiver"  , 1);
            GetTexaspokerConfig().TexaspokerStateWait.interim    = CIXml::getIntProperty(statetime, "showDownInterim",1);
            GetTexaspokerConfig().TexaspokerStateWait.showDown   = CIXml::getIntProperty(statetime, "showDown"  , 1);
            GetTexaspokerConfig().TexaspokerStateWait.cleanJunk  = CIXml::getIntProperty(statetime, "cleanJunk" , 1);
            GetTexaspokerConfig().TexaspokerStateWait.closeRoom  = CIXml::getIntProperty(statetime, "closeRoom" , 1);
        }
    }
    // texaspoker room data;
    {
        xmlNodePtr pTexaspoker = xml.getFirstChildNode( rootPtr , "texaspoker_room_data" );
        for ( ; pTexaspoker!=NULL; pTexaspoker=xml.getNextChildNode(pTexaspoker, "texaspoker_room_data") )
        {
            TexaspokerRoomData roomData;
            roomData.room_type          = CIXml::getStringProperty( pTexaspoker , "room_type", "");
            roomData.largePour          = CIXml::getIntProperty( pTexaspoker , "large_blind" , 0 );
            roomData.smallPour          = CIXml::getIntProperty( pTexaspoker , "small_blind" , 0 );
            roomData.autoStand          = CIXml::getIntProperty( pTexaspoker , "auto_stand"  , 0 );
            roomData.double_poll        = CIXml::getIntProperty( pTexaspoker , "double_poll" , 0 );
            roomData.double_time        = CIXml::getIntProperty( pTexaspoker , "double_time" , 0 )    * 60;
            roomData.double_time_inc    = CIXml::getIntProperty( pTexaspoker , "double_time_inc", 0 ) * 60;
            roomData.multiple           = CIXml::getIntProperty( pTexaspoker , "multiple"    , 0 );
            roomData.basePour           =   CIXml::getIntProperty( pTexaspoker , "basePour"    , 0 );
            roomData.reward1            = CIXml::getIntProperty( pTexaspoker , "reward1"     , 0 );
            roomData.reward2            = CIXml::getIntProperty( pTexaspoker , "reward2"     , 0 );
            roomData.reward3            = CIXml::getIntProperty( pTexaspoker , "reward3"     , 0 );
            roomData.isSelfCoins        = (bool)CIXml::getIntProperty( pTexaspoker , "handle_self_coins" , 0 );
            roomData.possess_score      = CIXml::getIntProperty( pTexaspoker , "possess_score" , 0 );
            roomData.chall_min_num      = CIXml::getIntProperty( pTexaspoker , "chall_min_num" , 1 );
            roomData.chall_max_num      = CIXml::getIntProperty( pTexaspoker , "chall_max_num" , 1 );
            roomData.isRankin           = (bool)CIXml::getIntProperty( pTexaspoker , "is_rankin" , 0 );
            GetTexaspokerConfig().TexaspokerRoom[roomData.room_type] = roomData;
        }
    }
    // load texaspoker chall time data;
    {
        load_challenge_config( xml );
    }
    return true;
}

bool CStaticTableMgr::load_game_blackjack_config()
{
    bool res = false;
    string path;

    try
    {
        path = NLMISC::CPath::lookup("GameBlackJack.xml");
    }
    catch (...)
    {
        return false;
    }

    CIFile file;
    CIXml xml;

    if (file.open (path))
    {
        if (xml.init (file))
        {
            xmlNodePtr rootPtr = xml.getRootNode();

            if ( rootPtr )
            {
                xmlNodePtr pBlackjackStateWait = xml.getFirstChildNode( rootPtr , "blackjack_state_wait" );

                if( pBlackjackStateWait!=NULL )
                {
                    BlackjackStateWaitConfig   state_wait;

                    state_wait.wait_finish          = CIXml::getIntProperty( pBlackjackStateWait, "wait_finish", 1 );
                    state_wait.wait_pour            = CIXml::getIntProperty( pBlackjackStateWait, "wait_pour", 1 );
                    state_wait.wait_determine       = CIXml::getIntProperty( pBlackjackStateWait, "wait_determine", 1 );
                    state_wait.wait_player_action   = CIXml::getIntProperty( pBlackjackStateWait, "wait_player_action", 1 );
                    state_wait.wait_split           = CIXml::getIntProperty( pBlackjackStateWait, "wait_split", 1 );

                    m_GameConfig.BlackjackStateWait = state_wait;
                }

                xmlNodePtr pBlackJackCoinVal = xml.getFirstChildNode( rootPtr , "blackjack_coin_val" );

                for ( ; pBlackJackCoinVal!=NULL; pBlackJackCoinVal=xml.getNextChildNode(pBlackJackCoinVal, "blackjack_coin_val") )
                {
                    BlackJackCoinVal   room_coin;

                    std::string  room_type = CIXml::getStringProperty( pBlackJackCoinVal, "room_type", "" );
                    room_coin.coin_1       = CIXml::getIntProperty( pBlackJackCoinVal, "coin_1", 0 );
                    room_coin.coin_2       = CIXml::getIntProperty( pBlackJackCoinVal, "coin_2", 0 );
                    room_coin.coin_3       = CIXml::getIntProperty( pBlackJackCoinVal, "coin_3", 0 );
                    room_coin.coin_4       = CIXml::getIntProperty( pBlackJackCoinVal, "coin_4", 0 );

                    m_BlackJackCoinVal[room_type] = room_coin;
                }

                xmlNodePtr pBlackjackShuffle = xml.getFirstChildNode( rootPtr , "blackjack_shuffle" );

                for ( ; pBlackjackShuffle!=NULL; pBlackjackShuffle=xml.getNextChildNode(pBlackjackShuffle, "blackjack_shuffle") )
                {
                    BlackjackShuffle   room_shuffle;

                    std::string  room_type            = CIXml::getStringProperty( pBlackjackShuffle, "room_type", "" );
                    room_shuffle.deck_of_cards        = CIXml::getIntProperty( pBlackjackShuffle, "deck_of_cards", 3 );
                    room_shuffle.shuffle_limit_cards  = CIXml::getIntProperty( pBlackjackShuffle, "shuffle_limit_cards", 10 );
                    room_shuffle.take_out_10          = CIXml::getIntProperty( pBlackjackShuffle, "take_out_10", 0 );
                    room_shuffle.give_banker_10_rate  = CIXml::getIntProperty( pBlackjackShuffle, "give_banker_10_rate", 0 );

                    m_BlackjackShuffle[room_type] = room_shuffle;
                }

                load_challenge_config( xml );

                res = true;
            }
        }

        file.close ();
    }

    return res;
}

bool CStaticTableMgr::load_game_runfast_config()
{
    bool res = false;
    string path;

    try
    {
        path = NLMISC::CPath::lookup("GameRunFast.xml");
    }
    catch (...)
    {
        return false;
    }

    CIFile file;
    CIXml xml;

    if (file.open (path))
    {
        if (xml.init (file))
        {
            xmlNodePtr rootPtr = xml.getRootNode();

            if ( rootPtr )
            {
                // 跑得快状态时间;
                {
                    // 等待开始时间
                    xmlNodePtr pStateTime = xml.getFirstChildNode( rootPtr , "wait_time" );
                    m_GameConfig.RunFastStateWaite.WaitTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

                    // 等待开始超时
                    pStateTime = xml.getFirstChildNode( rootPtr , "wait_time_out" );
                    m_GameConfig.RunFastStateWaite.WaitTimeOut = CIXml::getIntProperty( pStateTime , "time" , 0 );

                    // 检查游戏开始
                    pStateTime = xml.getFirstChildNode( rootPtr , "check_start_game" );
                    m_GameConfig.RunFastStateWaite.CheckGameTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

                    // 游戏开始时间
                    pStateTime = xml.getFirstChildNode( rootPtr , "start_time" );
                    m_GameConfig.RunFastStateWaite.StartTime   = CIXml::getIntProperty( pStateTime , "time" , 0 );

                    // 发牌时间
                    pStateTime = xml.getFirstChildNode( rootPtr , "brand_time" );
                    m_GameConfig.RunFastStateWaite.BrandTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

                    // 玩家活动时间
                    pStateTime = xml.getFirstChildNode( rootPtr , "action_time" );
                    m_GameConfig.RunFastStateWaite.ActionTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

                    // 出牌时间
                    pStateTime = xml.getFirstChildNode( rootPtr , "outcard_time" );
                    m_GameConfig.RunFastStateWaite.OutCardTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

                    // 结算时间
                    pStateTime = xml.getFirstChildNode( rootPtr , "showdown_time" );
                    m_GameConfig.RunFastStateWaite.ShowDwonTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

                    // 解散房间时间
                    pStateTime = xml.getFirstChildNode( rootPtr , "relieve_time" );
                    m_GameConfig.RunFastStateWaite.Relievetime  = CIXml::getIntProperty( pStateTime , "time" , 0 );
                    // 托管时间
                    pStateTime = xml.getFirstChildNode( rootPtr , "trust_time" );
                    m_GameConfig.RunFastStateWaite.TrustTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );
                    // 挂机时间
                    pStateTime = xml.getFirstChildNode( rootPtr , "machine_time" );
                    m_GameConfig.RunFastStateWaite.MachineTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );
                    // 智力运动会房间最大存活时间
                    pStateTime = xml.getFirstChildNode( rootPtr , "room_max_time" );
                    m_GameConfig.RunFastStateWaite.MSGRoomMaxTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );
                    // 加积分;
                    {
                        xmlNodePtr pRoomData = xml.getFirstChildNode( rootPtr , "integral_win" );
                        if ( NULL != pRoomData )
                        {
                            m_GameConfig.RunFastStateWaite.Integral = CIXml::getIntProperty( pRoomData , "integral" , 0  );
                        }
                    }
                }
                res = true;
            }
        }

        file.close ();
    }

    return res;
}

bool CStaticTableMgr::load_game_doushisi_config()
{
	bool res = false;
	string path;

	try
	{
		path = NLMISC::CPath::lookup("GameDouShiSi.xml");
	}
	catch (...)
	{
		return false;
	}

	CIFile file;
	CIXml xml;

	if (file.open (path))
	{
		if (xml.init (file))
		{
			xmlNodePtr rootPtr = xml.getRootNode();

			if ( rootPtr )
			{
				// 跑得快状态时间;
				{
					// 等待开始时间
					xmlNodePtr pStateTime = xml.getFirstChildNode( rootPtr , "wait_time" );
					m_GameConfig.DouShiSiStateWait.WaitTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

					// 等待开始超时
					pStateTime = xml.getFirstChildNode( rootPtr , "wait_time_out" );
					m_GameConfig.DouShiSiStateWait.WaitTimeOut = CIXml::getIntProperty( pStateTime , "time" , 0 );

					// 检查游戏开始
					pStateTime = xml.getFirstChildNode( rootPtr , "check_start_game" );
					m_GameConfig.DouShiSiStateWait.CheckGameTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

					// 游戏开始时间
					pStateTime = xml.getFirstChildNode( rootPtr , "start_time" );
					m_GameConfig.DouShiSiStateWait.StartTime   = CIXml::getIntProperty( pStateTime , "time" , 0 );

					// 发牌时间
					pStateTime = xml.getFirstChildNode( rootPtr , "brand_time" );
					m_GameConfig.DouShiSiStateWait.BrandTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

					// 玩家活动时间
					pStateTime = xml.getFirstChildNode( rootPtr , "action_time" );
					m_GameConfig.DouShiSiStateWait.ActionTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

					// 出牌时间
					pStateTime = xml.getFirstChildNode( rootPtr , "outcard_time" );
					m_GameConfig.DouShiSiStateWait.OutCardTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

					// 结算时间
					pStateTime = xml.getFirstChildNode( rootPtr , "showdown_time" );
					m_GameConfig.DouShiSiStateWait.ShowDwonTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

					// 解散房间时间
					pStateTime = xml.getFirstChildNode( rootPtr , "relieve_time" );
					m_GameConfig.DouShiSiStateWait.Relievetime  = CIXml::getIntProperty( pStateTime , "time" , 0 );
					// 托管时间
					pStateTime = xml.getFirstChildNode( rootPtr , "trust_time" );
					m_GameConfig.DouShiSiStateWait.TrustTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );
					// 手牌补花时间;
					pStateTime = xml.getFirstChildNode( rootPtr , "hand_card_mend" );
					m_GameConfig.DouShiSiStateWait.TrustTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );
					// 抓牌补花时间
					pStateTime = xml.getFirstChildNode( rootPtr , "ahold_card_mend" );
					m_GameConfig.DouShiSiStateWait.TrustTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );
					// 翻拍时间
					pStateTime = xml.getFirstChildNode( rootPtr , "fan_card" );
					m_GameConfig.DouShiSiStateWait.TrustTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );
				}
				res = true;
			}
		}

		file.close ();
	}

	return res;
}

bool CStaticTableMgr::load_game_penghu_config()
{
	bool res = false;
	string path;

	try
	{
		path = NLMISC::CPath::lookup("GamePengHu.xml");
	}
	catch (...)
	{
		return false;
	}

	CIFile file;
	CIXml xml;

	if (file.open (path))
	{
		if (xml.init (file))
		{
			xmlNodePtr rootPtr = xml.getRootNode();

			if ( rootPtr )
			{
				// 跑得快状态时间;
				{
					// 等待开始时间
					xmlNodePtr pStateTime = xml.getFirstChildNode( rootPtr , "wait_time" );
					m_GameConfig.PengHuStateWait.WaitTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

					// 等待开始超时
					pStateTime = xml.getFirstChildNode( rootPtr , "wait_time_out" );
					m_GameConfig.PengHuStateWait.WaitTimeOut = CIXml::getIntProperty( pStateTime , "time" , 0 );

					// 检查游戏开始
					pStateTime = xml.getFirstChildNode( rootPtr , "check_start_game" );
					m_GameConfig.PengHuStateWait.CheckGameTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

					// 游戏开始时间
					pStateTime = xml.getFirstChildNode( rootPtr , "start_time" );
					m_GameConfig.PengHuStateWait.StartTime   = CIXml::getIntProperty( pStateTime , "time" , 0 );

					// 发牌时间
					pStateTime = xml.getFirstChildNode( rootPtr , "brand_time" );
					m_GameConfig.PengHuStateWait.BrandTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

					// 玩家活动时间
					pStateTime = xml.getFirstChildNode( rootPtr , "action_time" );
					m_GameConfig.PengHuStateWait.ActionTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

					// 出牌时间
					pStateTime = xml.getFirstChildNode( rootPtr , "outcard_time" );
					m_GameConfig.PengHuStateWait.OutCardTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

					// 结算时间
					pStateTime = xml.getFirstChildNode( rootPtr , "showdown_time" );
					m_GameConfig.PengHuStateWait.ShowDwonTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

					// 解散房间时间
					pStateTime = xml.getFirstChildNode( rootPtr , "relieve_time" );
					m_GameConfig.PengHuStateWait.Relievetime  = CIXml::getIntProperty( pStateTime , "time" , 0 );
					// 托管时间
					pStateTime = xml.getFirstChildNode( rootPtr , "trust_time" );
					m_GameConfig.PengHuStateWait.TrustTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );
					// 托管时间
					pStateTime = xml.getFirstChildNode( rootPtr , "fan_card" );
					m_GameConfig.PengHuStateWait.FanCardTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );
				}
				res = true;
			}
		}

		file.close ();
	}

	return res;
}

bool CStaticTableMgr::GetIfHorseExist(uint32 horse_id)
{
    bool res = false;
    THorsesVal::iterator iter = StaticTableMgr.GetHorseListConfig().find(horse_id);

    if ( iter != StaticTableMgr.GetHorseListConfig().end() )
    {
        res = true;
    }

    return res;
}

bool CStaticTableMgr::load_game_horse_config()
{
    bool res = false;
    std::string path = "";

    try
    {
        path = NLMISC::CPath::lookup("GameHouse.xml");
    }
    catch (...)
    {
        return false;
    }

    CIFile file;
    CIXml xml;

    if (file.open (path))
    {
        if (xml.init (file))
        {
            xmlNodePtr rootPtr = xml.getRootNode();

            if ( rootPtr )
            {
                xmlNodePtr pHorsePlayerUpdateTime = xml.getFirstChildNode( rootPtr , "horse_player_update_time" );

                if( pHorsePlayerUpdateTime!=NULL )
                {
                    HorsePlayerUpdateConfig   update_time;

                    update_time.time          = CIXml::getIntProperty( pHorsePlayerUpdateTime, "time", 1 );

                    m_GameConfig.HorsePlayerUpdateTime = update_time;
                }

                xmlNodePtr pHorseStateWait = xml.getFirstChildNode( rootPtr , "horse_state_wait" );

                if( pHorseStateWait!=NULL )
                {
                    HorseStateWaitConfig   state_wait;

                    state_wait.wait_finish          = CIXml::getIntProperty( pHorseStateWait, "wait_finish", 1 );
                    state_wait.wait_pour            = CIXml::getIntProperty( pHorseStateWait, "wait_pour", 1 );

                    m_GameConfig.HorseStateWait = state_wait;
                }

                xmlNodePtr pHorseCoinVal = xml.getFirstChildNode( rootPtr , "horse_coin_val" );

                for ( ; pHorseCoinVal!=NULL; pHorseCoinVal=xml.getNextChildNode(pHorseCoinVal, "horse_coin_val") )
                {
                    HorseCoinVal   room_coin;

                    std::string  room_type = CIXml::getStringProperty( pHorseCoinVal, "room_type", "" );
                    room_coin.coin_1       = CIXml::getIntProperty( pHorseCoinVal, "coin_1", 0 );
                    room_coin.coin_2       = CIXml::getIntProperty( pHorseCoinVal, "coin_2", 0 );
                    room_coin.coin_3       = CIXml::getIntProperty( pHorseCoinVal, "coin_3", 0 );
                    room_coin.coin_4       = CIXml::getIntProperty( pHorseCoinVal, "coin_4", 0 );
                    room_coin.coin_5       = CIXml::getIntProperty( pHorseCoinVal, "coin_5", 0 );

                    m_HorseCoinVal[room_type] = room_coin;
                }

                xmlNodePtr pHorseInfoNode = xml.getFirstChildNode( rootPtr , "horse_info" );
                xmlNodePtr pHorseInfo = xml.getFirstChildNode( pHorseInfoNode , "horse" );
                m_HorsesVal.clear();
                for ( ; pHorseInfo!=NULL; pHorseInfo=xml.getNextChildNode(pHorseInfo, "horse") )
                {
                    HorseVal   horse;

                    uint32 horse_id        = CIXml::getIntProperty( pHorseInfo, "id", 0 );

                    horse.name             = CIXml::getStringProperty( pHorseInfo, "name", "" );
                    horse.weight           = CIXml::getIntProperty( pHorseInfo, "wight", 100 );

                    uint32 fWinRate        = CIXml::getIntProperty( pHorseInfo, "win", 1 );
                    uint32 fPlaceRate      = CIXml::getIntProperty( pHorseInfo, "place", 1 );
                    uint32 fShowRate       = CIXml::getIntProperty( pHorseInfo, "show", 1 );
                    uint32 sShowRate       = CIXml::getIntProperty( pHorseInfo, "show2", 1 );
                    uint32 tShowRate       = CIXml::getIntProperty( pHorseInfo, "show3", 1 );

                    HorseBetRateVal horseBetRateInfo;
                    horseBetRateInfo.win_rate = fWinRate;
                    horseBetRateInfo.place_rate = fPlaceRate;
                    horseBetRateInfo.show_rate = fShowRate;
                    HorseBetRateVal horseBetRateInfo2;
                    horseBetRateInfo2.show_rate = sShowRate;
                    HorseBetRateVal horseBetRateInfo3;
                    horseBetRateInfo3.show_rate = tShowRate;

                    horse.bet_rate_list.push_back(horseBetRateInfo);
                    horse.bet_rate_list.push_back(horseBetRateInfo2);
                    horse.bet_rate_list.push_back(horseBetRateInfo3);

                    m_HorsesVal[horse_id] = horse;
                }

                res = true;
            }
        }

        file.close ();
    }

    return res;
}
bool CStaticTableMgr::load_game_niuniu_config()
{
    bool res = false;
    std::string path = "";

    try
    {
        path = NLMISC::CPath::lookup("GameNiuNiu.xml");
    }
    catch (...)
    {
        return false;
    }

    CIFile file;
    CIXml xml;

    if (file.open (path))
    {
        if (xml.init (file))
        {
            xmlNodePtr rootPtr = xml.getRootNode();

            if ( rootPtr )
            {
                //获取游戏中等待时间配置
                // 等待开始时间
                xmlNodePtr pStateTime = xml.getFirstChildNode( rootPtr , "wait_time" );
                m_GameConfig.NiuNiuStateWaitTime.WaitTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

                // 等待开始超时
                pStateTime = xml.getFirstChildNode( rootPtr , "wait_time_out" );
                m_GameConfig.NiuNiuStateWaitTime.WaitTimeOut = CIXml::getIntProperty( pStateTime , "time" , 0 );

                // 检查游戏开始
                pStateTime = xml.getFirstChildNode( rootPtr , "check_start_game" );
                m_GameConfig.NiuNiuStateWaitTime.CheckGameTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

                // 游戏开始时间
                pStateTime = xml.getFirstChildNode( rootPtr , "start_time" );
                m_GameConfig.NiuNiuStateWaitTime.StartTime   = CIXml::getIntProperty( pStateTime , "time" , 0 );

                // 发牌时间
                pStateTime = xml.getFirstChildNode( rootPtr , "brand_time" );
                m_GameConfig.NiuNiuStateWaitTime.BrandTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

                // 玩家下注时间
                pStateTime = xml.getFirstChildNode( rootPtr , "addpour_time" );
                m_GameConfig.NiuNiuStateWaitTime.AddPourTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

                // 选择手牌个数时间
                pStateTime = xml.getFirstChildNode( rootPtr , "select_handcard" );
                m_GameConfig.NiuNiuStateWaitTime.SelectHandTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

                // 结算时间
                pStateTime = xml.getFirstChildNode( rootPtr , "showdown_time" );
                m_GameConfig.NiuNiuStateWaitTime.ShowDownTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

                // 解散房间时间
                pStateTime = xml.getFirstChildNode( rootPtr , "relieve_time" );
                m_GameConfig.NiuNiuStateWaitTime.RelieveTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );
                // 摊牌时间
                pStateTime = xml.getFirstChildNode( rootPtr , "show_handcard" );
                m_GameConfig.NiuNiuStateWaitTime.ShowHandTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

                //游戏的牌型以及赔率的配置
                xmlNodePtr pNiuNiuCardsTypeInfo = xml.getFirstChildNode(rootPtr, "desk_cards_type");
                xmlNodePtr pNiuNiuCardsType = xml.getFirstChildNode(pNiuNiuCardsTypeInfo, "cards_type");
                for (; pNiuNiuCardsType != NULL; pNiuNiuCardsType = xml.getNextChildNode(pNiuNiuCardsType, "cards_type"))
                {
                    uint32 nOdds = CIXml::getIntProperty(pNiuNiuCardsType, "odds", 1);
                    uint32 nID = CIXml::getIntProperty(pNiuNiuCardsType, "id", 1);
                    m_GameConfig.NiuNiuStateWaitTime.m_CardType_Multi.insert(std::make_pair(nID, nOdds));
                }

                res = true;
            }
        }

        file.close ();
    }

    return res;
}

bool CStaticTableMgr::load_game_gandengyan_config()
{
	bool res = false;
	std::string path = "";

	try
	{
		path = NLMISC::CPath::lookup("GameGanDengYan.xml");
	}
	catch (...)
	{
		return false;
	}

	CIFile file;
	CIXml xml;

	if (file.open (path))
	{
		if (xml.init (file))
		{
			xmlNodePtr rootPtr = xml.getRootNode();

			if ( rootPtr )
			{
				//获取游戏中等待时间配置
				// 等待开始时间
				xmlNodePtr pStateTime = xml.getFirstChildNode( rootPtr , "wait_time" );
				m_GameConfig.GanDengYanStateWaitTime.WaitTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

				// 等待开始超时
				pStateTime = xml.getFirstChildNode( rootPtr , "wait_time_out" );
				m_GameConfig.GanDengYanStateWaitTime.WaitTimeOut = CIXml::getIntProperty( pStateTime , "time" , 0 );

				// 检查游戏开始
				pStateTime = xml.getFirstChildNode( rootPtr , "check_start_game" );
				m_GameConfig.GanDengYanStateWaitTime.CheckGameTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

				// 游戏开始时间
				pStateTime = xml.getFirstChildNode( rootPtr , "start_time" );
				m_GameConfig.GanDengYanStateWaitTime.StartTime   = CIXml::getIntProperty( pStateTime , "time" , 0 );

				// 发牌时间
				pStateTime = xml.getFirstChildNode( rootPtr , "brand_time" );
				m_GameConfig.NiuNiuStateWaitTime.BrandTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

				// 玩家下注时间
				pStateTime = xml.getFirstChildNode( rootPtr , "addpour_time" );
				m_GameConfig.GanDengYanStateWaitTime.AddPourTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

				// 选择手牌个数时间
				pStateTime = xml.getFirstChildNode( rootPtr , "select_handcard" );
				m_GameConfig.GanDengYanStateWaitTime.SelectHandTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

				// 结算时间
				pStateTime = xml.getFirstChildNode( rootPtr , "showdown_time" );
				m_GameConfig.GanDengYanStateWaitTime.ShowDownTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

				// 解散房间时间
				pStateTime = xml.getFirstChildNode( rootPtr , "relieve_time" );
				m_GameConfig.GanDengYanStateWaitTime.RelieveTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );
				// 摊牌时间
				pStateTime = xml.getFirstChildNode( rootPtr , "show_handcard" );
				m_GameConfig.GanDengYanStateWaitTime.ShowHandTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

				//测试牌库
				pStateTime = xml.getFirstChildNode( rootPtr , "test_poolopen" );
				m_GameConfig.GanDengYanStateWaitTime.TestCardPoolOpen  = CIXml::getIntProperty( pStateTime , "open_flag" , 0 );

				pStateTime = xml.getFirstChildNode( rootPtr , "test_poolcards" );
				m_GameConfig.GanDengYanStateWaitTime.PoolCardStr  = CIXml::getStringProperty( pStateTime , "cards" , "" );

				////游戏的牌型以及赔率的配置
				//xmlNodePtr pNiuNiuCardsTypeInfo = xml.getFirstChildNode(rootPtr, "desk_cards_type");
				//xmlNodePtr pNiuNiuCardsType = xml.getFirstChildNode(pNiuNiuCardsTypeInfo, "cards_type");
				//for (; pNiuNiuCardsType != NULL; pNiuNiuCardsType = xml.getNextChildNode(pNiuNiuCardsType, "cards_type"))
				//{
				//	uint32 nOdds = CIXml::getIntProperty(pNiuNiuCardsType, "odds", 1);
				//	uint32 nID = CIXml::getIntProperty(pNiuNiuCardsType, "id", 1);
				//	m_GameConfig.NiuNiuStateWaitTime.m_CardType_Multi.insert(std::make_pair(nID, nOdds));
				//}

				res = true;
			}
		}

		file.close ();
	}

	return res;
}

bool CStaticTableMgr::load_game_fish_config()
{
    bool res = false;    
    std::string path = "";

    try
    {
        path = NLMISC::CPath::lookup("GameFish.xml");
    }
    catch (...)
    {
        return false;
    }
    CIFile file;
    CIXml xml;

    if (file.open (path))
    {
        if (xml.init (file))
        {
            xmlNodePtr rootPtr = xml.getRootNode();

            if ( rootPtr )
            {
                xmlNodePtr pFishRoomVal = xml.getFirstChildNode( rootPtr , "fish_room" );

                for ( ; pFishRoomVal!=NULL; pFishRoomVal=xml.getNextChildNode(pFishRoomVal, "fish_room") )
                {
                    FishRoomVal room_val;

                    std::string  room_type      = CIXml::getStringProperty( pFishRoomVal, "room_type", "" );
					room_val.return_money_rate  = CIXml::getFloatProperty( pFishRoomVal, "room_return_money_rate", 0 );
                    room_val.gun_rate           = CIXml::getIntProperty( pFishRoomVal, "room_gun_set", 0 );
                    room_val.exfish_need_count  = CIXml::getIntProperty( pFishRoomVal, "catch_fish", 0 );
                    room_val.exfish_need_money  = CIXml::getIntProperty( pFishRoomVal, "need_money", 0 );
                    room_val.exfish_probability = CIXml::getIntProperty( pFishRoomVal, "probability", 0 );

                    CSString  gun_limit_str     = CIXml::getStringProperty( pFishRoomVal, "room_use_gun", "" );
                    CVectorSString strGunLimitContent;
                    gun_limit_str.splitBySeparator(',', strGunLimitContent);

                    if ( strGunLimitContent.size() == 2 )
                    {
                        room_val.gun_min_limit  = strGunLimitContent[0].atoi();
                        room_val.gun_max_limit  = strGunLimitContent[1].atoi();
                    }

                    CSString exfish_list_str    = CIXml::getStringProperty( pFishRoomVal, "room_use_gun", "" );
                    CVectorSString strExfishContent;
                    gun_limit_str.splitBySeparator(',', strExfishContent);

                    for ( uint32 i = 0; i < strExfishContent.size(); i++ )
                    {
                        room_val.exfish_list.push_back(strExfishContent[i].atoi());
                    }
                    
                    m_FishRoomVal[room_type] = room_val;
                }
                res = true;
            }
        }

        file.close ();
    }

    return res;
}

bool CStaticTableMgr::load_fish_skill_config()
{
    bool res = false;
    std::string path = "";

    try
    {
        path = NLMISC::CPath::lookup("GunSkillConfig.xml");
    }
    catch (...)
    {
        return false;
    }
    CIFile file;
    CIXml xml;

    if (file.open (path))
    {
        if (xml.init (file))
        {
            xmlNodePtr rootPtr = xml.getRootNode();

            if ( rootPtr )
            {
                xmlNodePtr pFishSkillVal = xml.getFirstChildNode( rootPtr , "RoleSkill" );

                for ( ; pFishSkillVal!=NULL; pFishSkillVal=xml.getNextChildNode(pFishSkillVal, "RoleSkill") )
                {
                    FishSkillVal skill_val;

                    uint32 skill_id            = CIXml::getIntProperty( pFishSkillVal, "id", 0 );
                    skill_val.weight           = CIXml::getIntProperty( pFishSkillVal, "weight", 0 );
                    skill_val.is_roulette      = ( CIXml::getIntProperty( pFishSkillVal, "isRoulette", 0 )==1 ) ? true : false;
                    //skill_val.is_change_gun    = CIXml::getStringProperty( pFishSkillVal, "isChangeGun", 0 );
                    skill_val.continue_time    = CIXml::getIntProperty( pFishSkillVal, "Continuous", 0 );
                    skill_val.up_rate          = CIXml::getIntProperty( pFishSkillVal, "rateUp", 0 );
                    skill_val.item_template_id = CIXml::getIntProperty( pFishSkillVal, "useItemId", 0 );
                    skill_val.kill_now_level   = CIXml::getIntProperty( pFishSkillVal, "killLevel", 0 );

                    m_FishSkillVal[skill_id] = skill_val;
                }
                res = true;
            }
        }

        file.close ();
    }

    return res;
}

void CStaticTableMgr::load_challenge_config( CIXml& xml )
{
    xmlNodePtr rootPtr = xml.getRootNode();

    /// 比赛配置
    //m_GameConfig.Challenge.clear();
    xmlNodePtr pChallenge = xml.getFirstChildNode( rootPtr , "challenge" );

    for ( ; pChallenge!=NULL; pChallenge= xml.getNextChildNode(pChallenge,"challenge") )
    {
        ChallengeConfig     challenge_config;
        challenge_config.m_CostMoney  = CIXml::getIntProperty( pChallenge , "cost_money", 10000 );
        challenge_config.m_MaxBuyBackNumber = CIXml::getIntProperty( pChallenge , "buy_back_max_num", 0 );
		challenge_config.m_MaxRound = CIXml::getIntProperty( pChallenge , "game_round_num", 0 );
        std::string room_type = CIXml::getStringProperty( pChallenge , "room_type", "xxxxx");

        RoomConfigXml* pRoomConfig = GetRoomConfigXml( room_type );
        if ( NULL == pRoomConfig ) { continue; }
        m_ChallTypeTable[ pRoomConfig->game_type ].push_back( room_type );

        ///     读入比赛可购买复活配置
        xmlNodePtr pBuyBack = xml.getFirstChildNode( pChallenge , "buy_back" );
        for ( ; pBuyBack!=NULL; pBuyBack= xml.getNextChildNode(pBuyBack,"buy_back") )
        {
            ChallengeBuyBack   buy_back;

            buy_back.buy_num    = CIXml::getIntProperty( pBuyBack, "buy_num", 1 );
            buy_back.cost_money = CIXml::getIntProperty( pBuyBack, "cost_money", 0x7fffffff );
            buy_back.buy_coin   = CIXml::getIntProperty( pBuyBack, "buy_coin", 0 );

            challenge_config.m_BuyBack.push_back( buy_back );
        }

        ///     读入比赛时间
        xmlNodePtr pChallengeTime = xml.getFirstChildNode( pChallenge , "challenge_time" );
        uint chal_id = 0;

        for ( ; pChallengeTime!=NULL; pChallengeTime= xml.getNextChildNode(pChallengeTime,"challenge_time") )
        {
            ChallengeTime   challenge_time;
            challenge_time.id               = ++chal_id;
            challenge_time.open             = GetSeconds( CIXml::getStringProperty( pChallengeTime, "open", "" ) );
            challenge_time.close            = GetSeconds( CIXml::getStringProperty( pChallengeTime, "close", "" ) );
            challenge_time.clear_rnk        = GetSeconds( CIXml::getStringProperty( pChallengeTime, "clear_rnk", "" ) );
            challenge_time.limit_enter      = GetSeconds( CIXml::getStringProperty( pChallengeTime, "limit_enter","") );
            challenge_config.m_ChallengeTime.push_back( challenge_time );
        }

        ///     读入比赛奖励
        xmlNodePtr pChallengeReward = xml.getFirstChildNode( pChallenge , "reward" );
        for ( ; pChallengeReward!=NULL; pChallengeReward= xml.getNextChildNode(pChallengeReward,"reward") )
        {
            ChallengeReward   challenge_reward;

            CSString  csranking             = CIXml::getStringProperty( pChallengeReward, "ranking", "" );
            CVectorSString strContent;
            csranking.splitBySeparator('-', strContent);

            if ( strContent.size() == 2 )
            {
                challenge_reward.ranking_left  = strContent[0].atoi();
                challenge_reward.ranking_right = strContent[1].atoi();
            }
            else if ( strContent.size() == 1 )
            {
                challenge_reward.ranking_left  = strContent[0].atoi();
                challenge_reward.ranking_right = strContent[0].atoi();
            }
            else
            {
                nlassert(false);
            }

            if ( challenge_config.m_MaxRewardRanking < challenge_reward.ranking_right )
            {
                challenge_config.m_MaxRewardRanking = challenge_reward.ranking_right;
            }

            challenge_reward.prize_pool         = CIXml::getFloatProperty( pChallengeReward, "prize_pool", 0 );
            challenge_reward.mail_title         = CIXml::getStringProperty( pChallengeReward, "mail_title", "" );
            challenge_reward.mail_content       = CIXml::getStringProperty( pChallengeReward, "mail_content", "" );
            challenge_reward.score_return_rate  = CIXml::getFloatProperty( pChallengeReward, "score_return_rate", 1 );

            CSString formula_name = room_type + "_";
            formula_name.append( csranking );
            m_Formulas[formula_name]            = CIXml::getStringProperty( pChallengeReward, "base_money", "" );
            challenge_reward.base_money         = formula_name;

            challenge_config.m_ChallengeReward.push_back( challenge_reward );
        }

        m_GameConfig.Challenge[ room_type ] = challenge_config;
    }
}

bool CStaticTableMgr::load_robot_config()
{
    bool res = false;
    string path = NLMISC::CPath::lookup("RobotConfig.xml");
    CIFile file;
    CIXml xml;

    if (file.open (path))
    {
        if (xml.init (file))
        {
            xmlNodePtr rootPtr = xml.getRootNode();

            if ( rootPtr )
            {
                m_RobotConfig.Clear();

                xmlNodePtr pRobotSurname = xml.getFirstChildNode( rootPtr , "surname" );
                for ( ; pRobotSurname!=NULL; pRobotSurname=xml.getNextChildNode(pRobotSurname, "surname") )
                {
                    std::string surname  = CIXml::getStringProperty( pRobotSurname, "str", "" );
                    m_RobotConfig.m_RobotRandomName.surnames.push_back( surname );
                }

                xmlNodePtr pRobotName = xml.getFirstChildNode( rootPtr , "name" );
                for ( ; pRobotName!=NULL; pRobotName=xml.getNextChildNode(pRobotName, "name") )
                {
                    std::string name  = CIXml::getStringProperty( pRobotName, "str", "" );
                    m_RobotConfig.m_RobotRandomName.names.push_back( name );
                }

                xmlNodePtr pRobotInfo = xml.getFirstChildNode( rootPtr , "init" );
                if ( pRobotInfo != NULL )
                {
                    m_RobotConfig.m_ShardID     = CIXml::getIntProperty( pRobotInfo, "shard_id", 0 );
                    m_RobotConfig.m_StartPID    = CIXml::getIntProperty( pRobotInfo, "start_pid", 5000 );
                    m_RobotConfig.m_BaseName    = CIXml::getStringProperty( pRobotInfo, "base_name", "" );
                }

                xmlNodePtr pRobotDefine = xml.getFirstChildNode( rootPtr , "robot_define" );
                for ( ; pRobotDefine != NULL ; pRobotDefine = xml.getNextChildNode( pRobotDefine , "robot_define" ) )
                {
                    RobotDefine  robot_define;
                    std::string name            = CIXml::getStringProperty( pRobotDefine, "name", "" );
                    robot_define.enter_time     = CIXml::getIntProperty( pRobotDefine, "enter_time", 10 );
                    robot_define.variation      = CIXml::getIntProperty( pRobotDefine, "enter_variation", 5 );
                    robot_define.max_robot      = CIXml::getIntProperty( pRobotDefine, "max_robot", 3 );
                    robot_define.base_money     = CIXml::getIntProperty( pRobotDefine, "base_money", 10000 );
                    m_RobotConfig.m_RobotDefines[name] = robot_define;
                }
                res = true;
            }
        }

        file.close ();
    }

    return res;
}

bool CStaticTableMgr::load_slots_config()
{
    bool res = false;
    string path;

    try
    {
        path = NLMISC::CPath::lookup("GameSlots.xml");
    }
    catch (...)
    {
        return false;
    }

    CIFile file;
    CIXml xml;

    if (file.open (path))
    {
        if (xml.init (file))
        {
            xmlNodePtr rootPtr = xml.getRootNode();

            if ( rootPtr )
            {
                SlotsMachineConfiger.ClearData();
                m_SlotsRoomConfig.clear();

                xmlNodePtr pSlotsMachine = xml.getFirstChildNode( rootPtr , "machine" );
                for ( ; pSlotsMachine!=NULL; pSlotsMachine=xml.getNextChildNode(pSlotsMachine, "machine") )
                {
                    MachineConfigXml   machine_cfg;
                    machine_cfg.machine_name    = CIXml::getStringProperty( pSlotsMachine, "name", "" );
                    machine_cfg.machine_type    = CIXml::getStringProperty( pSlotsMachine, "type", "" );
                    machine_cfg.data_file       = CIXml::getStringProperty( pSlotsMachine, "data_file", "" );
                    machine_cfg.freespin_file   = CIXml::getStringProperty( pSlotsMachine, "freespin_file", machine_cfg.data_file );
                    machine_cfg.jackpots_single = CIXml::getFloatProperty( pSlotsMachine, "jackpots_single", 0 );

                    SlotsMachineConfiger.LoadSlotsData( machine_cfg );
                }

                xmlNodePtr pSlotsRoom = xml.getFirstChildNode( rootPtr , "slots" );
                for ( ; pSlotsRoom!=NULL; pSlotsRoom=xml.getNextChildNode(pSlotsRoom, "slots") )
                {
                    SlotsRoomConfigXml   slots_cfg;

                    slots_cfg.room_type             = CIXml::getStringProperty( pSlotsRoom, "room_type", "" );
                    slots_cfg.use_machine           = CIXml::getStringProperty( pSlotsRoom, "use_machine", "" );
                    slots_cfg.jackpots_colossal     = CIXml::getFloatProperty( pSlotsRoom, "jackpots_colossal", 0 );
                    slots_cfg.jackpots_monster      = CIXml::getFloatProperty( pSlotsRoom, "jackpots_monster", 0 );
                    slots_cfg.jackpots_challenge    = CIXml::getFloatProperty( pSlotsRoom, "jackpots_challenge", 0 );
                    slots_cfg.feature               = CIXml::getStringProperty( pSlotsRoom, "feature", "" );

                    m_SlotsRoomConfig.insert( make_pair(slots_cfg.room_type, slots_cfg) );
                }

                load_challenge_config(xml);

                xmlNodePtr pSlotsRoomFeature    = xml.getFirstChildNode( rootPtr , "room_feature" );

                for ( ; pSlotsRoomFeature!=NULL; pSlotsRoomFeature=xml.getNextChildNode(pSlotsRoomFeature, "room_feature") )
                {
                    std::string feature_name = CIXml::getStringProperty( pSlotsRoomFeature, "name", "" );

                    xmlNodePtr pCollectSymbols      = xml.getFirstChildNode( pSlotsRoomFeature , "collect_symbols" );
                    xmlNodePtr pCollectMission      = xml.getFirstChildNode( pCollectSymbols , "collect_mission" );
                    for ( ; pCollectMission!=NULL; pCollectMission=xml.getNextChildNode(pCollectMission, "collect_mission") )
                    {
                        TSlotsFeatureCollects   collect_map;

                        xmlNodePtr pCollect       = xml.getFirstChildNode( pCollectMission , "collect" );
                        for ( ; pCollect!=NULL; pCollect=xml.getNextChildNode(pCollect, "collect") )
                        {
                            SlotsFeatureCollect     slots_collect;
                            slots_collect.id            = CIXml::getIntProperty( pCollect, "id", 1 );
                            slots_collect.next_id       = CIXml::getIntProperty( pCollect, "next_id", 1 );
                            slots_collect.reward_money  = CIXml::getStringProperty( pCollect, "reward_money", "" );

                            xmlNodePtr pSymbol       = xml.getFirstChildNode( pCollect , "need_icon" );
                            for ( ; pSymbol!=NULL; pSymbol=xml.getNextChildNode(pSymbol, "need_icon") )
                            {
                                SlotsCollotSymbol  need_symbol;
                                need_symbol.symbol_id   = CIXml::getIntProperty( pSymbol, "id", 1 );
                                need_symbol.score       = CIXml::getFloatProperty( pSymbol, "score", 1 );
                                need_symbol.need_num    = CIXml::getIntProperty( pSymbol, "num", 1 );

                                slots_collect.need_symbols.push_back( need_symbol );
                            }

                            collect_map[ slots_collect.id ] = slots_collect;
                        }

                        if ( collect_map.size() > 0 )
                        {
                            m_SlotsRoomsFeatures[ feature_name ].m_SlotsRoomFeatureCollects.push_back( collect_map );
                        }
                    }
                }


                res = true;
            }
        }

        file.close ();
    }

    return res;
}

StaticData::RecordBase* CStaticTableMgr::GetAchievementData( uint record_id )
{
    GET_STATIC_RECORD(m_AchievementData);
}

StaticData::RecordBase* CStaticTableMgr::GetStatisticsData( uint record_id )
{
    GET_STATIC_RECORD(m_StatisticsData);
}

StaticData::RecordBase* CStaticTableMgr::GetExpData( uint record_id )
{
    GET_STATIC_RECORD(m_ExpData);
}

StaticData::RecordBase* CStaticTableMgr::GetItemData( uint record_id )
{
	GET_STATIC_RECORD(m_ItemData);
}

StaticData::RecordBase* CStaticTableMgr::GetMissionData( uint record_id )
{
    GET_STATIC_RECORD(m_MissionData);
}

StaticData::RecordBase* CStaticTableMgr::GetStoreItemData( uint record_id )
{
    GET_STATIC_RECORD(m_StoreItemData);
}

StaticData::RecordBase* CStaticTableMgr::GetSpendItemData( uint record_id )
{
    GET_STATIC_RECORD(m_SpendItemData);
}


StaticData::RecordBase* CStaticTableMgr::GetWeaponData( uint record_id )
{
    GET_STATIC_RECORD(m_WeaponData);
}

StaticData::RecordBase* CStaticTableMgr::GetBulletData( uint record_id )
{
    GET_STATIC_RECORD(m_BulletData);
}

StaticData::RecordBase* CStaticTableMgr::GetFishData( uint record_id )
{
    GET_STATIC_RECORD(m_FishData);
}

SlotsRoomConfigXml* CStaticTableMgr::GetSlotsRoomConfig( const std::string& room_type )
{
    SlotsRoomConfigXml* pSlotsRoomConfig = NULL;

    TSlotsRoomConfig::iterator iter = m_SlotsRoomConfig.find( room_type );

    if ( iter!=m_SlotsRoomConfig.end() )
    {
        pSlotsRoomConfig = &(iter->second);
    }

    return pSlotsRoomConfig;
}

std::string CStaticTableMgr::GetFormula( std::string& formula_name )
{
    TFormulas::iterator iter = m_Formulas.find(formula_name);

    if ( iter != m_Formulas.end() )
    {
        return iter->second;
    }

    throw FormulaNotFound (formula_name);
    return "";
}

void CStaticTableMgr::GetRoomTypeByGameName( std::string game_name, std::vector<std::string>& out_list)
{
    out_list.clear();
    std::map<std::string, RoomConfigXml>::iterator it = m_GameConfig.rooms.begin();
    for ( ; it != m_GameConfig.rooms.end(); ++it )
    {
        if ( it->second.game_name == game_name )
        {
            out_list.push_back( it->first );
        }
    }
}

std::string CStaticTableMgr :: GetHttpConfig( std::string name )
{
	uint32 http_type = StaticTableMgr.GetGameConfig().HttpConfig.type;

    std::string strContent = "";
    if ( http_type == 0 ) //  测试
    {
        strContent = GetHttpTestConfig( name );
    }
    else if ( http_type == 1 )  //  正式
    {
        strContent = GetHttpWWangConfig( name );
    }
    return strContent;
}

std::string CStaticTableMgr::GetHttpTestConfig( std::string& name )
{
    TFormulas::iterator iter = m_GameConfig.HttpTestAPIConfig.find( name );

    if ( iter != m_GameConfig.HttpTestAPIConfig.end() )
    {
        return iter->second;
    }
    return "";
}

std::string CStaticTableMgr :: GetHttpWWangConfig( std::string& name )
{
    TFormulas::iterator iter = m_GameConfig.HttpWWangAPIConfig.find( name );

    if ( iter != m_GameConfig.HttpWWangAPIConfig.end() )
    {
        return iter->second;
    }
    return "";
}

void CStaticTableMgr::GetChallengesRoomType( std::vector<std::string>& out_list )
{
    out_list.clear();
    std::map<std::string, RoomConfigXml>::iterator it = m_GameConfig.rooms.begin();
    for ( ; it != m_GameConfig.rooms.end(); ++it )
    {
        if ( it->second.challenge_type == "chal" )
        {
            out_list.push_back( it->first );
        }
    }
}

DEF::MONEY CStaticTableMgr::GetTexasPokerMttReward( DEF::RANKING rankin , DEF::MONEY money , uint rewardNum )
{
    float Yn = mMttYTable[ rankin ];
    float Sn = mMttSTable[ rewardNum ];
    return (DEF::MONEY)(money*Yn/Sn );
}

void CStaticTableMgr::load_texas_mtt_reward( void )
{
    mMttYTable[1] = 17.0f;
    mMttSTable[1] = 17.0f;
    float total = mMttYTable[ 1 ];
    for ( float idx = 2 ; idx < 1000 ; idx++ )
    {
        float Yn = ( ( idx-0.5 )/0.15f-1.1f ) * mMttSTable[idx-1]/1.5f;
        mMttYTable[idx] = Yn;
        mMttSTable[idx] = (total+=Yn);
    }
}

void CStaticTableMgr::process_level_exp()
{
    m_UpLevelNeedExpVec.clear();
    m_UpLevelNeedExpVec.resize( m_ExpData.size()+1, 0x7FFFFFFFFFFFFFFF );

    TStaticData::iterator it = m_ExpData.begin();
    for( ; it != m_ExpData.end(); ++it )
    {
        if ( it->second )
        {
            uint16 level = it->second->getAttribInt( LEVEL_INT, 0 );
            uint64 exp   = it->second->getAttribInt( EXP_VALUE_LONG, 0 );

            m_UpLevelNeedExpVec[level] = exp;
        }
    }
}

DEF::EXP CStaticTableMgr::GetUpLevelNeedExp( uint16 level )
{
    if ( level < m_UpLevelNeedExpVec.size() && level != 0 )
    {
        return m_UpLevelNeedExpVec[level];
    }
    return 0x7FFFFFFFFFFFFFFF;
}

SlotsRoomFeatures* CStaticTableMgr::GetSlotsRoomFeature( std::string& room_feature )
{
    SlotsRoomFeatures* pSlotsRoomFeatures = NULL;
    TSlotsRoomFeatures::iterator iter = m_SlotsRoomsFeatures.find( room_feature );

    if ( iter != m_SlotsRoomsFeatures.end() )
    {
        pSlotsRoomFeatures = &(iter->second);
    }

    return pSlotsRoomFeatures;
}

bool CStaticTableMgr::load_game_doudizhu_config()
{
    bool res = false;
    string path;

    try
    {
        path = NLMISC::CPath::lookup("GameDouDiZhu.xml");
    }
    catch (...)
    {
        return false;
    }

    CIFile file;
    CIXml xml;

    if (file.open (path))
    {
        if (xml.init (file))
        {
            xmlNodePtr rootPtr = xml.getRootNode();

            if ( rootPtr )
            {
                // 跑得快状态时间;
                {
                    // 等待开始时间
                    xmlNodePtr pStateTime = xml.getFirstChildNode( rootPtr , "wait_time" );
                    m_GameConfig.DDZStateWaite.WaitTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

                    // 等待开始超时
                    pStateTime = xml.getFirstChildNode( rootPtr , "wait_time_out" );
                    m_GameConfig.DDZStateWaite.WaitTimeOut = CIXml::getIntProperty( pStateTime , "time" , 0 );

                    // 检查游戏开始
                    pStateTime = xml.getFirstChildNode( rootPtr , "check_start_game" );
                    m_GameConfig.DDZStateWaite.CheckGameTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

                    // 游戏开始时间
                    pStateTime = xml.getFirstChildNode( rootPtr , "start_time" );
                    m_GameConfig.DDZStateWaite.StartTime   = CIXml::getIntProperty( pStateTime , "time" , 0 );

                    // 发牌时间
                    pStateTime = xml.getFirstChildNode( rootPtr , "brand_time" );
                    m_GameConfig.DDZStateWaite.BrandTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

                    // 玩家活动时间
                    pStateTime = xml.getFirstChildNode( rootPtr , "action_time" );
                    m_GameConfig.DDZStateWaite.ActionTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

                    // 出牌时间
                    pStateTime = xml.getFirstChildNode( rootPtr , "outcard_time" );
                    m_GameConfig.DDZStateWaite.OutCardTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

                    // 结算时间
                    pStateTime = xml.getFirstChildNode( rootPtr , "showdown_time" );
                    m_GameConfig.DDZStateWaite.ShowDwonTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

                    // 解散房间时间
                    pStateTime = xml.getFirstChildNode( rootPtr , "relieve_time" );
                    m_GameConfig.DDZStateWaite.Relievetime  = CIXml::getIntProperty( pStateTime , "time" , 0 );
                    // 托管时间
                    pStateTime = xml.getFirstChildNode( rootPtr , "trust_time" );
                    m_GameConfig.DDZStateWaite.TrustTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );


                    xmlNodePtr pRoomInfo = xml.getFirstChildNode( rootPtr, "room_info" );
                    // 基础分
                    xmlNodePtr pRoom = xml.getFirstChildNode( pRoomInfo , "Base_score" );
                    m_GameConfig.DDZStateWaite.BaseScore  = CIXml::getIntProperty( pRoom , "score" , 1);

                    // 抢地主翻倍
                    pRoom = xml.getFirstChildNode( pRoomInfo , "QiangDiZhu_add" );
                    m_GameConfig.DDZStateWaite.QiangDiZhuAdd  = CIXml::getIntProperty( pRoom , "add" , 1);

                    // 明牌开始倍数
                    pRoom = xml.getFirstChildNode( pRoomInfo , "MingPaiStart_add" );
                    m_GameConfig.DDZStateWaite.MingPaiStartAdd = CIXml::getIntProperty( pRoom , "add" , 1);

                    //地主明牌倍数
                    pRoom = xml.getFirstChildNode( pRoomInfo , "DiZhuMingPai_add" );
                    m_GameConfig.DDZStateWaite.DiZhuMingPaiAdd  = CIXml::getIntProperty( pRoom , "add" ,1 );

                    // 炸弹倍数
                    pRoom = xml.getFirstChildNode( pRoomInfo , "ZhaDan_add" );
                    m_GameConfig.DDZStateWaite.ZhaDanAdd  = CIXml::getIntProperty( pRoom , "add" , 1);
                    // 春天倍数
                    pRoom = xml.getFirstChildNode( pRoomInfo , "ChunTian_add" );
                    m_GameConfig.DDZStateWaite.ChunTianAdd  = CIXml::getIntProperty( pRoom , "add" , 1);

                    // 加倍倍数
                    pRoom = xml.getFirstChildNode( pRoomInfo , "AddTimes_add" );
                    m_GameConfig.DDZStateWaite.AddTimes  = CIXml::getIntProperty( pRoom , "add" , 1);

                    // 底牌倍数
                    xmlNodePtr pDiPaiInfo =  xml.getFirstChildNode( pRoomInfo , "bottom_add" );
                    for ( ; pDiPaiInfo!=NULL; pDiPaiInfo= xml.getNextChildNode(pDiPaiInfo,"bottom_add") )
                    {
                        uint32 ID     = CIXml::getIntProperty( pDiPaiInfo, "id", 1);
                        uint32 Add    = CIXml::getIntProperty( pDiPaiInfo, "add", 1);
                        m_GameConfig.DDZStateWaite.DiPaiAddTime[ID] = Add;
                    }

                    // 加积分;
                    {
                        xmlNodePtr pRoomData = xml.getFirstChildNode( rootPtr , "integral_win" );
                        if ( NULL != pRoomData )
                        {
                            m_GameConfig.DDZStateWaite.Integral = CIXml::getIntProperty( pRoomData , "integral" , 0  );
                        }
                    }
                }
                res = true;
            }
        }

        file.close ();
    }

    return res;
}

bool CStaticTableMgr::load_game_pinsanzhang_config()
{
    bool res = false;
    std::string path = "";

    try
    {
        path = NLMISC::CPath::lookup("GamePinSanZhang.xml");
    }
    catch (...)
    {
        return false;
    }

    CIFile file;
    CIXml xml;

    if (file.open (path))
    {
        if (xml.init (file))
        {
            xmlNodePtr rootPtr = xml.getRootNode();

            if ( rootPtr )
            {
                //获取游戏中等待时间配置
                // 等待开始时间
                xmlNodePtr pStateTime = xml.getFirstChildNode( rootPtr , "wait_time" );
                m_GameConfig.PinSanZhangStateWaitTime.WaitTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

                // 等待开始超时
                pStateTime = xml.getFirstChildNode( rootPtr , "wait_time_out" );
                m_GameConfig.PinSanZhangStateWaitTime.WaitTimeOut = CIXml::getIntProperty( pStateTime , "time" , 0 );

                // 检查游戏开始
                pStateTime = xml.getFirstChildNode( rootPtr , "check_start_game" );
                m_GameConfig.PinSanZhangStateWaitTime.CheckGameTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

                // 游戏开始时间
                pStateTime = xml.getFirstChildNode( rootPtr , "start_time" );
                m_GameConfig.PinSanZhangStateWaitTime.StartTime   = CIXml::getIntProperty( pStateTime , "time" , 0 );

                // 发牌时间
                pStateTime = xml.getFirstChildNode( rootPtr , "brand_time" );
                m_GameConfig.PinSanZhangStateWaitTime.BrandTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );
                // 结算时间
                pStateTime = xml.getFirstChildNode( rootPtr , "showdown_time" );
                m_GameConfig.PinSanZhangStateWaitTime.ShowDownTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

                // 解散房间时间
                pStateTime = xml.getFirstChildNode( rootPtr , "relieve_time" );
                m_GameConfig.PinSanZhangStateWaitTime.RelieveTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

                // 比牌时间
                pStateTime = xml.getFirstChildNode( rootPtr , "comparecard_time" );
                m_GameConfig.PinSanZhangStateWaitTime.CompareCardTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );
                // 玩家间歇时间
                pStateTime = xml.getFirstChildNode( rootPtr , "wait_next_time" );
                m_GameConfig.PinSanZhangStateWaitTime.WaitNextTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );
                
                res = true;
            }
        }

        file.close ();
    }

    return res;
}

bool CStaticTableMgr::load_game_chess_config()
{
    bool res = false;
    std::string path = "";

    try
    {
        path = NLMISC::CPath::lookup("GameChess.xml");
    }
    catch (...)
    {
        return false;
    }

    CIFile file;
    CIXml xml;

    if (file.open (path))
    {
        if (xml.init (file))
        {
            xmlNodePtr rootPtr = xml.getRootNode();

            if ( rootPtr )
            {
                //获取游戏中等待时间配置
                // 等待开始时间
                xmlNodePtr pStateTime = xml.getFirstChildNode( rootPtr , "wait_time" );
                m_GameConfig.ChessWaitTime.WaitTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

                // 等待开始超时
                pStateTime = xml.getFirstChildNode( rootPtr , "wait_time_out" );
                m_GameConfig.ChessWaitTime.WaitTimeOut = CIXml::getIntProperty( pStateTime , "time" , 0 );

                // 检查游戏开始
                pStateTime = xml.getFirstChildNode( rootPtr , "check_start_game" );
                m_GameConfig.ChessWaitTime.CheckGameTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

                // 游戏开始时间
                pStateTime = xml.getFirstChildNode( rootPtr , "start_time" );
                m_GameConfig.ChessWaitTime.StartTime   = CIXml::getIntProperty( pStateTime , "time" , 0 );
                // 结算时间
                pStateTime = xml.getFirstChildNode( rootPtr , "showdown_time" );
                m_GameConfig.ChessWaitTime.ShowDownTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

                // 解散房间时间
                pStateTime = xml.getFirstChildNode( rootPtr , "relieve_time" );
                m_GameConfig.ChessWaitTime.RelieveTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

                // 比牌时间1
                pStateTime = xml.getFirstChildNode( rootPtr , "action_time_one" );
                m_GameConfig.ChessWaitTime.ActionTimeOne  = CIXml::getIntProperty( pStateTime , "time" , 0 );

                // 比牌时间2
                pStateTime = xml.getFirstChildNode( rootPtr , "action_time_two" );
                m_GameConfig.ChessWaitTime.ActionTimeTwo  = CIXml::getIntProperty( pStateTime , "time" , 0 );

                // 悔棋时间
                pStateTime = xml.getFirstChildNode( rootPtr , "regretchess_time" );
                m_GameConfig.ChessWaitTime.RegretChessTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

                // 求和时间
                pStateTime = xml.getFirstChildNode( rootPtr , "askpeace_time" );
                m_GameConfig.ChessWaitTime.AskPeaceTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

                // 局时
                pStateTime = xml.getFirstChildNode( rootPtr , "innings_time" );
                m_GameConfig.ChessWaitTime.InningsTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

				// 思考违规时间
				pStateTime = xml.getFirstChildNode( rootPtr , "violation_time" );
				m_GameConfig.ChessWaitTime.ViolationTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

				// 思考超时时间
				pStateTime = xml.getFirstChildNode( rootPtr , "thinkout_time" );
				m_GameConfig.ChessWaitTime.ThinkOutTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );
                res = true;
            }
        }

        file.close ();
    }

    return res;
}

