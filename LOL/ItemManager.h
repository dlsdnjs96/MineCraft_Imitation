#pragma once

class ItemManager : public Singleton<ItemManager>
{
private:
	list<ItemObject*> objects;
public:
	Player* user;
	void Update();
	void Render();
	void RenderHierarchy();

	void Spawn(Vector3 _pos, Item _item);
};

