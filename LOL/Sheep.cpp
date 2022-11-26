#include "stdafx.h"

Sheep::Sheep()
{
	type = MonsterType::SHEEP;
}

void Sheep::Init(Vector3 _pos)
{
	LoadFile("Monster/Sheep.xml");
	SetLocalPos(_pos);
	maxHp = 8;
	PreInit();
	shaved = false;
	shavedTime = 0.f;
}

void Sheep::Update()
{
	PreUpdate();

	CheckWool();
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
	case MonsterState::HIT_NO_REACT:
		HitNoReact();
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

void Sheep::Render()
{
	Actor::Render();
}

void Sheep::RenderHierarchy()
{
	Actor::RenderHierarchy();
}

void Sheep::Release()
{
	Actor::Release();
}

void Sheep::Interact(int _itemid)
{
	switch (_itemid)
	{
	case 359:
	{
		if (not shaved)
		{
			shaved = true;
			Find("wool")->visible = false;
			ITEM_MANAGER->Spawn(Find("body")->GetWorldPos(), Item{ int(BlockType::WHITE_WOOL), (rand() % 2) + 2 });
			break;
		}
	}
	}
	return;
}

void Sheep::Idle()
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

void Sheep::Move()
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

void Sheep::Fall()
{
	if (FallingDown())
		HitByFallDown(int(passedTime * 10.f));
}

void Sheep::RunAway()
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

void Sheep::Follow()
{
	if (not DectectWheet(500.f)) {
		ChangeState(MonsterState::IDLE);
		leftTime = 1.f;
		return;
	}
	FollowPlayer();
}

void Sheep::CheckWool()
{
	if (shaved)
	{
		shavedTime += DELTA;
		if (shavedTime > 30.f)
		{
			shaved = false;
			shavedTime = 0.f;
			Find("wool")->visible = true;
		}
	}
}


