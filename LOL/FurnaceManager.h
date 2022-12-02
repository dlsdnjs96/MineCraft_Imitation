#pragma once
class FurnaceManager : public Singleton<FurnaceManager>
{
private:
	UI*				ui;
	UI*				mouse;
	Furnace*		target;
	float			fire_time;
	float			progress_time;
	Item			mousePick;
	bool			active;


public:
	map<int, map<int, map<int, Furnace*>>> furnaces;

	void	Init();
	void	Update();
	void	Render();
	void	RenderHierarchy();
	void	Release();

	void	OnFurnace(Int3 _pos);
	void	AddFurnace(Int3 _pos, Furnace* _furnace);
	void	RemoveFurnace(Int3 _pos);
	void	SetFurnace(Int3 _pos);
	void	SetFire(int _fire);
	void	SetProgress(int _progress);
	bool	IsFuel(int _itemid);
	int 	IsBurnable(int _itemid);
	
	void	UpdateMouse();
	void	UpdateInputSlot();
	void	UpdateOutputSlot();
	void	UpdateFuelSlot();
};

