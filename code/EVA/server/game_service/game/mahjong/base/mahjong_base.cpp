#include "mahjong_base.h"
#include <game_service/player/player_manager.h>

GSE_NAMESPACE_BEGIN_DECL

CMahJongBase::CMahJongBase( TCtorParam& CreateRoomData ) : CRoomBase( CreateRoomData,1000 )
{
    
}
CMahJongBase::~CMahJongBase( void )
{

}

bool CMahJongBase::JoinGameRoom( ROLE_ID RoleID )
{
    CPlayer* pPlayer = PlayerManager.GetPlayer( RoleID );
    if ( NULL == pPlayer) { return false; }
    return false;
    
}

GSE_NAMESPACE_END_DECL



