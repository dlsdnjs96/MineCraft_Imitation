#pragma once

class Inventory : public Singleton<Inventory>
{
private:
	Item	invenSlots[27];

	int		pickedSlot;
	Item	slots[10];
	Item	combineSlot[2][2];
	Item	equipSlot[4];
	Item	outcomeSlot;


	UI*		quickSlots;
	UI*		invens;
	UI*		mouse;
public:
	Inventory();
	Item	mousePick;
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
	void	UpdateInven(int _slot, UI* _ui);
	void	UpdateMouse();


	int GetPickedSlot();
	Item& GetPickedItem();
	Item& GetQuickItem(int _slot);
	Item SetPickedItem(int _slot, Item _item);
	void UsePickedItem();
	void UpdateQuickSlot(int _slot);
	void UpdateQuickSlot(int _slot, UI* _ui);

	void UpdateCombineSlot(int _slotX, int _slotY);

	void UpdateEquipSlot(int _slot);

	void UpdateOutcomeSlot();
};

