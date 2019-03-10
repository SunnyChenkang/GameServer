#include "CPlayerMail.h"

CPlayerMailInfo::CPlayerMailInfo( void )
{
    m_CommonMailMap.clear();
    m_SystemMailMap.clear();

    m_Random.srand( NLMISC::CTime::getSecondsSince1970() );
}

CPlayerMailInfo::~CPlayerMailInfo( void )
{

}

void CPlayerMailInfo::OnSaveCommonMail( MsgCommonMail& data )
{
    MailData mailData;
    mailData.roleID   = data.recvid();   // 自己ID;
    mailData.mailID   = data.mailid();   // 邮件ID;
    mailData.sendid   = data.sendid();   // 发送玩家ID;
    mailData.sendname = data.name();     // 发送玩家名字;
    mailData.title    = data.title();    // 标题;
    mailData.content  = data.content();  // 内容;
    mailData.sendtime = data.sendtime(); // 发送时间;
    mailData.isLook   = false;           // 查看标记;

    std::pair< TCommonMailMap::iterator, bool > res;
    res = m_CommonMailMap.insert( std::make_pair(data.mailid(), mailData) );
    if ( !res.second )
    {
        nldebug(" on save common mail fail~!! mail_id =  %"NL_I64"d", data.mailid());
    }
}

void CPlayerMailInfo::RecviveRequestMail( MsgMailList& data )
{
    uint32 unCommonMailCount = data.commonsize();
    uint32 unSystemMailCount = data.systemsize();

    MailData mailData;

    for( int i = 0; i < data.commonlist_size(); ++i )
    {
        mailData.roleID   = data.commonlist(i).recvid();   // 自己ID;
        mailData.mailID   = data.commonlist(i).mailid();   // 邮件ID;
        mailData.sendid   = data.commonlist(i).sendid();   // 发送玩家ID;
        mailData.sendname = data.commonlist(i).name();     // 发送玩家名字;
        mailData.title    = data.commonlist(i).title();    // 标题;
        mailData.content  = data.commonlist(i).content();  // 内容;
        mailData.sendtime = data.commonlist(i).sendtime(); // 发送时间;
        mailData.reward   = data.commonlist(i).reward();   // 邮件奖励;
        mailData.isLook   = false;                         // 查看标记;

        std::pair< TCommonMailMap::iterator, bool > res;
        res = m_CommonMailMap.insert( std::make_pair(data.commonlist(i).mailid(), mailData) );
        if ( !res.second )
        {
            nldebug(" recvive request mails data on save common mail fail~!! mail_id =  %"NL_I64"d", data.commonlist(i).mailid());
        }
    }
    for( int i = 0; i < data.systemlist_size(); ++i )
    {
        mailData.mailID   = data.systemlist(i).mailid();   // 邮件ID;
        mailData.title    = data.systemlist(i).title();    // 标题;
        mailData.content  = data.systemlist(i).content();  // 内容;
        mailData.sendtime = data.systemlist(i).sendtime(); // 发送时间;
        mailData.reward   = data.systemlist(i).reward();   // 邮件奖励;
        mailData.isLook   = false;                         // 查看标记;

        std::pair< TSystemMailMap::iterator, bool > res;
        res = m_SystemMailMap.insert( std::make_pair(data.systemlist(i).mailid(), mailData) );
        if ( !res.second )
        {
            nldebug(" recvive request mails data on save system mail fail~!! mail_id =  %"NL_I64"d", data.systemlist(i).mailid());
        }
    }
}

DEF::MAIL_ID CPlayerMailInfo::OnGetRandomSystemMailID()
{
    TSystemMailMap::iterator it = m_SystemMailMap.begin();

    int dist = std::distance( it , m_SystemMailMap.end() );
    if ( dist <= 0 ) { return 0; }

    int rand_index = ( (dist-1) == 0 ) ? 0 : m_Random.rand(dist - 1);

    std::advance( it , rand_index );

    return it->first;
}

DEF::MAIL_ID CPlayerMailInfo::OnGetRandomCommonMailID()
{
    TCommonMailMap::iterator it = m_CommonMailMap.begin();

    int dist = std::distance( it , m_CommonMailMap.end() );
    if ( dist <= 0 ) { return 0; }

    int rand_index = ( (dist-1) == 0 ) ? 0 : m_Random.rand(dist - 1);

    std::advance( it , rand_index );

    return it->first;
}

void CPlayerMailInfo::RemoveSystemMail( DEF::MAIL_ID mail_id )
{
    TSystemMailMap::iterator it = m_SystemMailMap.find( mail_id );
    if ( it != m_SystemMailMap.end() )
    {
        m_SystemMailMap.erase( it );
    }
}

void CPlayerMailInfo::RemoveCommonMail( DEF::MAIL_ID mail_id )
{
    TCommonMailMap::iterator it = m_CommonMailMap.find( mail_id );
    if ( it != m_CommonMailMap.end() )
    {
        m_CommonMailMap.erase( it );
    }
}

