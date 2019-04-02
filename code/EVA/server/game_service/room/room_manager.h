#ifndef GSE_ROOM_MANAGER_H_
#define GSE_ROOM_MANAGER_H_

#include <game_service/game_service/game_service_def.h>

GSE_NAMESPACE_BEGIN_DECL

class CRoomBase;

class CRoomManager : public NLMISC::CSingleton< CRoomManager >
{
public:
    typedef std::map< ROOM_ID , CRoomBase* >              ROOM_TABLE;
    CRoomManager( void );
   ~CRoomManager( void );

    //   创建房间;
    bool CreateRoom( ROLE_ID , PB_CreateRoom& );
    bool CreateRoomToScenes( ROLE_ID , PB_CreateRoom& );

    //   加入房间;
    bool JoinRoom( ROLE_ID , ROOM_ID );
    //   删除房间;
    bool DeleteRoom( ROOM_ID );

    //   查找房间;
    CRoomBase* GetRoomInfo( ROOM_ID );
    //   房间数量;
    uint32 GetRoomCount( NLMISC::CSString );

    SS_PROPERTY( ROOM_TABLE     , RoomTable     , private );
};

#define RoomManager CRoomManager::instance()

GSE_NAMESPACE_END_DECL

#endif//GSE_ROOM_MANAGER_H_