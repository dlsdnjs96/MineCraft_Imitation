#include "stdafx.h"



void Monster::HitByPlayer(int damage)
{
	hp -= damage;

	SOUND->Play(kind, Vector3::Distance(GetWorldPos(), PlayerModel::user->GetWorldPos()));
	ChangeState(MonsterState::HIT);
	leftTime = 1.f;

	ChangeShader("3.Scarlet.hlsl");

	if (hp <= 0)
	{
		ChangeShader("Block.hlsl");
		ChangeState(state = MonsterState::DEAD);
		leftTime = 0.5f;
		return;
	}
}

void Monster::HitByFallDown(int damage)
{
	hp -= damage;

	ChangeState(MonsterState::HIT_NO_REACT);
	leftTime = 1.f;

	ChangeShader("3.Scarlet.hlsl");

	if (hp <= 0)
	{
		ChangeState(state = MonsterState::DEAD);
		leftTime = 0.5f;
		return;
	}
}

void Monster::Hit()
{
	leftTime -= DELTA;

	float prevY, curY;
	prevY = jumpSpeed * (1.f - leftTime - DELTA) - (0.5f * gravity * powf((1.f - leftTime - DELTA), 2.f));
	curY = jumpSpeed * (1.f - leftTime) - (0.5f * gravity * powf((1.f - leftTime), 2.f));
	moveForce.y += curY - prevY;


	if (leftTime <= 0.f)
	{
		ChangeState(MonsterState::RUN_AWAY);
		ChangeShader("Block.hlsl");
		leftTime = 5.f;
		return;
	}
}

void Monster::HitNoReact()
{
	leftTime -= DELTA;

	float prevY, curY;
	prevY = jumpSpeed * (1.f - leftTime - DELTA) - (0.5f * gravity * powf((1.f - leftTime - DELTA), 2.f));
	curY = jumpSpeed * (1.f - leftTime) - (0.5f * gravity * powf((1.f - leftTime), 2.f));
	moveForce.y += curY - prevY;


	if (leftTime <= 0.f)
	{
		ChangeState(MonsterState::IDLE);
		ChangeShader("Block.hlsl");
		leftTime = 1.f;
		return;
	}
}

void Monster::Dead()
{
	leftTime -= DELTA;

	rotation.z -= DELTA * 3.f;
	if (leftTime <= 0.f) {
		isAlive = false;
		MONSTER_MANAGER->DropItem(type, Find("body")->GetWorldPos());
	}
}




void Monster::PreInit()
{
	ChangeState(MonsterState::FALL);
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

void Monster::LayEgg()
{
	layedTime -= DELTA;
	if (layedTime <= 0.f)
	{
		ITEM_MANAGER->Spawn(Find("body")->GetWorldPos(), Item{ ITEM_MANAGER->GetItemId("egg"), 1 });
		layedTime = ((rand() % 3) + 4.f) * 10.f;
	}
}

bool Monster::DectectPlayer(float dis)
{
	if (Vector3::Distance(PlayerModel::user->GetWorldPos(), GetWorldPos()) < dis)
		return true;
	return false;
}

void Monster::FollowPlayer()
{
	Vector3 forward = PlayerModel::user->GetWorldPos() - GetWorldPos();
	forward.y = 0.f;
	forward.Normalize();
	rotation.y = atan2f(-forward.z, forward.x);
	moveForce += forward * DELTA * moveSpeed;
}

bool Monster::DectectWheet(float dis)
{
	if (INVENTORY->GetPickedItem().itemid == ITEM_MANAGER->GetItemId("wheet") 
		and Vector3::Distance(PlayerModel::user->GetWorldPos(), GetWorldPos()) < dis)
		return true;
	return false;
}



void Monster::FollowWheet()
{
	Vector3 forward = PlayerModel::user->GetWorldPos() - GetWorldPos();
	forward.y = 0.f;
	forward.Normalize();
	rotation.y = atan2f(forward.x, forward.z);
	moveForce += forward * DELTA * moveSpeed;
}

void Monster::CheckBlockHeight()
{
	Int3 nextInt3 = Int3((GetLocalPos() + moveForce) / BLOCK_LENGTH);
	if (WORLD->GetBlock(nextInt3).blockType > BlockType::STILL_WATER
		&& WORLD->GetBlock(Int3{ nextInt3.x, nextInt3.y + 1, nextInt3.z }).blockType > BlockType::STILL_WATER)
	{
		ChangeState(MonsterState::IDLE);
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
		ChangeState(MonsterState::FALL);
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

bool Monster::FallingDown()
{
	float prevTime = jumppedTime;
	jumppedTime += DELTA;

	moveForce.y += (jumpSpeed * jumppedTime - (0.5f * gravity * powf(jumppedTime, 2.f)))
		- (jumpSpeed * prevTime - (0.5f * gravity * powf(prevTime, 2.f)));



	if (WORLD->GetBlock(curInt3).blockType == BlockType::STILL_WATER)
	{
		ChangeState(MonsterState::SWIM);
		return true;
	}
	else if (WORLD->GetBlock(curInt3).blockType > BlockType::STILL_WATER)
	{
		moveForce.y = 0.f;
		SetLocalPosY(static_cast<float>((curInt3.y + 1) * BLOCK_LENGTH));
		ChangeState(MonsterState::MOVE);
		return true;
	}
	return false;
}

void Monster::BackAndForthDir()
{
	if (int(passedTime / 1.5f) % 2 == 0)
		rotation.y += DELTA;
	else
		rotation.y -= DELTA;
}

void Monster::AniFlapping(float duration)
{
	float tTime = passedTime + duration;
	if (int(tTime / (duration)) % 2 == 0)
	{
		tTime = fmod(tTime, duration);

		Find("shoulderL")->rotation.z = -((tTime) / duration) * PI_DIV2;
		Find("shoulderR")->rotation.z = ((tTime) / duration) * PI_DIV2;
	}
	else {
		tTime = fmod(tTime, duration);

		Find("shoulderL")->rotation.z = -((duration - tTime) / duration) * PI_DIV2;
		Find("shoulderR")->rotation.z = ((duration - tTime) / duration) * PI_DIV2;
	}
}

void Monster::AniWalking(float duration)
{
	float tTime = passedTime + duration;
	if (int(tTime / (duration * 2.f))%2 == 0)
	{
		while (tTime > duration * 2.f)
			tTime -= duration * 2.f;
		Find("hipL")->rotation.x = tTime - duration;
		Find("hipR")->rotation.x = duration - tTime;
	}
	else {
		while (tTime > duration * 2.f)
			tTime -= duration * 2.f;
		Find("hipL")->rotation.x = duration - tTime;
		Find("hipR")->rotation.x = tTime - duration;
	}
}

void Monster::AniCrawling(float duration)
{
	float tTime = passedTime + duration;
	if (int(tTime / (duration * 2.f)) % 2 == 0)
	{
		while (tTime > duration * 2.f)
			tTime -= duration * 2.f;
		Find("shoulderL")->rotation.x = duration - tTime;
		Find("shoulderR")->rotation.x = tTime - duration;
		Find("hipL")->rotation.x = tTime - duration;
		Find("hipR")->rotation.x = duration - tTime;
	}
	else {
		while (tTime > duration * 2.f)
			tTime -= duration * 2.f;
		Find("shoulderL")->rotation.x = tTime - duration;
		Find("shoulderR")->rotation.x = duration - tTime;
		Find("hipL")->rotation.x = duration - tTime;
		Find("hipR")->rotation.x = tTime - duration;
	}
}

void Monster::AniCrawling8(float duration)
{
	float tTime = passedTime + duration;
	if (int(tTime / (duration * 2.f)) % 2 == 0)
	{
		while (tTime > duration * 2.f)
			tTime -= duration * 2.f;
		Find("hipL")->rotation.y = tTime - duration + 0.5235f;
		Find("hipL2")->rotation.y = duration - tTime + 0.1745;
		Find("hipL3")->rotation.y = tTime - duration - 0.1745;
		Find("hipL4")->rotation.y = duration - tTime - 0.5235f;
		Find("hipR")->rotation.y = duration - tTime + 0.5235f;
		Find("hipR2")->rotation.y = tTime - duration + 0.1745;
		Find("hipR3")->rotation.y = duration - tTime - 0.1745;
		Find("hipR4")->rotation.y = tTime - duration - 0.5235f;
	}
	else {
		while (tTime > duration * 2.f)
			tTime -= duration * 2.f;
		Find("hipL")->rotation.y = duration - tTime + 0.5235f;
		Find("hipL2")->rotation.y = tTime - duration + 0.1745;
		Find("hipL3")->rotation.y = duration - tTime - 0.1745;
		Find("hipL4")->rotation.y = tTime - duration - 0.5235f;
		Find("hipR")->rotation.y = tTime - duration + 0.5235f;
		Find("hipR2")->rotation.y = duration - tTime + 0.1745;
		Find("hipR3")->rotation.y = tTime - duration - 0.1745;
		Find("hipR4")->rotation.y = duration - tTime - 0.5235f;
	}
}

void Monster::AniAttacking1(float duration)
{
	Vector3 forward = PlayerModel::user->GetWorldPos() - GetWorldPos();
	rotation.y = atan2f(forward.x, forward.z);

	float tTime = fmod(passedTime, 1.f);

	if (tTime > 0.5f)
		tTime = 1.f - (tTime);
	tTime *= 20.f;

	Find("body")->SetLocalPos({ 0.f, tTime, tTime });
}

void Monster::AniAttacking2(float duration)
{
	Vector3 forward = PlayerModel::user->GetWorldPos() - GetWorldPos();
	rotation.y = atan2f(forward.x, forward.z);

	float tTime = fmod(passedTime, duration * 2.f);
	if (tTime > duration)
		tTime = (duration * 2.f) - tTime;

	tTime = (tTime / duration) * PI_DIV4;

	Find("shoulderR")->rotation.x = -PI_DIV2 - tTime;
}

void Monster::AniReset()
{
	for (auto& it : obList)
		it.second->rotation = { 0.f, 0.f, 0.f };
}

void Monster::ChangeState(MonsterState _state)
{
	state = _state;
	passedTime = 0.f;
	AniReset();
	if (_state == MonsterState::MOVE)
		SOUND->Play(kind, Vector3::Distance(GetWorldPos(), PlayerModel::user->GetWorldPos()));
}

void Monster::ChangeShader(string _shader)
{
	for (auto& it : obList)
		it.second->shader = RESOURCE->shaders.Load(_shader);
}
