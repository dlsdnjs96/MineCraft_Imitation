#include "stdafx.h"

void FurnaceManager::Init()
{
	ui = UI::Create("Furnace");
	ui->LoadFile("Ingame/Furnace.xml");


	mouse = UI::Create("MousePick");
	mouse->LoadFile("Ingame/MousePick.xml");


	fire_time = 0.f;
	target = new Furnace();

	for (int i = 0; i < 27; i++) {
		UI* temp = UI::Create("slot" + to_string(i));
		temp->material = RESOURCE->materials.Load("mouseOverSlot.mtl");
		temp->scale = { 0.1f, 0.1f, 1.f };
		float _x = (-0.37f + float((i % 9) * 0.0925f)) / 0.8999f;
		float _y = (-0.082f - float((i / 9) * 0.175f)) / 1.6f;
		temp->SetLocalPos({ _x, _y, -0.00f });
		ui->AddChild(temp);

		UI* temp2 = UI::Create("itemImg" + to_string(i));
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
		ui->AddChild(temp);

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
	//{
	//	UI* temp = UI::Create("iSlot");
	//	temp->material = RESOURCE->materials.Load("mouseOverSlot.mtl");
	//	temp->scale = { 0.1f, 0.1f, 1.f };
	//	temp->SetWorldPos({ -0.123f, 0.559f, -0.05f });
	//	ui->AddChild(temp);
	//
	//	UI* temp2 = UI::Create("iItemImg");
	//	temp2->scale = { 0.9f, 0.9f, 1.f };
	//	temp2->SetLocalPos({ 0, 0, -0.1f });
	//	temp->AddChild(temp2);
	//
	//	Text* temp3 = Text::Create("iItemEa");
	//	temp3->scale = { 3.0f, 3.0f, 1.f };
	//	temp3->SetLocalPos({ 0.4f / 0.81f, -0.2f / 1.44f, -0.00f });
	//	temp2->AddChild(temp3);
	//}
	////
	//{
	//	UI* temp = UI::Create("oSlot");
	//	temp->material = RESOURCE->materials.Load("mouseOverSlot.mtl");
	//	temp->scale = { 0.1f, 0.1f, 1.f };
	//	temp->SetWorldPos({ 0.185f, 0.38f, -0.05f });
	//	ui->AddChild(temp);
	//
	//	UI* temp2 = UI::Create("oItemImg");
	//	temp2->scale = { 0.9f, 0.9f, 1.f };
	//	temp2->SetLocalPos({ 0, 0, -0.1f });
	//	temp->AddChild(temp2);
	//
	//	Text* temp3 = Text::Create("oItemEa");
	//	temp3->scale = { 3.0f, 3.0f, 1.f };
	//	temp3->SetLocalPos({ 0.4f / 0.81f, -0.2f / 1.44f, -0.00f });
	//	temp2->AddChild(temp3);
	//}
	////
	//{
	//	UI* temp = UI::Create("fSlot");
	//	temp->material = RESOURCE->materials.Load("mouseOverSlot.mtl");
	//	temp->scale = { 0.1f, 0.1f, 1.f };
	//	temp->SetWorldPos({ -0.123f, 0.21f, -0.05f });
	//	ui->AddChild(temp);
	//
	//	UI* temp2 = UI::Create("fItemImg");
	//	temp2->scale = { 0.9f, 0.9f, 1.f };
	//	temp2->SetLocalPos({ 0, 0, -0.1f });
	//	temp->AddChild(temp2);
	//
	//	Text* temp3 = Text::Create("fItemEa");
	//	temp3->scale = { 3.0f, 3.0f, 1.f };
	//	temp3->SetLocalPos({ 0.4f / 0.81f, -0.2f / 1.44f, -0.00f });
	//	temp2->AddChild(temp3);
	//}

	for (int i = 0; i < 27; i++) {
		dynamic_cast<UI*>(ui->Find("slot" + to_string(i)))->mouseOver = [=]() { ui->Find("slot" + to_string(i))->SetLocalPosZ(-0.05f); };
		dynamic_cast<UI*>(ui->Find("slot" + to_string(i)))->mouseNotOver = [=]() { ui->Find("slot" + to_string(i))->SetLocalPosZ(0.05f); };
		dynamic_cast<UI*>(ui->Find("slot" + to_string(i)))->mouseDown = [=]() {
			if (INVENTORY->GetInvenItem(i).itemid == mousePick.itemid)
			{
				INVENTORY->GetInvenItem(i).ea += mousePick.ea;
				mousePick.Remove();
			}
			else
				Util::Swap(INVENTORY->GetInvenItem(i), mousePick);
			INVENTORY->UpdateInven(i, ui);
			UpdateMouse(); };

		dynamic_cast<UI*>(ui->Find("slot" + to_string(i)))->mouseDownR = [=]() {
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
			INVENTORY->UpdateInven(i, ui);
			UpdateMouse(); };
	}
	for (int i = 1; i <= 9; i++) {
		dynamic_cast<UI*>(ui->Find("qSlot" + to_string(i)))->mouseOver = [=]() { ui->Find("qSlot" + to_string(i))->SetLocalPosZ(-0.05f); };
		dynamic_cast<UI*>(ui->Find("qSlot" + to_string(i)))->mouseNotOver = [=]() { ui->Find("qSlot" + to_string(i))->SetLocalPosZ(0.f); };
		dynamic_cast<UI*>(ui->Find("qSlot" + to_string(i)))->mouseDown = [=]() {
			if (INVENTORY->GetQuickItem(i).itemid == mousePick.itemid)
			{
				INVENTORY->GetQuickItem(i).ea += mousePick.ea;
				mousePick.Remove();
			}
			else
				Util::Swap(INVENTORY->GetQuickItem(i), mousePick);
			INVENTORY->UpdateQuickSlot(i, ui);
			UpdateMouse(); };

		dynamic_cast<UI*>(ui->Find("qSlot" + to_string(i)))->mouseDownR = [=]() {
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
			INVENTORY->UpdateQuickSlot(i, ui);
			UpdateMouse(); };
	}
	dynamic_cast<UI*>(ui->Find("iSlot"))->mouseOver = [=]() { ui->Find("iSlot")->SetLocalPosZ(-0.05f); };
	dynamic_cast<UI*>(ui->Find("iSlot"))->mouseNotOver = [=]() { ui->Find("iSlot")->SetLocalPosZ(0.f); };
	dynamic_cast<UI*>(ui->Find("iSlot"))->mouseDown = [=]() {
		if (target->inputSlot.itemid == mousePick.itemid)
		{
			target->inputSlot.ea += mousePick.ea;
			mousePick.Remove();
		}
		else
			Util::Swap(target->inputSlot, mousePick);
		UpdateInputSlot();
		UpdateMouse(); };
	dynamic_cast<UI*>(ui->Find("iSlot"))->mouseDownR = [=]() {
		if (target->inputSlot.itemid == 0 and mousePick.itemid != 0)
		{
			target->inputSlot.itemid = mousePick.itemid;
			target->inputSlot.ea++;
			mousePick.ea--;
		}
		else if (mousePick.itemid == 0 and target->inputSlot.itemid != 0)
		{
			mousePick.itemid = target->inputSlot.itemid;
			mousePick.ea = int(target->inputSlot.ea / 2);
			target->inputSlot.ea -= mousePick.ea;
		}
		else if (target->inputSlot.itemid == mousePick.itemid and mousePick.itemid != 0)
		{
			target->inputSlot.ea++;
			mousePick.ea--;
		}
		else
			Util::Swap(target->inputSlot, mousePick);
		UpdateInputSlot();
		UpdateMouse(); };
	dynamic_cast<UI*>(ui->Find("fSlot"))->mouseOver = [=]() { ui->Find("fSlot")->SetLocalPosZ(-0.05f); };
	dynamic_cast<UI*>(ui->Find("fSlot"))->mouseNotOver = [=]() { ui->Find("fSlot")->SetLocalPosZ(0.f); };
	dynamic_cast<UI*>(ui->Find("fSlot"))->mouseDown = [=]() {
		if (target->fuelSlot.itemid == mousePick.itemid)
		{
			target->fuelSlot.ea += mousePick.ea;
			mousePick.Remove();
		}
		else
			Util::Swap(target->fuelSlot, mousePick);
		UpdateFuelSlot();
		UpdateMouse(); };
	dynamic_cast<UI*>(ui->Find("fSlot"))->mouseDownR = [=]() {
		if (target->fuelSlot.itemid == 0 and mousePick.itemid != 0)
		{
			target->fuelSlot.itemid = mousePick.itemid;
			target->fuelSlot.ea++;
			mousePick.ea--;
		}
		else if (mousePick.itemid == 0 and target->fuelSlot.itemid != 0)
		{
			mousePick.itemid = target->fuelSlot.itemid;
			mousePick.ea = int(target->fuelSlot.ea / 2);
			target->fuelSlot.ea -= mousePick.ea;
		}
		else if (target->fuelSlot.itemid == mousePick.itemid and mousePick.itemid != 0)
		{
			target->fuelSlot.ea++;
			mousePick.ea--;
		}
		else
			Util::Swap(target->fuelSlot, mousePick);
		UpdateFuelSlot();
		UpdateMouse(); };
	dynamic_cast<UI*>(ui->Find("oSlot"))->mouseOver = [=]() { ui->Find("oSlot")->SetLocalPosZ(-0.05f); };
	dynamic_cast<UI*>(ui->Find("oSlot"))->mouseNotOver = [=]() { ui->Find("oSlot")->SetLocalPosZ(0.f); };
	dynamic_cast<UI*>(ui->Find("oSlot"))->mouseDown = [=]() {
		if (mousePick.itemid == 0)
		{
			mousePick = target->outputSlot;
			target->outputSlot.Remove();
		}
		//else
		//	Util::Swap(target->outputSlot, mousePick);
		UpdateOutputSlot();
		UpdateMouse(); };

	ui->Update();


	for (int i = 0; i < 27; i++)
		INVENTORY->UpdateInven(i, ui);
	for (int i = 1; i <= 9; i++)
		INVENTORY->UpdateQuickSlot(i, ui);
	UpdateInputSlot();
	UpdateOutputSlot();
	UpdateFuelSlot();
	active = false;
}

void FurnaceManager::Update()
{
	for (auto it : furnaces)
	{
		for (auto it2 : it.second)
		{
			for (auto it3 : it2.second) {
				it3.second->Update();
				if (it3.second->changed)
				{
					it3.second->changed = false;
					if (it3.second->onFire)
						WORLD->SetBlockType(Int3{ it.first, it2.first, it3.first }, BlockType::BURNING_FURNACE);
					else
						WORLD->SetBlockType(Int3{ it.first, it2.first, it3.first }, BlockType::FURNACE);
					WORLD->UpdateMesh(Int3{ it.first, it2.first, it3.first });
				}
			}
		}
	}

	if (not active || not target)
		return;
	if (INPUT->KeyDown(VK_ESCAPE))
		active = false;


	if (mousePick.itemid != 0)
	{
		mouse->SetLocalPos({ INPUT->NDCPosition.x, INPUT->NDCPosition.y, mouse->GetLocalPos().z });
		mouse->Update();
	}


	fire_time = 6.f - fmod(target->fire_time, 6.f);
	SetFire(int(fire_time / 1.f));
	progress_time = 5.f - fmod(target->progress_time, 5.f);
	SetProgress(int(progress_time / 1.f));


	ui->Update();
	mouse->Update();
}

void FurnaceManager::Render()
{
	if (not active)
		return;

	ui->Render();
	if (mousePick.itemid != 0)
		mouse->Render();
}

void FurnaceManager::RenderHierarchy()
{
	ui->RenderHierarchy();
}

void FurnaceManager::Release()
{
	ui->Release();
	mouse->Release();
}

void FurnaceManager::OnFurnace(Int3 _pos)
{
	active = true;
	SetFurnace(_pos);
	UpdateFuelSlot();
	UpdateInputSlot();
	UpdateOutputSlot();
}

void FurnaceManager::AddFurnace(Int3 _pos, Furnace* _furnace)
{
	if (furnaces[_pos.x][_pos.y][_pos.z])
		delete furnaces[_pos.x][_pos.y][_pos.z];
	furnaces[_pos.x][_pos.y][_pos.z] = _furnace;
}

void FurnaceManager::RemoveFurnace(Int3 _pos)
{
	if (furnaces[_pos.x][_pos.y][_pos.z])
		delete furnaces[_pos.x][_pos.y][_pos.z];
	furnaces[_pos.x][_pos.y].erase(furnaces[_pos.x][_pos.y].find(_pos.z));
}

void FurnaceManager::SetFurnace(Int3 _pos)
{
	if (furnaces[_pos.x][_pos.y].find(_pos.z) == furnaces[_pos.x][_pos.y].end())
		furnaces[_pos.x][_pos.y][_pos.z] = new Furnace();
	target = furnaces[_pos.x][_pos.y][_pos.z];
}

void FurnaceManager::SetFire(int _fire)
{
	ui->Find("fire")->SetWorldPos({ -0.125f , 0.37f + (0.014f * float(_fire)), 0.4f });
	ui->Find("fire")->scale = { 0.1f, 0.1f - (0.02f * float(_fire)), 0.1f };
}

void FurnaceManager::SetProgress(int _progress)
{
	ui->Find("progress")->SetWorldPos({ 0.02f - (0.0125f * float(_progress)) , 0.35f, 0.5f });
	ui->Find("progress")->scale = { 0.11f - (0.025f * float(_progress)), 0.15f, 0.1f };
}

bool FurnaceManager::IsFuel(int _itemid)
{
	switch (_itemid)
	{
		case int(BlockType::BIRCH_WOOD) :
		case int(BlockType::SPRUCE_WOOD) :
		case int(BlockType::JUNGLE_WOOD) :
		case int(BlockType::OAK_WOOD) :
		case int(BlockType::ACACIA_WOOD_PLANK) :
		case int(BlockType::BIRCH_WOOD_PLANK) :
		case int(BlockType::SPRUCE_WOOD_PLANK) :
		case int(BlockType::DARK_OAK_WOOD_PLANK) :
		case int(BlockType::JUNGLE_WOOD_PLANK) :
		case int(BlockType::OAK_WOOD_PLANK) :
			return true;
	}
	return false;
}

int FurnaceManager::IsBurnable(int _itemid)
{
	switch (_itemid)
	{
	case 319:
		return 320;
	case int(BlockType::SAND):
		return int(BlockType::GLASS);
	case int(BlockType::COBBLESTONE):
		return int(BlockType::STONE);
	}
	return 0;
}

void FurnaceManager::UpdateMouse()
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

void FurnaceManager::UpdateInputSlot()
{
	if (target->inputSlot.ea <= 0) {
		ui->Find("iItemImg")->visible = false;
		target->inputSlot.Remove();
	}
	else {
		ui->Find("iItemImg")->visible = true;
		ITEM_MANAGER->SetItemImage(ui->Find("iItemImg"), target->inputSlot);
		dynamic_cast<Text*>(ui->Find("iItemEa"))->ChangeText(to_string(target->inputSlot.ea));
	}
}

void FurnaceManager::UpdateOutputSlot()
{
	if (target->outputSlot.ea <= 0) {
		ui->Find("oItemImg")->visible = false;
		target->outputSlot.Remove();
	}
	else {
		ui->Find("oItemImg")->visible = true;
		ITEM_MANAGER->SetItemImage(ui->Find("oItemImg"), target->outputSlot);
		dynamic_cast<Text*>(ui->Find("oItemEa"))->ChangeText(to_string(target->outputSlot.ea));
	}
}

void FurnaceManager::UpdateFuelSlot()
{
	if (target->fuelSlot.ea <= 0) {
		ui->Find("fItemImg")->visible = false;
		target->fuelSlot.Remove();
	}
	else {
		ui->Find("fItemImg")->visible = true;
		ITEM_MANAGER->SetItemImage(ui->Find("fItemImg"), target->fuelSlot);
		dynamic_cast<Text*>(ui->Find("fItemEa"))->ChangeText(to_string(target->fuelSlot.ea));
	}
}
