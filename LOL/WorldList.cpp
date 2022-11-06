#include "stdafx.h"

void WorldList::Init()
{
	name = "WorldList";
	LoadFile("Menu/WorldList.xml");

	pickedScroll = false;
	dynamic_cast<UI*>(Find("scrollBar"))->mouseDown = [=]() { pickedScroll = true; };
	dynamic_cast<UI*>(Find("scrollBar"))->mouseUp = [=]() { pickedScroll = false; };



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
	wList.clear();
	int idx = 0;
	if (filesystem::exists("../Contents/Map"))
	{
		for (filesystem::path const& path : filesystem::directory_iterator("../Contents/Map"))
		{
			if (filesystem::is_directory(path))
			{
				WorldIcon tIcon;
				tIcon.path = path.string();
				string worldName = path.string().substr(path.string().find_last_of('\\') + 1);
				wList.push_back(tIcon);
				Find("list")->AddChild(UI::Create(worldName));
				Find(worldName)->SetLocalPosY(2.f - (Find("list")->children.size() * 0.8f));
				Find(worldName)->SetLocalPosZ(-0.05f);
				Find(worldName)->scale = { 0.2f, 0.8f, 1.f };
				Find(worldName)->material = RESOURCE->materials.Load("PreImage/"+to_string(idx%7)+".mtl");
				dynamic_cast<UI*>(Find(worldName))->mouseDown = [=]() { selectedWorld = worldName; };
				//dynamic_cast<UI*>(Find(worldName))->mouseDown = [=]() { WORLD->name = worldName; WORLD->LoadWorld(); SCENE->ChangeScene("INGAME", 0.1f)->Init(); };
				idx++;
			}
		}
	}
}
