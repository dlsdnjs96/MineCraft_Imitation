#pragma once
class Furnace
{
private:
public:
	Int3	pos;
	float	fire_time;
	float	progress_time;
	Item	fuelSlot, inputSlot, outputSlot;
	bool	onFire, changed;

	Furnace();
	void	Update();
};

