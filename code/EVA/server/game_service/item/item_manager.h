#ifndef GSE_ITEM_MANAGER_H_
#define GSE_ITEM_MANAGER_H_

#include <game_service/game_service/game_service_def.h>

GSE_NAMESPACE_BEGIN_DECL

class CItemManager : public NLMISC::CSingleton< CItemManager >
{
public:
    ///  添加道具;
    bool AddItem( ROLE_ID , ITEM_ID , uint32 , PB_DotItem );
    ///  扣除道具;
    bool SubItem( ROLE_ID , ITEM_ID , uint32 , PB_DotItem );

    ///  获取道具数量;
    uint32  GetItemCount( ROLE_ID , ITEM_ID );

private:
    ///  获取道具信息;
    CRecordItem* GetItemInfo( ROLE_ID , ITEM_ID , bool IsAdd = false );
};

#define ItemManager CItemManager::getInstance();

GSE_NAMESPACE_END_DECL

#endif//GSE_ITEM_MANAGER_H_