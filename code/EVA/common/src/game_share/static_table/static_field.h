#ifndef GAME_SHARED_STATIC_FIELD
#define GAME_SHARED_STATIC_FIELD

#include "game_def.h"
#include <string>

namespace StaticData
{
	class FieldBase
	{
	public:
		ATTRIB_TYPE::TAttribType    m_type;
		sint64                      m_int;
		std::string                 m_str;
		bool                        m_bool;

        typedef  std::vector<sint64>    TParams;
        TParams                     m_param;
	public:

		virtual void set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value );
	};

 //   /**
	//*   @brief class类型的默认处理字段
	//*/
 //   class FieldClass : public FieldBase
 //   {
 //   public:
 //       std::vector<sint64>  m_param;
 //       virtual void set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value );
 //   };

	/**
	*   @brief 成长类型的字段
	*/
	class FieldGrow : public FieldBase
	{
	public:
		sint  m_base;
		sint  m_percent;
		sint  m_frequency;

		virtual void set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value );
	};


	/**
	*   @brief 装备升级需要的材料
	*/
	class FieldNeedMeta : public FieldBase
	{
	public:
        enum { NEED_META_MAX = 6 };
		DEF::TEMPLATE_ID  m_metaid;
		uint  m_num;

		virtual void set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value );
	};

	/**
	*   @brief 任务条件的参数
	*/
	class FieldParam : public FieldBase
	{
	public:
		virtual void set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value );
	};

    class FieldAcquireItem : public FieldBase
    {
    public:
        struct ItemPair
        {
            DEF::TEMPLATE_ID  template_id;
            sint              num;
        };

        std::vector<ItemPair>  m_getitem;

        virtual void set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value );
    };

    class FieldDupDropItem : public FieldBase
    {
    public:
        struct DropConfig
        {
            uint32  sprite_idx;     //  怪物索引
            uint32  template_id;    //  掉落物品模板ID
            uint32  probability;    //  掉落概率
            uint32  num;            //  掉落个数
        };

        typedef std::vector<DropConfig>  TDropConfig;
        TDropConfig  m_DropConfig;

        virtual void set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value );
    };

    class FieldDupDropMoney : public FieldBase
    {
    public:
        struct DropConfig
        {
            uint32  batch;              //  波数
            uint32  money_base;         //  最小掉落金币,基础值
            uint32  money_floating;     //  浮动掉落金币
            uint32  probability;        //  掉落概率
        };

        typedef std::vector<DropConfig>  TDropConfig;
        TDropConfig  m_DropConfig;

        virtual void set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value );
    };

    /**
	*   @brief  等级对应奖励字段   (VIP)
	*/
	class FieldRewardAdd : public FieldBase
	{
	public:
        typedef std::map<int, float>  TRewardAdd;
        TRewardAdd m_RewardAdd;
		virtual void set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value );
	};


    class FieldDupDropSoul : public FieldBase
    {
    public:
        typedef std::map<int/*sprite_id*/,int/*drop_num*/>  TDropSoul;
        TDropSoul      m_drop_soul;
    public:

        virtual void set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value );
    };

	class FieldActivateGuard : public FieldBase
	{
	public:
		struct ActivateGuards
		{
			sint32          type;
			sint64          param1;
			sint64          param2;
			ActivateGuards(void)
				:type(0),
				param1(0),
				param2(0)
			{}
		};

		std::vector<ActivateGuards>  m_ActivateGuards;

		virtual void set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value );
	};

    class FieldAchievementCondition : public FieldBase
    {
    public:
        struct AchievementCondition
        {
            sint32          type;
            sint64          param1;
            sint64          param2;
            AchievementCondition(void)
                :type(0),
                param1(-1),
                param2(-1)
            {}
        };

        std::vector<AchievementCondition>  m_AchievementCondition;

        virtual void set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value );
    };

    class FieldMissionStartTime : public FieldBase
    {
    public:

        std::vector<std::string> m_MissionStartTime;
        virtual void set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value );
    };

	class FieldMapData : public FieldBase
	{
	public:
		typedef std::map<sint64,sint64>  TMapData;
		TMapData      m_map_data;
	public:

		virtual void set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value );
	};

	class FieldItemBuyData : public FieldBase
	{
	public:
		struct ItemBuyData
		{
			DEF::TEMPLATE_ID template_id;
			uint32 count;
			ItemBuyData(void):template_id(0),count(0)
			{
			}
		};
		
		typedef std::vector<ItemBuyData> TItemBuyDataList;
		TItemBuyDataList m_ItemBuyDataList;

		virtual void set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value );
	};

	class FieldChalRoundReward: public FieldBase
	{
	public:
		struct ChalRoundReward
		{
			sint32 type;
			sint32 param1;
			sint32 param2;
			ChalRoundReward(void):
				type(-1),
				param1(-1),
				param2(-1)
			{
			}
		};
		typedef std::vector<ChalRoundReward> TChalRoundRewardList;
		TChalRoundRewardList m_ChalRoundRewardList;

		virtual void set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value );
	private:

	};

    class FieldItemCommon:public FieldBase
    {
    public:
        struct ItemData
        {
            DEF::TEMPLATE_ID template_id;
            uint32 count;
            ItemData(void):template_id(0),count(0)
            {
            }
        };
        typedef std::vector<ItemData> TItemCommonList;
        TItemCommonList m_ItemCommonList;

        virtual void set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value );

        FieldItemCommon(){}
        ~FieldItemCommon(){}
    private:

    };

    class FieldRangeCommon:public FieldBase
    {
    public:
        sint  min_value;
        sint  max_value;

        virtual void set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value );
    };

    class TwoParamListComman:public FieldBase
    {
    public:
        struct ParamData
        {
            sint64 param1;
            sint64 param2;

            ParamData(void):param1(0),param2(0)
            {
            }
        };
        typedef std::vector<ParamData> TParamList;
        TParamList m_ParamList;

        virtual void set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value );
    private:

    };
}

#endif /// GAME_SHARED_STATIC_FIELD

