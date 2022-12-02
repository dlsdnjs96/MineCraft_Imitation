#include "stdafx.h"

Chicken::Chicken()
{
	type = MonsterType::CHICKEN;
	kind = "chicken";
}

void Chicken::Init(Vector3 _pos)
{
	LoadFile("Monster/Chicken.xml");
	SetLocalPos(_pos);
	maxHp = 4;
	PreInit();
}

void Chicken::Update()
{
	PreUpdate();

	LayEgg();
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
	case MonsterState::HIT:
		Hit();
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

void Chicken::Interact(int _itemid)
{
}

void Chicken::Idle()
{
	AniFlapping(0.3f);


	CheckFloor();

	if (leftTime <= 0.f)
	{
		ChangeState(MonsterState::MOVE);
		leftTime = (float(rand() % 30) * 0.1f) + 1.f;
		rotation.y = float(float(rand() % 31415) * 0.0001f);
		return;
	}
}

void Chicken::Move()
{
	AniWalking(0.15f);


	CheckFloor();

	HorizontalMove();

	CheckBlockHeight();

	if (leftTime <= 0.f)
	{
		ChangeState(MonsterState::IDLE);
		leftTime = (float(rand() % 10) * 0.1f) + 1.f;
		return;
	}
}

void Chicken::Fall()
{
	AniFlapping(0.15f);


	FallingDown();
}

void Chicken::RunAway()
{
	AniWalking(0.05f);


	if (leftTime <= 0.f)
	{
		ChangeState(MonsterState::IDLE);
		leftTime = 1.f;
		return;
	}

	BackAndForthDir();

	HorizontalMove(2.5f);

	CheckBlockHeight();
}

