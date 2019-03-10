#include "CClient.h"
#include "CRobotTimer.h"
#include <server_share/script_mgr.h>
#include <game_share/tools.h>
#include <game_share/static_table/static_table_mgr.h>


static const std::string  GAME_BLACKJACK_NAME           = "BlackJack";
static const std::string  GAME_TEXASPOKER_NAME          = "TexasPoker";
static const std::string  GAME_SLOTS_NAME               = "Slots";
const std::string         GAME_MAHJONG                  = "MahJong";

CClient::CClient( void )
{
    m_SyncLoginState = 0;
    m_TimerQueue.clear();
    m_ClientState = client_state_null;
    m_MountLuaType = MountLua_Invalid;
}

CClient::~CClient( void )
{
    OnReset();
}

void CClient::OnReset()
{
    ClearTimer();
}

void CClient::OnUpdate( void )
{
    CConnect::OnUDPUpdate();
}

void CClient::OnCreateTimer( const char* lua_usename , const char* lua_funname , int time, bool flag/*  = false */)
{
    if ( IsInHall() ) // 在大厅;
    {
        if ( flag )
        {
            LuaParams score_param = ScriptMgr.run( lua_usename , lua_funname , LuaParams( (uint32)get_session() ) , 0 );
        }
        else
        {
            CTimer* pTimer = new CTimer();
            pTimer->setRemaining( time , new ClientEventTimer( this , lua_usename , lua_funname , time ) , 1 );
            m_TimerQueue.push_back( pTimer );
        }
        return;
    }
    else if ( IsInBlackJack() ) // 21点;
    {
        if ( flag )
        {
            LuaParams score_param = ScriptMgr.run( lua_usename , lua_funname , LuaParams( (uint32)get_session() ) , 0 );
        }
        else
        {
            CTimer* pTimer = new CTimer();
            pTimer->setRemaining( time , new ClientBlackJackEventTimer( this , lua_usename , lua_funname , time ) , 1 );
            m_TimerQueue.push_back( pTimer );
        }
    }
    else if ( IsInSlots() ) // 老虎机;
    {
        if ( flag )
        {
            LuaParams score_param = ScriptMgr.run( lua_usename , lua_funname , LuaParams( (uint32)get_session() ) , 0 );
        }
        else
        {
            CTimer* pTimer = new CTimer();
            pTimer->setRemaining( time , new ClientSlotEventTimer( this , lua_usename , lua_funname , time ) , 1 );
            m_TimerQueue.push_back( pTimer );
        }
    }
    else if ( IsInTexasPoker() ) // 德州扑克;
    {
        if ( flag )
        {
            LuaParams score_param = ScriptMgr.run( lua_usename , lua_funname , LuaParams( (uint32)get_session() ) , 0 );
        }
        else
        {
            CTimer* pTimer = new CTimer();
            pTimer->setRemaining( time , new ClientTexaspokerEventTimer( this , lua_usename , lua_funname , time ) , 1 );
            m_TimerQueue.push_back( pTimer );
        }
    }
    else if ( IsInMahJong() ) // 南京麻将;
    {
        if ( flag )
        {
            LuaParams score_param = ScriptMgr.run( lua_usename , lua_funname , LuaParams( (uint32)get_session() ) , 0 );
        }
        else
        {
            CTimer* pTimer = new CTimer();
            pTimer->setRemaining( time , new ClientMahJongEventTimer( this , lua_usename , lua_funname , time ) , 1 );
            m_TimerQueue.push_back( pTimer );
        }
    }
}

void CClient::SetSyncCleintState( uint32 unSyncValue )
{
    m_SyncLoginState |= unSyncValue;
}

void CClient::CleSyncClientState( uint32 unSyncValue )
{
    m_SyncLoginState &= ~unSyncValue;
}

bool CClient::IsSyncSucceed( void )
{
    if ( m_SyncLoginState != login_sync_succeed)
    {
        return false;
    }

    // 设置客户端状态;
    SetClientState( client_state_online );
    // 挂载脚本;
   // ScriptMgr.on_event( ROBOT_EVENT_REGSTEREVENT , LuaParams( (uint32)get_session() ) );

    // 初始化城堡信息;
    //OnStart();

    return true;
}

uint32 CClient::GetBufferLenght( google::protobuf::Message* Message )
{
    if ( NULL == Message )
        return 0;

    std::string buffer;
    Message->SerializeToString( &buffer );

    return crc32( 0 , ( const uint8* )buffer.c_str() , buffer.length() );
}

void CClient::ClearTimer()
{
    while ( !m_TimerQueue.empty() )
    {
        CTimer* pTimer = m_TimerQueue.front();
        if ( NULL != pTimer )
        {
            m_TimerQueue.pop_front();
            pTimer->reset();
            safe_delete( pTimer );
        }
    }
}

DEF::CHECK_SUM CClient::GetCRC32Achievement( void )
{
    MsgAchievementList AchievementList;

    for ( DB_RECORD::TRecordAchievement::iterator it = GetRecordAchievement().begin() ;
        it != GetRecordAchievement().end();
        ++it )
    {
        MsgAchievementInfo* pAchievement = AchievementList.add_achievement_list();

        it->second.getMsgAchievement( *pAchievement );
    }

    return GetBufferLenght( &AchievementList );
}

DEF::CHECK_SUM CClient::GetCRC32Item( void )
{
    MsgItemCont ItemCount;

    for ( DB_RECORD::TRecordItem::iterator it  = m_ItemData.begin();
        it != m_ItemData.end() ;
        ++it )
    {
        MsgItem* pItem = ItemCount.add_msg_item();
        it->second.getMsgItem( *pItem );
    }

    return GetBufferLenght( &ItemCount );
}

DEF::CHECK_SUM CClient::GetCRC32Mission( void )
{
    MsgMissionList MissionList;

    for ( DB_RECORD::TRecordMission::iterator it  = m_AcceptMission.begin();
        it != m_AcceptMission.end() ;
        ++it )
    {
        MsgMissionInfo* pMission = MissionList.add_mission_list();
        it->second.getMsgMission( *pMission );
    }

    return GetBufferLenght( &MissionList );
}
