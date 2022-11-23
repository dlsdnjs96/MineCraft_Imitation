#include "stdafx.h"



void Monster::HitByPlayer(int damage)
{
	hp -= damage;

	state = MonsterState::RUN_AWAY;
	leftTime = 5.f;
	if (hp <= 0)
	{
		state = MonsterState::DEAD;
		leftTime = 0.5f;
		return;
	}
}

void Monster::Hit()
{
	leftTime -= DELTA;

	float prevY, curY;
	prevY = jumpSpeed * (0.5f - leftTime - DELTA) - (0.5f * gravity * powf((0.5f - leftTime - DELTA), 2.f));
	curY = jumpSpeed * (0.5f - leftTime) - (0.5f * gravity * powf((0.5f - leftTime), 2.f));
	moveForce.y += curY - prevY;

	if (leftTime <= 0.f)
	{
		state = MonsterState::RUN_AWAY;
		leftTime = 3.f;
		return;
	}
}

void Monster::Dead()
{
	leftTime -= DELTA;

	rotation.z -= DELTA;
	if (leftTime <= 0.f) {
		isAlive = false;
		MONSTER_MANAGER->DropItem(type, Find("body")->GetWorldPos());
	}
}




void Monster::PreInit()
{
	state = MonsterState::FALL;
	passedTime = 0.f;
	isAlive = true;
	hp = maxHp;

	prevSector = (GetLocalPos() / BLOCK_LENGTH) / SECTOR_SIZE;
}

void Monster::PreUpdate()
{
	Actor::Update();

	passedTime += DELTA;
	leftTime -= DELTA;


	currSector = Int3(GetLocalPos() / BLOCK_LENGTH) / SECTOR_SIZE;
	curInt3 = Int3(GetWorldPos() / BLOCK_LENGTH);
	underInt3 = { curInt3.x, curInt3.y - 1, curInt3.z };
	moveForce = { 0.f, 0.f, 0.f };
}

bool Monster::DectectPlayer(float dis)
{
	if (Vector3::Distance(Player::user->GetWorldPos(), GetWorldPos()) < dis)
		return true;
	return false;
}

void Monster::FollowPlayer()
{
	Vector3 forward = Player::user->GetWorldPos() - GetWorldPos();
	forward.y = 0.f;
	forward.Normalize();
	rotation.y = atan2f(forward.x, forward.z);
	moveForce += forward * DELTA * moveSpeed;
}



void Monster::FollowWheet()
{
}

void Monster::CheckBlockHeight()
{
	Int3 nextInt3 = Int3((GetLocalPos() + moveForce) / BLOCK_LENGTH);
	if (WORLD->GetBlock(nextInt3).blockType > BlockType::STILL_WATER
		&& WORLD->GetBlock(Int3{ nextInt3.x, nextInt3.y + 1, nextInt3.z }).blockType > BlockType::STILL_WATER)
	{
		state = MonsterState::IDLE;
		leftTime = (float(rand() % 4) * 0.1f) + 0.2f;
		moveForce = { 0.f, 0.f, 0.f };
		return;
	}
	else if (WORLD->GetBlock(nextInt3).blockType == BlockType::AIR
		&& WORLD->GetBlock(Int3{ nextInt3.x, nextInt3.y - 1, nextInt3.z }).blockType == BlockType::AIR
		&& WORLD->GetBlock(Int3{ nextInt3.x, nextInt3.y - 2, nextInt3.z }).blockType == BlockType::AIR)
	{
		rotation.y = -rotation.y;
		moveForce = { 0.f, 0.f, 0.f };
		return;
	}
	else if (WORLD->GetBlock(nextInt3).blockType == BlockType::AIR
		&& WORLD->GetBlock(Int3{ nextInt3.x, nextInt3.y - 1, nextInt3.z }).blockType == BlockType::AIR
		&& WORLD->GetBlock(Int3{ nextInt3.x, nextInt3.y - 2, nextInt3.z }).blockType > BlockType::STILL_WATER)
	{
		SetLocalPosY(static_cast<float>((nextInt3.y - 1) * BLOCK_LENGTH));
		return;
	}
	else if (WORLD->GetBlock(nextInt3).blockType > BlockType::STILL_WATER
		&& WORLD->GetBlock(Int3{ nextInt3.x, nextInt3.y + 1, nextInt3.z }).blockType == BlockType::AIR)
	{
		SetLocalPosY(static_cast<float>((nextInt3.y + 1) * BLOCK_LENGTH));
		return;
	}
}

void Monster::CheckFloor()
{
	if (WORLD->GetBlock(underInt3).blockType == BlockType::AIR)
	{
		state = MonsterState::FALL;
		return;
	}
}

void Monster::HorizontalMove(float boost)
{
	Vector3 forward = GetForward();
	forward.y = 0.f;
	forward.Normalize();
	moveForce += forward * DELTA * moveSpeed * boost;
}

void Monster::FallingDown()
{
	float prevTime = jumppedTime;
	jumppedTime += DELTA;

	moveForce.y += (jumpSpeed * jumppedTime - (0.5f * gravity * powf(jumppedTime, 2.f)))
		- (jumpSpeed * prevTime - (0.5f * gravity * powf(prevTime, 2.f)));



	if (WORLD->GetBlock(curInt3).blockType == BlockType::STILL_WATER)
	{
		state = MonsterState::SWIM;
	}
	else if (WORLD->GetBlock(curInt3).blockType > BlockType::STILL_WATER)
	{
		moveForce.y = 0.f;
		SetLocalPosY(static_cast<float>((curInt3.y + 1) * BLOCK_LENGTH));
		state = MonsterState::MOVE;
	}
}

void Monster::BackAndForthDir()
{
	if (int(passedTime / 1.5f) % 2 == 0)
		rotation.y += DELTA;
	else
		rotation.y -= DELTA;
}
