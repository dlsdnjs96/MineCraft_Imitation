#pragma once

class Inventory
{
private:
	Item	invenSlots[27];

	int		pickedSlot;
	Item	slots[10];
	Item	mousePick;


	UI*		quickSlots;
	UI*		invens;
	UI*		mouse;
public:
	bool	showInven;
	void	Init();
	void	Update();
	void	RenderHierarchy();
	void	Render();

	void	ShowInven(bool _on);
	Item&	GetInvenItem(int _slot);
	void	SetInvenItem(int _slot, Item _item);
	void	GainItem(Item _item);
	void	LossItem(Item _item);
	void	UpdateInven(int _slot);
	void	UpdateMouse();


	int GetPickedSlot();
	Item& GetPickedItem();
	Item& GetSlotItem(int _slot);
	Item SetPickedItem(int _slot, Item _item);
	void UsePickedItem();
	void UpdateQuickSlot(int _slot);
};

