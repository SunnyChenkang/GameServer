#ifndef SSE_GAME_MANAGER_H_
#define SSE_GAME_MANAGER_H_

#include <schedule_service/schedule_service/schedule_service_def.h>

SSE_NAMESPACE_BEGIN_DECL

class CGameManager : public NLMISC::CSingleton< CGameManager >
{
public:
    CGameManager( void ){ m_GameList.clear(); }
   ~CGameManager( void ){ };

    ///  更新游戏列表;
    void UpdateGameList( TServiceId , RecordGameList& );
    ///  删除游戏列表;
    void DeleteGameList( TServiceId& );

    ///  获取服务器信息;
    TServiceId GetGoodServiceID( CSString& );

    ///  游戏列表;
    SS_PROPERTY( RecordGameTable , GameList , private );
};

SSE_NAMESPACE_END_DECL

#define GameManager CGameManager::instance()

#endif// SSE_GAME_MANAGER_H_