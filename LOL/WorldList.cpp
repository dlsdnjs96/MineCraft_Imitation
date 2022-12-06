#include "stdafx.h"

void WorldList::Init()
{
	name = "WorldList";
	LoadFile("Menu/WorldList.xml");

	pickedScroll = false;
	dynamic_cast<UI*>(Find("scrollBar"))->mouseDown = [=]() { pickedScroll = true; };
	dynamic_cast<UI*>(Find("scrollBar"))->mouseUp = [=]() { pickedScroll = false; };


	dynamic_cast<UI*>(Find("play"))->mouseOver = [=]() { if (selectedWorld != "") Find("play")->material = RESOURCE->materials.Load("button2.mtl"); };
	dynamic_cast<UI*>(Find("play"))->mouseNotOver = [=]() { if (selectedWorld != "") Find("play")->material = RESOURCE->materials.Load("button1.mtl"); };
	
	dynamic_cast<UI*>(Find("delete"))->mouseOver = [=]() { if (selectedWorld != "") Find("delete")->material = RESOURCE->materials.Load("button2.mtl"); };
	dynamic_cast<UI*>(Find("delete"))->mouseNotOver = [=]() { if (selectedWorld != "") Find("delete")->material = RESOURCE->materials.Load("button1.mtl"); };

	dynamic_cast<UI*>(Find("topPlane"))->mouseDown = [=]() { selectedWorld = ""; 
	Find("play")->material = RESOURCE->materials.Load("button0.mtl");
	Find("delete")->material = RESOURCE->materials.Load("button0.mtl"); };

	dynamic_cast<UI*>(Find("bottomPlane"))->mouseDown = [=]() { 
//		selectedWorld = ""; 
	Find("play")->material = RESOURCE->materials.Load("button0.mtl");
	Find("delete")->material = RESOURCE->materials.Load("button0.mtl"); };

	Find("play")->material = RESOURCE->materials.Load("button0.mtl");
	Find("delete")->material = RESOURCE->materials.Load("button0.mtl");

	dynamic_cast<UI*>(Find("play"))->mouseDown = [=]() { if (selectedWorld == "") return;
	SOUND->Play("click"); WORLD->name = selectedWorld; WORLD->LoadWorld(); SCENE->ChangeScene("INGAME", 0.1f)->Init(); };
	dynamic_cast<UI*>(Find("delete"))->mouseDown = [=]() { if (selectedWorld == "") return;
	SOUND->Play("click"); system(("RD ../Contents/Map/" + selectedWorld).c_str()); system(("rmdir ../Contents/Map/" + selectedWorld).c_str()); };

	LoadWorldList();
}

void WorldList::Update()
{
	UI::Update();

	float scrollBarY = Find("scrollBar")->GetWorldPos().y;
	if (pickedScroll)
		scrollBarY = INPUT->NDCPosition.y;
	if (over)
		scrollBarY += INPUT->wheelMoveValue.z / 10000.f;

	//Util::Saturate(scrollBarY, 
	//	Find("scrollTab")->GetWorldPos().y - (Find("scrollTab")->scale.y / 2.f) + (Find("scrollBar")->scale.y / 2.f),
	//	Find("scrollTab")->GetWorldPos().y + (Find("scrollTab")->scale.y / 2.f) - (Find("scrollBar")->scale.y / 2.f));
	Find("scrollBar")->SetWorldPosY(scrollBarY);
	Find("list")->SetWorldPosY((-scrollBarY * 2.f) + 1.f);
	//Find("list")->SetWorldPosY(0.f);

}

void WorldList::Render()
{
	UI::Render();
}

void WorldList::LoadWorldList()
{
	int idx = 0;
	if (filesystem::exists("../Contents/Map"))
	{
		for (filesystem::path const& path : filesystem::directory_iterator("../Contents/Map"))
		{
			if (filesystem::is_directory(path))
			{
				string worldName = path.string().substr(path.string().find_last_of('\\') + 1);
				string date = "";


				Find("list")->AddChild(UI::Create(worldName));
				Find(worldName)->SetLocalPosY(0.f - (idx * 0.5f));
				Find(worldName)->SetLocalPosZ(-0.05f);
				Find(worldName)->scale = { 0.6f, 0.4f, 1.f };
				Find(worldName)->material = RESOURCE->materials.Load("WorldIcon.mtl");
				Find(worldName)->AddChild(UI::Create(worldName+"_icon"));
				Find(worldName + "_icon")->material = RESOURCE->materials.Load("PreImage/"+to_string(idx%7)+".mtl");
				Find(worldName + "_icon")->SetLocalPos({ -0.44f / 1.2f, 0.f, -0.1f });
				Find(worldName + "_icon")->scale = { 0.15f, 0.6f, 1.f };
				dynamic_cast<UI*>(Find(worldName))->mouseDown = [=]() {
					SOUND->Play("click");
					if (dynamic_cast<UI*>(Find("topPlane"))->MouseOver() or dynamic_cast<UI*>(Find("bottomPlane"))->MouseOver())
						return;
					selectedWorld = worldName;
					Find("play")->material = RESOURCE->materials.Load("button1.mtl");
					Find("delete")->material = RESOURCE->materials.Load("button1.mtl"); };

				Text* temp2 = Text::Create(worldName + "_world_name");
				temp2->fromLeft = true;
				temp2->SetLocalPos({ -0.3f / 1.2f, 0.1f / 0.4f, 0.f });
				temp2->scale = { 0.3f, 1.1f, 1.f };
				temp2->shader = RESOURCE->shaders.Load("6.Black.hlsl");
				temp2->ChangeText(worldName);
				Find(worldName)->AddChild(temp2);

				//Text* temp3 = Text::Create(worldName + "created_date");
				//temp3->fromLeft = true;
				//temp3->SetLocalPos({ -0.3f / 1.2f, 0.f, 0.f });
				//temp3->scale = { 0.3f, 1.1f, 1.f };
				//temp3->shader = RESOURCE->shaders.Load("6.Black.hlsl");
				//temp3->ChangeText(worldName);
				//Find(worldName)->AddChild(temp3);
				//
				//Text* temp4 = Text::Create(worldName + "last_cennected");
				//temp4->fromLeft = true;
				//temp4->SetLocalPos({ -0.3f / 1.2f, -0.1f / 0.4f, 0.f });
				//temp4->scale = { 0.3f, 1.1f, 1.f };
				//temp4->shader = RESOURCE->shaders.Load("6.Black.hlsl");
				//temp4->ChangeText(worldName);
				//Find(worldName)->AddChild(temp4);
				////dynamic_cast<UI*>(Find(worldName))->mouseDown = [=]() { WORLD->name = worldName; WORLD->LoadWorld(); SCENE->ChangeScene("INGAME", 0.1f)->Init(); };
				


				idx++;
			}
		}
	}
}

void WorldList::LoadWorld()
{
	selectedWorld;
	WORLD->name = selectedWorld;
	DATABASE->LoadWolrd();

	if (WORLD->id == -1)
	{

	}
	else {
		DATABASE->LoadPlayer();
		DATABASE->LoadInventory();
		DATABASE->LoadItemObject();
		DATABASE->LoadMonster();
		DATABASE->LoadFurnace();
	}
}
