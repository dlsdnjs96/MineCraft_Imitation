#include "stdafx.h"

Cow::Cow()
{
	type = MonsterType::COW;
	kind = "cow";
}

void Cow::Init(Vector3 _pos)
{
	LoadFile("Monster/Cow.xml");
	SetLocalPos(_pos);
	maxHp = 10;
	PreInit();
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
	case MonsterState::FOLLOW:
		Follow();
		break;
	case MonsterState::HIT:
		Hit();
		break;
	case MonsterState::HIT_NO_REACT:
		HitNoReact();
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

void Cow::Interact(int _itemid)
{
}

void Cow::Idle()
{
	CheckFloor();

	if (leftTime <= 0.f)
	{
		ChangeState(MonsterState::MOVE);
		leftTime = (float(rand() % 30) * 0.1f) + 1.f;
		rotation.y = float(float(rand() % 31415) * 0.0001f);
		SOUND->Play("hitCow", Vector3::Distance(GetWorldPos(), PlayerModel::user->GetWorldPos()));
		return;
	}
	if (DectectWheet(500.f))
		ChangeState(MonsterState::FOLLOW);
	
}

void Cow::Move()
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

void Cow::Jump()
{
}

void Cow::Fall()
{
	if (FallingDown())
		HitByFallDown(int(passedTime * 10.f));
}

void Cow::RunAway()
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

void Cow::Follow()
{
	if (not DectectWheet(500.f)) {
		ChangeState(MonsterState::IDLE);
		leftTime = 1.f;
		return;
	}
	FollowPlayer();
}
