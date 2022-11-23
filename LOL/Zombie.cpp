#include "stdafx.h"

Zombie::Zombie()
{
	type = MonsterType::ZOMBIE;
}

void Zombie::Init(Vector3 _pos)
{
	LoadFile("Monster/Zombie.xml");
	SetLocalPos(_pos);

	state = MonsterState::FALL;
	passedTime = 0.f;
	isAlive = true;

	maxHp = 100;
	hp = maxHp;


	prevSector = (_pos / BLOCK_LENGTH) / SECTOR_SIZE;
}

void Zombie::Update()
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

void Zombie::Render()
{
	Actor::Render();
}

void Zombie::RenderHierarchy()
{
	Actor::RenderHierarchy();
}

void Zombie::Release()
{
	Actor::Release();
}

void Zombie::Idle()
{
	CheckFloor();

	if (DectectPlayer(500.f))
	{
		state = MonsterState::FOLLOW;
		return;
	}
	if (leftTime <= 0.f)
	{
		state = MonsterState::MOVE;
		leftTime = (float(rand() % 30) * 0.1f) + 1.f;
		rotation.y = float(float(rand() % 31415) * 0.0001f);
		return;
	}
}

void Zombie::Move()
{
	CheckFloor();

	HorizontalMove();

	CheckBlockHeight();

	if (DectectPlayer(500.f))
	{
		state = MonsterState::FOLLOW;
		return;
	}
	if (leftTime <= 0.f)
	{
		state = MonsterState::IDLE;
		leftTime = (float(rand() % 10) * 0.1f) + 1.f;
		return;
	}
}

void Zombie::Fall()
{
	FallingDown();
}

void Zombie::Follow()
{
	CheckFloor();

	FollowPlayer();

	CheckBlockHeight();


	if (DectectPlayer(15.f))
	{
		state = MonsterState::ATTACK;
		leftTime = 0.f;
		return;
	}
	if (not DectectPlayer(500.f))
	{
		state = MonsterState::IDLE;
		leftTime = 1.f;
		return;
	}
}

void Zombie::Attack()
{
	if (leftTime <= 0.f)
	{
		leftTime = 0.5f;
		return;
	}

	if (not DectectPlayer(15.f))
	{
		state = MonsterState::FOLLOW;
		leftTime = 0.f;
		return;
	}
}
