#ifndef GAME_SHARED_STATIC_TABLE_SLOTS_STRUCT_H
#define GAME_SHARED_STATIC_TABLE_SLOTS_STRUCT_H

#include <game_share/game_def.h>
#include <game_share/proto_msg/msg_slots.pb.h>

struct BonusGameRandom;
typedef std::vector<BonusGameRandom>    TBonusGameRandom;
typedef std::vector<sint32>             TSelectCount;

struct BonusGameRandom
{
    std::string         name;
    std::string         use;
    sint32              weight;
    sint32              multiplier;
    sint32              credit;
    sint32              sum_weight;
    sint32              free_spins;
    std::string         enter_fg;
    bool                is_bg_sel_fail;

    sint32              next_total_weight;
    TBonusGameRandom    next_random;

    BonusGameRandom() : weight(0), multiplier(-1), credit(-1), free_spins(0), next_total_weight(0), sum_weight(0), is_bg_sel_fail(false) {}
};

struct BonusGameSelect
{
    std::string             m_SelectName;
    TSelectCount            m_SelectCount;
    BonusGameRandom         m_BonusGameRandom;
    EnumBonusGameEndType    m_EndType;

    BonusGameSelect() {}
};

typedef std::map<std::string, BonusGameRandom>  TBonusGameRandoms;
typedef std::vector<BonusGameSelect>            TBonusGameSelect;

struct BonusGameStruct
{
    TBonusGameRandoms       m_BonusGameRandoms;     /// 命名Random模块
    TBonusGameSelect        m_BonusGameSelect;
    uint32                  m_EnterIConNum;         /// 进入Bonus游戏的最少图标个数
    std::vector<double>     m_SelectMultiplier;

    BonusGameStruct() {}
};

struct SlotsRoomConfigXml
{
    std::string         room_type;
    std::string         use_machine;
    double              jackpots_colossal;
    double              jackpots_monster;
    double              jackpots_challenge;
    std::string         feature;

    SlotsRoomConfigXml()
    {}
};

struct SlotsRandomWild
{
    sint32      weight;
    sint32      wild_num;
    sint32      weight_min;
    sint32      weight_max;

    SlotsRandomWild() : weight(0), wild_num(0), weight_min(0), weight_max(0)
    {}
};

struct MachineConfigXml
{
    std::string     machine_name;
    std::string     machine_type;
    std::string     data_file;
    std::string     freespin_file;
    double          jackpots_single;
};

typedef     std::vector<sint32>                         TSlotDataValue;

struct ColIConChangeWeight
{
    std::map<sint32, sint32>    m_ColWeights;           ///  <dec_icon, weight>
    sint32                      m_ColTotalWeight;

    ColIConChangeWeight() : m_ColTotalWeight(0) {}
};

typedef     std::vector<ColIConChangeWeight>                TSlotColIConChangeWeight;
typedef     std::map<sint32, TSlotColIConChangeWeight>      TSlotColIConChanges;        /// <src_icon, dec_weights>

struct SlotsCollotSymbol
{
    uint32      symbol_id;
    double      score;
    uint32      need_num;
};

struct SlotsFeatureCollect
{
    uint32      id;
    uint32      next_id;
    std::string reward_money;

    typedef std::vector<SlotsCollotSymbol>      TSlotsCollectSymbols;
    TSlotsCollectSymbols        need_symbols;
};

typedef std::map<uint32, SlotsFeatureCollect>                           TSlotsFeatureCollects;

struct SlotsRoomFeatures
{
    typedef std::vector<TSlotsFeatureCollects>      TSlotsRoomFeatureCollects;
    TSlotsRoomFeatureCollects       m_SlotsRoomFeatureCollects;



    bool  IsCollects() { return !m_SlotsRoomFeatureCollects.empty(); }
};

///   房间特性
typedef std::map<std::string, SlotsRoomFeatures>      TSlotsRoomFeatures;

#endif // GAME_SHARED_STATIC_TABLE_SLOTS_STRUCT_H


