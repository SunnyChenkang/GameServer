#include "static_table_guandan.h"
#include <nel/misc/file.h>
#include <nel/misc/i_xml.h>

using namespace NLMISC;

bool GuanDanCardPool::LoadCardConfig( void )
{
	CIFile file;
	ResetData();
	file.setCacheFileOnOpen( true );
	std::string path;
    try
    {
        path = NLMISC::CPath::lookup("GuanDanCardPool//GDCardConfig.txt");
    }
    catch(...)
    {
        return false;
    }
	if ( !file.open( path ) ) {
		return false;
	}
	char strBuff[1024] = { '\0' };

	// 解析玩家手牌;
	sint32 nIndex = 0;
	while ( !file.eof() )
	{
		if ( 4 == HandCardPool.size() ) { break; }
		file.getline( strBuff , sizeof( strBuff ) );
		CSString strSub( strBuff );
		CVectorSString strVec;
		strVec.clear();
		strSub.splitBySeparator('\t' , strVec );
		if ( strVec.empty() ) { continue; }
		std::vector<uint8> CardList;
		for ( int idx = 0; idx < strVec.size(); idx++ )
		{
			uint8 CardValue = SwitchToCardValue( strVec[idx] );
			if ( CardValue <= 0 ) { continue; }
			CardList.push_back( CardValue );
		}
		HandCardPool.push_back( CardList );
		nIndex++;
	}

	if ( 4 != HandCardPool.size() )
		return false;

	return true;
}

bool GuanDanCardPool::IsValidConfig( void ) const
{
	if ( 4 != HandCardPool.size() )
		return false;
	return true;
}
/*
转换规则：
a 黑桃
b 红桃
c 梅花
d 方块
e1 小王
e2 大王
*/

uint8 GuanDanCardPool::SwitchToCardValue( CSString& str )
{
	uint8 CvRet = 0;
	CSString left = str.left( 1 );
	CSString right = str.right( str.length() - 1 );
	uint8 CardColor = 0;
	uint8 CardValue = 0;

	// 颜色值
	if ( left == "a" )
	{
		CardColor = 3;
	}
	else if ( left == "b" )
	{
		CardColor = 2;
	}
	else if ( left == "c" )
	{
		CardColor = 1;
	}
	else if ( left == "d" )
	{
		CardColor = 0;
	}
	else if ( left == "e" )
	{
		CardColor = 4;
	}

	// 牌值
	CardValue = atoi( right.c_str() );

	CvRet = ( ( CardColor << 4 ) | CardValue );

	return CvRet;
}




//////////////////////////////////////////////////////////////////////////
CGuanDanConfig::CGuanDanConfig( void )
{

}

CGuanDanConfig::~CGuanDanConfig( void )
{

}

void CGuanDanConfig::ResetData( void )
{

}

bool CGuanDanConfig::LoadConfig( void )
{
    std::string path = "";

    try
    {
        path = NLMISC::CPath::lookup("GameGuanDan.xml");;
    }
    catch (...)
    {
        return false;
    }


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

    // 掼蛋状态时间;
    {
        xmlNodePtr pStateTime = xml.getFirstChildNode( rootPtr , "wait_time" );
        mGuanDanStateTime.WaitTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "wait_time_out" );
        mGuanDanStateTime.WaitTimeOut = CIXml::getIntProperty( pStateTime , "time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "start_time" );
        mGuanDanStateTime.StartTime   = CIXml::getIntProperty( pStateTime , "time" , 0 );
        // 
        pStateTime = xml.getFirstChildNode( rootPtr , "check_start_game" );
        mGuanDanStateTime.CheckStartTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "banker_time" );
        mGuanDanStateTime.BankerTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "brand_time" );
        mGuanDanStateTime.BrandTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "send_gift_time" );
        mGuanDanStateTime.SendGiftTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "recv_gift_time" );
        mGuanDanStateTime.RecvGiftTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "send_gift_finish_time" );
        mGuanDanStateTime.SendGiftFinishTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "recv_gift_finish_time" );
        mGuanDanStateTime.RecvGiftFinishTime = CIXml::getIntProperty( pStateTime , "time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "action_time" );
        mGuanDanStateTime.ActionTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "" );
        mGuanDanStateTime.OutCardTime = CIXml::getIntProperty( pStateTime , "outcard_time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "showdown_finish_time" );
        mGuanDanStateTime.ShowDwonTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

		pStateTime = xml.getFirstChildNode( rootPtr , "showdown_end_time" );
		mGuanDanStateTime.EndTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

		pStateTime = xml.getFirstChildNode( rootPtr , "relieve_time" );
		mGuanDanStateTime.RelieveTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

		pStateTime = xml.getFirstChildNode( rootPtr , "autocard_time" );
		mGuanDanStateTime.AutoCardTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

		pStateTime = xml.getFirstChildNode( rootPtr , "trust_time" );
		mGuanDanStateTime.TrustTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

		pStateTime = xml.getFirstChildNode( rootPtr , "auto_send_gift_time" );
		mGuanDanStateTime.AutoSendGiftTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

		pStateTime = xml.getFirstChildNode( rootPtr , "auto_pass_card_time" );
		mGuanDanStateTime.AutoPassCardTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "msg_game_max_time" );
        mGuanDanStateTime.MSGGameMaxTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );

        pStateTime = xml.getFirstChildNode( rootPtr , "msg_role_machine_state_time" );
        mGuanDanStateTime.MSGRoleMachineTime  = CIXml::getIntProperty( pStateTime , "time" , 0 );
    }

    // 抗贡信息;
    {
        xmlNodePtr pStateTime = xml.getFirstChildNode( rootPtr , "guandan_kang_gong" );
        mGuanDanResistInfo.CardValue = CIXml::getIntProperty( pStateTime , "value" , 0 );
        mGuanDanResistInfo.CardCount = CIXml::getIntProperty( pStateTime , "count" , 0 );
    }

    // 十连奖励;
    {
        xmlNodePtr pStateTime = xml.getFirstChildNode( rootPtr , "shilian_reward" );
        if ( NULL != pStateTime )
        {
            mGuanDanRewardRole.GameCount   = CIXml::getIntProperty( pStateTime , "count" , 0 );
            mGuanDanRewardRole.RewardMoney = CIXml::getIntProperty( pStateTime , "money" , 0 );
            mGuanDanRewardRole.RewardRmb   = CIXml::getIntProperty( pStateTime , "rmb"   , 0 );
            xmlNodePtr pItemXml = xml.getFirstChildNode( pStateTime , "item" );
            for ( ; pItemXml != NULL; pItemXml = xml.getNextChildNode( pItemXml ,"item" ) )
            {
                ItemEntity Item;
                Item.item_tid = CIXml::getIntProperty( pItemXml , "id"    , 0 );
                Item.item_num = CIXml::getIntProperty( pItemXml , "count" , 0 );
                mGuanDanRewardRole.RewardItem.push_back( Item );
            }
        }
    }

    {
        xmlNodePtr pReduceSeries = xml.getFirstChildNode( rootPtr , "reduce_series" );
        if( NULL != pReduceSeries )
        {
            mGuandanReduceSeries.ReduceSeries = CIXml::getIntProperty( pReduceSeries, "value", 0 );
        }
    }

	// 状态执行次数;
	{
		xmlNodePtr pRoomData = xml.getFirstChildNode( rootPtr , "guandan_state_count" );
		if ( NULL != pRoomData )
		{
			mGuandanStateCount.CheckStartGame         = CIXml::getIntProperty( pRoomData , "check_start_game" , 0 );
			mGuandanStateCount.CheckShowDownEochGame  = CIXml::getIntProperty( pRoomData , "showdown_eoch_game"  , 0 );
			mGuandanStateCount.CheckGameOverEochGame  = CIXml::getIntProperty( pRoomData , "gameover_eoch_game"  , 0 );
		}
	}

	mGuanDanCardPool.LoadCardConfig();

    return true;
}

