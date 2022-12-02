#include "stdafx.h"

Furnace::Furnace()
{
	fire_time = 0.f;
	progress_time = 0.f;
	fuelSlot.Remove();
	inputSlot.Remove(); 
	outputSlot.Remove();
}

void Furnace::Update()
{
	if (FURNACE_MANAGER->IsBurnable(inputSlot.itemid) && fire_time <= 0.f && FURNACE_MANAGER->IsFuel(fuelSlot.itemid))
	{
		fire_time += 8.f;
		fuelSlot.ea--;
		if (fuelSlot.ea <= 0)
			fuelSlot.Remove();
		FURNACE_MANAGER->UpdateFuelSlot();

		onFire = true;
		changed = true;
	}

	if (FURNACE_MANAGER->IsBurnable(inputSlot.itemid) && fire_time > 0.f)
	{
		fire_time -= DELTA;
		progress_time += DELTA;

		if (progress_time > 5.f)
		{
			outputSlot.itemid = FURNACE_MANAGER->IsBurnable(inputSlot.itemid);
			outputSlot.ea++;
			inputSlot.ea--;
			if (inputSlot.ea <= 0)
				inputSlot.Remove();
			progress_time -= 5.f;
			FURNACE_MANAGER->UpdateInputSlot();
			FURNACE_MANAGER->UpdateOutputSlot();
		}
	}
	if (onFire && fire_time <= 0.f)
	{
		onFire = false;
		changed = true;
	}
}
