#ifndef SS_JSON_STATISTICS_CONFIG_H_
#define SS_JSON_STATISTICS_CONFIG_H_

#include <server_share/common/common.h>
#include <server_share/json/json_base.h>

SS_NAMESPACE_BEGIN_DECL

class CJsonStatisticsCell;
typedef std::shared_ptr< CJsonStatisticsCell > CJsonStatisticsCellPtr;

class CJsonStatisticsCell : public CJsonBase
{
    SS_PROPERTY( STATISTICS_ID    , StatisticsID       , private );  /// 统计ID;
    SS_PROPERTY( NLMISC::CSString , StatisticsContent  , private );  /// 统计描述;

    PARSE_VALUE_BEGIN

    JsonParseBegin   ( JsonValue );
    JsonParseToUInt  ( m_StatisticsID );
    JsonParseToString( m_StatisticsContent );
    JsonParseEnd();

    PARSE_VALUE_END
};

class CJsonStatisticsConfig : public CJsonBase
{
    PARSE_VALUE_ARRAY_BEGIN

    JsonParseArrayBegin( JsonValue );
    CJsonStatisticsCellPtr StatisticsCellPtr = std::make_shared< CJsonStatisticsCell >();
    StatisticsCellPtr->ParseJson( Values );
    m_JsonUint32Array.insert(std::make_pair( StatisticsCellPtr->GetStatisticsID() , StatisticsCellPtr ) );
    JsonParseArrayEnd();

    PARSE_VALUE_ARRAY_END
};

SS_NAMESPACE_END_DECL

#endif//SS_JSON_STATISTICS_CONFIG_H_