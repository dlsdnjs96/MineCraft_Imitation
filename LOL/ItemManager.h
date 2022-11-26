#pragma once

class ItemManager : public Singleton<ItemManager>
{
private:
public:
	list<ItemObject*> objects;
	void Update();
	void Render();
	void RenderHierarchy();

	void Spawn(Vector3 _pos, Item _item, ItemObjectState _state = ItemObjectState::FALL);

	const char* GetItemName(int _itemid);
	int GetItemId(const char* _itemName);
	const char* GetBlockName(int _blockid);
	Item GetDropItem(BlockType _blockType);
	void SetItemImage(GameObject* _gameObject, Item _item);
	void SetItemObjectImage(GameObject* _gameObject, Item _item);
};

