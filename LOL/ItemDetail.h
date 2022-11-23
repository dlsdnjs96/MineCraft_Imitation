#pragma once

class ItemDetail : public Singleton<ItemDetail>
{
private:
	int _prevItemId;
	int _currItemId;
	int itemId;
	Vector3 pos;
public:
	UI* itemDetail;

	ItemDetail();

	void SetDetail(int _itemid);

	void Init();
	void Update();
	void Render();
	void RenderHierarchy();
	void Release();
};

