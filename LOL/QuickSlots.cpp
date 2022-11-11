#include "stdafx.h"

void QuickSlots::Init()
{
    LoadFile("Ingame/QuickSlots.xml");
    pickedSlot = 1;

    for (int i = 1; i <= 9; i++)
    {
        float width = -0.44f + (0.88f * ((i - 1) / 8.f));
        Find("slot" + to_string(i))->SetLocalPos({ width, 0.005, -0.05f });
        Find("slot" + to_string(i))->scale = { 0.08f, 0.615f, 1.f };
        Find("slot" + to_string(i))->visible = false;
        //Find("slot" + to_string(i))->material = RESOURCE->materials.Load("Items/100.mtl");
        //Find("slot" + to_string(i))->AddChild(Text::Create("slot" + to_string(i) + "_ea"));
        Find("slot" + to_string(i) + "_ea")->SetLocalPos({ -1.f / 100.f, -2.f / 100.f, 0.05f });
        Find("slot" + to_string(i) + "_ea")->scale = { 4.f, 4.f, 1.f };
        Find("slot" + to_string(i) + "_ea")->visible = true;
        //dynamic_cast<Text*>(Find("slot" + to_string(i) + "_ea"))->ChangeText("0");
    }
    SetPickedItem(2, Item{ 102, 10 });
    SetPickedItem(3, Item{ 104, 10 });
}

void QuickSlots::Update()
{
    for (int i = 1; i <= 9; i++)
    {
        if (INPUT->KeyDown('0' + i))
        {
            pickedSlot = i;
            float width = -0.44f + (0.88f * ((i - 1) / 8.f));
            Find("pickedSlot")->SetLocalPosX(width);
        }
    }
            Actor::Update();
}

int QuickSlots::GetPickedSlot()
{
    return pickedSlot;
}

Item& QuickSlots::GetPickedItem()
{
    return slots[pickedSlot];
}

Item& QuickSlots::GetSlotItem(int _slot)
{
    Util::Saturate(_slot, 1, 9);
    return slots[_slot];
}

Item QuickSlots::SetPickedItem(int _slot, Item _item)
{
    Item temp;
    Util::Saturate(_slot, 1, 9);
    temp = slots[_slot];
    slots[_slot] = _item;
    Find("slot" + to_string(_slot))->material = RESOURCE->materials.Load("Items/"+to_string(_item.itemid)+".mtl");
    Find("slot" + to_string(_slot))->visible = true;
    UpdateEa(_slot);

    return temp;
}

void QuickSlots::UsePickedItem()
{
    slots[pickedSlot].ea--;
    if (slots[pickedSlot].ea <= 0)
    {
        Find("slot" + to_string(pickedSlot))->visible = false;
    }
    UpdateEa(pickedSlot);
    return;
}
void QuickSlots::UpdateEa(int _slot)
{
    if (slots[_slot].ea < 10)
    {
        Find("slot" + to_string(_slot) + "_ea")->SetLocalPos({ 0.02f, 0.f, 0.05f });
        dynamic_cast<Text*>(Find("slot" + to_string(_slot) + "_ea"))->ChangeText(to_string(slots[_slot].ea));
    }
    else {
        Find("slot" + to_string(_slot) + "_ea")->SetLocalPos({ 0.0f, 0.f, 0.05f });
        dynamic_cast<Text*>(Find("slot" + to_string(_slot) + "_ea"))->ChangeText(to_string(slots[_slot].ea));
    }
}
