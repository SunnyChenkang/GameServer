#include "static_table_slots.h"
#include <nel/misc/file.h>
#include <game_share/tools.h>

using namespace std;
using namespace NLMISC;

SlotsData::SlotsData():m_SymbolChangeSrc(-1),m_Col(0),m_Row(0),m_Sctter(-1),m_Wild(-1),m_Bonus(-1),m_MaxRandomWildWeight(0)
{
}

SlotsData::~SlotsData()
{
}

void SlotsData::ClearSelfData()
{
    m_SymbolChangeSrc = -1;
    m_Col = 0;
    m_Row = 0;
    m_Sctter = -1;
    m_Wild = -1;
    m_Bonus = -1;
    m_MaxRandomWildWeight = 0;

    SetIsFillAll(false);
    SetIsSplash(false);
    SetChangeSymbolID(-1);

    m_IConPrice.clear();
    m_WinningLine.clear();
    m_Wheels.clear();
    m_SlotsRandomWilds.clear();
    m_ColSymbolChanges.clear();
    m_FeatureCollects.clear();
    //m_ColIConChanges.clear();
}

bool SlotsData::LoadData( std::string filename )
{
    string file_full_path = NLMISC::CPath::lookup(filename);
    string::size_type idx = filename.find( ".xml" );

    if ( idx != string::npos )
    {
        m_Name = filename;
        return LoadXmlData(file_full_path);
    }

    return false;
}

TSlotDataValue SlotsData::SplitLineToInt( NLMISC::CSString& data_line )
{
    TSlotDataValue   slt_val;
    NLMISC::CVectorSString  vct_str;
    data_line.splitBySeparator( ',', vct_str );

    for ( uint i=0; i<vct_str.size(); ++i )
    {
        slt_val.push_back( vct_str[i].strip().atoi() );
    }

    return slt_val;
}

std::vector<double> SlotsData::SplitLineToDouble( NLMISC::CSString& data_line )
{
    std::vector<double>   slt_val;
    NLMISC::CVectorSString  vct_str;
    data_line.splitBySeparator( ',', vct_str );

    for ( uint i=0; i<vct_str.size(); ++i )
    {
        slt_val.push_back( vct_str[i].strip().atof() );
    }

    return slt_val;
}

bool SlotsData::LoadXmlData( std::string file_full_path )
{
    CIFile file;

    if (file.open (file_full_path))
    {
        CIXml xml;
        if (xml.init (file))
        {
            ClearSelfData();
            xmlNodePtr pSlotsConfig = xml.getRootNode();

            m_Col       = CIXml::getIntProperty( pSlotsConfig, "col", 0 );
            m_Row       = CIXml::getIntProperty( pSlotsConfig, "row", 0 );
            m_Wild      = CIXml::getIntProperty( pSlotsConfig, "wild", -1 );
            m_Sctter    = CIXml::getIntProperty( pSlotsConfig, "sctter", -1 );
            m_Bonus     = CIXml::getIntProperty( pSlotsConfig, "bonus", -1 );

            /// 图标倍率
            xmlNodePtr pICons       = xml.getFirstChildNode( pSlotsConfig , "icons" );
            xmlNodePtr pIConLeaf    = xml.getFirstChildNode( pICons , "leaf" );

            for ( ; pIConLeaf!=NULL; pIConLeaf=xml.getNextChildNode(pIConLeaf, "leaf") )
            {
                uint32 icon_id      = CIXml::getIntProperty( pIConLeaf, "id", 0 );
                CSString icon_rate  = CIXml::getStringProperty( pIConLeaf, "rate", "" );

                m_IConPrice[icon_id] = SplitLineToInt(icon_rate);
            }

            /// 线型
            xmlNodePtr pLines       = xml.getFirstChildNode( pSlotsConfig , "lines" );
            xmlNodePtr pLineLeaf    = xml.getFirstChildNode( pLines , "leaf" );

            for ( ; pLineLeaf!=NULL; pLineLeaf=xml.getNextChildNode(pLineLeaf, "leaf") )
            {
                CSString line_rule  = CIXml::getStringProperty( pLineLeaf, "line", "" );

                m_WinningLine.push_back( SplitLineToInt(line_rule) );
            }

            /// 滚轮排列
            xmlNodePtr pWheels       = xml.getFirstChildNode( pSlotsConfig , "wheels" );
            xmlNodePtr pWheelLeaf    = xml.getFirstChildNode( pWheels , "leaf" );
            CSString   wheels_mask   = CIXml::getStringProperty( pWheels, "mask", "" );
            m_WheelsMask = SplitLineToInt( wheels_mask );

            for ( ; pWheelLeaf!=NULL; pWheelLeaf=xml.getNextChildNode(pWheelLeaf, "leaf") )
            {
                CSString line_rule  = CIXml::getStringProperty( pWheelLeaf, "wheel", "" );
                m_Wheels.push_back( SplitLineToInt(line_rule) );
            }

            /// 随机WILD
            xmlNodePtr pRandomWilds = xml.getFirstChildNode( pSlotsConfig , "random_wilds" );

            if ( pRandomWilds!=NULL )
            {
                xmlNodePtr pWildLeaf    = xml.getFirstChildNode( pRandomWilds , "leaf" );
                m_MaxRandomWildWeight = 0;

                for ( ; pWildLeaf!=NULL; pWildLeaf=xml.getNextChildNode(pWildLeaf, "leaf") )
                {
                    SlotsRandomWild  rnd_wild;

                    rnd_wild.weight     = CIXml::getIntProperty( pWildLeaf, "weight", 0 );
                    rnd_wild.wild_num   = CIXml::getIntProperty( pWildLeaf, "num", 0 );

                    if ( rnd_wild.weight > 0 )
                    {
                        rnd_wild.weight_min     =   m_MaxRandomWildWeight+1;
                        m_MaxRandomWildWeight  +=   rnd_wild.weight;
                        rnd_wild.weight_max     =   m_MaxRandomWildWeight;

                        m_SlotsRandomWilds.push_back( rnd_wild );
                    }
                }
            }


            xmlNodePtr pFeature = xml.getFirstChildNode( pSlotsConfig , "feature" );

            if ( pFeature!=NULL )
            {
                xmlNodePtr pSymbolChange    = xml.getFirstChildNode( pFeature , "symbol_change" );
                
                if ( pSymbolChange!=NULL )
                {
                    SetChangeSymbolID( CIXml::getIntProperty( pSymbolChange, "symbol_id", -1 ) );
                    SetIsFillAll( CIXml::getStringProperty( pSymbolChange, "fill_all", "false" )=="true"?true:false );
                    SetIsSplash( CIXml::getStringProperty( pSymbolChange, "splash", "false" )=="true"?true:false );
                }

                /// 可变为其它图标的规则
                xmlNodePtr pIConChange       = xml.getFirstChildNode( pFeature , "col_icon_change" );
                for ( ; pIConChange!=NULL; pIConChange=xml.getNextChildNode(pIConChange, "col_icon_change") )
                {
                    m_SymbolChangeSrc = CIXml::getIntProperty( pIConChange, "src_icon", 0 );

                    xmlNodePtr pChange       = xml.getFirstChildNode( pIConChange , "change" );
                    for ( ; pChange!=NULL; pChange=xml.getNextChildNode(pChange, "change") )
                    {
                        sint32 dec_icon  = CIXml::getIntProperty( pChange, "icon", 0 );
                        CSString icon_weights  = CIXml::getStringProperty( pChange, "weights", "" );
                        TSlotDataValue data_values =  SplitLineToInt(icon_weights);

                        m_ColSymbolChanges.resize( GetCol() );
                        
                        for ( uint widx=0; widx<data_values.size(); ++widx )
                        {
                            ColIConChangeWeight& change_weights = m_ColSymbolChanges[widx];

                            sint32 temp_weight = data_values[widx];

                            temp_weight += change_weights.m_ColTotalWeight;
                            change_weights.m_ColTotalWeight = temp_weight;
                            change_weights.m_ColWeights[dec_icon] = temp_weight;
                        }
                    }
                }

                /// 有图标可收集
                xmlNodePtr pCollect       = xml.getFirstChildNode( pFeature , "collect" );
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

                    m_FeatureCollects[slots_collect.id] = slots_collect;
                }

            }

            LoadXmlBonusGame(xml);
            return true;
        }
    }

    return false;
}

uint32 SlotsData::GetIConPrice( sint32 icon_id, sint32 icon_num )
{
    TIConPrice::iterator iter = m_IConPrice.find( icon_id );

    if ( icon_num>0 && iter!=m_IConPrice.end() )
    {
        if ( icon_num <= iter->second.size() )
        {
            return iter->second[icon_num-1];
        }
    }

    return 0;
}

uint32 SlotsData::GetIConPriceSize( sint32 icon_id )
{
    TIConPrice::iterator iter = m_IConPrice.find( icon_id );

    if ( iter!=m_IConPrice.end() )
    {
        return iter->second.size();
    }

    return 0;
}

uint32 SlotsData::GetRandomWildNum()
{
    uint32  wild_num = 0;
    sint32 rnd_wild_weight = GetRandom(m_MaxRandomWildWeight-1)+1;

    for ( uint i=0; i<m_SlotsRandomWilds.size(); ++i )
    {
        if ( m_SlotsRandomWilds[i].weight_min <= rnd_wild_weight &&
             m_SlotsRandomWilds[i].weight_max >= rnd_wild_weight )
        {
            wild_num = m_SlotsRandomWilds[i].wild_num;
            break;
        }
    }

    return wild_num;
}

void RecursiveBonusRandom( NLMISC::CIXml& xml, xmlNodePtr pXmlRandom, BonusGameRandom& bonus_random, BonusGameStruct& bonus_game )
{
    bonus_random.use        = CIXml::getStringProperty( pXmlRandom, "use", "" );
    bonus_random.name       = CIXml::getStringProperty( pXmlRandom, "name", "" );
    bonus_random.credit     = CIXml::getIntProperty( pXmlRandom, "credit", -1 );
    bonus_random.weight     = CIXml::getIntProperty( pXmlRandom, "weight", 0 );
    bonus_random.multiplier = CIXml::getIntProperty( pXmlRandom, "multiplier", -1 );
    bonus_random.free_spins = CIXml::getIntProperty( pXmlRandom, "free_spins", 0 );
    bonus_random.enter_fg   = CIXml::getStringProperty( pXmlRandom, "enter_fg", "" );
    bonus_random.is_bg_sel_fail = CIXml::getStringProperty( pXmlRandom, "is_fail", "false" )=="true"?true:false;

    xmlNodePtr pNextRandom    = xml.getFirstChildNode( pXmlRandom, "random" );

    for ( ; pNextRandom!=NULL; pNextRandom=xml.getNextChildNode(pNextRandom, "random") )
    {
        bonus_random.next_random.push_back( BonusGameRandom() );
        RecursiveBonusRandom( xml, pNextRandom, bonus_random.next_random.back(), bonus_game );
    }

    ///  整理weight
    for ( uint i=0; i<bonus_random.next_random.size(); ++i )
    {
        BonusGameRandom& next_rnd = bonus_random.next_random[i];

        bonus_random.next_total_weight += next_rnd.weight;
        next_rnd.sum_weight = bonus_random.next_total_weight;
    }

    if ( bonus_random.name.size() > 0 )
    {
        bonus_game.m_BonusGameRandoms.insert( make_pair(bonus_random.name, bonus_random) );
    }
}

void ReplaceRandomName( BonusGameRandom& bonus_random, BonusGameStruct& bonus_game )
{
    for ( uint i=0; i<bonus_random.next_random.size(); ++i )
    {
        BonusGameRandom& next_rnd = bonus_random.next_random[i];

        if ( next_rnd.next_random.empty() )
        {
            if ( !next_rnd.use.empty() )
            {
                TBonusGameRandoms::iterator iter = bonus_game.m_BonusGameRandoms.find( next_rnd.use );

                if ( iter!=bonus_game.m_BonusGameRandoms.end() )
                {
                    next_rnd.next_random = iter->second.next_random;
                }
            }
        }
        else
        {
            ReplaceRandomName( next_rnd, bonus_game );
        }
    }
}

void SlotsData::LoadXmlBonusGame( NLMISC::CIXml& xml )
{
    xmlNodePtr pSlotsConfig = xml.getRootNode();
    xmlNodePtr pBonusGame   = xml.getFirstChildNode( pSlotsConfig, "bonus_game" );

    if ( pBonusGame!=NULL )
    {
        m_BonusGame.m_EnterIConNum  = CIXml::getIntProperty( pBonusGame, "enter_icon_num", 3 );
        CSString select_multiplier  = CIXml::getStringProperty( pBonusGame, "bonus_icons_multiplier", "" );
        m_BonusGame.m_SelectMultiplier = SplitLineToDouble( select_multiplier );

        xmlNodePtr pSelect    = xml.getFirstChildNode( pBonusGame, "select" );

        for ( ; pSelect!=NULL; pSelect=xml.getNextChildNode(pSelect, "select") )
        {
            m_BonusGame.m_BonusGameSelect.push_back( BonusGameSelect() );
            BonusGameSelect&  bonus_select = m_BonusGame.m_BonusGameSelect.back();

            CSString select_count  = CIXml::getStringProperty( pSelect, "select_count", "" );
            bonus_select.m_SelectCount = SplitLineToInt( select_count );

            CSString end_type       = CIXml::getStringProperty( pSelect, "end_type", "" );
            EnumBonusGameEndType_Parse( end_type, &bonus_select.m_EndType );

            xmlNodePtr pNextRandom    = xml.getFirstChildNode( pSelect, "random" );
            for ( ; pNextRandom!=NULL; pNextRandom=xml.getNextChildNode(pNextRandom, "random") )
            {
                bonus_select.m_BonusGameRandom.next_random.push_back( BonusGameRandom() );
                RecursiveBonusRandom( xml, pNextRandom, bonus_select.m_BonusGameRandom.next_random.back(), m_BonusGame);
            }

            for ( uint i=0; i<bonus_select.m_BonusGameRandom.next_random.size(); ++i )
            {
                BonusGameRandom& next_rnd = bonus_select.m_BonusGameRandom.next_random[i];

                bonus_select.m_BonusGameRandom.next_total_weight += next_rnd.weight;
                next_rnd.sum_weight = bonus_select.m_BonusGameRandom.next_total_weight;
            }
        }

        /// 使用模块名字填充到具体模块
        for ( uint select_idx=0; select_idx<m_BonusGame.m_BonusGameSelect.size(); ++select_idx )
        {
            BonusGameSelect&  bonus_select = m_BonusGame.m_BonusGameSelect[select_idx];
            ReplaceRandomName( bonus_select.m_BonusGameRandom, m_BonusGame );
        }
    }
}

sint32 SlotsData::GetColIConChange( uint32 col )
{
    sint32 dec_icon = -1;

    if ( col < m_ColSymbolChanges.size() )
    {
        ColIConChangeWeight& icon_weights = m_ColSymbolChanges[col];

        if ( icon_weights.m_ColTotalWeight > 0 )
        {
            sint32 rnd_weight = GetRandom( icon_weights.m_ColTotalWeight-1 ) + 1;
            std::map<sint32, sint32>::iterator dec_weight_iter = icon_weights.m_ColWeights.begin();
            while ( dec_weight_iter!=icon_weights.m_ColWeights.end() )
            {
                if ( rnd_weight <= dec_weight_iter->second )
                {
                    dec_icon = dec_weight_iter->first;
                    break;
                }

                ++dec_weight_iter;
            }
        }
    }
    else
    {
        nlwarning("");
    }

    return dec_icon;
}

SlotsFeatureCollect* SlotsData::GetFeatureCollect( uint32 symbol_id )
{
    SlotsFeatureCollect* pFeatureCollect = NULL;

    TSlotsFeatureCollects::iterator iter = m_FeatureCollects.find(symbol_id);

    if ( iter != m_FeatureCollects.end() )
    {
        pFeatureCollect = &(iter->second);
    }
    else if( !m_FeatureCollects.empty() )
    {
        pFeatureCollect = &( m_FeatureCollects.begin()->second );
    }

    return pFeatureCollect;
}

bool CSlotsMachineConfiger::LoadSlotsData( MachineConfigXml&  config )
{
    SlotsData   slots_data;
    m_MachineDatas.insert( std::make_pair( config.machine_name, config ) );

    if ( slots_data.LoadData( config.data_file ) )
    {
        m_SlotsDataCont.insert( std::make_pair(config.data_file, slots_data) );

        SlotsData   freespin_data;
        if ( freespin_data.LoadData(config.freespin_file) )
        {
            m_SlotsDataCont.insert( std::make_pair(config.freespin_file, freespin_data) );
        }

        return true;
    }
    
    return false;
}

SlotsData* CSlotsMachineConfiger::GetSlotsData( const std::string& data_name )
{
    SlotsData*  pSlotsData = NULL;
    TSlotsDataCont::iterator iter = m_SlotsDataCont.find( data_name );

    if ( iter != m_SlotsDataCont.end() )
    {
        pSlotsData = &(iter->second);
    }

    return pSlotsData;
}

void CSlotsMachineConfiger::ClearData()
{
    m_MachineDatas.clear();
    m_SlotsDataCont.clear();
}

MachineConfigXml* CSlotsMachineConfiger::GetMachineConfig( const std::string& machine_name )
{
    MachineConfigXml* pMachineConfig = NULL;
    TMachineDatas::iterator iter = m_MachineDatas.find( machine_name );

    if ( iter != m_MachineDatas.end() )
    {
        pMachineConfig = &(iter->second);
    }

    return pMachineConfig;
}

