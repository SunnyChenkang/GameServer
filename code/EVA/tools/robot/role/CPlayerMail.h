#ifndef CPlayerMailInfo_h__
#define CPlayerMailInfo_h__
#include <game_share/game_def.h>
#include <server_share/database/record_player.h>
#include <game_share/proto_msg/mail_pro.pb.h>
#include <nel/misc/random.h>

struct MailData
{
    DEF::PID          roleID;   // 自己ID;
    DEF::MAIL_ID      mailID;   // 邮件ID;
    DEF::PID          sendid;   // 发送玩家ID;
    std::string       sendname; // 发送玩家名字;
    std::string       title;    // 标题;
    std::string       content;  // 内容;
    uint32            sendtime; // 发送时间;
    uint64            reward;   // 奖励;
    TMailType         type;     // 邮件类型;
    bool              isLook;   // 查看标记;
};

typedef std::map< DEF::MAIL_ID, MailData > TCommonMailMap;
typedef std::map< DEF::MAIL_ID, MailData > TSystemMailMap;

class CPlayerMailInfo
{
public:
    CPlayerMailInfo( void );
    virtual ~CPlayerMailInfo( void );

    void OnSaveCommonMail( MsgCommonMail& );
    void RecviveRequestMail( MsgMailList& );

    DEF::MAIL_ID OnGetRandomSystemMailID();
    DEF::MAIL_ID OnGetRandomCommonMailID();

    void RemoveSystemMail( DEF::MAIL_ID );
    void RemoveCommonMail( DEF::MAIL_ID );

    std::map< DEF::MAIL_ID, MailData >& GetCommonMailMap() { return m_CommonMailMap; }
    std::map< DEF::MAIL_ID, MailData >& GetSystemMailMap() { return m_SystemMailMap; }



private:
    TCommonMailMap   m_CommonMailMap;
    TSystemMailMap   m_SystemMailMap;

    // 随机;
    NLMISC::CRandom m_Random;
};

#endif // CPlayerMailInfo_h__