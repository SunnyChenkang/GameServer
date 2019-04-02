#ifndef GSE_MAHJONG_BASE_H_
#define GSE_MAHJONG_BASE_H_
#include <game_service/game_service/game_service_def.h>
#include <game_service/room/room_base.h>
#include "mahjong_struct.h"
#include "mahjong_def.h"
#include "mahjong_state.h"

GSE_NAMESPACE_BEGIN_DECL

class CMahJongBase : public CRoomBase
{
public:
    CMahJongBase( CRoomBase::TCtorParam& );
    virtual ~CMahJongBase( void );

    // 加入房间;
    virtual bool JoinGameRoom( ROLE_ID );

};

GSE_NAMESPACE_END_DECL
#endif // GSE_MAHJONG_BASE_H_