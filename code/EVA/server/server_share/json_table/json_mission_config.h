#ifndef SS_JSON_MISSION_CONFIG_H_
#define SS_JSON_MISSION_CONFIG_H_

#include <server_share/common/common.h>
#include <server_share/json/json_base.h>

SS_NAMESPACE_BEGIN_DECL

/// 任务属性参数;
class CJsonMissionCell : public CJsonBase
{
    SS_PROPERTY( MISSION_ID         , MissionID             , private );    // 任务ID;
    SS_PROPERTY( NLMISC::CSString   , MissionIcon           , private );    // 任务图标;
    SS_PROPERTY( NLMISC::CSString   , MissionContent        , private );    // 任务描述;
    SS_PROPERTY( NLMISC::CSString   , MissionRewardContent  , private );    // 任务奖励描述;
    SS_PROPERTY( uint32             , MissionCount          , private );    // 任务次数;
    SS_PROPERTY( uint32             , MissionRewardID       , private );    // 任务奖励ID;
    SS_PROPERTY( uint32             , MissionIsDayRefresh   , private );    // 任务是否跨天刷新;
    SS_PROPERTY( uint32             , MissionStartTime      , private );    // 任务开始时间;
    SS_PROPERTY( uint32             , MissionEndTime        , private );    // 任务结束时间;

    void ParseJson( const Value& JsonValue )
    {
        JsonParseBegin   ( JsonValue );
        JsonParseToUInt  ( m_MissionID );
        JsonParseToString( m_MissionIcon );
        JsonParseToString( m_MissionContent );
        JsonParseToString( m_MissionRewardContent );
        JsonParseToUInt  ( m_MissionCount );
        JsonParseToUInt  ( m_MissionRewardID );
        JsonParseToUInt  ( m_MissionIsDayRefresh );
        JsonParseToUInt  ( m_MissionStartTime );
        JsonParseToUInt  ( m_MissionEndTime );
        JsonParseEnd();
    }
};
typedef std::shared_ptr< CJsonMissionCell > CJsonMissionCellPtr;

class CJsonMissionConfig : public CJsonBase
{
    void ParseJsonArray( const GenericValue< UTF8<> >& JsonValue )
    {
        JsonParseArrayBegin( JsonValue );
        CJsonMissionCellPtr MissionCellPtr = std::make_shared< CJsonMissionCell >();
        MissionCellPtr->ParseJson( Values );
        m_JsonStringArray.insert(std::make_pair( MissionCellPtr->GetMissionID() , MissionCellPtr ) );
        JsonParseArrayEnd();
    }
};

SS_NAMESPACE_END_DECL

#endif//SS_JSON_MISSION_CONFIG_H_
