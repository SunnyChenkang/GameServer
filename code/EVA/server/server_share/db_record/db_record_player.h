#ifndef SERVER_SHARED_RECORDPLAYER_H_
#define SERVER_SHARED_RECORDPLAYER_H_

#include "db_record_base.h"

SS_NAMESPACE_BEGIN_DECL

class CRecordPlayer : public CRecordBase
{
public:
    CRecordPlayer( void ) { };
    virtual ~CRecordPlayer( void ) { };

    CRecordPlayerInfo RecordPlayerInfo;       // 玩家基础信息;
    TRecordItem         RecordItem;             // 玩家道具信息;

    void serial( NLMISC::IStream& s )
    {
        s.serial( RecordPlayerInfo );
        s.serialCont( RecordItem );
    }
};

SS_NAMESPACE_END_DECL

#endif // SERVER_SHARED_DBRECORDPLAYER_H_