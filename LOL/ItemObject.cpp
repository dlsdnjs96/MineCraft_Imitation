#include "stdafx.h"


ItemObject::ItemObject(Item _item, Vector3 _dir)
{
	item = _item;
	state = ItemObjectState::FALL;
	passedTime = 0.f;
	dir = _dir;

	ITEM_MANAGER->SetItemObjectImage(this, _item);
	scale = { 2.f, 2.f, 2.f };
}

void ItemObject::Update()
{
	GameObject::Update();
	passedTime += DELTA;
	switch (state)
	{
	case ItemObjectState::STAY:
		Stay();
		break;
	case ItemObjectState::FALL:
		Fall();
		break;
	case ItemObjectState::GAIN:
		Gain();
		break;
	case ItemObjectState::THROW:
		Throw();
		break;
	}
}


void ItemObject::Stay()
{
	Int3 curInt3 = Int3(GetWorldPos() / BLOCK_LENGTH);
	//curInt3 = Int3{ curInt3.x, curInt3.y - 1, curInt3.z };

	if (WORLD->GetBlock(curInt3).blockType != BlockType::AIR) {
		MoveLocalPos({ 0.f, DELTA * 30.f, 0.f });
	} else if (WORLD->GetBlock(Int3{ curInt3.x, curInt3.y - 1, curInt3.z }).blockType == BlockType::AIR) {
		state = ItemObjectState::FALL;
	}
	else {
		rotation.y += DELTA;
		float height = floorf(GetLocalPos().y / BLOCK_LENGTH) * BLOCK_LENGTH;
		height += sinf(passedTime) + 3.f;
		SetLocalPosY(height);
	}

	if (Vector3::Distance(GetWorldPos(), PlayerModel::user->GetWorldPos()) < 10.f)
	{
		state = ItemObjectState::GAIN;
		return;
	}
}

void ItemObject::Fall()
{
	Int3 curInt3 = Int3(GetWorldPos() / BLOCK_LENGTH);
	curInt3 = Int3{ curInt3.x, curInt3.y, curInt3.z };

	if (WORLD->GetBlock(curInt3).blockType != BlockType::AIR) {
		state = ItemObjectState::STAY;
	} else
		MoveLocalPos({ 0.f, -DELTA * 20.f, 0.f });
}

void ItemObject::Gain()
{
	Vector3 toUser = PlayerModel::user->GetWorldPos() - GetWorldPos();
	toUser.Normalize();
	MoveWorldPos(toUser * DELTA * 10.f);
	if (Vector3::Distance(GetWorldPos(), PlayerModel::user->GetWorldPos()) < 2.f)
	{
		INVENTORY->GainItem(item);
		item.Remove();
		return;
	}
}

void ItemObject::Throw()
{
	float height = (passedTime * 10.f) - (0.5f * 9.8f * powf(passedTime, 2.f));
	Vector3 tempDir = dir;
	tempDir.y = height;
	tempDir.Normalize();

	MoveWorldPos(tempDir * DELTA * 10.f);

	if (passedTime > 0.1f)
	{
		state = ItemObjectState::FALL;
		return;
	}

	Int3 curInt3 = Int3(GetWorldPos() / BLOCK_LENGTH);
	curInt3 = Int3{ curInt3.x, curInt3.y, curInt3.z };
	if (WORLD->GetBlock(curInt3).blockType != BlockType::AIR) {
		state = ItemObjectState::STAY;
		return;
	}
}

Item ItemObject::GetItem()
{
	return item;
}
