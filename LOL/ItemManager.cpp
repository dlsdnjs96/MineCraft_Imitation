#include "stdafx.h"

void ItemManager::Update()
{
	auto iter = objects.begin();
	while (iter != objects.end())
	{
		(*iter)->Update();
		if ((*iter)->GetItem().itemid == 0) {
			objects.erase(iter++);
		}
		else iter++;
	}
}

void ItemManager::Render()
{
	for (auto& it : objects)
		it->Render();
}

void ItemManager::RenderHierarchy()
{
	for (auto& it : objects)
		it->RenderHierarchy();
}

void ItemManager::Spawn(Vector3 _pos, Item _item)
{
	ItemObject* temp = new ItemObject(_item);
	_pos.y += BLOCK_LENGTH;
	temp->SetLocalPos(_pos);
	objects.push_back(temp);
}
