#include "static_table_mahjong.h"
#include <nel/misc/file.h>
#include <nel/misc/i_xml.h>

using namespace NLMISC;

MahJongConfig::MahJongConfig( void )
{
    mMahJongRoomData.clear();
}

MahJongConfig::~MahJongConfig( void )
{

}

void MahJongConfig::ResetData( void )
{
    mMahJongRoomData.clear();
    mMahJongHuData.clear();
    mFlowerSubsection.clear();
    m_MahJongAmerceScore.clear();
    m_MahJongKaiGangScore.clear();
    m_MahJongMildFlowerScore.clear();
    m_MahJongStateTime.clear();
    //m_CreatePrivateConsumeItem.clear();
}

bool MahJongConfig::LoadConfig( void )
{
    try
    {
        ResetData();
        LoadMahJongPool();
        LoadFlowerSubsection();
    }
    catch ( ... ) {
    }
    std::string path = NLMISC::CPath::lookup("GameMahJong.xml");
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
    // 南京麻将状态时间;
    {
        MahJongNanJingStateTime FreeRoomTime;
        MahJongNanJingStateTime PrivateRoomTime;

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

        m_MahJongStateTime[TGD_NORMAL]       = FreeRoomTime;
        m_MahJongStateTime[TGD_JINYUANZI]    = PrivateRoomTime;
    }

    // 房间数据;
    {
        xmlNodePtr pRoomData = xml.getFirstChildNode( rootPtr , "mahjong_room_data" );
        for ( ; pRoomData!=NULL; pRoomData=xml.getNextChildNode(pRoomData, "mahjong_room_data") )
        {
            MahJongRoomData data;
            std::string room_type = CIXml::getStringProperty( pRoomData , "room_type" , "" );
            data.Kind             = (TGameRoomKind)CIXml::getIntProperty( pRoomData , "kind" , 0 );
            data.FlowerNum        = CIXml::getIntProperty( pRoomData , "flower_num"   , 0 );
            data.DaGangKaiHua     = CIXml::getIntProperty( pRoomData , "da_gang_kaihua" , 0 );
            data.FlowerScoreMoney = CIXml::getIntProperty( pRoomData , "flower_score_money" , 0 );
            data.BaseScore        = CIXml::getIntProperty( pRoomData , "base_score"  , 0);
            data.BaseFlower       = CIXml::getIntProperty( pRoomData , "base_flower", 0 );
            data.WinScore         = CIXml::getIntProperty( pRoomData , "win_score"  , 0 );
            data.LostScore        = CIXml::getIntProperty( pRoomData , "lost_score" , 0 );
            data.FlatScore        = CIXml::getIntProperty( pRoomData , "flat_score" , 0 );
            data.LeiBaoTaScore    = CIXml::getIntProperty( pRoomData , "leibaota_score" , 0 );
            data.LeiBaoTaCount    = CIXml::getIntProperty( pRoomData , "leibaota_max_count" , 0 );
            mMahJongRoomData[room_type] = data;
        }
    }

    // 软花
    {
        xmlNodePtr pRoomData = xml.getFirstChildNode( rootPtr , "mahjong_mild" );
        if ( NULL != pRoomData )
        {
            for ( ;NULL != pRoomData; pRoomData = xml.getNextChildNode( pRoomData , "mahjong_mild" ) )
            {
                TGameRoomKind Kind =   (TGameRoomKind)CIXml::getIntProperty( pRoomData , "kind" , 0 );
                m_MahJongMildFlowerScore[Kind].RateValue      = CIXml::getIntProperty( pRoomData , "za_er" , 1 );
                m_MahJongMildFlowerScore[Kind].SidesPeng      = CIXml::getIntProperty( pRoomData , "fengtou_peng" , 0 );
                m_MahJongMildFlowerScore[Kind].SidesMingGang  = CIXml::getIntProperty( pRoomData , "fengtou_ming_gang" , 0 );
                m_MahJongMildFlowerScore[Kind].SidesAnGang    = CIXml::getIntProperty( pRoomData , "fengtou_an_gang" , 0 );
                m_MahJongMildFlowerScore[Kind].NormalMingGang = CIXml::getIntProperty( pRoomData , "ming_gang" , 0 );
                m_MahJongMildFlowerScore[Kind].NormalAnGang   = CIXml::getIntProperty( pRoomData , "an_gang" , 0 );
                m_MahJongMildFlowerScore[Kind].QueYiMen       = CIXml::getIntProperty( pRoomData , "que_yi_men" , 0 );
                m_MahJongMildFlowerScore[Kind].YaDang         = CIXml::getIntProperty( pRoomData , "ya_dang" , 0 );
                m_MahJongMildFlowerScore[Kind].DuDiao         = CIXml::getIntProperty( pRoomData , "du_diao" , 0 );
                m_MahJongMildFlowerScore[Kind].HandFengTou    = CIXml::getIntProperty( pRoomData , "hand_fengtou" , 0 );
            }
        }
    }

    // 外包;
    {
        xmlNodePtr pRoomData = xml.getFirstChildNode( rootPtr , "mahjong_waibao" );
        if ( NULL != pRoomData )
        {
            m_PackCardScore.Score = CIXml::getIntProperty( pRoomData , "score" , 0  );
        }
    }

    // 加积分;
    {
        xmlNodePtr pRoomData = xml.getFirstChildNode( rootPtr , "integral_win" );
        if ( NULL != pRoomData )
        {
            m_WinIntegral.Integral = CIXml::getIntProperty( pRoomData , "integral" , 0  );
        }
    }

    // 状态执行次数;
    {
        xmlNodePtr pRoomData = xml.getFirstChildNode( rootPtr , "mahjong_state_count" );
        if ( NULL != pRoomData )
        {
            m_MahJongStateCount.CheckStartGame         = CIXml::getIntProperty( pRoomData , "check_start_game" , 0 );
            m_MahJongStateCount.CheckShowDownEochGame  = CIXml::getIntProperty( pRoomData , "showdown_eoch_game"  , 0 );
            m_MahJongStateCount.CheckGameOverEochGame  = CIXml::getIntProperty( pRoomData , "gameover_eoch_game"  , 0 );
        }
    }

    // 胡牌积分;
    {
        xmlNodePtr pRoomData = xml.getFirstChildNode( rootPtr , "nanjing_hu_flower" );
        if ( NULL != pRoomData )
        {
            for ( ; NULL != pRoomData ; pRoomData = xml.getNextChildNode( pRoomData , "nanjing_hu_flower" ) )
            {
                MahJongHuScore HuScore;
                HuScore.FlowerValue                 = CIXml::getIntProperty( pRoomData , "val" , 0  );
                HuScore.FlowerList[TGD_NORMAL]      = (TGameRoomKind)CIXml::getIntProperty( pRoomData , "flower_num_putong" , 0 );
                HuScore.FlowerList[TGD_JINYUANZI]   = (TGameRoomKind)CIXml::getIntProperty( pRoomData , "flower_num_jinyuanzi" , 0 );
                HuScore.FlowerList[TGD_CHANGKAITOU] = (TGameRoomKind)CIXml::getIntProperty( pRoomData , "flower_num_changkaitou" , 0 );
                mMahJongHuData.insert( std::make_pair( HuScore.FlowerValue , HuScore ) );
            }
        }
    }

    // 开杠积分;
    {
        xmlNodePtr pRoomData = xml.getFirstChildNode( rootPtr , "mahjong_gang" );
        if ( NULL != pRoomData )
        {
            for ( ; NULL != pRoomData; pRoomData = xml.getNextChildNode( pRoomData , "mahjong_gang" ) )
            {
                MahJongAmerceScore AmerceScore;
                TGameRoomKind Kind =   (TGameRoomKind)CIXml::getIntProperty( pRoomData , "kind" , 0 );
                m_MahJongKaiGangScore[Kind].MingGangScore    = CIXml::getIntProperty( pRoomData , "ming_gang" , 0 );
                m_MahJongKaiGangScore[Kind].AnGangScore      = CIXml::getIntProperty( pRoomData , "an_gang"   , 0 );
                m_MahJongKaiGangScore[Kind].FlowerGangScore  = CIXml::getIntProperty( pRoomData , "hua_gang"  , 0 );
                m_MahJongKaiGangScore[Kind].HuiPiMBarScore   = CIXml::getIntProperty( pRoomData , "huipi_ming_gang" , 0 );
                m_MahJongKaiGangScore[Kind].HuiPiABarScore   = CIXml::getIntProperty( pRoomData , "huipi_an_gang" , 0 );
				m_MahJongKaiGangScore[Kind].HuiABarScore     = CIXml::getIntProperty( pRoomData , "hui_an_gang" , 0 );
				m_MahJongKaiGangScore[Kind].HuiMBarScore     = CIXml::getIntProperty( pRoomData , "hui_ming_gang" , 0 );
			}
        }
    }
    // 其它积分;
    {
        xmlNodePtr pRoomData = xml.getFirstChildNode( rootPtr , "mahjong_other" );
        if ( NULL != pRoomData )
        {
            for ( ; NULL != pRoomData; pRoomData = xml.getNextChildNode( pRoomData , "mahjong_other" ) )
            {
                TGameRoomKind Kind =   (TGameRoomKind)CIXml::getIntProperty( pRoomData , "kind" , 0 );
                m_MahJongOtherScore[Kind].Param1 = CIXml::getIntProperty( pRoomData , "param1" , 0 );
                m_MahJongOtherScore[Kind].Param2 = CIXml::getIntProperty( pRoomData , "param2"   , 0 );
            }
        }
    }

    // 罚款积分;
    {
        xmlNodePtr pRoomData = xml.getFirstChildNode( rootPtr , "mahjong_fakuan" );
        if ( NULL != pRoomData )
        {
            for ( ; NULL != pRoomData; pRoomData = xml.getNextChildNode( pRoomData , "mahjong_fakuan" ) )
            {
                MahJongAmerceScore AmerceScore;
                TGameRoomKind Kind = (TGameRoomKind)CIXml::getIntProperty  ( pRoomData , "kind" , 0 );
                m_MahJongAmerceScore[Kind].OutCardScore    = CIXml::getIntProperty( pRoomData , "out_card" , 0 );
                m_MahJongAmerceScore[Kind].WithCardScore   = CIXml::getIntProperty( pRoomData , "with_card", 0 );
                m_MahJongAmerceScore[Kind].SeriesCardScore = CIXml::getIntProperty( pRoomData , "series_card",0 );
            }
        }
    }

    // 创建私房消耗;
    {
        //xmlNodePtr pRoomData = xml.getFirstChildNode( rootPtr , "create_room" );
        //if ( NULL != pRoomData )
        //{
        //    for ( ; NULL != pRoomData; pRoomData = xml.getNextChildNode( pRoomData , "create_room" ) )
        //    {
        //        CreatePrivateConsumeItem ConsumeItem;
        //        ConsumeItem.ID              = CIXml::getIntProperty( pRoomData , "id" , 0 );
        //        ConsumeItem.GameCount       = CIXml::getIntProperty( pRoomData , "game_count", 0 );
        //        ConsumeItem.ConsumeItemNum  = CIXml::getIntProperty( pRoomData , "consume_item_num" , 0 );
        //        ConsumeItem.ItemID          = CIXml::getIntProperty( pRoomData , "item_id" , 0 );
        //        m_CreatePrivateConsumeItem[ConsumeItem.ID] = ConsumeItem;
        //    }
        //}
    }
    return true;
}

bool MahJongConfig::LoadMahJongPool( void )
{
    CIFile file;
    mNanJingCardPool.ResetData();
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
        if ( HandCount == mNanJingCardPool.HandCardPool.size() ) { break; }
        file.getline( strBuff , sizeof( strBuff ) );
        CSString strSub( strBuff );
        CVectorSString strVec;strVec.clear();
        strSub.splitBySeparator(',' , strVec );
        if ( strVec.empty() ) { continue; }
        for ( int idx = 0; idx < strVec.size(); idx++ )
        {
            uint8 CardValue = mNanJingCardPool.SwitchToCard( strVec[idx].atoi() );
            if ( CardValue <= 0 ) { continue; }
            mNanJingCardPool.HandCardPool[HandCount].push_back( CardValue );
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
            uint8 CardValue = mNanJingCardPool.SwitchToCard( strVec[idx].atoi() );
            if ( CardValue <= 0 ) { continue; }
            mNanJingCardPool.CardPool.push_back( CardValue );
        }
    }
    return true;
}

bool MahJongConfig::LoadFlowerSubsection( void )
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
        FlowerSubsection FlowerData;
        FlowerData.ID       = CIXml::getIntProperty( pFlowerSubsection , "id" , 0 );
        FlowerData.FlowerNum= CIXml::getIntProperty( pFlowerSubsection , "flower" , 0 );
        FlowerData.MinMoney = CIXml::getIntProperty( pFlowerSubsection , "min_money" , 0 );
        FlowerData.MaxMoney = CIXml::getIntProperty( pFlowerSubsection , "max_money" , 0 );
        mFlowerSubsection.push_back( FlowerData );
    }
    return true;
}

MahJongRoomData* MahJongConfig::GetMahJongRoomData( std::string room_type )
{
    std::map<std::string,MahJongRoomData>::iterator it = mMahJongRoomData.find( room_type );
    if ( it == mMahJongRoomData.end() ) { return NULL; }
    return &( it->second );
}

uint MahJongConfig::GetFlowerSubsection( DEF::MONEY Money )
{
    if ( mFlowerSubsection.empty() ) { return 0; }
    for ( int idx = 0; idx < mFlowerSubsection.size(); idx++ )
    {
        FlowerSubsection& FlowerData = mFlowerSubsection[idx];
        if ( Money>=FlowerData.MinMoney && ( Money<=FlowerData.MaxMoney||FlowerData.MaxMoney==0 ) )
        {
            return FlowerData.FlowerNum;
        }
    }
    return mFlowerSubsection[mFlowerSubsection.size()-1].FlowerNum;
}

uint MahJongConfig::GetMinFlowerMoney( void )
{
    if ( mFlowerSubsection.empty() ) { return std::numeric_limits<uint>::max(); }
    return mFlowerSubsection[0].MinMoney;
}

MahJongAmerceScore* MahJongConfig::GetMahJongAmerceScore( TGameRoomKind Kind )
{
    std::map<TGameRoomKind , MahJongAmerceScore >::iterator it = m_MahJongAmerceScore.find( Kind );
    if ( it == m_MahJongAmerceScore.end() ){ return NULL; }
    return &it->second;
}

MahJongMildFlowerScore* MahJongConfig::GetMildFlowerScore( TGameRoomKind Kind )
{
    std::map<TGameRoomKind , MahJongMildFlowerScore >::iterator it = m_MahJongMildFlowerScore.find( Kind );
    if ( it == m_MahJongMildFlowerScore.end() ) { return NULL; }
    return &it->second;
}

MahJongKaiGangScore* MahJongConfig::GetMahJongKaiGangScore( TGameRoomKind Kind )
{
    std::map< TGameRoomKind , MahJongKaiGangScore >::iterator it = m_MahJongKaiGangScore.find( Kind );
    if ( it == m_MahJongKaiGangScore.end() ) { return NULL; }
    return &it->second;
}

MahJongNanJingStateTime* MahJongConfig::GetMahJongNanJingStateTime( TGameRoomKind Kind )
{
    std::map<TGameRoomKind , MahJongNanJingStateTime >::iterator it = m_MahJongStateTime.find( Kind );
    if ( it != m_MahJongStateTime.end() ) { return &it->second; }

    it = m_MahJongStateTime.find( TGD_JINYUANZI );
    if ( it == m_MahJongStateTime.end() ) { return NULL; }
    return &it->second;
}

MahJongOtherScoreData* MahJongConfig::GetMahJongOtherScore( TGameRoomKind Kind )
{
    std::map<TGameRoomKind , MahJongOtherScoreData >::iterator it = m_MahJongOtherScore.find( Kind );
    if ( it == m_MahJongOtherScore.end() ) { return NULL; }
    return &it->second;
}

//CreatePrivateConsumeItem* MahJongConfig::GetCreateConsumeItem( uint ID )
//{
//    std::map<uint,CreatePrivateConsumeItem>::iterator it = m_CreatePrivateConsumeItem.find( ID );
//    if ( it == m_CreatePrivateConsumeItem.end() ) { return NULL; }
//    return &it->second;
//}

