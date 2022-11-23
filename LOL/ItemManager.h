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

	const char* GetItemName(int _itemid);
	int GetItemId(const char* _itemName);
	const char* GetBlockName(int _blockid);
	Item GetDropItem(BlockType _blockType);
	void SetItemImage(GameObject* _gameObject, Item _item);
	void SetItemObjectImage(GameObject* _gameObject, Item _item);
};

