#ifndef SERVICE_SHARED_RECORDGAME_H_
#define SERVICE_SHARED_RECORDGAME_H_

#include "record_base.h"

SS_NAMESPACE_BEGIN_DECL

class CRecordGameInfo
{
    SS_PROPERTY( NLMISC::CSString , GameName     , private );
    SS_PROPERTY( NLMISC::CSString , ServiceName  , private );
    SS_PROPERTY( uint32           , GameMaxCount , private );
    SS_PROPERTY( sint32           , GameCurrCount, private );

public:
    CRecordGameInfo( void ) : m_GameName("")
                            , m_ServiceName("")
                            , m_GameMaxCount(0)
                            , m_GameCurrCount(0)
    {

    }

    void serial( NLMISC::IStream& s )
    {
        s.serial( m_GameName );
        s.serial( m_ServiceName );
        s.serial( m_GameMaxCount );
        s.serial( m_GameCurrCount );
    }
};

typedef std::vector< CRecordGameInfo >                   RecordGameList;
typedef std::map< NLNET::TServiceId , RecordGameList >   RecordGameTable;

SS_NAMESPACE_END_DECL


#endif//SERVICE_SHARED_RECORDGAME_H_