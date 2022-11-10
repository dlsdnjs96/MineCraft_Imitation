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

	dynamic_cast<UI*>(Find("play"))->mouseDown = [=]() { if (selectedWorld == "") return; WORLD->name = selectedWorld; WORLD->LoadWorld(); SCENE->ChangeScene("INGAME", 0.1f)->Init(); };
	dynamic_cast<UI*>(Find("delete"))->mouseDown = [=]() { if (selectedWorld == "") return; system(("RD ../Contents/Map/" + selectedWorld).c_str()); system(("rmdir ../Contents/Map/" + selectedWorld).c_str()); };

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

	Util::Saturate(scrollBarY, 
		Find("scrollTab")->GetWorldPos().y - (Find("scrollTab")->scale.y / 2.f) + (Find("scrollBar")->scale.y / 2.f),
		Find("scrollTab")->GetWorldPos().y + (Find("scrollTab")->scale.y / 2.f) - (Find("scrollBar")->scale.y / 2.f));
	Find("scrollBar")->SetWorldPosY(scrollBarY);
	Find("list")->SetWorldPosY(-scrollBarY * 2.f);

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
				Find("list")->AddChild(UI::Create(worldName));
				Find(worldName)->SetLocalPosY(2.f - (idx * 0.5f));
				Find(worldName)->SetLocalPosZ(-0.05f);
				Find(worldName)->scale = { 0.6f, 0.4f, 1.f };
				Find(worldName)->material = RESOURCE->materials.Load("WorldIcon.mtl");
				Find(worldName)->AddChild(UI::Create(worldName+"_icon"));
				Find(worldName + "_icon")->material = RESOURCE->materials.Load("PreImage/"+to_string(idx%7)+".mtl");
				Find(worldName + "_icon")->SetLocalPos({ -0.3f, 0.f, -0.1f });
				Find(worldName + "_icon")->scale = { 0.15f, 0.6f, 1.f };
				dynamic_cast<UI*>(Find(worldName))->mouseDown = [=]() { 
					selectedWorld = worldName;
					Find("play")->material = RESOURCE->materials.Load("button1.mtl");
					Find("delete")->material = RESOURCE->materials.Load("button1.mtl"); };
				//dynamic_cast<UI*>(Find(worldName))->mouseDown = [=]() { WORLD->name = worldName; WORLD->LoadWorld(); SCENE->ChangeScene("INGAME", 0.1f)->Init(); };
				idx++;
			}
		}
	}
}
