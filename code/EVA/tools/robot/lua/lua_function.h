#ifndef PLS_LUA_FUNCTION_H
#define PLS_LUA_FUNCTION_H
#include <game_share/define_pro.pb.h>

/**
*   @brief 创建计时器;
*   @param SessionID  会话ID;
*   @param EventID    使用LuaID;
*   @param LuaEvent   事件类型;
*/
void CreateTimer( unsigned long long session_id , int time , const char* lua_usename , const char* lua_funname = "" , bool flag = false );

/**
*   @brief 进入房间;
*   @param SessionID 会话ID;
*/
void EnterGame( unsigned long long session_id );


/**
*   @brief 离开房间;
*   @param SessionID 会话ID;
*/
void LeaveRoom( unsigned long long session_id );

/**
*   @brief 请求刷新玩家信息;
*   @param SessionID 会话ID;
*/
void SyncPlayerInfo( unsigned long long session_id );

/**
*   @brief 请求游戏币排行榜（前十名）;
*   @param SessionID 会话ID;
*/
void MoneyRanking( unsigned long long session_id );

/**
*   @brief 请求下注;
*   @param SessionID 会话ID;
*   @param rand_pour 随机下注金额;
*/
void BlackJackAddPour( unsigned long long session_id, int rand_count, int rand_pour );

/**
*   @brief 请求要牌;
*   @param SessionID 会话ID;
*/
void BlackJackAskCard( unsigned long long session_id );

/**
*   @brief 请求分牌;
*   @param SessionID 会话ID;
*/
void BlackJackSplitCard( unsigned long long session_id );

/**
*   @brief 请求停牌;
*   @param SessionID 会话ID;
*/
void BlackJackStandCard( unsigned long long session_id );

/**
*   @brief 购买保险;
*   @param SessionID 会话ID;
*/
void BlackJackBuySurrender( unsigned long long session_id );

/**
*   @brief 跳过保险;
*   @param SessionID 会话ID;
*/
void BlackJackSkipSurrender( unsigned long long session_id );

/**
*   @brief 双倍;
*   @param SessionID 会话ID;
*/
void BlackJackDoubleCard( unsigned long long session_id );

/**
*   @brief 清除下注;
*   @param SessionID 会话ID;
*/
void BlackJackClearPour( unsigned long long session_id );

/**
*   @brief 添加金钱;
*   @param SessionID 会话ID;
*/
void PlayerAddMoney( unsigned long long session_id );

/**
*   @brief 减少金钱;
*   @param SessionID 会话ID;
*/
void PlayerSubMoney( unsigned long long session_id );

/**
*   @brief 领取奖励;
*   @param SessionID 会话ID;
*/
void GetReward( unsigned long long session_id );

/**
*   @brief 请求比赛数据;
*   @param SessionID 会话ID;
*/
void GetChampionship( unsigned long long session_id );

/**
*   @brief 请求比赛奖池;
*   @param SessionID 会话ID;
*/
void RequestPrizePool( unsigned long long session_id );

/**
*   @brief Ranking Room Top;
*   @param SessionID 会话ID;
*/
void RankingRoomTop( unsigned long long session_id );

/**
*   @brief 请求获取自己的排行榜数据;
*   @param SessionID 会话ID;
*/
void GetRankingMyData( unsigned long long session_id );

/**
*   @brief 请求发送普通邮件;
*   @param SessionID 会话ID;
*/
void RequestSendCommmonMail( unsigned long long session_id, int rand_title_count , int rand_content_count );

/**
*   @brief 请求邮件数据;
*   @param SessionID 会话ID;
*/
void RequestMailData( unsigned long long session_id );

/**
*   @brief 请求获取系统邮件奖励;
*   @param SessionID 会话ID;
*/
void RequestSystemMailReward( unsigned long long session_id );

/**
*   @brief 请求获取普通邮件奖励;
*   @param SessionID 会话ID;
*/
void RequestCommonMailReward( unsigned long long session_id );

/**
*   @brief 请求删除系统邮件;
*   @param SessionID 会话ID;
*/
void RequestDeleteSystemMail( unsigned long long session_id );

/**
*   @brief 请求删除普通邮件;
*   @param SessionID 会话ID;
*/
void RequestDeleteCommonMail( unsigned long long session_id );

/**
*   @brief 请求查看普通邮件;
*   @param SessionID 会话ID;
*/
void RequestLookCommonMail( unsigned long long session_id );

/**
*   @brief 请求同步好友列表;
*   @param SessionID 会话ID;
*/
void SynchFriendList( unsigned long long session_id );

/**
*   @brief 请求同步好友申请列表;
*   @param SessionID 会话ID;
*/
void SynchApplyList( unsigned long long session_id );

/**
*   @brief 好友申请;
*   @param SessionID 会话ID;
*/
void AddFriendApply( unsigned long long session_id );

/**
*   @brief 好友添加;
*   @param SessionID 会话ID;
*/
void AddFriend( unsigned long long session_id );

/**
*   @brief 删除好友;
*   @param SessionID 会话ID;
*/
void DeleteFriend( unsigned long long session_id );

/**
*   @brief 删除好友申请;
*   @param SessionID 会话ID;
*/
void DeleteApplyFriend( unsigned long long session_id );

/**
*   @brief 请求好友详细信息;
*   @param SessionID 会话ID;
*/
void RequestFriendDetail( unsigned long long session_id );

/**
*   @brief 请求申请好友详细信息;
*   @param SessionID 会话ID;
*/
void RequestApplyDetail( unsigned long long session_id );

/**
*   @brief 请求奖励好友;
*   @param SessionID 会话ID;
*/
void RequestRewardFriend( unsigned long long session_id, int rand_money );

/**
*   @brief 房间内聊天;
*   @param SessionID 会话ID;
*/
void ChatRoom( unsigned long long session_id, int rand_count );

/**
*   @brief 牌桌上打赏;
*   @param SessionID 会话ID;
*/
void GiveTips( unsigned long long session_id );

/**
*   @brief 请求同局其它玩家详细信息;
*   @param SessionID 会话ID;
*/
void RoomPlayerInfo( unsigned long long session_id );

/**
*   @brief 好友邀请;
*   @param SessionID 会话ID;
*/
void InviteFriend( unsigned long long session_id );

/**
*   @brief 绑定facebook;
*   @param SessionID 会话ID;
*/
void BindFacebook( unsigned long long session_id );

/**
*   @brief 大转盘;
*   @param SessionID 会话ID;
*/
void PullRouletteMoney( unsigned long long session_id );

/**
*   @brief 转倍率;
*   @param SessionID 会话ID;
*/ 
void PullRouletteRate( unsigned long long session_id );

/**
*   @brief 美金转倍率;
*   @param SessionID 会话ID;
*/ 
void PullRouletteRateRMB( unsigned long long session_id );

/**
*   @brief 获取转盘奖励;
*   @param SessionID 会话ID;
*/ 
void RouletteGetMoney( unsigned long long session_id );

/**
*   @brief 请求商店信息;
*   @param SessionID 会话ID;
*/ 
void RequestShopInfo( unsigned long long session_id );

/**
*   @brief 请求购买Money;
*   @param SessionID 会话ID;
*/ 
void RequestBuyMoney( unsigned long long session_id );

/**
*   @brief 请求购买Money;
*   @param SessionID 会话ID;
*/ 
// 请求改名字;
void PlayerRename( unsigned long long session_id );

/**
*   @brief 请求其他玩家详细信息;
*   @param SessionID 会话ID;
*/ 
void ReqOtherPlayerInfo( unsigned long long session_id );

/**
*   @brief 请求自己详细信息;
*   @param SessionID 会话ID;
*/ 
void ReqSelfPlayerInfo( unsigned long long session_id );

/**
*   @brief 请求其他玩家统计数据;
*   @param SessionID 会话ID;
*/
void ReqPlayerKPI( unsigned long long session_id );

/**
*   @brief 大厅看广告领取奖励;
*   @param SessionID 会话ID;
*/
void HallAdsDrawAward( unsigned long long session_id );

/**
*   @brief 房间看广告领取奖励;
*   @param SessionID 会话ID;
*/
void RoomAdsDrawAward( unsigned long long session_id );

/**
*   @brief 检测消息发送时间;
*   @param SessionID 会话ID;
*/
void CkeckSendMsgTime( unsigned long long session_id );

/**
*   @brief 玩家跟注;
*   @param SessionID 会话ID;
*/
void CallPour( unsigned long long session_id );

/**
*   @brief 玩家加注;
*   @param SessionID 会话ID;
*/
void RaisePour( unsigned long long session_id );

/**
*   @brief 玩家弃牌;
*   @param SessionID 会话ID;
*/
void FoldCard( unsigned long long session_id );

/**
*   @brief 玩家让牌;
*   @param SessionID 会话ID;
*/
void CheckCard( unsigned long long session_id );

/**
*   @brief 重置筹码;
*   @param SessionID 会话ID;
*/
void ResetCoins( unsigned long long session_id );

/**
*   @brief 返回游戏;
*   @param SessionID 会话ID;
*/
void GoBackGame( unsigned long long session_id );

/**
*   @brief 老虎机拉杆;
*   @param SessionID 会话ID;
*/
void SlotsSpin( unsigned long long session_id );

/**
*   @brief 请求查看邮件状态;
*   @param SessionID 会话ID;
*/
void CheckMailState( unsigned long long session_id );

/**
*   @brief 查看BJ比赛参赛人数;
*   @param SessionID 会话ID;
*/
void SynchRoomRankPlayerNum( unsigned long long session_id );

/**
*   @brief 请求同步成就信息;
*   @param SessionID 会话ID;
*/
void SynchAchievementData( unsigned long long session_id );

/**
*   @brief 请求同步已完成成就信息;
*   @param SessionID 会话ID;
*/
void SynchCompleteAchievementData( unsigned long long session_id );

/**
*   @brief 请求领取成就奖励;
*   @param SessionID 会话ID;
*/
void DrawAchievementReward( unsigned long long session_id );

/**
*   @brief 重置赌注(Bet, Bet*2, Betall);
*   @param1 SessionID 会话ID;
*   @param2 rand_pour 随机赌注;
*/
void BlackJackResetPour( unsigned long long session_id, int rand_pour );

/**
*   @brief 老虎机小游戏;
*   @param SessionID 会话ID;
*/
void SlotsBonusGameSelect( unsigned long long session_id );

/**
*   @brief 推荐好友;
*   @param SessionID 会话ID;
*/
void RequestRecommendFriend( unsigned long long session_id );

/**
*   @brief 请求同步统计信息;
*   @param SessionID 会话ID;
*/
void SynchStatisticsData( unsigned long long session_id );

/**
*   @brief 更新个性签名;
*   @param SessionID 会话ID;
*/
void UpdateDynamicMsg( unsigned long long session_id );

/**
*   @brief 修改头像;
*   @param SessionID 会话ID;
*/
void ReHeadPortrait( unsigned long long session_id, int rand_index );

/**
*   @brief Slots请求奖池数据;
*   @param SessionID 会话ID;
*/
void GetSlotsJackpots( unsigned long long session_id );

/**
*   @brief 德州竞技场报名;
*   @param SessionID 会话ID;
*/
void TPChallApplyGame( unsigned long long session_id );

/**
*   @brief 德州竞技场取消报名;
*   @param SessionID 会话ID;
*/
void TPChallCancelApplyGame( unsigned long long session_id );

/**
*   @brief 德州竞技场房间信息;
*   @param SessionID 会话ID;
*/
void TPChallRoomData( unsigned long long session_id );

/**
*   @brief 德州竞技场请求退出;
*   @param SessionID 会话ID;
*/
void TPChallRequestQuit( unsigned long long session_id );

/**
*   @brief 好友私聊;
*   @param SessionID 会话ID;
*/
void PrivateChat( unsigned long long session_id );

/**
*   @brief 南京麻将 用户选择权限;
*   @param1 SessionID 会话ID;
*   @param2 rand_index 随机权限;
*/
void MahjongUserOperate( unsigned long long session_id, int rand_index );

/**
*   @brief 南京麻将 出牌;
*   @param1 SessionID 会话ID;
*/
void MahjongOutCard( unsigned long long session_id );

/**
*   @brief 南京麻将 用户开始准备;
*   @param1 SessionID 会话ID;
*/
void MahjongStartReady( unsigned long long session_id );

/**
*   @brief 南京麻将 用户取消准备;
*   @param1 SessionID 会话ID;
*/
void MahjongCancelReady( unsigned long long session_id );

// 请求道具数据;
void SynchItemData( unsigned long long session_id );

// 使用道具;
void UseItem( unsigned long long session_id );

// 出售道具;
void SellItem( unsigned long long session_id );

// 商城购买道具;
void StoreBuyItem( unsigned long long session_id );

// 检验校验码绑定手机号;
void BindMobileNumberCheck( unsigned long long session_id );

// 跑马灯喊话;
void ChatPaoMaDeng( unsigned long long session_id );

// 获取 Send Money Limit;
void GetSendMoneyLimit( unsigned long long session_id );

// 搜索PID;
void SearchPID( unsigned long long session_id );

// 同步屏蔽列表;
void SyncBlackList( unsigned long long session_id );

// 移除屏蔽列表;
void DeleteBlackList( unsigned long long session_id );

// 添加屏蔽列表;
void AddBlackList( unsigned long long session_id );

// 请求同步任务数据;
void SynchMissionData( unsigned long long session_id );

// 请求统计积分清零;
void RestoreScoreData( unsigned long long session_id );
#endif
