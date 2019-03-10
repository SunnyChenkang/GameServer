#include "CPlayerAchievement.h"
#include <game_share/proto_msg/public_pro.pb.h>
#include <game_share/static_table/static_table_mgr.h>

CPlayerAchievementInfo::CPlayerAchievementInfo( void )
{
    m_Random.srand( NLMISC::CTime::getSecondsSince1970() );
}

CPlayerAchievementInfo::~CPlayerAchievementInfo( void )
{
    m_Random.srand( NLMISC::CTime::getSecondsSince1970() );
}


bool CPlayerAchievementInfo::OnSaveAchievementInfo( MsgAchievementList& Data )
{
    for ( int index = 0; index < Data.achievement_list().size(); index++ )
    {
        const MsgAchievementInfo& msgAchievement = Data.achievement_list( index );

        DB_RECORD::CRecordAchievement achievement;

        achievement.pid            = 0;//m_Player->GetPID();
        achievement.achievement_id = msgAchievement.achievement_id();
        achievement.state          = msgAchievement.state();
        achievement.target         = msgAchievement.target();

        std::pair<DB_RECORD::TRecordAchievement::iterator,bool> res = _RecordAchievement.insert( std::make_pair( msgAchievement.achievement_id(), achievement ) );
        if ( res.second )
        {
            return true;
        }
    }
    return false;
}

DEF::ACHIEVE_ID CPlayerAchievementInfo::GetRandomAchievementID()
{
   std::map<uint,StaticData::RecordBase*>::iterator it = StaticTableMgr.m_AchievementData.begin();
   
   if ( it != StaticTableMgr.m_AchievementData.end() )
   {
       int dist = std::distance( it , StaticTableMgr.m_AchievementData.end() );
       if ( dist <= 0 ) { 
           return 0;
       }

       int rand_index = ( (dist-1) == 0 ) ? 0 : m_Random.rand(dist - 1);

       std::advance( it , rand_index );

       return it->first;
   }
   return 0;
}


