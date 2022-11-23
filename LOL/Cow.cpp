#include "stdafx.h"

Cow::Cow()
{
	type = MonsterType::COW;
}

void Cow::Init(Vector3 _pos)
{
	LoadFile("Monster/Cow.xml");
	SetLocalPos(_pos);

	state = MonsterState::FALL;
	passedTime = 0.f;
	isAlive = true;

	maxHp = 100;
	hp = maxHp;


	prevSector = (_pos / BLOCK_LENGTH) / SECTOR_SIZE;
}

void Cow::Update()
{
	PreUpdate();

	switch (state)
	{
	case MonsterState::IDLE:
		Idle();
		break;
	case MonsterState::MOVE:
		Move();
		break;
	case MonsterState::FALL:
		Fall();
		break;
	case MonsterState::RUN_AWAY:
		RunAway();
		break;
	case MonsterState::DEAD:
		Dead();
		break;
	}
	MoveWorldPos(moveForce);
}

void Cow::Render()
{
	Actor::Render();
}

void Cow::RenderHierarchy()
{
	Actor::RenderHierarchy();
}

void Cow::Release()
{
	Actor::Release();
}

void Cow::Idle()
{
	CheckFloor();

	if (leftTime <= 0.f)
	{
		state = MonsterState::MOVE;
		leftTime = (float(rand() % 30) * 0.1f) + 1.f;
		rotation.y = float(float(rand() % 31415) * 0.0001f);
		return;
	}
}

void Cow::Move()
{
	CheckFloor();

	HorizontalMove();

	CheckBlockHeight();

	if (leftTime <= 0.f)
	{
		state = MonsterState::IDLE;
		leftTime = (float(rand() % 10) * 0.1f) + 1.f;
		return;
	}

}

void Cow::Jump()
{
}

void Cow::Fall()
{
	FallingDown();
}

void Cow::RunAway()
{
	if (leftTime <= 0.f)
	{
		state = MonsterState::IDLE;
		leftTime = 1.f;
		return;
	}

	BackAndForthDir();

	HorizontalMove(2.f);

	CheckBlockHeight();
}