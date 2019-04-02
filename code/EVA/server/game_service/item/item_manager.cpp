#include "item_manager.h"
#include <game_service/player/player.h>
#include <game_service/player/player_manager.h>
#include <game_service/event/event_define.h>

GSE_NAMESPACE_BEGIN_DECL

bool CItemManager::AddItem( ROLE_ID RoleID , ITEM_ID ItemID , uint32 ItemCount , PB_DotItem DotItem )
{
    CPlayer* pPlayer = PlayerManager.GetPlayer( RoleID );
    if ( NULL == pPlayer )   return false;
    CJsonItemCell* pItemCell = JsonRoomConfig.GetJsonCell< CJsonItemCell >( ItemID );
    if ( NULL == pItemCell ) return false;

    // 构造新道具;
    CRecordItem RecordItem;
    RecordItem.SetInsert();
    RecordItem.SetRoleID( RoleID );
    RecordItem.SetItemID( ItemID );
    RecordItem.SetItemCount( ItemCount );

    // 插入新道具;
    std::pair< TRecordItem::iterator , bool > res = pPlayer->GetRecordItemInfo().insert( std::make_pair( ItemID , RecordItem ) );
    if ( !res.second )
    {
        res.first->second += RecordItem;
        res.first->second.SetUpdate();
    }

    // 保存数据库;
    res.first->second.SaveToDataBase();

    // 道具日志;
    EventDefine.EventAddItem( RoleID , ItemID , ItemCount , res.first->second.GetItemCount() , DotItem );
    return true;
}

bool CItemManager::SubItem( ROLE_ID RoleID , ITEM_ID ItemID , uint32 ItemCount , PB_DotItem DotItem )
{
    CPlayer* pPlayer = PlayerManager.GetPlayer( RoleID );
    if ( NULL == pPlayer ) return false;

    // 查找道具实体;
    TRecordItem::iterator it = pPlayer->GetRecordItemInfo().find( ItemID );
    if ( it == pPlayer->GetRecordItemInfo().end() ) return false;
    if ( it->second.GetItemCount() < ItemCount ) return false;

    // 更新道具数量;
    it->second.SetItemCount( it->second.GetItemCount() - ItemCount );
    it->second.SetUpdate();
    it->second.SaveToDataBase();

    // 道具日志;
    EventDefine.EventAddItem( RoleID , ItemID , ItemCount , it->second.GetItemCount() , DotItem );
    return true;
}

uint32 CItemManager::GetItemCount( ROLE_ID RoleID , ITEM_ID ItemID )
{
    CPlayer* pPlayer = PlayerManager.GetPlayer( RoleID );
    if ( NULL == pPlayer ) return 0;

    TRecordItem::iterator it = pPlayer->GetRecordItemInfo().find( ItemID );
    if ( it == pPlayer->GetRecordItemInfo().end() ) return 0;
    return it->second.GetItemCount();
}

GSE_NAMESPACE_END_DECL