#ifndef STATIC_TABLE_QUALIFYING_H
#define STATIC_TABLE_QUALIFYING_H

#include <vector>
#include <string>
#include <game_share/game_def.h>
#include <nel/misc/singleton.h>


// 段位数据;
struct PiecewiseData
{
    uint32          DanWeiID;            // 段位ID;
    uint32          RisingStar;          // 升星数量;
    uint32          RisingStarScore;     // 升星积分值;
    uint32          ProtectScore;        // 保护分值;
    uint32          BaseScore;           // 基础分值;
    uint32          CreditPenalty;       // 信用分惩罚;
    uint32          CreditLimit;         // 信用分限制;
    std::string     RoomType;            // 比赛类型;

    PiecewiseData() : DanWeiID( 0 )
                    , RisingStar( 0 )
                    , RisingStarScore( 0 )
                    , ProtectScore( 0 )
                    , BaseScore( 0 )
                    , CreditPenalty( 0 )
                    , CreditLimit( 0 )
    {
        RoomType.clear();
    }
};

// 段位数据表;
typedef std::vector<PiecewiseData>          Piecewise;
typedef std::map< std::string , Piecewise > PiecewiseTable;

class CQualifyingConfiger : public NLMISC::CSingleton<CQualifyingConfiger>
{
public:
    CQualifyingConfiger( void );
   ~CQualifyingConfiger( void );

    //                  加载配置文件;
    void                LoadQualifyingXml( void );
    //                  是否存在比赛;
    bool                IsExist( std::string& );
    //                  获取段位数据;
    PiecewiseData*      GetPiecewiseData( std::string& , uint32 );
    //                  获取最小段位;
    PiecewiseData*      GetMinPiecewiseData( std::string& );
    //                  获取最大段位;
    PiecewiseData*      GetMaxPiecewiseData( std::string& );

private:
    //   加载段位数据表;
    void LoadPiecewiseXml( void );

private:
    PiecewiseTable      m_PiecwiseTable;
};

#define QualifyingConfiger CQualifyingConfiger::instance()


#endif // STATIC_TABLE_QUALIFYING_H
