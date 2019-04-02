#ifndef GSE_ROOM_REGISTER_H_
#define GSE_ROOM_REGISTER_H_

#include <game_service/game_service/game_service_def.h>

GSE_NAMESPACE_BEGIN_DECL

class CRoomRegister : public NLMISC::CSingleton< CRoomRegister >
{
public:
    CRoomRegister( void );

    //   加载配置;
    void LoadRoomInfo( void );
    //   同步房间信息;
    void UpdateRoomInfo( void );

    SS_PROPERTY( PB_RoomInfoList , Roomlist     , private );

private:
    CTimer m_RoomInfoTimer;
};

#define RoomRegister CRoomRegister::instance()

GSE_NAMESPACE_END_DECL

#endif//GSE_ROOM_REGISTER_H_