/*
** Lua binding: lua_function
** Generated automatically by tolua++-1.0.92 on 06/22/16 15:50:16.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_lua_function_open (lua_State* tolua_S);

#include "lua_function.h"
#include "lua_event.h"

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
}

/* function: CreateTimer */
#ifndef TOLUA_DISABLE_tolua_lua_function_CreateTimer00
static int tolua_lua_function_CreateTimer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isstring(tolua_S,4,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  int time = ((int)  tolua_tonumber(tolua_S,2,0));
  const char* lua_usename = ((const char*)  tolua_tostring(tolua_S,3,0));
  const char* lua_funname = ((const char*)  tolua_tostring(tolua_S,4,""));
  bool flag = ((bool)  tolua_toboolean(tolua_S,5,false));
  {
   CreateTimer(session_id,time,lua_usename,lua_funname,flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateTimer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CkeckSendMsgTime */
#ifndef TOLUA_DISABLE_tolua_lua_function_CkeckSendMsgTime00
static int tolua_lua_function_CkeckSendMsgTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   CkeckSendMsgTime(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CkeckSendMsgTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: MoneyRanking */
#ifndef TOLUA_DISABLE_tolua_lua_function_MoneyRanking00
static int tolua_lua_function_MoneyRanking00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   MoneyRanking(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MoneyRanking'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: EnterGame */
#ifndef TOLUA_DISABLE_tolua_lua_function_EnterGame00
static int tolua_lua_function_EnterGame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   EnterGame(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EnterGame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: LeaveRoom */
#ifndef TOLUA_DISABLE_tolua_lua_function_LeaveRoom00
static int tolua_lua_function_LeaveRoom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   LeaveRoom(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LeaveRoom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: BlackJackAddPour */
#ifndef TOLUA_DISABLE_tolua_lua_function_BlackJackAddPour00
static int tolua_lua_function_BlackJackAddPour00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  int rand_count = ((int)  tolua_tonumber(tolua_S,2,0));
  int rand_pour = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   BlackJackAddPour(session_id,rand_count,rand_pour);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BlackJackAddPour'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: BlackJackAskCard */
#ifndef TOLUA_DISABLE_tolua_lua_function_BlackJackAskCard00
static int tolua_lua_function_BlackJackAskCard00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   BlackJackAskCard(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BlackJackAskCard'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: BlackJackSplitCard */
#ifndef TOLUA_DISABLE_tolua_lua_function_BlackJackSplitCard00
static int tolua_lua_function_BlackJackSplitCard00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   BlackJackSplitCard(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BlackJackSplitCard'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: BlackJackStandCard */
#ifndef TOLUA_DISABLE_tolua_lua_function_BlackJackStandCard00
static int tolua_lua_function_BlackJackStandCard00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   BlackJackStandCard(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BlackJackStandCard'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: BlackJackBuySurrender */
#ifndef TOLUA_DISABLE_tolua_lua_function_BlackJackBuySurrender00
static int tolua_lua_function_BlackJackBuySurrender00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   BlackJackBuySurrender(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BlackJackBuySurrender'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: BlackJackSkipSurrender */
#ifndef TOLUA_DISABLE_tolua_lua_function_BlackJackSkipSurrender00
static int tolua_lua_function_BlackJackSkipSurrender00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   BlackJackSkipSurrender(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BlackJackSkipSurrender'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: BlackJackDoubleCard */
#ifndef TOLUA_DISABLE_tolua_lua_function_BlackJackDoubleCard00
static int tolua_lua_function_BlackJackDoubleCard00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   BlackJackDoubleCard(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BlackJackDoubleCard'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: BlackJackClearPour */
#ifndef TOLUA_DISABLE_tolua_lua_function_BlackJackClearPour00
static int tolua_lua_function_BlackJackClearPour00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   BlackJackClearPour(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BlackJackClearPour'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: PlayerAddMoney */
#ifndef TOLUA_DISABLE_tolua_lua_function_PlayerAddMoney00
static int tolua_lua_function_PlayerAddMoney00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   PlayerAddMoney(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PlayerAddMoney'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: PlayerSubMoney */
#ifndef TOLUA_DISABLE_tolua_lua_function_PlayerSubMoney00
static int tolua_lua_function_PlayerSubMoney00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   PlayerSubMoney(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PlayerSubMoney'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetReward */
#ifndef TOLUA_DISABLE_tolua_lua_function_GetReward00
static int tolua_lua_function_GetReward00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   GetReward(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetReward'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetChampionship */
#ifndef TOLUA_DISABLE_tolua_lua_function_GetChampionship00
static int tolua_lua_function_GetChampionship00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   GetChampionship(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetChampionship'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RequestPrizePool */
#ifndef TOLUA_DISABLE_tolua_lua_function_RequestPrizePool00
static int tolua_lua_function_RequestPrizePool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   RequestPrizePool(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RequestPrizePool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RankingRoomTop */
#ifndef TOLUA_DISABLE_tolua_lua_function_RankingRoomTop00
static int tolua_lua_function_RankingRoomTop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   RankingRoomTop(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RankingRoomTop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetRankingMyData */
#ifndef TOLUA_DISABLE_tolua_lua_function_GetRankingMyData00
static int tolua_lua_function_GetRankingMyData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   GetRankingMyData(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRankingMyData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RequestSendCommmonMail */
#ifndef TOLUA_DISABLE_tolua_lua_function_RequestSendCommmonMail00
static int tolua_lua_function_RequestSendCommmonMail00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  int rand_title_count = ((int)  tolua_tonumber(tolua_S,2,0));
  int rand_content_count = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   RequestSendCommmonMail(session_id,rand_title_count,rand_content_count);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RequestSendCommmonMail'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RequestMailData */
#ifndef TOLUA_DISABLE_tolua_lua_function_RequestMailData00
static int tolua_lua_function_RequestMailData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   RequestMailData(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RequestMailData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RequestSystemMailReward */
#ifndef TOLUA_DISABLE_tolua_lua_function_RequestSystemMailReward00
static int tolua_lua_function_RequestSystemMailReward00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   RequestSystemMailReward(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RequestSystemMailReward'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RequestCommonMailReward */
#ifndef TOLUA_DISABLE_tolua_lua_function_RequestCommonMailReward00
static int tolua_lua_function_RequestCommonMailReward00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   RequestCommonMailReward(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RequestCommonMailReward'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RequestDeleteSystemMail */
#ifndef TOLUA_DISABLE_tolua_lua_function_RequestDeleteSystemMail00
static int tolua_lua_function_RequestDeleteSystemMail00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   RequestDeleteSystemMail(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RequestDeleteSystemMail'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RequestDeleteCommonMail */
#ifndef TOLUA_DISABLE_tolua_lua_function_RequestDeleteCommonMail00
static int tolua_lua_function_RequestDeleteCommonMail00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   RequestDeleteCommonMail(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RequestDeleteCommonMail'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RequestLookCommonMail */
#ifndef TOLUA_DISABLE_tolua_lua_function_RequestLookCommonMail00
static int tolua_lua_function_RequestLookCommonMail00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   RequestLookCommonMail(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RequestLookCommonMail'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SynchFriendList */
#ifndef TOLUA_DISABLE_tolua_lua_function_SynchFriendList00
static int tolua_lua_function_SynchFriendList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   SynchFriendList(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SynchFriendList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SynchApplyList */
#ifndef TOLUA_DISABLE_tolua_lua_function_SynchApplyList00
static int tolua_lua_function_SynchApplyList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   SynchApplyList(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SynchApplyList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AddFriendApply */
#ifndef TOLUA_DISABLE_tolua_lua_function_AddFriendApply00
static int tolua_lua_function_AddFriendApply00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   AddFriendApply(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddFriendApply'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AddFriend */
#ifndef TOLUA_DISABLE_tolua_lua_function_AddFriend00
static int tolua_lua_function_AddFriend00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   AddFriend(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddFriend'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DeleteFriend */
#ifndef TOLUA_DISABLE_tolua_lua_function_DeleteFriend00
static int tolua_lua_function_DeleteFriend00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   DeleteFriend(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DeleteFriend'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DeleteApplyFriend */
#ifndef TOLUA_DISABLE_tolua_lua_function_DeleteApplyFriend00
static int tolua_lua_function_DeleteApplyFriend00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   DeleteApplyFriend(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DeleteApplyFriend'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RequestFriendDetail */
#ifndef TOLUA_DISABLE_tolua_lua_function_RequestFriendDetail00
static int tolua_lua_function_RequestFriendDetail00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   RequestFriendDetail(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RequestFriendDetail'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RequestApplyDetail */
#ifndef TOLUA_DISABLE_tolua_lua_function_RequestApplyDetail00
static int tolua_lua_function_RequestApplyDetail00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   RequestApplyDetail(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RequestApplyDetail'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RequestRewardFriend */
#ifndef TOLUA_DISABLE_tolua_lua_function_RequestRewardFriend00
static int tolua_lua_function_RequestRewardFriend00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  int rand_money = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   RequestRewardFriend(session_id,rand_money);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RequestRewardFriend'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ChatRoom */
#ifndef TOLUA_DISABLE_tolua_lua_function_ChatRoom00
static int tolua_lua_function_ChatRoom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  int rand_count = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   ChatRoom(session_id,rand_count);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ChatRoom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GiveTips */
#ifndef TOLUA_DISABLE_tolua_lua_function_GiveTips00
static int tolua_lua_function_GiveTips00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   GiveTips(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GiveTips'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RoomPlayerInfo */
#ifndef TOLUA_DISABLE_tolua_lua_function_RoomPlayerInfo00
static int tolua_lua_function_RoomPlayerInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   RoomPlayerInfo(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RoomPlayerInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: InviteFriend */
#ifndef TOLUA_DISABLE_tolua_lua_function_InviteFriend00
static int tolua_lua_function_InviteFriend00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   InviteFriend(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InviteFriend'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: BindFacebook */
#ifndef TOLUA_DISABLE_tolua_lua_function_BindFacebook00
static int tolua_lua_function_BindFacebook00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   BindFacebook(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BindFacebook'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: PullRouletteMoney */
#ifndef TOLUA_DISABLE_tolua_lua_function_PullRouletteMoney00
static int tolua_lua_function_PullRouletteMoney00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   PullRouletteMoney(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PullRouletteMoney'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: PullRouletteRate */
#ifndef TOLUA_DISABLE_tolua_lua_function_PullRouletteRate00
static int tolua_lua_function_PullRouletteRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   PullRouletteRate(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PullRouletteRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: PullRouletteRateRMB */
#ifndef TOLUA_DISABLE_tolua_lua_function_PullRouletteRateRMB00
static int tolua_lua_function_PullRouletteRateRMB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   PullRouletteRateRMB(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PullRouletteRateRMB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RouletteGetMoney */
#ifndef TOLUA_DISABLE_tolua_lua_function_RouletteGetMoney00
static int tolua_lua_function_RouletteGetMoney00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   RouletteGetMoney(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RouletteGetMoney'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RequestShopInfo */
#ifndef TOLUA_DISABLE_tolua_lua_function_RequestShopInfo00
static int tolua_lua_function_RequestShopInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   RequestShopInfo(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RequestShopInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RequestBuyMoney */
#ifndef TOLUA_DISABLE_tolua_lua_function_RequestBuyMoney00
static int tolua_lua_function_RequestBuyMoney00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   RequestBuyMoney(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RequestBuyMoney'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: PlayerRename */
#ifndef TOLUA_DISABLE_tolua_lua_function_PlayerRename00
static int tolua_lua_function_PlayerRename00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   PlayerRename(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PlayerRename'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ReqOtherPlayerInfo */
#ifndef TOLUA_DISABLE_tolua_lua_function_ReqOtherPlayerInfo00
static int tolua_lua_function_ReqOtherPlayerInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   ReqOtherPlayerInfo(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReqOtherPlayerInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ReqSelfPlayerInfo */
#ifndef TOLUA_DISABLE_tolua_lua_function_ReqSelfPlayerInfo00
static int tolua_lua_function_ReqSelfPlayerInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   ReqSelfPlayerInfo(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReqSelfPlayerInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ReqPlayerKPI */
#ifndef TOLUA_DISABLE_tolua_lua_function_ReqPlayerKPI00
static int tolua_lua_function_ReqPlayerKPI00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   ReqPlayerKPI(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReqPlayerKPI'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: HallAdsDrawAward */
#ifndef TOLUA_DISABLE_tolua_lua_function_HallAdsDrawAward00
static int tolua_lua_function_HallAdsDrawAward00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   HallAdsDrawAward(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HallAdsDrawAward'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RoomAdsDrawAward */
#ifndef TOLUA_DISABLE_tolua_lua_function_RoomAdsDrawAward00
static int tolua_lua_function_RoomAdsDrawAward00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   RoomAdsDrawAward(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RoomAdsDrawAward'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CallPour */
#ifndef TOLUA_DISABLE_tolua_lua_function_CallPour00
static int tolua_lua_function_CallPour00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   CallPour(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CallPour'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RaisePour */
#ifndef TOLUA_DISABLE_tolua_lua_function_RaisePour00
static int tolua_lua_function_RaisePour00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   RaisePour(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RaisePour'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: FoldCard */
#ifndef TOLUA_DISABLE_tolua_lua_function_FoldCard00
static int tolua_lua_function_FoldCard00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   FoldCard(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FoldCard'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CheckCard */
#ifndef TOLUA_DISABLE_tolua_lua_function_CheckCard00
static int tolua_lua_function_CheckCard00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   CheckCard(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CheckCard'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ResetCoins */
#ifndef TOLUA_DISABLE_tolua_lua_function_ResetCoins00
static int tolua_lua_function_ResetCoins00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   ResetCoins(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ResetCoins'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GoBackGame */
#ifndef TOLUA_DISABLE_tolua_lua_function_GoBackGame00
static int tolua_lua_function_GoBackGame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   GoBackGame(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GoBackGame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SlotsSpin */
#ifndef TOLUA_DISABLE_tolua_lua_function_SlotsSpin00
static int tolua_lua_function_SlotsSpin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   SlotsSpin(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SlotsSpin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: CheckMailState */
#ifndef TOLUA_DISABLE_tolua_lua_function_CheckMailState00
static int tolua_lua_function_CheckMailState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   CheckMailState(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CheckMailState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SynchRoomRankPlayerNum */
#ifndef TOLUA_DISABLE_tolua_lua_function_SynchRoomRankPlayerNum00
static int tolua_lua_function_SynchRoomRankPlayerNum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   SynchRoomRankPlayerNum(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SynchRoomRankPlayerNum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SynchAchievementData */
#ifndef TOLUA_DISABLE_tolua_lua_function_SynchAchievementData00
static int tolua_lua_function_SynchAchievementData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   SynchAchievementData(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SynchAchievementData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SynchCompleteAchievementData */
#ifndef TOLUA_DISABLE_tolua_lua_function_SynchCompleteAchievementData00
static int tolua_lua_function_SynchCompleteAchievementData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   SynchCompleteAchievementData(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SynchCompleteAchievementData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DrawAchievementReward */
#ifndef TOLUA_DISABLE_tolua_lua_function_DrawAchievementReward00
static int tolua_lua_function_DrawAchievementReward00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   DrawAchievementReward(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DrawAchievementReward'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: BlackJackResetPour */
#ifndef TOLUA_DISABLE_tolua_lua_function_BlackJackResetPour00
static int tolua_lua_function_BlackJackResetPour00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  int rand_pour = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   BlackJackResetPour(session_id,rand_pour);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BlackJackResetPour'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SlotsBonusGameSelect */
#ifndef TOLUA_DISABLE_tolua_lua_function_SlotsBonusGameSelect00
static int tolua_lua_function_SlotsBonusGameSelect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   SlotsBonusGameSelect(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SlotsBonusGameSelect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RequestRecommendFriend */
#ifndef TOLUA_DISABLE_tolua_lua_function_RequestRecommendFriend00
static int tolua_lua_function_RequestRecommendFriend00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   RequestRecommendFriend(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RequestRecommendFriend'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SynchStatisticsData */
#ifndef TOLUA_DISABLE_tolua_lua_function_SynchStatisticsData00
static int tolua_lua_function_SynchStatisticsData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   SynchStatisticsData(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SynchStatisticsData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: UpdateDynamicMsg */
#ifndef TOLUA_DISABLE_tolua_lua_function_UpdateDynamicMsg00
static int tolua_lua_function_UpdateDynamicMsg00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   UpdateDynamicMsg(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UpdateDynamicMsg'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ReHeadPortrait */
#ifndef TOLUA_DISABLE_tolua_lua_function_ReHeadPortrait00
static int tolua_lua_function_ReHeadPortrait00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  int rand_index = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   ReHeadPortrait(session_id,rand_index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReHeadPortrait'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetSlotsJackpots */
#ifndef TOLUA_DISABLE_tolua_lua_function_GetSlotsJackpots00
static int tolua_lua_function_GetSlotsJackpots00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   GetSlotsJackpots(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSlotsJackpots'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TPChallApplyGame */
#ifndef TOLUA_DISABLE_tolua_lua_function_TPChallApplyGame00
static int tolua_lua_function_TPChallApplyGame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   TPChallApplyGame(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TPChallApplyGame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TPChallCancelApplyGame */
#ifndef TOLUA_DISABLE_tolua_lua_function_TPChallCancelApplyGame00
static int tolua_lua_function_TPChallCancelApplyGame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   TPChallCancelApplyGame(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TPChallCancelApplyGame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TPChallRoomData */
#ifndef TOLUA_DISABLE_tolua_lua_function_TPChallRoomData00
static int tolua_lua_function_TPChallRoomData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   TPChallRoomData(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TPChallRoomData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: TPChallRequestQuit */
#ifndef TOLUA_DISABLE_tolua_lua_function_TPChallRequestQuit00
static int tolua_lua_function_TPChallRequestQuit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   TPChallRequestQuit(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TPChallRequestQuit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: PrivateChat */
#ifndef TOLUA_DISABLE_tolua_lua_function_PrivateChat00
static int tolua_lua_function_PrivateChat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   PrivateChat(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PrivateChat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: MahjongUserOperate */
#ifndef TOLUA_DISABLE_tolua_lua_function_MahjongUserOperate00
static int tolua_lua_function_MahjongUserOperate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  int rand_index = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   MahjongUserOperate(session_id,rand_index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MahjongUserOperate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: MahjongOutCard */
#ifndef TOLUA_DISABLE_tolua_lua_function_MahjongOutCard00
static int tolua_lua_function_MahjongOutCard00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   MahjongOutCard(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MahjongOutCard'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: MahjongStartReady */
#ifndef TOLUA_DISABLE_tolua_lua_function_MahjongStartReady00
static int tolua_lua_function_MahjongStartReady00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   MahjongStartReady(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MahjongStartReady'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: MahjongCancelReady */
#ifndef TOLUA_DISABLE_tolua_lua_function_MahjongCancelReady00
static int tolua_lua_function_MahjongCancelReady00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   MahjongCancelReady(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MahjongCancelReady'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SynchItemData */
#ifndef TOLUA_DISABLE_tolua_lua_function_SynchItemData00
static int tolua_lua_function_SynchItemData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   SynchItemData(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SynchItemData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: UseItem */
#ifndef TOLUA_DISABLE_tolua_lua_function_UseItem00
static int tolua_lua_function_UseItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   UseItem(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UseItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SellItem */
#ifndef TOLUA_DISABLE_tolua_lua_function_SellItem00
static int tolua_lua_function_SellItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   SellItem(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SellItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: StoreBuyItem */
#ifndef TOLUA_DISABLE_tolua_lua_function_StoreBuyItem00
static int tolua_lua_function_StoreBuyItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   StoreBuyItem(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StoreBuyItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: BindMobileNumberCheck */
#ifndef TOLUA_DISABLE_tolua_lua_function_BindMobileNumberCheck00
static int tolua_lua_function_BindMobileNumberCheck00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   BindMobileNumberCheck(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BindMobileNumberCheck'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ChatPaoMaDeng */
#ifndef TOLUA_DISABLE_tolua_lua_function_ChatPaoMaDeng00
static int tolua_lua_function_ChatPaoMaDeng00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   ChatPaoMaDeng(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ChatPaoMaDeng'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetSendMoneyLimit */
#ifndef TOLUA_DISABLE_tolua_lua_function_GetSendMoneyLimit00
static int tolua_lua_function_GetSendMoneyLimit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   GetSendMoneyLimit(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSendMoneyLimit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SearchPID */
#ifndef TOLUA_DISABLE_tolua_lua_function_SearchPID00
static int tolua_lua_function_SearchPID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   SearchPID(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SearchPID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SyncBlackList */
#ifndef TOLUA_DISABLE_tolua_lua_function_SyncBlackList00
static int tolua_lua_function_SyncBlackList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   SyncBlackList(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SyncBlackList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: DeleteBlackList */
#ifndef TOLUA_DISABLE_tolua_lua_function_DeleteBlackList00
static int tolua_lua_function_DeleteBlackList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   DeleteBlackList(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DeleteBlackList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SynchMissionData */
#ifndef TOLUA_DISABLE_tolua_lua_function_SynchMissionData00
static int tolua_lua_function_SynchMissionData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   SynchMissionData(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SynchMissionData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RestoreScoreData */
#ifndef TOLUA_DISABLE_tolua_lua_function_RestoreScoreData00
static int tolua_lua_function_RestoreScoreData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned long long session_id = ((unsigned long long)  tolua_tonumber(tolua_S,1,0));
  {
   RestoreScoreData(session_id);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RestoreScoreData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_lua_function_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"ROBOT_EVENT_INVALID",ROBOT_EVENT_INVALID);
  tolua_constant(tolua_S,"ROBOT_EVENT_REGSTEREVENT",ROBOT_EVENT_REGSTEREVENT);
  tolua_constant(tolua_S,"ROBOT_EVENT_BLACKJACK",ROBOT_EVENT_BLACKJACK);
  tolua_constant(tolua_S,"ROBOT_EVENT_TEXASPOKER",ROBOT_EVENT_TEXASPOKER);
  tolua_constant(tolua_S,"ROBOT_EVENT_SLOT",ROBOT_EVENT_SLOT);
  tolua_constant(tolua_S,"ROBOT_EVENT_MAHJONG",ROBOT_EVENT_MAHJONG);
  tolua_function(tolua_S,"CreateTimer",tolua_lua_function_CreateTimer00);
  tolua_function(tolua_S,"CkeckSendMsgTime",tolua_lua_function_CkeckSendMsgTime00);
  tolua_function(tolua_S,"MoneyRanking",tolua_lua_function_MoneyRanking00);
  tolua_function(tolua_S,"EnterGame",tolua_lua_function_EnterGame00);
  tolua_function(tolua_S,"LeaveRoom",tolua_lua_function_LeaveRoom00);
  tolua_function(tolua_S,"BlackJackAddPour",tolua_lua_function_BlackJackAddPour00);
  tolua_function(tolua_S,"BlackJackAskCard",tolua_lua_function_BlackJackAskCard00);
  tolua_function(tolua_S,"BlackJackSplitCard",tolua_lua_function_BlackJackSplitCard00);
  tolua_function(tolua_S,"BlackJackStandCard",tolua_lua_function_BlackJackStandCard00);
  tolua_function(tolua_S,"BlackJackBuySurrender",tolua_lua_function_BlackJackBuySurrender00);
  tolua_function(tolua_S,"BlackJackSkipSurrender",tolua_lua_function_BlackJackSkipSurrender00);
  tolua_function(tolua_S,"BlackJackDoubleCard",tolua_lua_function_BlackJackDoubleCard00);
  tolua_function(tolua_S,"BlackJackClearPour",tolua_lua_function_BlackJackClearPour00);
  tolua_function(tolua_S,"PlayerAddMoney",tolua_lua_function_PlayerAddMoney00);
  tolua_function(tolua_S,"PlayerSubMoney",tolua_lua_function_PlayerSubMoney00);
  tolua_function(tolua_S,"GetReward",tolua_lua_function_GetReward00);
  tolua_function(tolua_S,"GetChampionship",tolua_lua_function_GetChampionship00);
  tolua_function(tolua_S,"RequestPrizePool",tolua_lua_function_RequestPrizePool00);
  tolua_function(tolua_S,"RankingRoomTop",tolua_lua_function_RankingRoomTop00);
  tolua_function(tolua_S,"GetRankingMyData",tolua_lua_function_GetRankingMyData00);
  tolua_function(tolua_S,"RequestSendCommmonMail",tolua_lua_function_RequestSendCommmonMail00);
  tolua_function(tolua_S,"RequestMailData",tolua_lua_function_RequestMailData00);
  tolua_function(tolua_S,"RequestSystemMailReward",tolua_lua_function_RequestSystemMailReward00);
  tolua_function(tolua_S,"RequestCommonMailReward",tolua_lua_function_RequestCommonMailReward00);
  tolua_function(tolua_S,"RequestDeleteSystemMail",tolua_lua_function_RequestDeleteSystemMail00);
  tolua_function(tolua_S,"RequestDeleteCommonMail",tolua_lua_function_RequestDeleteCommonMail00);
  tolua_function(tolua_S,"RequestLookCommonMail",tolua_lua_function_RequestLookCommonMail00);
  tolua_function(tolua_S,"SynchFriendList",tolua_lua_function_SynchFriendList00);
  tolua_function(tolua_S,"SynchApplyList",tolua_lua_function_SynchApplyList00);
  tolua_function(tolua_S,"AddFriendApply",tolua_lua_function_AddFriendApply00);
  tolua_function(tolua_S,"AddFriend",tolua_lua_function_AddFriend00);
  tolua_function(tolua_S,"DeleteFriend",tolua_lua_function_DeleteFriend00);
  tolua_function(tolua_S,"DeleteApplyFriend",tolua_lua_function_DeleteApplyFriend00);
  tolua_function(tolua_S,"RequestFriendDetail",tolua_lua_function_RequestFriendDetail00);
  tolua_function(tolua_S,"RequestApplyDetail",tolua_lua_function_RequestApplyDetail00);
  tolua_function(tolua_S,"RequestRewardFriend",tolua_lua_function_RequestRewardFriend00);
  tolua_function(tolua_S,"ChatRoom",tolua_lua_function_ChatRoom00);
  tolua_function(tolua_S,"GiveTips",tolua_lua_function_GiveTips00);
  tolua_function(tolua_S,"RoomPlayerInfo",tolua_lua_function_RoomPlayerInfo00);
  tolua_function(tolua_S,"InviteFriend",tolua_lua_function_InviteFriend00);
  tolua_function(tolua_S,"BindFacebook",tolua_lua_function_BindFacebook00);
  tolua_function(tolua_S,"PullRouletteMoney",tolua_lua_function_PullRouletteMoney00);
  tolua_function(tolua_S,"PullRouletteRate",tolua_lua_function_PullRouletteRate00);
  tolua_function(tolua_S,"PullRouletteRateRMB",tolua_lua_function_PullRouletteRateRMB00);
  tolua_function(tolua_S,"RouletteGetMoney",tolua_lua_function_RouletteGetMoney00);
  tolua_function(tolua_S,"RequestShopInfo",tolua_lua_function_RequestShopInfo00);
  tolua_function(tolua_S,"RequestBuyMoney",tolua_lua_function_RequestBuyMoney00);
  tolua_function(tolua_S,"PlayerRename",tolua_lua_function_PlayerRename00);
  tolua_function(tolua_S,"ReqOtherPlayerInfo",tolua_lua_function_ReqOtherPlayerInfo00);
  tolua_function(tolua_S,"ReqSelfPlayerInfo",tolua_lua_function_ReqSelfPlayerInfo00);
  tolua_function(tolua_S,"ReqPlayerKPI",tolua_lua_function_ReqPlayerKPI00);
  tolua_function(tolua_S,"HallAdsDrawAward",tolua_lua_function_HallAdsDrawAward00);
  tolua_function(tolua_S,"RoomAdsDrawAward",tolua_lua_function_RoomAdsDrawAward00);
  tolua_function(tolua_S,"CallPour",tolua_lua_function_CallPour00);
  tolua_function(tolua_S,"RaisePour",tolua_lua_function_RaisePour00);
  tolua_function(tolua_S,"FoldCard",tolua_lua_function_FoldCard00);
  tolua_function(tolua_S,"CheckCard",tolua_lua_function_CheckCard00);
  tolua_function(tolua_S,"ResetCoins",tolua_lua_function_ResetCoins00);
  tolua_function(tolua_S,"GoBackGame",tolua_lua_function_GoBackGame00);
  tolua_function(tolua_S,"SlotsSpin",tolua_lua_function_SlotsSpin00);
  tolua_function(tolua_S,"CheckMailState",tolua_lua_function_CheckMailState00);
  tolua_function(tolua_S,"SynchRoomRankPlayerNum",tolua_lua_function_SynchRoomRankPlayerNum00);
  tolua_function(tolua_S,"SynchAchievementData",tolua_lua_function_SynchAchievementData00);
  tolua_function(tolua_S,"SynchCompleteAchievementData",tolua_lua_function_SynchCompleteAchievementData00);
  tolua_function(tolua_S,"DrawAchievementReward",tolua_lua_function_DrawAchievementReward00);
  tolua_function(tolua_S,"BlackJackResetPour",tolua_lua_function_BlackJackResetPour00);
  tolua_function(tolua_S,"SlotsBonusGameSelect",tolua_lua_function_SlotsBonusGameSelect00);
  tolua_function(tolua_S,"RequestRecommendFriend",tolua_lua_function_RequestRecommendFriend00);
  tolua_function(tolua_S,"SynchStatisticsData",tolua_lua_function_SynchStatisticsData00);
  tolua_function(tolua_S,"UpdateDynamicMsg",tolua_lua_function_UpdateDynamicMsg00);
  tolua_function(tolua_S,"ReHeadPortrait",tolua_lua_function_ReHeadPortrait00);
  tolua_function(tolua_S,"GetSlotsJackpots",tolua_lua_function_GetSlotsJackpots00);
  tolua_function(tolua_S,"TPChallApplyGame",tolua_lua_function_TPChallApplyGame00);
  tolua_function(tolua_S,"TPChallCancelApplyGame",tolua_lua_function_TPChallCancelApplyGame00);
  tolua_function(tolua_S,"TPChallRoomData",tolua_lua_function_TPChallRoomData00);
  tolua_function(tolua_S,"TPChallRequestQuit",tolua_lua_function_TPChallRequestQuit00);
  tolua_function(tolua_S,"PrivateChat",tolua_lua_function_PrivateChat00);
  tolua_function(tolua_S,"MahjongUserOperate",tolua_lua_function_MahjongUserOperate00);
  tolua_function(tolua_S,"MahjongOutCard",tolua_lua_function_MahjongOutCard00);
  tolua_function(tolua_S,"MahjongStartReady",tolua_lua_function_MahjongStartReady00);
  tolua_function(tolua_S,"MahjongCancelReady",tolua_lua_function_MahjongCancelReady00);
  tolua_function(tolua_S,"SynchItemData",tolua_lua_function_SynchItemData00);
  tolua_function(tolua_S,"UseItem",tolua_lua_function_UseItem00);
  tolua_function(tolua_S,"SellItem",tolua_lua_function_SellItem00);
  tolua_function(tolua_S,"StoreBuyItem",tolua_lua_function_StoreBuyItem00);
  tolua_function(tolua_S,"BindMobileNumberCheck",tolua_lua_function_BindMobileNumberCheck00);
  tolua_function(tolua_S,"ChatPaoMaDeng",tolua_lua_function_ChatPaoMaDeng00);
  tolua_function(tolua_S,"GetSendMoneyLimit",tolua_lua_function_GetSendMoneyLimit00);
  tolua_function(tolua_S,"SearchPID",tolua_lua_function_SearchPID00);
  tolua_function(tolua_S,"SyncBlackList",tolua_lua_function_SyncBlackList00);
  tolua_function(tolua_S,"DeleteBlackList",tolua_lua_function_DeleteBlackList00);
  tolua_function(tolua_S,"SynchMissionData",tolua_lua_function_SynchMissionData00);
  tolua_function(tolua_S,"RestoreScoreData",tolua_lua_function_RestoreScoreData00);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_lua_function (lua_State* tolua_S) {
 return tolua_lua_function_open(tolua_S);
};
#endif

