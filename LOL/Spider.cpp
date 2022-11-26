#include "stdafx.h"

Spider::Spider()
{
	type = MonsterType::SPIDER;
}

void Spider::Init(Vector3 _pos)
{
	LoadFile("Monster/Spider.xml");
	SetLocalPos(_pos);
	maxHp = 20;
	PreInit();
}

void Spider::Update()
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
	case MonsterState::FOLLOW:
		Follow();
		break;
	case MonsterState::ATTACK:
		Attack();
		break;
	case MonsterState::DEAD:
		Dead();
		break;
	}
	MoveWorldPos(moveForce);
}

void Spider::Render()
{
	Actor::Render();
}

void Spider::RenderHierarchy()
{
	Actor::RenderHierarchy();
}

void Spider::Release()
{
	Actor::Release();
}

void Spider::Interact(int _itemid)
{
}

void Spider::Idle()
{
	CheckFloor();

	if (DectectPlayer(500.f))
	{
		ChangeState(MonsterState::FOLLOW);
		return;
	}
	if (leftTime <= 0.f)
	{
		ChangeState(MonsterState::MOVE);
		leftTime = (float(rand() % 30) * 0.1f) + 1.f;
		rotation.y = float(float(rand() % 31415) * 0.0001f);
		return;
	}
}

void Spider::Move()
{
	AniCrawling8(0.13f);


	CheckFloor();

	HorizontalMove();

	CheckBlockHeight();

	if (DectectPlayer(100.f))
	{
		ChangeState(MonsterState::FOLLOW);
		return;
	}
	if (leftTime <= 0.f)
	{
		ChangeState(MonsterState::IDLE);
		leftTime = (float(rand() % 10) * 0.1f) + 1.f;
		return;
	}
}

void Spider::Fall()
{
	FallingDown();
}

void Spider::Follow()
{
	AniCrawling8(0.13f);


	CheckFloor();

	FollowPlayer();

	CheckBlockHeight();


	if (DectectPlayer(30.f))
	{
		ChangeState(MonsterState::ATTACK);
		leftTime = 1.f;
		return;
	}
	if (not DectectPlayer(100.f))
	{
		ChangeState(MonsterState::IDLE);
		leftTime = 1.f;
		return;
	}
}

void Spider::Attack()
{
	AniAttacking1(1.f);


	if (leftTime <= 0.f)
	{
		Player::user->AttackedByMonster(3);
		leftTime = 1.f;
		passedTime = 0.f;
	}

	if (not DectectPlayer(30.f))
	{
		ChangeState(MonsterState::FOLLOW);
		leftTime = 0.f;
		return;
	}
}

void Spider::AniReset()
{
	for (auto& it : obList)
		it.second->rotation = { 0.f, 0.f, 0.f };
	Find("hipL")->rotation.y = 0.5235f;
	Find("hipL2")->rotation.y = 0.1745;
	Find("hipL3")->rotation.y = -0.1745;
	Find("hipL4")->rotation.y = -0.5235f;
	Find("hipR")->rotation.y = 0.5235f;
	Find("hipR2")->rotation.y = 0.1745;
	Find("hipR3")->rotation.y = -0.1745;
	Find("hipR4")->rotation.y = -0.5235f;
	rotation = rotatedDir;
}
