#ifndef GSE_MAHJONG_DEF_H_
#define GSE_MAHJONG_DEF_H_

#include <game_service/game_service/game_service_def.h>

GSE_NAMESPACE_BEGIN_DECL

#define MAX_COMMON_CARD                                 108     // 普通牌数量;
#define MAC_WIND_CARD                                   16      // 风牌数量;
#define MASK_COLOR                                      0xF0    // 花色掩码;
#define MASK_VALUE                                      0x0F    // 数值掩码;
#define MAX_INDEX                                       42      // 最大索引;
#define MAX_COMMON_VALUE                                0x41    // 最大普通牌;
#define MASK_AHOLD_INDEX                                100     // 抓牌索引;

typedef uint32                                          WIKSTATE;
typedef uint8                                           CARD;       
// 手牌数据;
typedef std::vector<CARD>                               TCard;

// 普通牌;
static CARD BaseCard[] = 
{
    0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,       //万;
    0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,       //万;
    0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,       //万;
    0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,       //万;
    0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,       //条;
    0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,       //条;
    0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,       //条;
    0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,       //条;
    0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,       //筒;
    0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,       //筒;
    0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,       //筒;
    0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29        //筒;
};

// 东南西北;
static CARD WindCard1[] =
{
    0x31,0x31,0x31,0x31,                                //东;
    0x32,0x32,0x32,0x32,                                //南;
    0x33,0x33,0x33,0x33,                                //西;
    0x34,0x34,0x34,0x34                                 //北;
};

// 中发白;
static CARD WindCard2[] =
{
    0x35,0x35,0x35,0x35,                                //中;
    0x36,0x36,0x36,0x36,                                //发;
    0x37,0x37,0x37,0x37,                                //白;
};

// 麻将单牌集合;
static CARD MJCardData[] =
{
    0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,       //万;
    0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,       //条;
    0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,       //筒;
    0x31,0x32,0x33,0x34,0x35,0x36,0x37,                 //字;
};

// 模板;
template< typename T >
size_t CountCard( const std::vector<T>& table , T value )
{
    return std::count( table.begin() , table.end() , value );
}

 // 是否东南西北;
inline bool IsExistAllSidesCard( uint8 CardValue ) { return ( CardValue >= 0x31 && CardValue <= 0x34 ); }

// 是否中发白;
inline bool IsExistAllZfbCard( uint8 CardValue )   { return ( CardValue >= 0x35 && CardValue <= 0x37 ); }

// 是否普通牌;
inline bool IsExistCommonCard( uint8 CardValue )   { return ( CardValue >= 0x01 && CardValue <= 0x29 ); }

// 判断是否为效盘;
inline bool IsValidCard( sint32 CardValue )
{
    if ( CardValue <= 0 ) { return false; }
    uint8 Value = ( CardValue & MASK_VALUE );
    uint8 Color = ( CardValue & MASK_COLOR ) >> 4;
    bool CommonCard = ( ( Value >= 1 ) && ( Value <= 9 ) && ( Color <= 2 ) ); // 普通牌;
    bool WindCard   = ( ( Value >= 1 ) && ( Value <= 7 ) && ( Color == 3 ) ); // 风;
    if ( CommonCard || WindCard ) { return true; }
    return false;
}

// 索引转换实际牌值;
inline uint8 SwitchToCardData( sint32 CardIndex )
{
    if ( CardIndex < 0 ) { return 0; }
    if ( CardIndex >= MAX_INDEX ) { return 0; }
    return ( ( CardIndex/9) << 4) | (CardIndex%9+1);
}

// 牌转换实际索引;
inline sint32 SwitchToCardIndex( uint8 CardValue )
{
    if ( !IsValidCard( CardValue ) ) { return -1; }
    uint8 Value = ( CardValue & MASK_VALUE );
    uint8 Color = ( CardValue & MASK_COLOR ) >> 4;
    return Color*9 + (Value-1);
}

// 删除状态;
inline void DeleteState( uint32& State , uint32 DeleteState )
{
    uint32 Mask = 0;
    Mask = ( ~Mask )^DeleteState;
    State &= Mask;
}

GSE_NAMESPACE_END_DECL
#endif  //GSE_MAHJONG_DEF_H_