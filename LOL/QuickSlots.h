#pragma once

class QuickSlots : public UI
{
private:
	int pickedSlot;
	Item slots[10];
public:
	void Init();
	void Update();

	int GetPickedSlot();
	Item& GetPickedItem();
	Item& GetSlotItem(int _slot);
	Item SetPickedItem(int _slot, Item _item);
	void UsePickedItem();
	void UpdateEa(int _slot);
};

