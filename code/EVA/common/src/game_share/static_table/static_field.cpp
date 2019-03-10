#include "static_field.h"
#include <nel/misc/common.h>
#include <nel/misc/sstring.h>

using namespace NLMISC;

namespace StaticData
{
	void FieldBase::set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value )
	{
		m_type = field_attrib;

		if ( field_type=="int" || field_type=="long" )
		{
			fromString( value, m_int );
		}
		else if ( field_type=="string" )
		{
			m_str = value;
		}
		else if ( field_type=="bool" )
		{
			if ( toUpper(value)=="TRUE" )
			{
				m_bool = true;
			}
			else
			{
				m_bool = false;
			}
		}
        else //if ( field_type=="class" )
        {
            CVectorSString result;
            CSString cstring(value);
            cstring.splitBySeparator(',',result);

            for ( uint i=0; i<result.size(); ++i )
            {
                m_param.push_back( trim(result[i]).atoi() );
            }
        }
	}

	void FieldGrow::set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value )
	{
		m_type = field_attrib;
	}

	void FieldNeedMeta::set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value )
	{
		m_type = field_attrib;
		CVectorSString result;
		CSString cstring(value);
		cstring.splitBySeparator(',',result);

		nlassert( result.size()==2 );

		m_metaid    = trim(result[0]).atoui();
		m_num       = trim(result[1]).atoui();
	}

	void FieldParam::set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value )
	{
		m_type = field_attrib;
		CVectorSString result;
		CSString cstring(value);
		cstring.splitBySeparator(',',result);

		for ( uint i=0; i<result.size(); ++i )
		{
			m_param.push_back( trim(result[i]).atoi() );
		}
	}

    //void FieldClass::set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value )
    //{
    //    m_type = field_attrib;
    //    CVectorSString result;
    //    CSString cstring(value);
    //    cstring.splitBySeparator(',',result);

    //    for ( uint i=0; i<result.size(); ++i )
    //    {
    //        m_param.push_back(result[i].atoi());
    //    }
    //}

    void FieldAcquireItem::set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value )
    {
        m_type = field_attrib;
        CVectorSString result_1;
        CSString cstring(value);
        cstring.splitBySeparator(';',result_1);

        for ( uint i=0; i<result_1.size(); ++i )
        {
            CVectorSString result_2;
            CSString cstring2(result_1[i]);
            cstring2.splitBySeparator(',',result_2);

            if ( result_2.size() == 2 )
            {
                ItemPair  item_pair;
                item_pair.template_id = trim(result_2[0]).atoi();
                item_pair.num         = trim(result_2[1]).atoi();

                m_getitem.push_back(item_pair);
            }
        }
    }


    void FieldDupDropItem::set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value )
    {
        m_type = field_attrib;
        CVectorSString result_1;
        CSString cstring(value);
        cstring.splitBySeparator(';',result_1);
        m_DropConfig.resize(result_1.size());

        for ( uint i=0; i<result_1.size(); ++i )
        {
            CVectorSString result_2;
            CSString cstring2(result_1[i]);
            cstring2.splitBySeparator(',',result_2);

            if ( result_2.size() == 4 )
            {
                m_DropConfig[i].sprite_idx          = trim(result_2[0]).atoi();
                m_DropConfig[i].template_id         = trim(result_2[1]).atoi();
                m_DropConfig[i].probability         = trim(result_2[2]).atoi();
                m_DropConfig[i].num                 = trim(result_2[3]).atoi();
            }
            else
            {
                nlwarning("FieldDupDrop Parse Error. %s=%s",TAttribType_Name(field_attrib).c_str(),value.c_str());
            }
        }
    }

    void FieldDupDropMoney::set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value )
    {
        m_type = field_attrib;
        CVectorSString result_1;
        CSString cstring(value);
        cstring.splitBySeparator(';',result_1);
        m_DropConfig.resize(result_1.size());

        for ( uint i=0; i<result_1.size(); ++i )
        {
            CVectorSString result_2;
            CSString cstring(result_1[i]);
            cstring.splitBySeparator(',',result_2);

            if ( result_2.size() == 4 )
            {
                m_DropConfig[i].batch           = trim(result_2[0]).atoi();
                m_DropConfig[i].money_base      = trim(result_2[1]).atoi();
                m_DropConfig[i].money_floating  = trim(result_2[2]).atoi();
                m_DropConfig[i].probability     = trim(result_2[3]).atoi();
            }
            else
            {
                nlwarning("FieldDupDropMoney Parse Error. %s=%s",TAttribType_Name(field_attrib).c_str(),value.c_str());
            }
        }
    }


    void FieldRewardAdd::set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value )
    {
        m_type = field_attrib;
        CVectorSString result_1;
        CSString cstring(value);
        cstring.splitBySeparator(';',result_1);

        for ( uint i=0; i<result_1.size(); ++i )
        {
            CVectorSString result_2;
            CSString cstring2(result_1[i]);
            cstring2.splitBySeparator(',',result_2);

            if ( result_2.size() == 2 )
            {
                int idx = trim(result_2[0]).atoi();
                int val = trim(result_2[1]).atoi();
                m_RewardAdd[idx] = val;
            }
            else
            {
                nlwarning("FieldRewardRate Parse Error. %s=%s",TAttribType_Name(field_attrib).c_str(),value.c_str());
            }
        }
    }


    void FieldDupDropSoul::set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value )
    {
        m_type = field_attrib;
        CVectorSString result_1;
        CSString cstring(value);
        cstring.splitBySeparator(';',result_1);

        for ( uint i=0; i<result_1.size(); ++i )
        {
            CVectorSString result_2;
            CSString cstring2(result_1[i]);
            cstring2.splitBySeparator(',',result_2);

            if ( result_2.size() == 2 )
            {
                int idx = trim(result_2[0]).atoi();
                int val = trim(result_2[1]).atoi();
                m_drop_soul[idx] = val;
            }
            else
            {
                nlwarning("FieldDropSoul Parse Error. %s=%s",TAttribType_Name(field_attrib).c_str(),value.c_str());
            }
        }
    }


	void FieldActivateGuard::set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value )
	{
		m_type = field_attrib;
		CVectorSString result_1;
		CSString cstring(value);
		cstring.splitBySeparator(';',result_1);

		for ( uint i=0; i<result_1.size(); ++i )
		{
			CVectorSString result_2;
			CSString cstring2(result_1[i]);
			cstring2.splitBySeparator(',',result_2);

			ActivateGuards  activate_guard;

			if ( result_2.size() == 2 )
			{
				activate_guard.type     = trim(result_2[0]).atoi();
				activate_guard.param1  = trim(result_2[1]).atoi();
			}
			else if ( result_2.size() == 3 )
			{
				activate_guard.type     = trim(result_2[0]).atoi();
				activate_guard.param1  = trim(result_2[1]).atoi();
				activate_guard.param2  = trim(result_2[2]).atoi();

			}
			else
			{
				nlwarning("FieldActivateGuard Parse Error. %s=%s",TAttribType_Name(field_attrib).c_str(),value.c_str());
				continue;
			}

			m_ActivateGuards.push_back(activate_guard);
		}
	}


    void FieldAchievementCondition::set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value )
    {
        m_type = field_attrib;
        CVectorSString result_1;
        CSString cstring(value);
        cstring.splitBySeparator(';',result_1);

        for ( uint i=0; i<result_1.size(); ++i )
        {
            CVectorSString result_2;
            CSString cstring2(result_1[i]);
            cstring2.splitBySeparator(',',result_2);

            AchievementCondition  Conditions;

            if ( result_2.size() == 1 )
            {
                Conditions.type     = trim(result_2[0]).atoi();
            }
            else if ( result_2.size() == 2 )
            {
                Conditions.type     = trim(result_2[0]).atoi();
                Conditions.param1   = trim(result_2[1]).atoi();
            }
            else if ( result_2.size() == 3 )
            {
                Conditions.type     = trim(result_2[0]).atoi();
                Conditions.param1  = trim(result_2[1]).atoi();
                Conditions.param2  = trim(result_2[2]).atoi();
            }
            else
            {
                nlwarning("FieldAchievementCondition Parse Error. %s=%s",TAttribType_Name(field_attrib).c_str(),value.c_str());
                continue;
            }

            m_AchievementCondition.push_back(Conditions);
        }
    }


    void FieldMissionStartTime::set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value )
    {
        m_type = field_attrib;
        CVectorSString result_1;
        CSString cstring(value);
        cstring.splitBySeparator(',',result_1);

        for ( uint i=0; i<result_1.size(); ++i )
        {
            m_MissionStartTime.push_back(result_1[i]);
        }
    }

	void FieldMapData::set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value )
	{
		m_type = field_attrib;
		CVectorSString result_1;
		CSString cstring(value);
		cstring.splitBySeparator(';',result_1);

		for ( uint i=0; i<result_1.size(); ++i )
		{
			CVectorSString result_2;
			CSString cstring2(result_1[i]);
			cstring2.splitBySeparator(',',result_2);

			if ( result_2.size() == 2 )
			{
				int idx = trim(result_2[0]).atoi();
				int val = trim(result_2[1]).atoi();
				m_map_data[idx] = val;
			}
			else
			{
				nlwarning("FieldMapData Parse Error. %s=%s",TAttribType_Name(field_attrib).c_str(),value.c_str());
			}
		}
	}


	void FieldItemBuyData::set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value )
	{
		m_type = field_attrib;
		CVectorSString result_1;
		CSString cstring(value);
		cstring.splitBySeparator(';',result_1);

		for ( uint i=0; i<result_1.size(); ++i )
		{
			CVectorSString result_2;
			CSString cstring2(result_1[i]);
			cstring2.splitBySeparator(',',result_2);

			ItemBuyData ItemData;

			if ( result_2.size() == 2 )
			{
				ItemData.template_id = trim(result_2[0]).atoi();
				ItemData.count       = trim(result_2[1]).atoi();
				m_ItemBuyDataList.push_back(ItemData);
			}
			else
			{
				nlwarning("FieldMapData Parse Error. %s=%s",TAttribType_Name(field_attrib).c_str(),value.c_str());
			}
		}
	}


	void FieldChalRoundReward::set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value )
	{
		m_type = field_attrib;
		CVectorSString result_1;
		CSString cstring(value);
		cstring.splitBySeparator(';',result_1);

		for ( uint i=0; i<result_1.size(); ++i )
		{
			CVectorSString result_2;
			CSString cstring2(result_1[i]);
			cstring2.splitBySeparator(',',result_2);

			ChalRoundReward  Data;
            if ( result_2.size() == 3 )
			{
				Data.type     = trim(result_2[0]).atoi();
				Data.param1  = trim(result_2[1]).atoi();
				Data.param2  = trim(result_2[2]).atoi();
			}
			else
			{
				nlwarning("ChalRoundReward Parse Error. %s=%s",TAttribType_Name(field_attrib).c_str(),value.c_str());
				continue;
			}

			m_ChalRoundRewardList.push_back(Data);
		}

	}


    void FieldItemCommon::set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value )
    {
        m_type = field_attrib;
        CVectorSString result_1;
        CSString cstring(value);
        cstring.splitBySeparator(';',result_1);

        for ( uint i=0; i<result_1.size(); ++i )
        {
            CVectorSString result_2;
            CSString cstring2(result_1[i]);
            cstring2.splitBySeparator(',',result_2);

            ItemData data;

            if ( result_2.size() == 2 )
            {
                data.template_id = trim(result_2[0]).atoi();
                data.count       = trim(result_2[1]).atoi();
                m_ItemCommonList.push_back(data);
            }
            else
            {
                nlwarning("FieldMapData Parse Error. %s=%s",TAttribType_Name(field_attrib).c_str(),value.c_str());
            }
        }
    }

    void TwoParamListComman::set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value )
    {
        m_type = field_attrib;
        CVectorSString result_1;
        CSString cstring(value);
        cstring.splitBySeparator(';',result_1);

        for ( uint i=0; i<result_1.size(); ++i )
        {
            CVectorSString result_2;
            CSString cstring2(result_1[i]);
            cstring2.splitBySeparator(',',result_2);

            ParamData data;

            if ( result_2.size() == 2 )
            {
                data.param1 = trim(result_2[0]).atoi();
                data.param2       = trim(result_2[1]).atoi();
                m_ParamList.push_back(data);
            }
            else
            {
                nlwarning("FieldMapData Parse Error. %s=%s",TAttribType_Name(field_attrib).c_str(),value.c_str());
            }
        }
    }

    void FieldRangeCommon::set( ATTRIB_TYPE::TAttribType field_attrib, std::string field_type, std::string value )
    {
        m_type = field_attrib;
        CVectorSString result;
        CSString cstring(value);
        cstring.splitBySeparator(',',result);

        nlassert( result.size()==2 );

        min_value = trim(result[0]).atoui();
        max_value = trim(result[1]).atoui();
    }
}