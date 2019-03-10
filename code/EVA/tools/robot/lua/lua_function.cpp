
#include <server_share/lua_engine.h>
#include <server_share/script_mgr.h>
#include <server_share/server_def.h>
#include <game_share/timer.h>
#include "lua_function.h"

#include "../CClient.h"
#include "../CClientMgr.h"
#include "../CRobotHelper.h"
#include "../msg/send_logic.h"

void CreateTimer( unsigned long long session_id , int time , const char* lua_usename , const char* lua_funname , bool flag /*= false*/ )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    if ( !pClient->IsOnlineState() )
        return;

    pClient->OnCreateTimer( lua_usename , lua_funname , time , flag );
}

void EnterGame( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;


    pClient->GetSendLogic()->EnterGame();
}

void LeaveRoom( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;


    pClient->GetSendLogic()->LeaveRoom();
}

void SyncPlayerInfo( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;


    pClient->GetSendLogic()->SyncPlayerInfo();

}

void MoneyRanking( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;


    pClient->GetSendLogic()->MoneyRanking();
}

void BlackJackAddPour( unsigned long long session_id, int rand_count, int rand_pour )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;


    pClient->GetSendLogic()->BlackJackAddPour(rand_count, rand_pour);
}

void BlackJackAskCard( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;


    pClient->GetSendLogic()->BlackJackAskCard();
}

void BlackJackSplitCard( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;


    pClient->GetSendLogic()->BlackJackSplitCard();
}

void BlackJackStandCard( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->BlackJackStandCard();
}

void BlackJackBuySurrender( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->BlackJackBuySurrender();
}

void BlackJackSkipSurrender( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->BlackJackSkipSurrender();
}

void BlackJackDoubleCard( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->BlackJackDoubleCard();
}

void BlackJackClearPour( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->BlackJackClearPour();
}

void PlayerAddMoney( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->PlayerAddMoney();
}

void PlayerSubMoney( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->PlayerSubMoney();
}

void GetReward( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->GetReward();
}

void GetChampionship( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->GetChampionship();
}

void RequestPrizePool( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->RequestPrizePool();
}

void RankingRoomTop( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->RankingRoomTop();
}

void GetRankingMyData( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->GetRankingMyData();
}

void RequestSendCommmonMail( unsigned long long session_id, int rand_title_count , int rand_content_count )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->RequestSendCommmonMail( rand_title_count , rand_content_count );
}

void RequestMailData( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->RequestMailData();
}

void RequestSystemMailReward( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->RequestSystemMailReward();
}

void RequestCommonMailReward( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->RequestCommonMailReward();
}

void RequestDeleteSystemMail( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->RequestDeleteSystemMail();
}

void RequestDeleteCommonMail( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->RequestDeleteCommonMail();
}

void RequestLookCommonMail( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->RequestLookCommonMail();

}

void SynchFriendList( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->SynchFriendList();
}

void SynchApplyList( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->SynchApplyList();
}

void AddFriendApply( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->AddFriendApply();
}

void AddFriend( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->AddFriend();
}

void DeleteFriend( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->DeleteFriend();
}

void DeleteApplyFriend( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->DeleteApplyFriend();
}

void RequestFriendDetail( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->RequestFriendDetail();
}

void RequestApplyDetail( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->RequestApplyDetail();
}

void RequestRewardFriend( unsigned long long session_id, int rand_money )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->RequestRewardFriend(rand_money);
}

void ChatRoom( unsigned long long session_id, int rand_count )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->ChatRoom( rand_count );
}

void GiveTips( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->GiveTips();
}

void RoomPlayerInfo( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->RoomPlayerInfo();
}

void InviteFriend( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient )
        return;

    pClient->GetSendLogic()->InviteFriend();
}

void BindFacebook( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->BindFacebook();
}

void PullRouletteMoney( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->PullRouletteMoney();
}

void PullRouletteRate( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->PullRouletteRate();
}

void PullRouletteRateRMB( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->PullRouletteRateRMB();
}

void RouletteGetMoney( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->RouletteGetMoney();
}

void RequestShopInfo( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->RequestShopInfo();
}

void RequestBuyMoney( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->RequestBuyMoney();
}

void PlayerRename( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->PlayerRename();
}

void ReqOtherPlayerInfo( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->ReqOtherPlayerInfo();
}

void ReqSelfPlayerInfo( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->ReqSelfPlayerInfo();
}

void ReqPlayerKPI( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->ReqPlayerKPI();
}

void HallAdsDrawAward( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->HallAdsDrawAward();
}

void RoomAdsDrawAward( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->RoomAdsDrawAward();
}

void CkeckSendMsgTime( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->CkeckSendMsgTime();
}

void CallPour( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->CallPour();
}

void RaisePour( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->RaisePour();
}

void FoldCard( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->FoldCard();
}

void CheckCard( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->CheckCard();
}

void ResetCoins( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->ResetCoins();
}

void GoBackGame( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->GoBackGame();
}

void SlotsSpin( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->SlotsSpin();
}

void CheckMailState( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    //pClient->GetSendLogic()->CheckMailState();
}

void SynchRoomRankPlayerNum( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->SynchRoomRankPlayerNum();
}

void SynchAchievementData( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->SynchAchievementData();
}

void SynchCompleteAchievementData( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->SynchCompleteAchievementData();
}

void DrawAchievementReward( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->DrawAchievementReward();
}

void BlackJackResetPour( unsigned long long session_id, int rand_pour )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->BlackJackResetPour(rand_pour);
}

void SlotsBonusGameSelect( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->SlotsBonusGameSelect();
}

void RequestRecommendFriend( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->RequestRecommendFriend();
}

void SynchStatisticsData( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->SynchStatisticsData();
}

void UpdateDynamicMsg( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->UpdateDynamicMsg();
}

void ReHeadPortrait( unsigned long long session_id, int rand_index )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->ReHeadPortrait( rand_index );
}

void GetSlotsJackpots( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->GetSlotsJackpots();
}

void TPChallApplyGame( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->TPChallApplyGame();
}

void TPChallCancelApplyGame( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->TPChallCancelApplyGame();
}

void TPChallRoomData( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->TPChallRoomData();
}

void TPChallRequestQuit( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->TPChallRequestQuit();
}

void PrivateChat( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->PrivateChat();
}

void MahjongUserOperate( unsigned long long session_id, int rand_index )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->MahjongUserOperate(rand_index);
}

void MahjongOutCard( unsigned long long session_id )
{

    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->MahjongOutCard(); 
}

void MahjongStartReady( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->MahjongStartReady();
}

void MahjongCancelReady( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->MahjongCancelReady();
}

void SynchItemData( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->SynchItemData();
}

void UseItem( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->UseItem();
}

void SellItem( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->SellItem();
}

void StoreBuyItem( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->StoreBuyItem();
}

void BindMobileNumberCheck( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->BindMobileNumberCheck();
}

void ChatPaoMaDeng( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->ChatPaoMaDeng();
}

void GetSendMoneyLimit( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->GetSendMoneyLimit();
}

void SearchPID( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->SearchPID();
}

void SyncBlackList( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->SyncBlackList();
}

void DeleteBlackList( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->DeleteBlackList();
}

void AddBlackList( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->AddBlackList();
}

void SynchMissionData( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->SynchMissionData();
}

void RestoreScoreData( unsigned long long session_id )
{
    CClient* pClient = ClientMgr->FindClient( session_id );
    if ( NULL == pClient ) {
        return;
    }
    pClient->GetSendLogic()->RestoreScoreData();
}

