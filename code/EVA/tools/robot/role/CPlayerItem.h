#ifndef CPlayerItem_h__
#define CPlayerItem_h__

#include <game_share/game_def.h>
#include <server_share/database/db_logic_chunk.h>
#include <game_share/proto_msg/mail_pro.pb.h>
#include <nel/misc/random.h>

class CPlayerItem
{
public:
    CPlayerItem( void );
    virtual ~CPlayerItem( void );

    // 保存道具数据;
    void OnSavePlayerItem( MsgItemCont& );

    // 删除道具;
    void OnDeleteItem( DEF::ITEM_ID );

    // 删除道具;
    void OnDeleteItem( DEF::TEMPLATE_ID );

    // 更新售出道具;
    void OnUpdateSellItem( MsgSellItemUpdate& );

    // 更新消耗道具;
    void OnUpdateUseItem( MsgUseItemUpdate& );

    // 更新商城购买道具;
    void OnUpdateBuyItem( MsgStoreBuyItemInfo& );

    // 更新邮件道具;
    void OnUpdateMailItem( MsgGainReward& );

    // 更新任务奖励道具;
    void OnUpdateMissionRewardItem( MsgMissionReward& );

    // 更新签到道具;
    //void OnUpdatCheckinItem( MsgReward& );

    //// 更新英雄升级道具;
    //void OnUpdateHeroUpLevelItem( MsgUpdateHero& );
    //// 更新英雄经验升级道具;
    //void OnUpdateHeroExpUp( MsgUseExpUpdate& );
    //// 更新英雄装备道具;
    //void OnUpdateHeroEquip( MsgUpdateMeta& );
    //// 更新英雄技能升级道具;
    //void OnUpdateHeroSkillLevel( MsgHeroSkillUpRes& );
    //// 更新随机商店道具;
    //void OnUpdateRandomShopItem( MsgBuyItemResult& );
    //// 更新随机卡片道具;
    //void OnUpdateRandomCardItem( MsgCardAward& );
    //// 更新PVE奖励道具;
    //void OnUpdateItemPvE( MsgPvELeaveRes& );
    //// 更新PVP奖励道具;
    //void OnUpdateItemPvP( MsgPvPLeaveRes& );
    //// 更新副本掉落道具;
    //void OnUpdateDupDropItem( MsgBattleEndRes& );

    // 获取道具;
    DB_RECORD::CRecordItem* GetItem( DEF::TEMPLATE_ID );

    // 获取随机道具;
    DB_RECORD::CRecordItem* GetRandomItem( void );
    // 获取售出道具;
    DB_RECORD::CRecordItem* GetSellItem( void );
    // 获取消耗道具;
    //DB_RECORD::CRecordItem* GetConsumeItem( void );
    // 获取经验道具;
    //DB_RECORD::CRecordItem* GetUseExpItem( void );

    // 更新道具;
    void OnUpdateItem( std::vector< MsgItem >& data );
private:

protected:
    // 道具数据;
    DB_RECORD::TRecordItem   m_ItemData;
    // 随机;
    NLMISC::CRandom          m_Random;
};

#endif // CPlayerItem_h__