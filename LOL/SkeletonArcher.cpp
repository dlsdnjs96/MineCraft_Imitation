#include "stdafx.h"

SkeletonArcher::SkeletonArcher()
{
}

void SkeletonArcher::Init(Vector3 _pos)
{
	LoadFile("Monster/Skeleton.xml");
	SetLocalPos(_pos);
	maxHp = 20;
	PreInit();
}

void SkeletonArcher::Update()
{
}

void SkeletonArcher::Render()
{
}

void SkeletonArcher::RenderHierarchy()
{
}

void SkeletonArcher::Release()
{
}

void SkeletonArcher::Interact(int _itemid)
{
}

void SkeletonArcher::Idle()
{
}

void SkeletonArcher::Move()
{
}

void SkeletonArcher::Fall()
{
}

void SkeletonArcher::Follow()
{
}

void SkeletonArcher::Attack()
{
}
