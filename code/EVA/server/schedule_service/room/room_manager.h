#ifndef SSE_ROOM_MANAGER_H_
#define SSE_ROOM_MANAGER_H_

#include <schedule_service/schedule_service/schedule_service_def.h>
#include <server_share/id_allocate/id_allocate.h>

SSE_NAMESPACE_BEGIN_DECL

class CRoomManager : public NLMISC::CSingleton< CRoomManager >
{
public:
    typedef std::map< uint32 , PB_RoomInfoList > ROOM_INFO_TABLE;
    CRoomManager( void );
   ~CRoomManager( void ){ };

    //   用户私房信息;
    void CreateRoom( NLNET::CMessage& );
    //   删除房间信息;
    void DeleteRoomInfo( NLNET::TServiceId& );
    //   注册房间信息;
    void RegisterRoomInfo( NLNET::CMessage& );

    //   登录获取有效服务器;
    NLNET::TServiceId GetLoginGamaService( void );
    //   创建房间有效服务器;
    NLNET::TServiceId GetRoomGameService( NLMISC::CSString );

    SS_PROPERTY( ROOM_INFO_TABLE    , RoomInfo      , private );
    SS_PROPERTY( CRandomIDAlloc*    , RandomIdAlloc , private );
};

#define RoomManager CRoomManager::instance()

SSE_NAMESPACE_END_DECL

#endif// SSE_ROOM_MANAGER_H_