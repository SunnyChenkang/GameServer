#ifndef GES_PLAYER_H_
#define GES_PLAYER_H_

#include <game_service/game_service/game_service_def.h>

GSE_NAMESPACE_BEGIN_DECL

class CPlayer
{
public:
    CPlayer( void ) { };
   ~CPlayer( void );
    explicit CPlayer( CRecordPlayer& );

    // serial;
    void serial( NLMISC::IStream& s )
    {
        s.serial( m_RecordPlayer );
        s.serial( m_FrontendServiceID );
    }

    SS_PROPERTY_QUOTE( TServiceId    , FrontendServiceID , private );
    SS_PROPERTY_QUOTE( CRecordPlayer , RecordPlayer      , private );
};

typedef std::shared_ptr<CPlayer> CPlayerPtr;
typedef std::map< ROLE_ID , CPlayerPtr > PLAYER_TABLE;

GSE_NAMESPACE_END_DECL

#endif//GES_PLAYER_H_