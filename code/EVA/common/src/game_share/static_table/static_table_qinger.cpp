#include "static_table_qinger.h"
#include <nel/misc/file.h>
#include <nel/misc/i_xml.h>

using namespace NLMISC;

QingErConfig::QingErConfig( void )
{
}

QingErConfig::~QingErConfig( void )
{

}

void QingErConfig::ResetData( void )
{
    mFlowerSubsection.clear();
    m_QingErKaiGangScore.clear();
    m_QingErStateTime.clear();
}

bool QingErConfig::LoadConfig( void )
{
    try
    {
        ResetData();
        LoadQingErPool();
        LoadFlowerSubsection();
    }
    catch ( ... ) {
    }
    std::string path = NLMISC::CPath::lookup("GameQingEr.xml");
    CIFile file;
    CIXml xml;

    if ( !file.open( path ) ) {
        return false;
    }
    if ( !xml.init( file ) ) {
        return false;
    }
    xmlNodePtr rootPtr = xml.getRootNode();
    if ( NULL == rootPtr ) {
        return false;
    }
    // 青儿状态时间;
    {
        QingErStateTime FreeRoomTime;
        QingErStateTime PrivateRoomTime;

        xmlNodePtr pStateTime = xml.getFirstChildNode( rootPtr , "start_time" );
        FreeRoomTime.StartGameTime         = CIXml::getIntProperty( pStateTime , "ziyoufang_time", 0 );
        PrivateRoomTime.StartGameTime      = CIXml::getIntProperty( pStateTime , "private_time", 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "check_start_game" );
        FreeRoomTime.CheckStartGameTime      = CIXml::getIntProperty( pStateTime , "ziyoufang_time", 0 );
        PrivateRoomTime.CheckStartGameTime   = CIXml::getIntProperty( pStateTime , "private_time", 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "wait_time" );
        FreeRoomTime.WaitTime                 = CIXml::getIntProperty( pStateTime , "ziyoufang_time", 0 );
        PrivateRoomTime.WaitTime              = CIXml::getIntProperty( pStateTime , "private_time", 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "wait_time_out" );
        FreeRoomTime.WaitTimeOut              = CIXml::getIntProperty( pStateTime , "ziyoufang_time", 0 );
        PrivateRoomTime.WaitTimeOut           = CIXml::getIntProperty( pStateTime , "private_time", 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "banker_time" );
        FreeRoomTime.MakeBankerTime            = CIXml::getIntProperty( pStateTime , "ziyoufang_time", 0 );
        PrivateRoomTime.MakeBankerTime         = CIXml::getIntProperty( pStateTime , "private_time", 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "mound_time" );
        FreeRoomTime.MakeMoundTime             = CIXml::getIntProperty( pStateTime , "ziyoufang_time", 0 );
        PrivateRoomTime.MakeMoundTime          = CIXml::getIntProperty( pStateTime , "private_time", 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "brand_time" );
        FreeRoomTime.FirstBrandTime            = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.FirstBrandTime         = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "hand_flower_time" );
        FreeRoomTime.HandMendFlowerTime        = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.HandMendFlowerTime     = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "check_tiandihu_choice" );
        FreeRoomTime.CheckTianDiChoiceTime      = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.CheckTianDiChoiceTime   = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "ahold_flower_time" );
        FreeRoomTime.AholdMendFlowerTime        = CIXml::getIntProperty( pStateTime , "ziyoufang_time" ,0 );
        PrivateRoomTime.AholdMendFlowerTime     = CIXml::getIntProperty( pStateTime , "private_time" ,0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "action_time" );
        FreeRoomTime.ActionTime                 = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.ActionTime              = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "action_listen_time" );
        FreeRoomTime.ActionListenTime           = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.ActionListenTime        = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "action_trust_time" );
        FreeRoomTime.ActionTrustTime            = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.ActionTrustTime         = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "showdown_time");
        FreeRoomTime.ShowDownTime               = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.ShowDownTime            = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "user_choice_time" );
        FreeRoomTime.WaitUserChoiceTime         = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.WaitUserChoiceTime      = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "self_choice_time");
        FreeRoomTime.WaitSelfChoiceTime         = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.WaitSelfChoiceTime      = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr ,"user_trust_choice_time" );
        FreeRoomTime.WaitUserTrustChoiceTime      = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.WaitUserTrustChoiceTime   = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "self_trust_choice_time" );
        FreeRoomTime.WaitSelfTrustChoiceTime      = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.WaitSelfTrustChoiceTime   = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "qianggang_choice_time" );
        FreeRoomTime.WaitQiangGangChoiceTime      = CIXml::getIntProperty( pStateTime , "ziyoufang_time" ,0 );
        PrivateRoomTime.WaitQiangGangChoiceTime   = CIXml::getIntProperty( pStateTime , "private_time" ,0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "out_card_time" );
        FreeRoomTime.WaitOutCardTime              = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.WaitOutCardTime           = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "touch_card_time" );
        FreeRoomTime.WaitTouchCardTime            = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.WaitTouchCardTime         = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "touch_card_finish_time" );
        FreeRoomTime.WaitTouchFinishTime          = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.WaitTouchFinishTime       = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "gang_card_time" );
        FreeRoomTime.WaitBarCardTime              = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.WaitBarCardTime           = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "gang_card_finish_time" );
        FreeRoomTime.WaitBarFinishTime            = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.WaitBarFinishTime         = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "zimo_hu_time" );
        FreeRoomTime.WaitZiMoHuTime               = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.WaitZiMoHuTime            = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "amerce_money_time" );
        FreeRoomTime.WaitAmerceTime               = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.WaitAmerceTime            = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "amerce_finish_time" );
        FreeRoomTime.WaitAmerceFinishTime         = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.WaitAmerceFinishTime      = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "relieve_time" );
        FreeRoomTime.WaitRelieveTime              = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.WaitRelieveTime           = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "relieve_time_finish" );
        FreeRoomTime.WaitRelieveFinishTime        = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.WaitRelieveFinishTime     = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "dianpao_hu_time" );
        FreeRoomTime.WaitDianPaoHuTime            = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.WaitDianPaoHuTime         = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "liuju_hu_time" );
        FreeRoomTime.WaitLiuJuHuTime              = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.WaitLiuJuHuTime           = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "qiangganghu_time" );
        FreeRoomTime.WaitQiangGangHuTime          = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.WaitQiangGangHuTime       = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "dabarkaihuahu_time" );
        FreeRoomTime.WaitDaBarKaiHuaHuTime        = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.WaitDaBarKaiHuaHuTime     = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "pengduihu_time" );
        FreeRoomTime.WaitPengDuiHuTime            = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.WaitPengDuiHuTime         = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "zimomeng_time" );
        FreeRoomTime.WaitZiMoMengTime             = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.WaitZiMoMengTime          = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "cathen_time" );
        FreeRoomTime.WaitCathenTime               = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.WaitCathenTime			  = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

		pStateTime = xml.getFirstChildNode( rootPtr , "contract_time" );
		FreeRoomTime.WaitContract				  = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
		PrivateRoomTime.WaitContract			  = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

		pStateTime = xml.getFirstChildNode( rootPtr , "autoout_time" );
		FreeRoomTime.WaitAutoOutCardTime          = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
		PrivateRoomTime.WaitAutoOutCardTime       = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "gameover_time" );
        FreeRoomTime.WaitGameOver                 = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.WaitGameOver              = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "virtual_time" );
        FreeRoomTime.WaitVirtualTime                 = CIXml::getIntProperty( pStateTime , "ziyoufang_time" , 0 );
        PrivateRoomTime.WaitVirtualTime              = CIXml::getIntProperty( pStateTime , "private_time" , 0 );

        m_QingErStateTime[TGD_NORMAL]       = FreeRoomTime;
        m_QingErStateTime[TGD_JINYUANZI]    = PrivateRoomTime;
    }


	{
		//测试牌库
		xmlNodePtr pTestPool = xml.getFirstChildNode( rootPtr , "test_poolopen" );
		m_QingErTestPool.TestCardPoolOpen  = CIXml::getIntProperty( pTestPool , "open_flag" , 0 );

		pTestPool = xml.getFirstChildNode( rootPtr , "test_jianzhang" );
		m_QingErTestPool.TestJianZhang  = CIXml::getIntProperty( pTestPool , "jian_zhang" , 0 );

		pTestPool = xml.getFirstChildNode( rootPtr , "test_poolcards" );
		m_QingErTestPool.PoolCardStr  = CIXml::getStringProperty( pTestPool , "cards" , "" );
	}

	// 积分;
	{
		xmlNodePtr pRoomData = xml.getFirstChildNode( rootPtr , "qinger_jifen" );
		if ( NULL != pRoomData )
		{
			for ( ; NULL != pRoomData; pRoomData = xml.getNextChildNode( pRoomData , "qinger_jifen" ) )
			{
				QingErJieSuanScore Score;
				uint32 Kind = CIXml::getIntProperty  ( pRoomData , "kind" , 0 );
				Score.OutCardScore = CIXml::getIntProperty( pRoomData , "score" , 0 );
				//Score.ScoreName = CIXml::getStringProperty( pRoomData , "name" , "" );
				m_QingErScore[Kind] = Score;
			}
		}
	}

    // 状态执行次数;
    {
        xmlNodePtr pRoomData = xml.getFirstChildNode( rootPtr , "mahjong_state_count" );
        if ( NULL != pRoomData )
        {
            m_QingErStateCount.CheckStartGame         = CIXml::getIntProperty( pRoomData , "check_start_game" , 0 );
            m_QingErStateCount.CheckShowDownEochGame  = CIXml::getIntProperty( pRoomData , "showdown_eoch_game"  , 0 );
            m_QingErStateCount.CheckGameOverEochGame  = CIXml::getIntProperty( pRoomData , "gameover_eoch_game"  , 0 );
        }
    }

    return true;
}

bool QingErConfig::LoadQingErPool( void )
{
    CIFile file;
    mQingErCardPool.ResetData();
    file.setCacheFileOnOpen( true );
    std::string path = NLMISC::CPath::lookup("MahJongPool//01.txt");
    if ( !file.open( path ) ) {
        return false;
    }
    int HandCount = 0;
    char strBuff[1024] = { '\0' };
    // 解析玩家手牌;
    while ( !file.eof() )
    {
        if ( HandCount == mQingErCardPool.HandCardPool.size() ) { break; }
        file.getline( strBuff , sizeof( strBuff ) );
        CSString strSub( strBuff );
        CVectorSString strVec;strVec.clear();
        strSub.splitBySeparator(',' , strVec );
        if ( strVec.empty() ) { continue; }
        for ( int idx = 0; idx < strVec.size(); idx++ )
        {
            uint8 CardValue = mQingErCardPool.SwitchToCard( strVec[idx].atoi() );
            if ( CardValue <= 0 ) { continue; }
            mQingErCardPool.HandCardPool[HandCount].push_back( CardValue );
        }
        HandCount++;
    }

    // 解析牌桌牌池;
    while ( !file.eof() )
    {
        file.getline( strBuff , sizeof( strBuff ) );
        CSString strSub( strBuff );
        CVectorSString strVec;strVec.clear();
        strSub.splitBySeparator( ',' , strVec );
        for ( int idx = 0; idx < strVec.size(); idx++ )
        {
            uint8 CardValue = mQingErCardPool.SwitchToCard( strVec[idx].atoi() );
            if ( CardValue <= 0 ) { continue; }
            mQingErCardPool.CardPool.push_back( CardValue );
        }
    }
    return true;
}

bool QingErConfig::LoadFlowerSubsection( void )
{
    std::string path = NLMISC::CPath::lookup("FlowerSubsection.xml");
    CIFile file;
    CIXml xml;

    if ( !file.open( path ) ) {
        return false;
    }
    if ( !xml.init( file ) ) {
        return false;
    }
    xmlNodePtr rootPtr = xml.getRootNode();
    if ( NULL == rootPtr ) {
        return false;
    }

    mFlowerSubsection.clear();
    xmlNodePtr pFlowerSubsection = xml.getFirstChildNode( rootPtr , "score" );
    for ( ; NULL != pFlowerSubsection ; pFlowerSubsection = xml.getNextChildNode( pFlowerSubsection , "score" ) )
    {
        QingErFlowerSubsection FlowerData;
        FlowerData.ID       = CIXml::getIntProperty( pFlowerSubsection , "id" , 0 );
        FlowerData.FlowerNum= CIXml::getIntProperty( pFlowerSubsection , "flower" , 0 );
        FlowerData.MinMoney = CIXml::getIntProperty( pFlowerSubsection , "min_money" , 0 );
        FlowerData.MaxMoney = CIXml::getIntProperty( pFlowerSubsection , "max_money" , 0 );
        mFlowerSubsection.push_back( FlowerData );
    }
    return true;
}

QingErTestPool& QingErConfig::GetQingErTestPool()
{
	return m_QingErTestPool;
}

std::map<uint32 , QingErJieSuanScore > QingErConfig::GetQingErScore()
{
	return m_QingErScore;
}



uint QingErConfig::GetQEFlowerSubsection( DEF::MONEY Money )
{
    if ( mFlowerSubsection.empty() ) { return 0; }
    for ( int idx = 0; idx < mFlowerSubsection.size(); idx++ )
    {
        QingErFlowerSubsection& FlowerData = mFlowerSubsection[idx];
        if ( Money>=FlowerData.MinMoney && ( Money<=FlowerData.MaxMoney||FlowerData.MaxMoney==0 ) )
        {
            return FlowerData.FlowerNum;
        }
    }
    return mFlowerSubsection[mFlowerSubsection.size()-1].FlowerNum;
}

uint QingErConfig::GetMinFlowerMoney( void )
{
    if ( mFlowerSubsection.empty() ) { return std::numeric_limits<uint>::max(); }
    return mFlowerSubsection[0].MinMoney;
}

QingErStateTime* QingErConfig::GetQingErStateTime( TGameRoomKind Kind )
{
    std::map<TGameRoomKind , QingErStateTime >::iterator it = m_QingErStateTime.find( Kind );
    if ( it != m_QingErStateTime.end() ) { return &it->second; }

    it = m_QingErStateTime.find( TGD_JINYUANZI );
    if ( it == m_QingErStateTime.end() ) { return NULL; }
    return &it->second;
}

