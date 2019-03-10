#ifndef CPlayerAchievementInfo_h__
#define CPlayerAchievementInfo_h__
#include <game_share/game_def.h>
#include <server_share/database/record_achievement.h>
#include <game_share/proto_msg/public_pro.pb.h>
#include <server_share/database/db_logic_chunk.h>
#include <nel/misc/random.h>

class CPlayerAchievementInfo
{
public:
    CPlayerAchievementInfo( void );
    virtual ~CPlayerAchievementInfo( void );

    bool OnSaveAchievementInfo( MsgAchievementList& Data );

    DEF::ACHIEVE_ID GetRandomAchievementID();

    DB_RECORD::TRecordAchievement& GetRecordAchievement() { return _RecordAchievement; }
private:
    // Ëæ»ú;
    NLMISC::CRandom m_Random;
    DB_RECORD::TRecordAchievement _RecordAchievement;
};

#endif // CPlayerAchievementInfo_h__