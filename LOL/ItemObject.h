#pragma once

enum class ItemObjectState
{
	STAY,
	FALL,
	GAIN
};

class ItemObject : public GameObject
{
private:
	ItemObjectState state;
	Item item;
	float passedTime;
public:
	ItemObject(Item _item);

	void Update();

	void Stay();
	void Fall();
	void Gain();

	Item GetItem();
};

