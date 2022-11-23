#include "stdafx.h"

Chicken::Chicken()
{
	type = MonsterType::CHICKEN;
}

void Chicken::Init(Vector3 _pos)
{
	LoadFile("Monster/Chicken.xml");
	SetLocalPos(_pos);
	maxHp = 100;
	PreInit();
}

void Chicken::Update()
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

void Chicken::Render()
{
	Actor::Render();
}

void Chicken::RenderHierarchy()
{
	Actor::RenderHierarchy();
}

void Chicken::Release()
{
	Actor::Release();
}

void Chicken::Idle()
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

void Chicken::Move()
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

void Chicken::Fall()
{
	FallingDown();
}

void Chicken::RunAway()
{
	if (leftTime <= 0.f)
	{
		state = MonsterState::IDLE;
		leftTime = 1.f;
		return;
	}

	BackAndForthDir();

	HorizontalMove(2.5f);

	CheckBlockHeight();
}

