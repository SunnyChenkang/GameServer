#include "player.h"

SSE_NAMESPACE_BEGIN_DECL

CPlayer::CPlayer( void ) : m_GameServiceId( NLNET::TServiceId::InvalidId )
                         , m_FrontendServiceId( NLNET::TServiceId::InvalidId )
{
    
}

CPlayer::~CPlayer( void )
{
    
}

SSE_NAMESPACE_END_DECL