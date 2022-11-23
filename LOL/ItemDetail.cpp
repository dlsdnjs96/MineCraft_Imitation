#include "stdafx.h"

ItemDetail::ItemDetail()
{
    Init();
}

void ItemDetail::SetDetail(int _itemid)
{
    itemId = _itemid;
    if (_itemid == 0)
        return;

    string str;
    if (_itemid > 200)
        str = ITEM_MANAGER->GetItemName(_itemid);
    else
        str = ITEM_MANAGER->GetBlockName(_itemid);
    float size = str.size() * 0.025f;
    dynamic_cast<Text*>(itemDetail->Find("text"))->ChangeText(str);
    itemDetail->Find("text")->SetLocalPosX(0.025f);

    itemDetail->Find("background")->SetLocalPosX(size);
    itemDetail->Find("background")->scale = { 0.5f * str.size(), 1.f, 1.f };

    itemDetail->Update();
}

void ItemDetail::Init()
{
    itemDetail = UI::Create("ItemDetail");
    itemDetail->LoadFile("Ingame/ItemDetail.xml");
}

void ItemDetail::Update()
{
    itemDetail->Update();

    if (itemId == 0)
    {
        itemDetail->visible = false;
    }
    else {
        itemDetail->visible = true;
        itemDetail->SetLocalPos(INPUT->NDCPosition);
        itemDetail->SetLocalPosZ( 0.3f );
        itemDetail->Update();
    }
    
}

void ItemDetail::Render()
{
    itemDetail->Render();
}

void ItemDetail::RenderHierarchy()
{
    itemDetail->RenderHierarchy();
}

void ItemDetail::Release()
{
    itemDetail->Release();
}
