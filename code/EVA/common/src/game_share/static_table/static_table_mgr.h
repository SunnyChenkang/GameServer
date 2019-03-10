#ifndef GAME_SHARED_STATIC_TABLE_MGR
#define GAME_SHARED_STATIC_TABLE_MGR

#include <nel/misc/types_nl.h>
#include <nel/misc/common.h>
#include <nel/misc/singleton.h>
#include <nel/misc/random.h>
#include <nel/misc/sstring.h>
#include <game_share/game_def.h>
#include "static_record.h"
#include "static_tabel_struct.h"
#include "static_table_slots.h"
#include "static_table_mahjong.h"
#include "static_table_guandan.h"
#include "static_table_robot.h"
#include "static_table_createroomcost.h"
#include "static_table_runfastpool.h"
#include "static_table_qualify_key.h"
#include "static_table_qinger.h"
//inline bool  IsStuff( uint template_id )        {   return template_id>=IDFAMILY::STUFF_START && template_id<=IDFAMILY::STUFF_END; }
inline bool  IsUseProps( uint template_id )     {   return template_id>=IDFAMILY::USE_PROPS_START && template_id<=IDFAMILY::USE_PROPS_END; }
//inline bool  IsGuardCard( uint template_id )    {   return template_id>=IDFAMILY::GUARDCARD_START && template_id<=IDFAMILY::GUARDCARD_END; }
//inline bool  IsItem( uint template_id )         {   return IsStuff(template_id)||IsUseProps(template_id)||IsGuardCard(template_id);    }

#define GET_FIELD( __record_ptr, __field_type, __attrib )\
    __field_type* p##__field_type = dynamic_cast<__field_type*>(__record_ptr->getAttribute(__attrib));\
    if( p##__field_type!=NULL )

namespace NLMISC { class CIXml; }

typedef std::map< uint,StaticData::RecordBase* >                                TStaticData;
typedef std::vector<uint64>                                                     TUpLevelNeedExpVec;

struct FormulaNotFound : public NLMISC::Exception
{
    FormulaNotFound (const std::string& formula_name) : NLMISC::Exception ("Formula not found for " + formula_name) { }
};

class CStaticTableMgr : public NLMISC::CSingleton<CStaticTableMgr>
{
public:

    CStaticTableMgr();

    void init();

    GameConfig&                     GetGameConfig()            { return m_GameConfig; }
    RoomConfigXml*                  GetRoomConfigXml( std::string room_type );
    RobotConfig&                    GetRobotConfig()           { return m_RobotConfig; }
    TSignInSevenMap&				GetSignInSevenConfig()	{ return m_SignInSeven; }

    BlackjackShuffle&               GetBlackjackShuffleConfig( std::string room_type );
    BlackJackCoinVal&               GetBlackjackCoinValConfig( std::string room_type );

    CDKeyConfigXml*                 GetCDKeyConfig( uint32  template_id );
    ChallengeConfig*                GetChallengeConfig( std::string room_type );
    //uint32                          GetTip( uint32 tip_type );
    DEF::MONEY                      GetTexasPokerMttReward( DEF::RANKING , DEF::MONEY , uint rewardNum );
    VIPConfigXml*                   GetVIPConfig( uint32 vip_level );
    PigConfigXml*                   GetPigConfig( uint32 pig_id );
    TPigConfigXml&                  GetPigConfig() { return m_PigConfig; }
    TChallType&                     GetChallType( void ){ return m_ChallTypeTable; }
    TexaspokerConfig&               GetTexaspokerConfig( void ) { return m_TexaspokerConfig; }
    SlotsRoomConfigXml*             GetSlotsRoomConfig( const std::string& room_type );
    std::string                     GetFormula( std::string& formula_name );
    TCollectEvents&                 GetCollectConfig( void ){ return m_CollectConfig; }
    SlotsRoomFeatures*              GetSlotsRoomFeature( std::string& room_feature );
    THorsesVal&                     GetHorseListConfig(){return m_HorsesVal;}

    TFishRoomVal&                   GetFishRoomValConfig(){return m_FishRoomVal;}
    TFishSkillVal&                  GetFishSkillValConfig(){return m_FishSkillVal;}
    bool                            GetIfHorseExist(uint32 horse_id);

    DEF::EXP                        GetUpLevelNeedExp( uint16 level );
    bool                            IsRobot( DEF::PID pid ) { return m_RobotConfig.m_ShardID == (pid & 0xf); }
    uint32                          GetSeconds( NLMISC::CSString str );
    void                            GetRoomTypeByGameName(std::string game_type, std::vector<std::string>&);
    std::string GetHttpConfig ( std::string );  //  获取http 地址，根据gamedef 区分测试正式
    std::string                     GetSandHttpConfig(std::string);
    void                            GetChallengesRoomType(std::vector<std::string>&);
    StaticData::RecordBase*         GetAchievementData( uint record_id );
    StaticData::RecordBase*         GetStatisticsData( uint record_id );
    StaticData::RecordBase*         GetMissionData( uint record_id );
    StaticData::RecordBase*         GetExpData( uint record_id );
    StaticData::RecordBase*         GetItemData( uint template_id );
    StaticData::RecordBase*         GetShopItemData( uint template_id );
    StaticData::RecordBase*         GetStoreItemData( uint template_id );
    StaticData::RecordBase*         GetSpendItemData( uint record_id );
    StaticData::RecordBase*         GetWeaponData( uint template_id );
    StaticData::RecordBase*         GetBulletData( uint template_id );
    StaticData::RecordBase*         GetFishData( uint template_id );
    StaticData::RecordBase*         GetSplitGiftData( uint template_id );


    void    ChangeVersion() { ++m_Version; }
    uint32  GetVersion()    { return m_Version; }

public:

    TStaticData             m_AchievementData;
    TStaticData             m_StatisticsData;
    TStaticData             m_ExpData;
    TStaticData             m_ItemData;
    TStaticData             m_MissionData;
    TStaticData             m_StoreItemData;
    TStaticData             m_SpendItemData;
    TStaticData             m_WeaponData;
    TStaticData             m_BulletData;
    TStaticData             m_FishData;

private:

    void addToRecord( ATTRIB_TYPE::TAttribType field_attrib, NLMISC::CSString field_type, NLMISC::CSString field_val, NLMISC::CSString field_save, StaticData::RecordBase* pRecord );

    bool load_game_config();
    bool load_game_blackjack_config();
    bool load_game_horse_config();
    bool load_game_niuniu_config();
	bool load_game_gandengyan_config();
    bool load_game_fish_config();
    bool load_fish_skill_config();
    bool load_game_texaspoker_config( void );
    bool load_vip_config();
    bool load_robot_config();
    bool load_slots_config();
    bool load_game_runfast_config();
    bool load_game_doushisi_config();
    bool load_game_penghu_config();
    bool load_game_doudizhu_config();
    bool load_game_pinsanzhang_config();
    bool load_game_chess_config();
    bool load_game_match_config();
    bool load_config( std::string xml_name, TStaticData& static_data );
    std::string	        GetHttpTestConfig(std::string& name);
    std::string	        GetHttpWWangConfig(std::string& name);
    void clear_config(TStaticData& static_data);

    NLMISC::CRandom         m_Random;

    GameConfig              m_GameConfig;
    TPigConfigXml           m_PigConfig;
    TBlackjackShuffle       m_BlackjackShuffle;
    TBlackJackCoinVal       m_BlackJackCoinVal;
    TSignInSevenMap			m_SignInSeven;

    THorseCoinVal           m_HorseCoinVal;
    THorsesVal              m_HorsesVal;

    TFishRoomVal            m_FishRoomVal;
    TFishSkillVal           m_FishSkillVal;
    TexaspokerConfig        m_TexaspokerConfig;
    BlackjackShuffle        m_DefaultBlackjackShuffle;
    BlackJackCoinVal        m_DefaultBlackJackCoinVal;
    TChallType              m_ChallTypeTable;
    TCollectEvents          m_CollectEvents;
    RobotConfig             m_RobotConfig;

    typedef std::map< DEF::RANKING,float>                                           TTexasMttYTable;
    typedef std::map< DEF::RANKING,float>                                           TTexasMttSTable;
    TTexasMttYTable         mMttYTable;
    TTexasMttSTable         mMttSTable;

    typedef std::map< std::string, SlotsRoomConfigXml >                             TSlotsRoomConfig;

    TSlotsRoomConfig            m_SlotsRoomConfig;
    TFormulas                   m_Formulas;
    TUpLevelNeedExpVec          m_UpLevelNeedExpVec;
    TCollectEvents			    m_CollectConfig;
    TSlotsRoomFeatures          m_SlotsRoomsFeatures;

private:

    void load_challenge_config( NLMISC::CIXml& );
    void load_slots_data( std::string datafile );
    void load_texas_mtt_reward( void );
    void process_level_exp( void );

private:

    enum StaticTableEnum
    {
        MAX_LEVEL   = 1024,
        MAX_INT32   = 0x7fffffff,
    };

    uint32 m_Version;

};


#define  StaticTableMgr                 CStaticTableMgr::instance()
#define  StaticTexasPoker               StaticTableMgr.GetTexaspokerConfig()
#define  StaticTexasRoom                StaticTexasPoker.TexaspokerRoom
#define  StaticTexasWait                StaticTexasPoker.TexaspokerStateWait
#define  StaticMailConfig               StaticTableMgr.GetGameConfig().MailConfig
#define  StaticChallTime(args)          StaticTableMgr.GetChallengeConfig(args)
#define  StaticChallType                StaticTableMgr.GetChallType()
#define  StaticGiftConfig               StaticTableMgr.GetGameConfig().GiftConfig
#define  StaticEnvelopeConfig           StaticTableMgr.GetGameConfig().EvelopeConfig
#define  StaticViewPlayersConfig        StaticTableMgr.GetGameConfig().ViewPlayersConfig
#define  StaticRenameTimeLimitConfig    StaticTableMgr.GetGameConfig().RenameTimeLimitConfig
#define  StaticUseItemConfig            StaticTableMgr.GetGameConfig().UseItemConfig
#define  StaticNiuNiuTimeConfig         StaticTableMgr.GetGameConfig().NiuNiuStateWaitTime
#define  StaticRunFastTimeConfig        StaticTableMgr.GetGameConfig().RunFastStateWaite
#define  StaticDouShiSiTimeConfig       StaticTableMgr.GetGameConfig().DouShiSiStateWait
#define  StaticPengHuTimeConfig         StaticTableMgr.GetGameConfig().PengHuStateWait
#define  StaticDouDiZhuTimeConfig       StaticTableMgr.GetGameConfig().DDZStateWaite
#define	 StaticSignInSevenConfig		StaticTableMgr.GetSignInSevenConfig()
#define  StaticGanDengYanTimeConfig     StaticTableMgr.GetGameConfig().GanDengYanStateWaitTime
#define  StaticPinSanZhangTimeConfig    StaticTableMgr.GetGameConfig().PinSanZhangStateWaitTime
#define  StaticChessTimeConfig          StaticTableMgr.GetGameConfig().ChessWaitTime

#endif // GAME_SHARED_STATIC_TABLE_MGR
/* End of static_table.h */

