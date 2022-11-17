#include "stdafx.h"

Crafting::Crafting()
{
	Init();
}

void Crafting::LoadData()
{
	list1x1.push_back(Craft1x1{ int(BlockType::OAK_WOOD), Item{ int(BlockType::OAK_WOOD_PLANK), 4 } });
	list1x1.push_back(Craft1x1{ int(BlockType::SPRUCE_WOOD), Item{ int(BlockType::SPRUCE_WOOD_PLANK), 4 } });
	list1x1.push_back(Craft1x1{ int(BlockType::BIRCH_WOOD), Item{ int(BlockType::BIRCH_WOOD_PLANK), 4 } });
	list1x1.push_back(Craft1x1{ int(BlockType::JUNGLE_WOOD), Item{ int(BlockType::JUNGLE_WOOD_PLANK), 4 } });

	list2x2.push_back(Craft2x2{ { 
		{ int(BlockType::OAK_WOOD_PLANK), 0 }, 
		{ int(BlockType::OAK_WOOD_PLANK), 0 } 
		}, Item{ 280, 4 } });

	list3x3.push_back(Craft3x3{ { 
		{ int(BlockType::STONE), int(BlockType::STONE), int(BlockType::STONE) },
		{ 0, 280, 0 },
		{ 0, 280, 0 }
		}, Item{ 273, 1 } });
}

Item Crafting::GetCraftItem2x2(Item _table[][2])
{
	for (auto& it : list1x1)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (it.table[0][0] == _table[i][j].itemid && CheckEmptySlot2x2(_table, i, j, 1))
					return it.output;
			}
		}
	}
	for (auto& it : list2x2)
	{
		bool chk = true;
		for (int x = 0; x < 2; x++)
		{
			for (int y = 0; y < 2; y++)
			{
				if (it.table[x][y] != _table[x][y].itemid)
					chk = false;
			}
		}
		if (chk)
			return it.output;
	}
}

Item Crafting::GetCraftItem3x3(Item _table[][3])
{
	for (auto& it : list1x1)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (it.table[0][0] == _table[i][j].itemid)
					return it.output;
			}
		}
	}
	for (auto& it : list2x2)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				bool chk = true;
				for (int x = 0; x < 2; x++)
				{
					for (int y = 0; y < 2; y++)
					{
						if (it.table[x][y] != _table[i + x][j + y].itemid)
							chk = false;
					}
				}
				if (chk)
					return it.output;
			}
		}
	}
	for (auto& it : list3x3)
	{
		bool chk = true;
		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				if (it.table[x][y] != _table[x][y].itemid)
					chk = false;
			}
		}
		if (chk)
			return it.output;
	}
}

void Crafting::MakeCraftItem2x2(Item _table[][2], Item& _outcome)
{
	for (auto& it : list1x1)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (it.table[0][0] == _table[i][j].itemid && CheckEmptySlot2x2(_table, i, j, 1))
				{
					_table[i][j].ea--;
					return;
				}
			}
		}
	}
	for (auto& it : list2x2)
	{
		bool chk = true;
		for (int x = 0; x < 2; x++)
		{
			for (int y = 0; y < 2; y++)
			{
				if (it.table[x][y] != _table[x][y].itemid)
					chk = false;
			}
		}
		if (chk) {
			for (int x = 0; x < 2; x++)
			{
				for (int y = 0; y < 2; y++)
					_table[x][y].ea--;
			}
			return;
		}
	}
}

void Crafting::MakeCraftItem3x3(Item _table[][3], Item& _outcome)
{
	for (auto& it : list1x1)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (it.table[0][0] == _table[i][j].itemid) {
					_table[i][j].ea--;
					return;
				}
			}
		}
	}
	for (auto& it : list2x2)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				bool chk = true;
				for (int x = 0; x < 2; x++)
				{
					for (int y = 0; y < 2; y++)
					{
						if (it.table[x][y] != _table[i + x][j + y].itemid)
							chk = false;
					}
				}
				if (chk) {
					for (int x = 0; x < 2; x++)
					{
						for (int y = 0; y < 2; y++)
							_table[i + x][j + y].ea--;
					}
					return;
				}
			}
		}
	}
	for (auto& it : list3x3)
	{
		bool chk = true;
		for (int x = 0; x < 3; x++)
		{
			for (int y = 0; y < 3; y++)
			{
				if (it.table[x][y] != _table[x][y].itemid)
					chk = false;
			}
		}
		if (chk) {
			for (int x = 0; x < 3; x++)
			{
				for (int y = 0; y < 3; y++)
					_table[x][y].ea--;
			}
			return;
		}
	}
}

bool Crafting::CheckEmptySlot2x2(Item _table[][2], int _x, int _y, int _size)
{
	switch (_size) {
	case 1:
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				if (i != _x || j != _y)
				{
					if (_table[i][j].itemid != 0)
						return false;
				}
			}
		}
		return true;
	case 2:
		return true;
	}
	return false;
}

bool Crafting::CheckEmptySlot3x3(Item _table[][3], int _x, int _y, int _size)
{
	switch (_size) {
	case 1:
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (i != _x || j != _y)
				{
					if (_table[i][j].itemid != 0)
						return false;
				}
			}
		}
		return true;
	case 2:
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if ((i > _x + 1 && i < _x) || (j > _y + 1 && j < _y))
				{
					if (_table[i][j].itemid != 0)
						return false;
				}
			}
		}
		return true;
	case 3:
		return true;
	}
	return false;
}

void Crafting::UpdateCombineSlot(int _slotX, int _slotY)
{
	if (combineSlot[_slotX][_slotY].ea <= 0) {
		table->Find("cItemImg" + to_string((3 * _slotX) + _slotY))->visible = false;
		combineSlot[_slotX][_slotY].Remove();
	}
	else {
		table->Find("cItemImg" + to_string((3 * _slotX) + _slotY))->visible = true;
		ITEM_MANAGER->SetItemImage(table->Find("cItemImg" + to_string((3 * _slotX) + _slotY)), combineSlot[_slotX][_slotY]);
		dynamic_cast<Text*>(table->Find("cItemEa" + to_string((3 * _slotX) + _slotY)))->ChangeText(to_string(combineSlot[_slotX][_slotY].ea));
	}
	outcomeSlot = GetCraftItem3x3(combineSlot);
	UpdateOutcomeSlot();
}

void Crafting::UpdateOutcomeSlot()
{
	if (outcomeSlot.ea <= 0) {
		table->Find("oItemImg")->visible = false;
		outcomeSlot.Remove();
	}
	else {
		table->Find("oItemImg")->visible = true;
		ITEM_MANAGER->SetItemImage(table->Find("oItemImg"), outcomeSlot);
		dynamic_cast<Text*>(table->Find("oItemEa"))->ChangeText(to_string(outcomeSlot.ea));
	}
}

Item Crafting::GetOutput(Item _table[][2], int _size)
{
	for (auto& it : list1x1)
	{
		for (int i = 0; i < _size; i++)
		{
			for (int j = 0; j < _size; j++)
			{
				if (it.table[0][0] == _table[i][j].itemid)
					return it.output;
			}
		}
	}
	for (auto& it : list2x2)
	{
		for (int i = 0; i < _size - 1; i++)
		{
			for (int j = 0; j < _size - 1; j++)
			{
				bool chk = true;
				for (int x = 0; x < 2; x++)
				{
					for (int y = 0; y < 2; y++)
					{
						if (it.table[x][y] != _table[i + x][j + y].itemid)
							chk = false;
					}
				}
				if (chk)
					return it.output;
			}
		}
	}
	for (auto& it : list3x3)
	{
		for (int i = 0; i < _size - 2; i++)
		{
			for (int j = 0; j < _size - 2; j++)
			{
				bool chk = true;
				for (int x = 0; x < 3; x++)
				{
					for (int y = 0; y < 3; y++)
					{
						if (it.table[x][y] != _table[i + x][j + y].itemid)
							chk = false;
					}
				}
				if (chk)
					return it.output;
			}
		}
	}
	return Item{0,0};
}

void Crafting::CraftItem(Item _table[][2], int _size, Item& _outcome)
{
	for (auto& it : list1x1)
	{
		for (int i = 0; i < _size; i++)
		{
			for (int j = 0; j < _size; j++)
			{
				if (it.table[0][0] == _table[i][j].itemid) {
					_table[i][j].ea--;
					_outcome = it.output;
					return;
				}
			}
		}
	}
	for (auto& it : list2x2)
	{
		for (int i = 0; i < _size - 1; i++)
		{
			for (int j = 0; j < _size - 1; j++)
			{
				bool chk = true;
				for (int x = 0; x < 2; x++)
				{
					for (int y = 0; y < 2; y++)
					{
						if (it.table[x][y] != _table[i + x][j + y].itemid)
							chk = false;
					}
				}
				if (chk)
				{
					for (int x = 0; x < 2; x++)
					{
						for (int y = 0; y < 2; y++)
							_table[i + x][j + y].ea--;
					}
					return;
				}
			}
		}
	}
	return;
}

void Crafting::UpdateMouse()
{
	if (mousePick.ea <= 0) {
		mouse->visible = false;
		mousePick.Remove();
	}
	else {
		mouse->visible = true;
		ITEM_MANAGER->SetItemImage(mouse, mousePick);
		dynamic_cast<Text*>(mouse->Find("ea"))->ChangeText(to_string(mousePick.ea));
	}
}

void Crafting::Init()
{
	table = UI::Create("Table");
	table->LoadFile("Ingame/Table.xml");

	mouse = UI::Create("MousePick");
	mouse->LoadFile("Ingame/MousePick.xml");

	LoadData();
	active = false;

	table->Update();
	for (int i = 0; i < 27; i++) {
		UI* temp = UI::Create("slot" + to_string(i));
		temp->material = RESOURCE->materials.Load("mouseOverSlot.mtl");
		temp->scale = { 0.1f, 0.1f, 1.f };
		float _x = (-0.37f + float((i % 9) * 0.0925f)) / 0.8999f;
		float _y = (-0.082f - float((i / 9) * 0.175f)) / 1.6f;
		temp->SetLocalPos({ _x, _y, -0.00f });
		table->AddChild(temp);

		UI* temp2 = UI::Create("itemImg" + to_string(i));
		temp2->material = RESOURCE->materials.Load("Items/100.mtl");
		temp2->scale = { 0.9f, 0.9f, 1.f };
		temp2->SetLocalPos({ 0, 0, -0.1f });
		temp->AddChild(temp2);

		Text* temp3 = Text::Create("itemEa" + to_string(i));
		temp3->scale = { 3.0f, 3.0f, 1.f };
		temp3->fromLeft = false;
		temp3->SetLocalPos({ 0.4f / 0.81f, -0.2f / 1.44f, -0.00f });
		temp3->ChangeText("10");
		temp2->AddChild(temp3);
	}
	for (int i = 0; i < 9; i++) {
		UI* temp = UI::Create("qSlot" + to_string(i + 1));
		temp->material = RESOURCE->materials.Load("mouseOverSlot.mtl");
		temp->scale = { 0.1f, 0.1f, 1.f };
		float _x = (-0.37f + float((i % 9) * 0.0925f)) / 0.8999f;
		float _y = (-0.645) / 1.6f;
		temp->SetLocalPos({ _x, _y, -0.05f });
		table->AddChild(temp);

		UI* temp2 = UI::Create("qItemImg" + to_string(i + 1));
		temp2->material = RESOURCE->materials.Load("Items/100.mtl");
		temp2->scale = { 0.9f, 0.9f, 1.f };
		temp2->SetLocalPos({ 0, 0, -0.1f });
		temp->AddChild(temp2);

		Text* temp3 = Text::Create("qItemEa" + to_string(i + 1));
		temp3->scale = { 3.0f, 3.0f, 1.f };
		temp3->fromLeft = false;
		temp3->SetLocalPos({ 0.4f / 0.81f, -0.2f / 1.44f, -0.00f });
		temp3->ChangeText("10");
		temp2->AddChild(temp3);
	}
	for (int i = 0; i < 9; i++) {
		UI* temp = UI::Create("cSlot" + to_string(i));
		temp->material = RESOURCE->materials.Load("mouseOverSlot.mtl");
		temp->scale = { 0.1f, 0.1f, 1.f };
		float _x = (-0.255f + float((i % 3) * 0.0925f)) / 0.8999f;
		float _y = (0.56f - float((i / 3) * 0.175f)) / 1.6f;
		temp->SetLocalPos({ _x, _y, -0.05f });
		table->AddChild(temp);

		UI* temp2 = UI::Create("cItemImg" + to_string(i));
		temp2->material = RESOURCE->materials.Load("Items/100.mtl");
		temp2->scale = { 0.9f, 0.9f, 1.f };
		temp2->SetLocalPos({ 0, 0, -0.1f });
		temp->AddChild(temp2);

		Text* temp3 = Text::Create("cItemEa" + to_string(i));
		temp3->scale = { 3.0f, 3.0f, 1.f };
		temp3->fromLeft = false;
		temp3->SetLocalPos({ 0.4f / 0.81f, -0.2f / 1.44f, -0.00f });
		temp3->ChangeText("10");
		temp2->AddChild(temp3);
	}
	UI* temp = UI::Create("outcome");
	temp->material = RESOURCE->materials.Load("mouseOverSlot.mtl");
	temp->scale = { 0.1f, 0.1f, 1.f };
	float _x = (0.225f) / 0.8999f;
	float _y = (0.380f) / 1.6f;
	temp->SetLocalPos({ _x, _y, -0.05f });
	table->AddChild(temp);

	UI* temp2 = UI::Create("oItemImg");
	temp2->material = RESOURCE->materials.Load("Items/100.mtl");
	temp2->scale = { 0.9f, 0.9f, 1.f };
	temp2->SetLocalPos({ 0, 0, -0.1f });
	temp->AddChild(temp2);

	Text* temp3 = Text::Create("oItemEa");
	temp3->scale = { 3.0f, 3.0f, 1.f };
	temp3->fromLeft = false;
	temp3->SetLocalPos({ 0.4f / 0.81f, -0.2f / 1.44f, -0.00f });
	temp3->ChangeText("10");
	temp2->AddChild(temp3);



	for (int i = 0; i < 27; i++) {
		dynamic_cast<UI*>(table->Find("slot" + to_string(i)))->mouseOver = [=]() { table->Find("slot" + to_string(i))->SetLocalPosZ(-0.05f); };
		dynamic_cast<UI*>(table->Find("slot" + to_string(i)))->mouseNotOver = [=]() { table->Find("slot" + to_string(i))->SetLocalPosZ(0.05f); };
		dynamic_cast<UI*>(table->Find("slot" + to_string(i)))->mouseDown = [=]() {
			if (INVENTORY->GetInvenItem(i).itemid == mousePick.itemid)
			{
				INVENTORY->GetInvenItem(i).ea += mousePick.ea;
				mousePick.Remove();
			}
			else
				Util::Swap(INVENTORY->GetInvenItem(i), mousePick);
			INVENTORY->UpdateInven(i, table);
			UpdateMouse(); };

		dynamic_cast<UI*>(table->Find("slot" + to_string(i)))->mouseDownR = [=]() {
			if (INVENTORY->GetInvenItem(i).itemid == 0 and mousePick.itemid != 0)
			{
				INVENTORY->GetInvenItem(i).itemid = mousePick.itemid;
				INVENTORY->GetInvenItem(i).ea++;
				mousePick.ea--;
			}
			else if (mousePick.itemid == 0 and INVENTORY->GetInvenItem(i).itemid != 0)
			{
				mousePick.itemid = INVENTORY->GetInvenItem(i).itemid;
				mousePick.ea = int(INVENTORY->GetInvenItem(i).ea / 2);
				INVENTORY->GetInvenItem(i).ea -= mousePick.ea;
			}
			else if (INVENTORY->GetInvenItem(i).itemid == mousePick.itemid and mousePick.itemid != 0)
			{
				INVENTORY->GetInvenItem(i).ea++;
				mousePick.ea--;
			}
			else
				Util::Swap(INVENTORY->GetInvenItem(i), mousePick);
			INVENTORY->UpdateInven(i, table);
			UpdateMouse(); };
	}
	for (int i = 1; i <= 9; i++) {
		dynamic_cast<UI*>(table->Find("qSlot" + to_string(i)))->mouseOver = [=]() { table->Find("qSlot" + to_string(i))->SetLocalPosZ(-0.05f); };
		dynamic_cast<UI*>(table->Find("qSlot" + to_string(i)))->mouseNotOver = [=]() { table->Find("qSlot" + to_string(i))->SetLocalPosZ(0.f); };
		dynamic_cast<UI*>(table->Find("qSlot" + to_string(i)))->mouseDown = [=]() {
			if (INVENTORY->GetQuickItem(i).itemid == mousePick.itemid)
			{
				INVENTORY->GetQuickItem(i).ea += mousePick.ea;
				mousePick.Remove();
			}
			else
				Util::Swap(INVENTORY->GetQuickItem(i), mousePick);
			INVENTORY->UpdateQuickSlot(i, table);
			UpdateMouse(); };

		dynamic_cast<UI*>(table->Find("qSlot" + to_string(i)))->mouseDownR = [=]() {
			if (INVENTORY->GetQuickItem(i).itemid == 0 and mousePick.itemid != 0)
			{
				INVENTORY->GetQuickItem(i).itemid = mousePick.itemid;
				INVENTORY->GetQuickItem(i).ea++;
				mousePick.ea--;
			}
			else if (mousePick.itemid == 0 and INVENTORY->GetQuickItem(i).itemid != 0)
			{
				mousePick.itemid = INVENTORY->GetQuickItem(i).itemid;
				mousePick.ea = int(INVENTORY->GetQuickItem(i).ea / 2);
				INVENTORY->GetQuickItem(i).ea -= mousePick.ea;
			}
			else if (INVENTORY->GetQuickItem(i).itemid == mousePick.itemid and mousePick.itemid != 0)
			{
				INVENTORY->GetQuickItem(i).ea++;
				mousePick.ea--;
			}
			else
				Util::Swap(INVENTORY->GetQuickItem(i), mousePick);
			INVENTORY->UpdateQuickSlot(i, table);
			UpdateMouse(); };
	}
	for (int i = 0; i < 9; i++) {
		dynamic_cast<UI*>(table->Find("cSlot" + to_string(i)))->mouseOver = [=]() { table->Find("cSlot" + to_string(i))->SetLocalPosZ(-0.05f); };
		dynamic_cast<UI*>(table->Find("cSlot" + to_string(i)))->mouseNotOver = [=]() { table->Find("cSlot" + to_string(i))->SetLocalPosZ(0.f); };
		dynamic_cast<UI*>(table->Find("cSlot" + to_string(i)))->mouseDown = [=]() {
			if (combineSlot[i / 3][i % 3].itemid == mousePick.itemid)
			{
				combineSlot[i / 3][i % 3].ea += mousePick.ea;
				mousePick.Remove();
			}
			else
				Util::Swap(combineSlot[i / 3][i % 3], mousePick);
			outcomeSlot = GetCraftItem3x3(combineSlot);
			UpdateCombineSlot(i / 3, i % 3);
			UpdateOutcomeSlot();
			UpdateMouse(); };

		dynamic_cast<UI*>(table->Find("cSlot" + to_string(i)))->mouseDownR = [=]() {
			if (combineSlot[i / 3][i % 3].itemid == 0 and mousePick.itemid != 0)
			{
				combineSlot[i / 3][i % 3].itemid = mousePick.itemid;
				combineSlot[i / 3][i % 3].ea++;
				mousePick.ea--;
			}
			else if (mousePick.itemid == 0 and combineSlot[i / 3][i % 3].itemid != 0)
			{
				mousePick.itemid = combineSlot[i / 3][i % 3].itemid;
				mousePick.ea = int(combineSlot[i / 3][i % 3].ea / 2);
				combineSlot[i / 3][i % 3].ea -= mousePick.ea;
			}
			else if (combineSlot[i / 3][i % 3].itemid == mousePick.itemid and mousePick.itemid != 0)
			{
				combineSlot[i / 3][i % 3].ea++;
				mousePick.ea--;
			}
			else
				Util::Swap(combineSlot[i / 3][i % 3], mousePick);
			outcomeSlot = GetCraftItem3x3(combineSlot);
			UpdateCombineSlot(i / 3, i % 3);
			UpdateOutcomeSlot();
			UpdateMouse(); };
	}
	dynamic_cast<UI*>(table->Find("outcome"))->mouseOver = [=]() { table->Find("outcome")->SetLocalPosZ(-0.05f); };
	dynamic_cast<UI*>(table->Find("outcome"))->mouseNotOver = [=]() { table->Find("outcome")->SetLocalPosZ(0.f); };
	dynamic_cast<UI*>(table->Find("outcome"))->mouseDown = [=]() {
		if (outcomeSlot.itemid != 0 && mousePick.itemid == 0) {
			MakeCraftItem3x3(combineSlot, outcomeSlot);
			Util::Swap(outcomeSlot, mousePick);
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
					UpdateCombineSlot(j, i);
			}
			UpdateOutcomeSlot();
			UpdateMouse();
		}
		else if (outcomeSlot.itemid == mousePick.itemid && mousePick.itemid != 0)
		{
			MakeCraftItem3x3(combineSlot, outcomeSlot);
			mousePick.ea += outcomeSlot.ea;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
					UpdateCombineSlot(j, i);
			}
			UpdateOutcomeSlot();
			UpdateMouse();
		}
	};
}

void Crafting::Update()
{
	if (not active)
		return;

	table->Update();

	if (mousePick.itemid != 0)
	{
		mouse->SetLocalPos({ INPUT->NDCPosition.x, INPUT->NDCPosition.y, mouse->GetLocalPos().z });
		mouse->Update();
	}

	if (INPUT->KeyDown(VK_LBUTTON) && not table->MouseOver() && mousePick.itemid != 0)
	{
		ITEM_MANAGER->Spawn(ITEM_MANAGER->user->GetWorldPos(), mousePick);
		mousePick.Remove();
		UpdateMouse();
	}
}

void Crafting::Render()
{
	if (not active)
		return;

	table->Render();
	mouse->Render();
}

void Crafting::RenderHierarchy()
{
	table->RenderHierarchy();
}

void Crafting::Release()
{
}
