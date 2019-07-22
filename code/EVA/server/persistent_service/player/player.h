#ifndef PSE_PLAYER_H_
#define PSE_PLAYER_H_

#include <persistent_service/persistent_service/persistent_service_def.h>

PSE_NAMESPACE_BEGIN_DECL

class CPlayer
{
    SS_PROPERTY_QUOTE( CRecordPlayer , RecordPlayer , private );
};

typedef std::shared_ptr< CPlayer > CPlayerPtr;
typedef std::map< ROLE_ID , CPlayerPtr > PLAYER_TABLE;

PSE_NAMESPACE_END_DECL

#endif//PSE_PLAYER_H_