#include "CPlayerFriend.h"

CPlayerFriendInfo::CPlayerFriendInfo( void )
{
    m_FriendList.clear();
    m_ApplyFriendList.clear();
    m_Random.srand( NLMISC::CTime::getSecondsSince1970() );
}

CPlayerFriendInfo::~CPlayerFriendInfo( void )
{
    m_FriendList.clear();
    m_ApplyFriendList.clear();
    m_Random.srand( NLMISC::CTime::getSecondsSince1970() );
}

void CPlayerFriendInfo::OnSaveFriendList( MsgFriendList& data )
{
    for( int i =0; i < data.friend_list_size(); ++i )
    {
        m_FriendList.insert( data.friend_list(i).roleid() );
    }
}

DEF::PID CPlayerFriendInfo::OnGetRandomApplyFriendID()
{
    std::set< DEF::PID >::iterator it = m_ApplyFriendList.begin();
    if ( it != m_ApplyFriendList.end() )
    {
        int dist = std::distance( it , m_ApplyFriendList.end() );
        if ( dist <= 0 ) { 
            return 0;
        }

        int rand_index = ( (dist-1) == 0 ) ? 0 : m_Random.rand(dist - 1);
        
        std::advance( it , rand_index );

        return ( *it );
    }
    return 0;
}

DEF::PID CPlayerFriendInfo::OnGetRandomFriendID()
{
    std::set<DEF::PID>::iterator it = m_FriendList.begin();
    if ( it != m_FriendList.end() )
    {
        int dist = std::distance( it , m_FriendList.end() );
        if ( dist <= 0 ) { return 0; }

        int rand_index = ( (dist-1) == 0 ) ? 0 : m_Random.rand(dist - 1);

        std::advance( it , rand_index );

        return (*it);
    }
    return 0;
}
void CPlayerFriendInfo::OnSaveApplyFriendList( MsgFriendList& data )
{
    for( int i =0; i < data.friend_list_size(); ++i )
    {
        m_ApplyFriendList.insert( data.friend_list(i).roleid() );
    }
}

void CPlayerFriendInfo::AddFriend( MsgFriendBase& data )
{
    std::set< DEF::PID >::iterator it = m_ApplyFriendList.find( data.roleid() );
    if ( it != m_ApplyFriendList.end() )
    {
        m_ApplyFriendList.erase( it );
        AddFriendList(data);
    }
}

void CPlayerFriendInfo::DeleteFriend( DEF::PID pid )
{
    std::set<DEF::PID>::iterator it = m_FriendList.find( pid );
    if ( it != m_FriendList.end() )
    {
        m_FriendList.erase( it );
    }
}

void CPlayerFriendInfo::DeleteApplyFriend( DEF::PID pid )
{
    std::set< DEF::PID >::iterator it = m_ApplyFriendList.find( pid );
    if ( it != m_ApplyFriendList.end() )
    {
        m_ApplyFriendList.erase( it );
    }
}

void CPlayerFriendInfo::AddFriendList( MsgFriendBase& data )
{
    m_FriendList.insert( data.roleid() );
}

void CPlayerFriendInfo::OnSaveBlackList( MsgBlackListCont& data )
{
    for ( int i = 0 ; i < data.black_list_size(); ++i )
    {
        m_BlackList.insert( data.black_list( i ).pid() );
    }
}

DEF::PID CPlayerFriendInfo::OnGetRandomBlackListPID()
{
    std::set< DEF::PID >::iterator it = m_BlackList.begin();
    if ( it == m_BlackList.end() )
        return 0;

    int nDist = m_Random.rand( m_BlackList.size() - 1 );
    std::advance( it , nDist );

    return ( *it );
}

void CPlayerFriendInfo::DeleteBlackList( DEF::PID pid )
{
    std::set<DEF::PID>::iterator it = m_BlackList.find( pid );
    if ( it != m_BlackList.end() )
    {
        m_BlackList.erase( it );
    }
}
