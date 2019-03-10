#include "CPlayerInfo.h"

CPlayerInfo::CPlayerInfo( void )
{

}

CPlayerInfo::~CPlayerInfo( void )
{

}

void CPlayerInfo::OnSavePlayerInfo( MsgPlayerInfo& data )
{
    m_PlayerData.pid           = data.pid();
    m_PlayerData.uid           = data.uid();
    m_PlayerData.player_name   = data.name();
    m_PlayerData.level         = data.level();
    m_PlayerData.money         = data.money();

}
