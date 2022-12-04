#include "stdafx.h"

Inventory::Inventory()
{
    Init();
}

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



    for (int i = 0; i < 27; i++)
    {
        dynamic_cast<UI*>(invens->Find("slot" + to_string(i)))->mouseOver = [=]() { ITEM_DETAIL->SetDetail(invenSlots[i].itemid); invens->Find("slot" + to_string(i))->SetWorldPosZ(0.55f); };
        dynamic_cast<UI*>(invens->Find("slot" + to_string(i)))->mouseNotOver = [=]() { ITEM_DETAIL->SetDetail(0); invens->Find("slot" + to_string(i))->SetWorldPosZ(0.6f); };
        dynamic_cast<UI*>(invens->Find("slot" + to_string(i)))->mouseDown  = [=]() {
            if (invenSlots[i].itemid == mousePick.itemid)
            {
                invenSlots[i].ea += mousePick.ea;
                mousePick.Remove();
            }
            else
                    Util::Swap(invenSlots[i], mousePick);
            UpdateInven(i);
            UpdateMouse(); };
        dynamic_cast<UI*>(invens->Find("slot" + to_string(i)))->mouseDownR = [=]() {
            if (invenSlots[i].itemid == 0 and mousePick.itemid != 0)
            {
                invenSlots[i].itemid = mousePick.itemid;
                invenSlots[i].ea++;
                mousePick.ea--;
            }
            else if (mousePick.itemid == 0 and invenSlots[i].itemid != 0)
            {
                mousePick.itemid = invenSlots[i].itemid;
                mousePick.ea = int(invenSlots[i].ea / 2);
                invenSlots[i].ea -= mousePick.ea;
            } else if (invenSlots[i].itemid == mousePick.itemid and mousePick.itemid != 0)
            {
                invenSlots[i].ea++;
                mousePick.ea--;
            }
            else
                Util::Swap(invenSlots[i], mousePick);
            UpdateInven(i);
            UpdateMouse(); };
    }
    invens->Update();
    for (int j = 0; j < 4; j++)
    {
        dynamic_cast<UI*>(invens->Find("equip" + to_string(j)))->mouseOver = [=]() { ITEM_DETAIL->SetDetail(equipSlot[j].itemid); invens->Find("equip" + to_string(j))->SetWorldPosZ(0.55f); };
        dynamic_cast<UI*>(invens->Find("equip" + to_string(j)))->mouseNotOver = [=]() { ITEM_DETAIL->SetDetail(0); invens->Find("equip" + to_string(j))->SetWorldPosZ(0.6f); };
        dynamic_cast<UI*>(invens->Find("equip" + to_string(j)))->mouseDown = [=]() {
            Util::Swap(equipSlot[j], mousePick);
            UpdateEquipSlot(j);
            UpdateMouse(); };

        //UI* temp = UI::Create("eItemImg" + to_string(j));
        //temp->visible = true;
        //temp->material = RESOURCE->materials.Load("Items/100.mtl");
        //temp->scale = { 0.8f, 0.8f, 1.f };
        //temp->SetLocalPos({ 0.f, 0.f, -0.2f });
        //invens->Find("equip" + to_string(j))->AddChild(temp);
        //Text* temp2 = Text::Create("eItemEa" + to_string(j));
        //invens->Find("eItemImg" + to_string(j))->AddChild(temp2);
        //invens->Find("eItemEa" + to_string(j))->SetLocalPos({ 0.52f, -0.0625f, -0.05f });
        //invens->Find("eItemEa" + to_string(j))->scale = { 4.f, 4.f, 1.f };
        //dynamic_cast<Text*>(invens->Find("eItemEa" + to_string(j)))->ChangeText(to_string(j));
    }
    for (int j = 1; j <= 9; j++)
    {
        dynamic_cast<UI*>(invens->Find("qSlot" + to_string(j)))->mouseOver = [=]() { ITEM_DETAIL->SetDetail(slots[j].itemid); invens->Find("qSlot" + to_string(j))->SetWorldPosZ(0.55f); };
        dynamic_cast<UI*>(invens->Find("qSlot" + to_string(j)))->mouseNotOver = [=]() { ITEM_DETAIL->SetDetail(0); invens->Find("qSlot" + to_string(j))->SetWorldPosZ(0.6f); };
        dynamic_cast<UI*>(invens->Find("qSlot" + to_string(j)))->mouseDown = [=]() {
            if (slots[j].itemid == mousePick.itemid)
            {
                slots[j].ea += mousePick.ea;
                mousePick.Remove();
            } else
                Util::Swap(slots[j], mousePick);
            UpdateQuickSlot(j);
            UpdateMouse(); };
        dynamic_cast<UI*>(invens->Find("qSlot" + to_string(j)))->mouseDownR = [=]() {
            if (slots[j].itemid == 0 and mousePick.itemid != 0)
            {
                slots[j].itemid = mousePick.itemid;
                slots[j].ea++;
                mousePick.ea--;
            }
            else if (mousePick.itemid == 0 and slots[j].itemid != 0)
            {
                mousePick.itemid = slots[j].itemid;
                mousePick.ea = int(slots[j].ea / 2);
                slots[j].ea -= mousePick.ea;
            }
            else if (slots[j].itemid == mousePick.itemid and mousePick.itemid != 0)
            {
                slots[j].ea++;
                mousePick.ea--;
            }
            else
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
            dynamic_cast<UI*>(invens->Find("combine" + to_string(int((j * 2) + i))))->mouseOver = [=]() { ITEM_DETAIL->SetDetail(combineSlot[j][i].itemid); invens->Find("combine" + to_string(int((j * 2) + i)))->SetWorldPosZ(0.55f); };
            dynamic_cast<UI*>(invens->Find("combine" + to_string(int((j * 2) + i))))->mouseNotOver = [=]() { ITEM_DETAIL->SetDetail(0); invens->Find("combine" + to_string(int((j * 2) + i)))->SetWorldPosZ(0.6f); };
            dynamic_cast<UI*>(invens->Find("combine" + to_string(int((j * 2) + i))))->mouseDown = [=]() {
                if (combineSlot[j][i].itemid == mousePick.itemid)
                {
                    combineSlot[j][i].ea += mousePick.ea;
                    mousePick.Remove();
                }
                else
                    Util::Swap(combineSlot[j][i], mousePick);
                outcomeSlot = CRAFTING->GetCraftItem2x2(combineSlot);
                UpdateOutcomeSlot();
                UpdateCombineSlot(j, i);
                UpdateMouse(); };
            dynamic_cast<UI*>(invens->Find("combine" + to_string(int((j * 2) + i))))->mouseDownR = [=]() {
                if (combineSlot[j][i].itemid == 0 and mousePick.itemid != 0)
                {
                    combineSlot[j][i].itemid = mousePick.itemid;
                    combineSlot[j][i].ea++;
                    mousePick.ea--;
                }
                else if (mousePick.itemid == 0 and combineSlot[j][i].itemid != 0)
                {
                    mousePick.itemid = combineSlot[j][i].itemid;
                    mousePick.ea = int(combineSlot[j][i].ea / 2);
                    combineSlot[j][i].ea -= mousePick.ea;
                }
                else if (combineSlot[j][i].itemid == mousePick.itemid and mousePick.itemid != 0)
                {
                    combineSlot[j][i].ea++;
                    mousePick.ea--;
                }
                else
                    Util::Swap(combineSlot[j][i], mousePick);
                //outcomeSlot = CRAFTING->GetCraftItem2x2(combineSlot);
                UpdateOutcomeSlot();
                UpdateCombineSlot(j, i);
                UpdateMouse(); };
            //UI* temp = UI::Create("cItemImg" + to_string(int((j * 2) + i)));
            //temp->visible = false;
            //temp->material = RESOURCE->materials.Load("Items/100.mtl");
            //temp->scale = { 0.8f, 0.8f, 1.f };
            //temp->SetLocalPos({ 0.f, 0.f, -0.2f });
            //invens->Find("combine" + to_string(int((j * 2) + i)))->AddChild(temp);
            //Text* temp2 = Text::Create("cItemEa" + to_string(int((j * 2) + i)));
            //invens->Find("cItemImg" + to_string(int((j * 2) + i)))->AddChild(temp2);
            //invens->Find("cItemEa" + to_string(int((j * 2) + i)))->SetLocalPos({ 0.52f, -0.0625f, -0.05f });
            //invens->Find("cItemEa" + to_string(int((j * 2) + i)))->scale = { 4.f, 4.f, 1.f };
            //dynamic_cast<Text*>(invens->Find("cItemEa" + to_string(int((j * 2) + i))))->ChangeText(to_string(j));
        }
    }
    dynamic_cast<UI*>(invens->Find("outcome"))->mouseOver = [=]() { ITEM_DETAIL->SetDetail(outcomeSlot.itemid); invens->Find("outcome")->SetWorldPosZ(0.55f); };
    dynamic_cast<UI*>(invens->Find("outcome"))->mouseNotOver = [=]() { ITEM_DETAIL->SetDetail(0); invens->Find("outcome")->SetWorldPosZ(0.6f); };
    dynamic_cast<UI*>(invens->Find("outcome"))->mouseDown = [=]() {
        if (outcomeSlot.itemid != 0 && mousePick.itemid == 0) {
            CRAFTING->MakeCraftItem2x2(combineSlot, outcomeSlot);
            Util::Swap(outcomeSlot, mousePick);
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                    UpdateCombineSlot(j, i);
            }
            UpdateOutcomeSlot();
            UpdateMouse();
        }
        else if (outcomeSlot.itemid == mousePick.itemid && mousePick.itemid != 0)
        {
            CRAFTING->MakeCraftItem2x2(combineSlot, outcomeSlot);
            mousePick.ea += outcomeSlot.ea;
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                    UpdateCombineSlot(j, i);
            }
            UpdateOutcomeSlot();
            UpdateMouse();
        }
    };
    //UI* temp = UI::Create("oItemImg");
    //temp->visible = true;
    //temp->material = RESOURCE->materials.Load("Items/100.mtl");
    //temp->scale = { 0.8f, 0.8f, 1.f };
    //temp->SetLocalPos({ 0.f, 0.f, -0.2f });
    //invens->Find("outcome")->AddChild(temp);
    //Text* temp2 = Text::Create("oItemEa");
    //invens->Find("oItemImg")->AddChild(temp2);
    //invens->Find("oItemEa")->SetLocalPos({ 0.52f, -0.0625f, -0.05f });
    //invens->Find("oItemEa")->scale = { 4.f, 4.f, 1.f };
    //dynamic_cast<Text*>(invens->Find("oItemEa"))->ChangeText(to_string(10));


    //SetPickedItem(1, Item{ 100, 10 });
    //SetPickedItem(2, Item{ 102, 10 });
    //SetPickedItem(3, Item{ 260, 10 });
    //SetPickedItem(4, Item{ 275, 10 });
    //SetPickedItem(5, Item{ int(BlockType::FURNACE), 100 });
    //SetPickedItem(6, Item{ int(BlockType::CRAFTING_TABLE), 10 });
    //SetPickedItem(7, Item{ 359, 1 });
    //SetPickedItem(8, Item{ 319, 10 });

    quickSlots->Update();
    invens->Update();
    

    showInven = false;
}

void Inventory::Update()
{
    if (INPUT->wheelMoveValue.z != 0.f) {
        pickedSlot -= int(INPUT->wheelMoveValue.z / 120.f);
        if (pickedSlot > 9)
            pickedSlot -= 9;
        if (pickedSlot < 1)
            pickedSlot += 9;
        float width = -0.44f + (0.88f * ((pickedSlot - 1) / 8.f));
        quickSlots->Find("pickedSlot")->SetLocalPosX(width);
        quickSlots->Update();
    }

    if (INPUT->KeyDown('R'))
    {
        if (showInven) {
            Util::LockMouse();
            ShowInven(false);
        }
        else {
            Util::UnLockMouse();
            ShowInven(true);
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
            ITEM_MANAGER->Spawn(PlayerModel::user->GetWorldPos(), mousePick);
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
        for (int i = 0; i < 27; i++)
            UpdateInven(i);
        for (int i = 1; i <= 9; i++)
            UpdateQuickSlot(i);
        UpdateMouse();

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
    for (int i = 0; i < 27; i++)
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
    for (int i = 0; i < 27; i++)
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
    if (invenSlots[_slot].ea <= 0) {
        invens->Find("itemImg" + to_string(_slot))->visible = false;
        invenSlots[_slot].Remove();
    }
    else {
        invens->Find("itemImg" + to_string(_slot))->visible = true;
        ITEM_MANAGER->SetItemImage(invens->Find("itemImg" + to_string(_slot)), invenSlots[_slot]);
        dynamic_cast<Text*>(invens->Find("itemEa" + to_string(_slot)))->ChangeText(to_string(invenSlots[_slot].ea));
    }
}

void Inventory::UpdateInven(int _slot, UI* _ui)
{
    if (invenSlots[_slot].ea <= 0) {
        _ui->Find("itemImg" + to_string(_slot))->visible = false;
        invenSlots[_slot].Remove();
    }
    else {
        _ui->Find("itemImg" + to_string(_slot))->visible = true;
        ITEM_MANAGER->SetItemImage(_ui->Find("itemImg" + to_string(_slot)), invenSlots[_slot]);
        dynamic_cast<Text*>(_ui->Find("itemEa" + to_string(_slot)))->ChangeText(to_string(invenSlots[_slot].ea));
    }
}

void Inventory::UpdateMouse()
{
    if (mousePick.ea <= 0) {
        mouse->visible = false;
        mousePick.Remove();
    }
    else {
        mouse->visible = true;
        ITEM_MANAGER->SetItemImage(mouse, mousePick);
        //mouse->material = RESOURCE->materials.Load("Items/" + to_string(mousePick.itemid) + ".mtl");
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

Item& Inventory::GetQuickItem(int _slot)
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
    ITEM_MANAGER->SetItemImage(quickSlots->Find("slot" + to_string(_slot)), _item);
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
        slots[_slot].Remove();
    }
    else {
        quickSlots->Find("slot" + to_string(_slot))->visible = true;
        ITEM_MANAGER->SetItemImage(quickSlots->Find("slot" + to_string(_slot)), slots[_slot]);
        dynamic_cast<Text*>(quickSlots->Find("slot" + to_string(_slot) + "_ea"))->ChangeText(to_string(slots[_slot].ea));

        invens->Find("qItemImg" + to_string(_slot))->visible = true;
        ITEM_MANAGER->SetItemImage(invens->Find("qItemImg" + to_string(_slot)), slots[_slot]);
        dynamic_cast<Text*>(invens->Find("qItemEa" + to_string(_slot)))->ChangeText(to_string(slots[_slot].ea));
    }
}

void Inventory::UpdateQuickSlot(int _slot, UI* _ui)
{
    if (slots[_slot].ea <= 0) {
        quickSlots->Find("slot" + to_string(_slot))->visible = false;
        _ui->Find("qItemImg" + to_string(_slot))->visible = false;
        slots[_slot].Remove();
    }
    else {
        quickSlots->Find("slot" + to_string(_slot))->visible = true;
        ITEM_MANAGER->SetItemImage(quickSlots->Find("slot" + to_string(_slot)), slots[_slot]);
        dynamic_cast<Text*>(quickSlots->Find("slot" + to_string(_slot) + "_ea"))->ChangeText(to_string(slots[_slot].ea));

        _ui->Find("qItemImg" + to_string(_slot))->visible = true;
        ITEM_MANAGER->SetItemImage(_ui->Find("qItemImg" + to_string(_slot)), slots[_slot]);
        dynamic_cast<Text*>(_ui->Find("qItemEa" + to_string(_slot)))->ChangeText(to_string(slots[_slot].ea));
    }
    quickSlots->Update();
}

void Inventory::UpdateCombineSlot(int _slotX, int _slotY)
{
    if (combineSlot[_slotX][_slotY].ea <= 0) {
        invens->Find("cItemImg" + to_string((2 * _slotX) + _slotY))->visible = false;
        combineSlot[_slotX][_slotY].Remove();
    }
    else {
        invens->Find("cItemImg" + to_string((2 * _slotX) + _slotY))->visible = true;
        ITEM_MANAGER->SetItemImage(invens->Find("cItemImg" + to_string((2 * _slotX) + _slotY)), combineSlot[_slotX][_slotY]);
        dynamic_cast<Text*>(invens->Find("cItemEa" + to_string((2 * _slotX) + _slotY)))->ChangeText(to_string(combineSlot[_slotX][_slotY].ea));
    }
    outcomeSlot = CRAFTING->GetCraftItem2x2(combineSlot);
    UpdateOutcomeSlot();
}

void Inventory::UpdateEquipSlot(int _slot)
{
    if (equipSlot[_slot].ea <= 0) {
        invens->Find("eItemImg" + to_string(_slot))->visible = false;
        equipSlot[_slot].Remove();
    }
    else {
        invens->Find("eItemImg" + to_string(_slot))->visible = true;
        ITEM_MANAGER->SetItemImage(invens->Find("eItemImg" + to_string(_slot)), equipSlot[_slot]);
        //dynamic_cast<Text*>(invens->Find("eItemEa" + to_string(_slot)))->ChangeText(to_string(equipSlot[_slot].ea));
    }
}

void Inventory::UpdateOutcomeSlot()
{
    if (outcomeSlot.ea <= 0) {
        invens->Find("oItemImg")->visible = false;
        outcomeSlot.Remove();
    }
    else {
        invens->Find("oItemImg")->visible = true;
        ITEM_MANAGER->SetItemImage(invens->Find("oItemImg"), outcomeSlot);
        dynamic_cast<Text*>(invens->Find("oItemEa"))->ChangeText(to_string(outcomeSlot.ea));
    }
}
