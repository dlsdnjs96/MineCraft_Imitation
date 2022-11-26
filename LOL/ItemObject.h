#pragma once

enum class ItemObjectState
{
	STAY,
	FALL,
	GAIN,
	THROW
};

class ItemObject : public GameObject
{
private:
	float passedTime;
	Vector3 dir;
public:
	ItemObjectState state;
	Item item;
	ItemObject(Item _item, Vector3 _dir = { 0.f, 1.f, 0.f });

	void Update();

	void Stay();
	void Fall();
	void Gain();
	void Throw();

	Item GetItem();
};

