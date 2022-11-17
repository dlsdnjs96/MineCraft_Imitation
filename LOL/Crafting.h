#pragma once

struct Craft1x1
{
	int table[1][1];
	Item output;
};
struct Craft2x2
{
	int table[2][2];
	Item output;
};
struct Craft3x3
{
	int table[3][3];
	Item output;
};

class Crafting : public Singleton<Crafting>
{
private:
	vector<Craft1x1> list1x1;
	vector<Craft2x2> list2x2;
	vector<Craft3x3> list3x3;

	UI*		table;
	UI*		mouse;
	Item	mousePick;
	Item	outcomeSlot;
	Item	combineSlot[3][3];
public:
	bool	active;
	Crafting();
	void	LoadData();
	Item	GetCraftItem2x2(Item _table[][2]);
	Item	GetCraftItem3x3(Item _table[][3]);
	void	MakeCraftItem2x2(Item _table[][2], Item& _outcome);
	void	MakeCraftItem3x3(Item _table[][3], Item& _outcome);
	bool	CheckEmptySlot2x2(Item _table[][2], int _x, int _y, int _size);
	bool	CheckEmptySlot3x3(Item _table[][3], int _x, int _y, int _size);

	void	UpdateCombineSlot(int _slotX, int _slotY);
	void	UpdateOutcomeSlot();
	Item	GetOutput(Item _table[][2], int _size);
	void	CraftItem(Item _table[][2], int _size, Item& _outcome);
	void	UpdateMouse();

	void	Init();
	void	Update();
	void	Render();
	void	RenderHierarchy();
	void	Release();
};

