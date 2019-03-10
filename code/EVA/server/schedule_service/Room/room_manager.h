#ifndef SSE_ROOM_MANAGER_H_
#define SSE_ROOM_MANAGER_H_

#include "../schedule_def.h"

SSE_NAMESPACE_BEGIN_DECL

class CRoomManager : public NLMISC::CSingleton< CRoomManager >
{
public:
    CRoomManager( void ){ };
   ~CRoomManager( void ){ };

    
}

#define RoomManager CRoomManager::instance()

SSE_NAMESPACE_END_DECL

#endif// SSE_ROOM_MANAGER_H_