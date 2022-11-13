#include "stdafx.h"

void Inventory::Init()
{
    quickSlots = UI::Create("QuickSlots");
    quickSlots->LoadFile("Ingame/QuickSlots.xml");

    invens = UI::Create("Invens");
    invens->LoadFile("Ingame/Invens.xml");

    mouse = UI::Create("MousePick");
    mouse->LoadFile("Ingame/MousePick.xml");
    //Text* temp3 = Text::Create("ea");
    //temp3->ChangeText("10");
    //mouse->AddChild(temp3);
    //mouse->scale = { 0.0799f, 0.123f, 1.f };
    //mouse->SetLocalPosZ(-0.1f);

    mousePick.itemid = 100;
    mousePick.ea = 12;
    mouse->material = RESOURCE->materials.Load("Items/100.mtl");

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            dynamic_cast<UI*>(invens->Find("slot" + to_string(int((j * 9) + i))))->mouseOver = [=]() { invens->Find("slot" + to_string(int((j * 9) + i)))->SetWorldPosZ(0.55f); };
            dynamic_cast<UI*>(invens->Find("slot" + to_string(int((j * 9) + i))))->mouseNotOver = [=]() { invens->Find("slot" + to_string(int((j * 9) + i)))->SetWorldPosZ(0.6f); };
            dynamic_cast<UI*>(invens->Find("slot" + to_string(int((j * 9) + i))))->mouseDown  = [=]() { 
                Util::Swap(invenSlots[(j * 9) + i], mousePick);
                UpdateInven((j * 9) + i);
                UpdateMouse(); };

            //UI* temp = UI::Create("itemImg" + to_string(int((j * 9) + i)));
            //temp->visible = false;
            //temp->material = RESOURCE->materials.Load("Items/100.mtl");
            //temp->scale = { 0.8f, 0.8f, 1.f };
            //temp->SetLocalPos({ 0.f, 0.f, -0.2f });
            //invens->Find("slot" + to_string(int((j * 9) + i)))->AddChild(temp);
            //Text* temp2 = Text::Create("itemEa" + to_string(int((j * 9) + i)));
            //invens->Find("itemImg" + to_string(int((j * 9) + i)))->AddChild(temp2);
            //invens->Find("itemEa" + to_string(int((j * 9) + i)))->SetLocalPos({ 0.52f, -0.0625f, -0.05f });
            //invens->Find("itemEa" + to_string(int((j * 9) + i)))->scale = { 4.f, 4.f, 1.f };
            //dynamic_cast<Text*>(invens->Find("itemEa" + to_string(int((j * 9) + i))))->ChangeText(to_string(int((j * 9) + i)));

        }
    }
    invens->Update();
    for (int j = 0; j < 4; j++)
    {
        dynamic_cast<UI*>(invens->Find("equip" + to_string(j)))->mouseOver = [=]() { invens->Find("equip" + to_string(j))->SetWorldPosZ(0.55f); };
        dynamic_cast<UI*>(invens->Find("equip" + to_string(j)))->mouseNotOver = [=]() { invens->Find("equip" + to_string(j))->SetWorldPosZ(0.6f); };
    }
    for (int j = 1; j <= 9; j++)
    {
        dynamic_cast<UI*>(invens->Find("qSlot" + to_string(j)))->mouseOver = [=]() { invens->Find("qSlot" + to_string(j))->SetWorldPosZ(0.55f); };
        dynamic_cast<UI*>(invens->Find("qSlot" + to_string(j)))->mouseNotOver = [=]() { invens->Find("qSlot" + to_string(j))->SetWorldPosZ(0.6f); };
        dynamic_cast<UI*>(invens->Find("qSlot" + to_string(j)))->mouseDown = [=]() {
            Util::Swap(slots[j], mousePick);
            UpdateQuickSlot(j);
            UpdateMouse(); };

        //UI* temp = UI::Create("qItemImg" + to_string(j));
        //temp->visible = false;
        //temp->material = RESOURCE->materials.Load("Items/100.mtl");
        //temp->scale = { 0.8f, 0.8f, 1.f };
        //temp->SetLocalPos({ 0.f, 0.f, -0.2f });
        //invens->Find("qSlot" + to_string(j))->AddChild(temp);
        //Text* temp2 = Text::Create("qItemEa" + to_string(j));
        //invens->Find("qItemImg" + to_string(j))->AddChild(temp2);
        //invens->Find("qItemEa" + to_string(j))->SetLocalPos({ 0.52f, -0.0625f, -0.05f });
        //invens->Find("qItemEa" + to_string(j))->scale = { 4.f, 4.f, 1.f };
        //dynamic_cast<Text*>(invens->Find("qItemEa" + to_string(j)))->ChangeText(to_string(j));
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            dynamic_cast<UI*>(invens->Find("combine" + to_string(int((j * 2) + i))))->mouseOver = [=]() { invens->Find("combine" + to_string(int((j * 2) + i)))->SetWorldPosZ(0.55f); };
            dynamic_cast<UI*>(invens->Find("combine" + to_string(int((j * 2) + i))))->mouseNotOver = [=]() { invens->Find("combine" + to_string(int((j * 2) + i)))->SetWorldPosZ(0.6f); };
        }
    }
    dynamic_cast<UI*>(invens->Find("outcome"))->mouseOver = [=]() { invens->Find("outcome")->SetWorldPosZ(0.55f); };
    dynamic_cast<UI*>(invens->Find("outcome"))->mouseNotOver = [=]() { invens->Find("outcome")->SetWorldPosZ(0.6f); };


    SetPickedItem(2, Item{ 102, 10 });
    SetPickedItem(3, Item{ 104, 10 });

    quickSlots->Update();
    invens->Update();
    

    showInven = false;
}

void Inventory::Update()
{
    if (INPUT->KeyDown('E'))
    {
        if (showInven) {
            POINT cursor;
            if (GetCursorPos(&cursor)) {
                INPUT->fixedMousePos.x = cursor.x;
                INPUT->fixedMousePos.y = cursor.y;
                INPUT->prevPosition = INPUT->position;
            }
            Util::CursorVisible(false);
            showInven = false;
        }
        else {
            INPUT->fixedMousePos.x = -1;
            Util::CursorVisible(true);
            showInven = true;
        }
    }

    for (int i = 1; i <= 9; i++)
    {
        if (INPUT->KeyDown('0' + i))
        {
            pickedSlot = i;
            float width = -0.44f + (0.88f * ((i - 1) / 8.f));
            quickSlots->Find("pickedSlot")->SetLocalPosX(width);
            quickSlots->Update();
        }
    }
    if (showInven) {
        invens->Update();

        if (mousePick.itemid != 0)
        {
            mouse->SetLocalPos({ INPUT->NDCPosition.x, INPUT->NDCPosition.y, mouse->GetLocalPos().z });
            mouse->Update();
        }

        if (INPUT->KeyDown(VK_LBUTTON) && not invens->MouseOver() && mousePick.itemid != 0)
        {
            ITEM_MANAGER->Spawn(ITEM_MANAGER->user->GetWorldPos(), mousePick);
            mousePick.Remove();
            UpdateMouse();
        }
    }
}

void Inventory::RenderHierarchy()
{
    quickSlots->RenderHierarchy();
    invens->RenderHierarchy();
    mouse->RenderHierarchy();
}

void Inventory::Render()
{
    quickSlots->Render();
    if (showInven) {
        invens->Render();
        mouse->Render();
    }
    
}

void Inventory::ShowInven(bool _on)
{
    if (_on)
    {
        showInven = true;
    }
    else {
        showInven = false;
    }
}

Item& Inventory::GetInvenItem(int _slot)
{
    Util::Saturate(_slot, 0, 26);
    return invenSlots[_slot];
}

void Inventory::SetInvenItem(int _slot, Item _item)
{
    Util::Saturate(_slot, 0, 26);
    invenSlots[_slot] = _item;
    return;
}

void Inventory::GainItem(Item _item)
{
    if (_item.itemid == 0)
        return;

    for (int i = 1; i <= 9; i++)
    {
        if (slots[i].itemid == _item.itemid)
        {
            slots[i].ea += _item.ea;
            UpdateQuickSlot(i);
            return;
        }
    }
    for (int i = 0; i <= 27; i++)
    {
        if (invenSlots[i].itemid == _item.itemid)
        {
            invenSlots[i].ea += _item.ea;
            UpdateInven(i);
            return;
        }
    }
    for (int i = 1; i <= 9; i++)
    {
        if (slots[i].itemid == 0)
        {
            slots[i] = _item;
            UpdateQuickSlot(i);
            return;
        }
    }
    for (int i = 0; i <= 27; i++)
    {
        if (invenSlots[i].itemid == 0)
        {
            invenSlots[i] = _item;
            UpdateInven(i);
            return;
        }
    }
}

void Inventory::LossItem(Item _item)
{
}

void Inventory::UpdateInven(int _slot)
{
    if (invenSlots[_slot].ea <= 0)
        invens->Find("itemImg" + to_string(_slot))->visible = false;
    else {
        invens->Find("itemImg" + to_string(_slot))->visible = true;
        invens->Find("itemImg" + to_string(_slot))->material = RESOURCE->materials.Load("Items/" + to_string(invenSlots[_slot].itemid) + ".mtl");
        dynamic_cast<Text*>(invens->Find("itemEa" + to_string(_slot)))->ChangeText(to_string(invenSlots[_slot].ea));
    }
}

void Inventory::UpdateMouse()
{
    if (mousePick.ea <= 0)
        mouse->visible = false;
    else {
        mouse->visible = true;
        mouse->material = RESOURCE->materials.Load("Items/" + to_string(mousePick.itemid) + ".mtl");
        dynamic_cast<Text*>(mouse->Find("ea"))->ChangeText(to_string(mousePick.ea));
    }
}

int Inventory::GetPickedSlot()
{
    return pickedSlot;
}

Item& Inventory::GetPickedItem()
{
    return slots[pickedSlot];
}

Item& Inventory::GetSlotItem(int _slot)
{
    Util::Saturate(_slot, 1, 9);
    return slots[_slot];
}

Item Inventory::SetPickedItem(int _slot, Item _item)
{
    Item temp;
    Util::Saturate(_slot, 1, 9);
    temp = slots[_slot];
    slots[_slot] = _item;
    quickSlots->Find("slot" + to_string(_slot))->material = RESOURCE->materials.Load("Items/" + to_string(_item.itemid) + ".mtl");
    quickSlots->Find("slot" + to_string(_slot))->visible = true;
    UpdateQuickSlot(_slot);

    return temp;
}

void Inventory::UsePickedItem()
{
    slots[pickedSlot].ea--;
    if (slots[pickedSlot].ea <= 0)
    {
        quickSlots->Find("slot" + to_string(pickedSlot))->visible = false;
    }
    UpdateQuickSlot(pickedSlot);
    return;
}

void Inventory::UpdateQuickSlot(int _slot)
{
    if (slots[_slot].ea <= 0) {
        quickSlots->Find("slot" + to_string(_slot))->visible = false;
        invens->Find("qItemImg" + to_string(_slot))->visible = false;
    }
    else {
        quickSlots->Find("slot" + to_string(_slot))->visible = true;
        quickSlots->Find("slot" + to_string(_slot))->material = RESOURCE->materials.Load("Items/" + to_string(slots[_slot].itemid) + ".mtl");
        dynamic_cast<Text*>(quickSlots->Find("slot" + to_string(_slot) + "_ea"))->ChangeText(to_string(slots[_slot].ea));

        invens->Find("qItemImg" + to_string(_slot))->visible = true;
        invens->Find("qItemImg" + to_string(_slot))->material = RESOURCE->materials.Load("Items/" + to_string(slots[_slot].itemid) + ".mtl");
        dynamic_cast<Text*>(invens->Find("qItemEa" + to_string(_slot)))->ChangeText(to_string(slots[_slot].ea));
    }
}
