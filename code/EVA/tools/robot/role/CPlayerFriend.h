#ifndef CPlayerFriendInfo_h__
#define CPlayerFriendInfo_h__
#include <game_share/game_def.h>
#include <server_share/database/record_player.h>
#include <game_share/proto_msg/friend_pro.pb.h>
#include <nel/misc/random.h>

struct CFriend
{
    DEF::PID unRoleID;
    std::string strPortrait;
    std::string strName;
    bool bOnlineState;
    CFriend( void ):unRoleID(0),bOnlineState(false)
    {
        strPortrait = "";
        strName = "";
    }
    ~CFriend() {}
};

typedef std::map<DEF::PID,CFriend>       TApplyFriendList;

class CPlayerFriendInfo
{
public:
    CPlayerFriendInfo( void );
    virtual ~CPlayerFriendInfo( void );

    void OnSaveFriendList( MsgFriendList& );
    void OnSaveApplyFriendList( MsgFriendList& );
    // 保存黑名单列表;
    void OnSaveBlackList( MsgBlackListCont& );

    void AddFriend( MsgFriendBase& );
    void DeleteFriend( DEF::PID );
    void DeleteApplyFriend( DEF::PID );

    void DeleteBlackList( DEF::PID );

    DEF::PID OnGetRandomApplyFriendID();
    DEF::PID OnGetRandomFriendID();
    DEF::PID OnGetRandomBlackListPID();

    void AddFriendList( MsgFriendBase& );

    // 获取好友数量;
    size_t OnGetFriendListNum( void ){ return m_FriendList.size(); }
    // 请求列表数量;
    size_t OnGetApplyListNum( void ){ return m_ApplyFriendList.size(); }
    // 获取黑名单数量;
    size_t OnGetBlackListNum( void ) { return m_BlackList.size() ; }

private:
    // 好友数据;
    std::set< DEF::PID >    m_FriendList;
    // 黑名单数据;
    std::set< DEF::PID >    m_BlackList;
    // 请求列表;
    std::set< DEF::PID >    m_ApplyFriendList;
    // 随机;
    NLMISC::CRandom m_Random;
};

#endif // CPlayerFriendInfo_h__