#ifndef GAME_SHARE_STATIC_TABLE_SLOTS_H
#define GAME_SHARE_STATIC_TABLE_SLOTS_H

#include <vector>
#include <nel/misc/sstring.h>
#include <game_share/game_def.h>
#include <nel/misc/singleton.h>
#include "static_table_struct_slots.h"

namespace NLMISC
{
    class CIXml;
}

class SlotsData
{
public:
    SlotsData();
    ~SlotsData();

    bool    LoadData( std::string filename );

    uint32  GetCol()        { return m_Col; }
    uint32  GetRow()        { return m_Row; }
    sint32  GetWild()       { return m_Wild; }
    sint32  GetScatter()    { return m_Sctter; }
    sint32  GetBonus()      { return m_Bonus; }
    

    typedef   std::map< uint32, TSlotDataValue >    TIConPrice;
    typedef   std::vector< TSlotDataValue >         TWinningLine;
    typedef   std::vector< TSlotDataValue >         TWheels;            ///     滚轮式样
    typedef   std::vector< TSlotDataValue >         TParams;            ///     其它各种参数
    typedef   std::vector< SlotsRandomWild >        TSlotsRandomWilds;


    const TWinningLine&             GetWinningLine()            { return m_WinningLine; }
    const TWheels&                  GetWheels()                 { return m_Wheels; }
    const BonusGameStruct&          GetBonusGame()              { return m_BonusGame; }
    const TSlotDataValue&           GetWheelsMask()             { return m_WheelsMask; }
    uint32                          GetIConPrice( sint32 icon_id, sint32 icon_num );
    uint32                          GetIConPriceSize( sint32 icon_id );
    uint32                          GetIConCount()              { return m_IConPrice.size(); }

    uint32                          GetRandomWildNum();
    const std::string&              GetName()                   { return m_Name; }
    sint32                          GetColIConChange( uint32 col );
    sint32                          GetColChangeSymbol()        { return m_SymbolChangeSrc; }
    SlotsFeatureCollect*            GetFeatureCollect( uint32 symbol_id );

    bool                            IsFeatureRandomWilds()      { return m_MaxRandomWildWeight>0; }
    bool                            IsFetureChangeColICons()    { return m_ColSymbolChanges.size()>0; }
    bool                            IsFetureCollect()           { return m_FeatureCollects.size()>0; }

    PROP(bool,      IsFillAll );
    PROP(bool,      IsSplash );
    PROP(sint32,    ChangeSymbolID );

private:

    bool    LoadXmlData( std::string file_full_path );
    void    LoadXmlBonusGame( NLMISC::CIXml& );

    void    ClearSelfData();
    TSlotDataValue      SplitLineToInt( NLMISC::CSString&  data_line );
    std::vector<double> SplitLineToDouble( NLMISC::CSString&  data_line );

private:

    TIConPrice              m_IConPrice;
    TWinningLine            m_WinningLine;
    TWheels                 m_Wheels;
    TSlotDataValue          m_WheelsMask;
    TParams                 m_Params;
    TSlotsRandomWilds           m_SlotsRandomWilds;
    //TSlotColIConChanges       m_ColIConChanges;
    TSlotsFeatureCollects       m_FeatureCollects;
    TSlotColIConChangeWeight    m_ColSymbolChanges;
    sint32                      m_SymbolChangeSrc;
    
    BonusGameStruct     m_BonusGame;
    std::string         m_Name;
    uint32              m_MaxRandomWildWeight;
    uint32              m_Col;
    uint32              m_Row;
    sint32              m_Sctter;
    sint32              m_Wild;
    sint32              m_Bonus;
};

class CSlotsMachineConfiger : public NLMISC::CSingleton<CSlotsMachineConfiger>
{
public:

    void        ClearData();
    bool        LoadSlotsData( MachineConfigXml& );

    MachineConfigXml*   GetMachineConfig( const std::string& machine_name );
    SlotsData*          GetSlotsData( const std::string& data_name );

private:

    typedef  std::map<std::string, MachineConfigXml>    TMachineDatas;
    typedef  std::map<std::string, SlotsData>           TSlotsDataCont;

    TMachineDatas       m_MachineDatas;
    TSlotsDataCont      m_SlotsDataCont;
};

#define  SlotsMachineConfiger   CSlotsMachineConfiger::instance()




#endif // GAME_SHARE_STATIC_TABLE_SLOTS_H
