#include "stdafx.h"

Pig::Pig()
{
	type = MonsterType::PIG;
	kind = "pig";
}

void Pig::Init(Vector3 _pos)
{
	LoadFile("Monster/Pig.xml");
	SetLocalPos(_pos);
	maxHp = 10;
	PreInit();
}

void Pig::Update()
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
	case MonsterState::HIT:
		Hit();
		break;
	case MonsterState::HIT_NO_REACT:
		HitNoReact();
		break;
	case MonsterState::FOLLOW:
		Follow();
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

void Pig::Render()
{
	Actor::Render();
}

void Pig::RenderHierarchy()
{
	Actor::RenderHierarchy();
}

void Pig::Release()
{
	Actor::Release();
}

void Pig::Interact(int _itemid)
{
}

void Pig::Idle()
{
	CheckFloor();

	if (leftTime <= 0.f)
	{
		ChangeState(MonsterState::MOVE);
		leftTime = (float(rand() % 30) * 0.1f) + 1.f;
		rotation.y = float(float(rand() % 31415) * 0.0001f);
		return;
	}
	if (DectectWheet(500.f))
		ChangeState(MonsterState::FOLLOW);
}

void Pig::Move()
{
	AniCrawling(0.3f);


	CheckFloor();

	HorizontalMove();

	CheckBlockHeight();

	if (leftTime <= 0.f)
	{
		ChangeState(MonsterState::IDLE);
		leftTime = (float(rand() % 10) * 0.1f) + 1.f;
		return;
	}
	if (DectectWheet(500.f))
		ChangeState(MonsterState::FOLLOW);

}

void Pig::Jump()
{
}

void Pig::Fall()
{
	if (FallingDown())
		HitByFallDown(int(passedTime * 10.f));
}

void Pig::RunAway()
{
	AniCrawling(0.15f);


	if (leftTime <= 0.f)
	{
		ChangeState(MonsterState::IDLE);
		leftTime = 1.f;
		return;
	}

	BackAndForthDir();

	HorizontalMove(2.f);

	CheckBlockHeight();
}

void Pig::Follow()
{
	if (not DectectWheet(500.f)) {
		ChangeState(MonsterState::IDLE);
		leftTime = 1.f;
		return;
	}
	CheckFloor();

	FollowPlayer();

	CheckBlockHeight();

	if (not DectectPlayer(100.f))
	{
		ChangeState(MonsterState::IDLE);
		leftTime = 1.f;
		return;
	}
}


