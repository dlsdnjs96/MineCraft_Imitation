#include "stdafx.h"

Zombie::Zombie()
{
	type = MonsterType::ZOMBIE;
	kind = "zombie;";
}

void Zombie::Init(Vector3 _pos)
{
	LoadFile("Monster/Zombie.xml");
	SetLocalPos(_pos);
	maxHp = 20;
	PreInit();
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
	case MonsterState::HIT:
		Hit();
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

void Zombie::Interact(int _itemid)
{
}

void Zombie::Idle()
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
		rotatedDir.y = float(float(rand() % 31415) * 0.0001f);
		return;
	}
}

void Zombie::Move()
{
	AniWalking(0.3f);


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

void Zombie::Fall()
{
	FallingDown();
}

void Zombie::Follow()
{
	AniWalking(0.3f);


	CheckFloor();

	FollowPlayer();

	CheckBlockHeight();


	if (DectectPlayer(30.f))
	{
		ChangeState(MonsterState::ATTACK);
		leftTime = 0.6f;
		return;
	}
	if (not DectectPlayer(100.f))
	{
		ChangeState(MonsterState::IDLE);
		leftTime = 1.f;
		return;
	}
}

void Zombie::Attack()
{
	AniAttacking2(0.6f);

	if (leftTime <= 0.f)
	{
		PlayerModel::user->AttackedByMonster(2);
		leftTime = 0.6f;
		return;
	}

	if (not DectectPlayer(30.f))
	{
		ChangeState(MonsterState::FOLLOW);
		leftTime = 0.f;
		return;
	}
}

void Zombie::AniReset()
{
	for (auto& it : obList)
		it.second->rotation = { 0.f, 0.f, 0.f };
	Find("shoulderL")->rotation.x = -PI_DIV2;
	Find("shoulderR")->rotation.x = -PI_DIV2;
	rotation = rotatedDir;
}
