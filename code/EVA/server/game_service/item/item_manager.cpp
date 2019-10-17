#include "item_manager.h"
#include <game_service/player/player.h>
#include <game_service/player/player_manager.h>
#include <game_service/event/event_define.h>

GSE_NAMESPACE_BEGIN_DECL

bool CItemManager::AddItem( ROLE_ID RoleID , ITEM_ID ItemID , uint32 ItemCount , PB_DotItem DotItem )
{
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( RoleID );
    if ( nullptr == PlayerPtr )  { return false; }
    CItemCell* pItemCell = JsonItemConfig.GetJsonCell< CItemCell >( ItemID );
    if ( NULL == pItemCell )     { return false; }

    CRecordItem* pRecordItem = GetItemInfo( RoleID , ItemID , true );
    if ( nullptr == pRecordItem ){ return false; }
    pRecordItem->SetItemCount( pRecordItem->GetItemCount() + ItemCount );
    pRecordItem->SaveDB();

    /// 道具日志;
    EventDefine.AddItem( RoleID , ItemID , ItemCount , pRecordItem->GetItemCount() , DotItem );
    return true;
}

bool CItemManager::SubItem( ROLE_ID RoleID , ITEM_ID ItemID , uint32 ItemCount , PB_DotItem DotItem )
{
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( RoleID );
    if ( nullptr == PlayerPtr )  { return false; }

    CRecordItem* pRecordItem = GetItemInfo( RoleID , ItemID , false );
    if ( nullptr == pRecordItem ){ return false; }
    if ( pRecordItem->GetItemCount() < ItemCount ) { return false; }

    /// 更新道具数量;
    pRecordItem->SetItemCount( pRecordItem->GetItemCount() - ItemCount );
    pRecordItem->SetUpdate();
    pRecordItem->SaveDB();

    /// 道具日志;
    EventDefine.AddItem( RoleID , ItemID , ItemCount , pRecordItem->GetItemCount() , DotItem );
    return true;
}

uint32 CItemManager::GetItemCount( ROLE_ID RoleID , ITEM_ID ItemID )
{
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( RoleID );
    if ( nullptr == PlayerPtr )  { return 0; }
    CRecordItem* pRecordItem = GetItemInfo( RoleID , ItemID , false );
    if ( nullptr == pRecordItem ){ return 0; }

    return pRecordItem->GetItemCount();
}

CRecordItem* CItemManager::GetItemInfo( ROLE_ID RoleID , ITEM_ID ItemID , bool IsAdd )
{
    CPlayerPtr PlayerPtr = PlayerManager.GetPlayer( RoleID );
    if ( nullptr == PlayerPtr ) { return nullptr; }

    TRecordItem& TRecordData = PlayerPtr->GetRecordPlayer().GetRecordItem();
    auto It = TRecordData.find( ItemID );
    if ( It != TRecordData.end() )
    {
        It->second.SetUpdate();
        return &It->second;
    }

    if ( !IsAdd ) return nullptr;
    CRecordItem ItemData;
    ItemData.SetInsert();
    ItemData.SetRoleID( RoleID );
    ItemData.SetItemID( ItemID );
    auto Res = TRecordData.insert( std::make_pair(ItemID , ItemData) );
    return &Res.first->second;
}

GSE_NAMESPACE_END_DECL