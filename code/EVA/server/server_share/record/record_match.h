#ifndef SERVER_SHARED_RECORDMATCH_H_
#define SERVER_SHARED_RECORDMATCH_H_

#include "record_base.h"

SS_NAMESPACE_BEGIN_DECL

class CRecordMatch : public CRecordBase
{
public:
    CRecordMatch( void );
    virtual ~CRecordMatch( void ) { };

    SS_PROPERTY( NLMISC::CSString , GameName    , private );
    SS_PROPERTY( uint32           , MatchTime   , private );
};

SS_NAMESPACE_END_DECL

#endif//SERVER_SHARED_RECORDMATCH_H_;