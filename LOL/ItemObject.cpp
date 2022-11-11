#include "stdafx.h"

ItemObject::ItemObject(Item _item)
{
	item = _item;
	state = ItemObjectState::FALL;
	passedTime = 0.f;

	mesh = RESOURCE->meshes.Load("6.OneFaceBlock.mesh");
	shader = RESOURCE->shaders.Load("Block.hlsl");
	material = RESOURCE->materials.Load("Items/100.mtl");
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
	}
}


void ItemObject::Stay()
{
	Int3 curInt3 = Int3(GetWorldPos() / BLOCK_LENGTH);
	curInt3 = Int3{ curInt3.x, curInt3.y - 1, curInt3.z };

	if (WORLD->GetBlock(curInt3).blockType == BlockType::EMPTY) {
		state = ItemObjectState::FALL;
	}
	else {
		rotation.y += DELTA;
		float height = floorf(GetLocalPos().y / BLOCK_LENGTH) * BLOCK_LENGTH;
		height += sinf(passedTime) + 3.f;
		SetLocalPosY(height);
	}
}

void ItemObject::Fall()
{
	MoveLocalPos({ 0.f, -DELTA, 0.f });

	Int3 curInt3 = Int3(GetWorldPos() / BLOCK_LENGTH);
	curInt3 = Int3{ curInt3.x, curInt3.y - 1, curInt3.z };
	if (WORLD->GetBlock(curInt3).blockType != BlockType::EMPTY) {
		state = ItemObjectState::STAY;
	}
}

void ItemObject::Gain()
{
}
