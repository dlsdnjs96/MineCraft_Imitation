#include "stdafx.h"

Monster* MonsterFactory::GetMonster(MonsterType _monsterType)
{
	Monster* tMonster = nullptr;

	switch (_monsterType)
	{
	case MonsterType::PIG:
		if (pigs.empty())
			return new Pig();
		tMonster = pigs.back();
		pigs.pop();
		break;
	case MonsterType::COW:
		if (cows.empty())
			return new Cow();
		tMonster = cows.back();
		cows.pop();
		break;
	case MonsterType::SHEEP:
		if (sheeps.empty())
			return new Sheep();
		tMonster = sheeps.back();
		sheeps.pop();
		break;
	case MonsterType::CHICKEN:
		if (chickens.empty())
			return new Chicken();
		tMonster = chickens.back();
		chickens.pop();
		break;
	case MonsterType::SKELETON:
		if (skeletons.empty())
			return new SkeletonArcher();
		tMonster = skeletons.back();
		skeletons.pop();
		break;
	case MonsterType::ZOMBIE:
		if (zombies.empty())
			return new Zombie();
		tMonster = zombies.back();
		zombies.pop();
		break;
	case MonsterType::SPIDER:
		if (spiders.empty())
			return new Spider();
		tMonster = spiders.back();
		spiders.pop();
		break;
	}

	return tMonster;
}

void MonsterFactory::ReturnMonster(Monster* _monster)
{
	switch (_monster->type)
	{
	case MonsterType::PIG:
		pigs.push(dynamic_cast<Pig*>(_monster));
		break;
	case MonsterType::COW:
		cows.push(dynamic_cast<Cow*>(_monster));
		break;
	case MonsterType::SHEEP:
		sheeps.push(dynamic_cast<Sheep*>(_monster));
		break;
	case MonsterType::CHICKEN:
		chickens.push(dynamic_cast<Chicken*>(_monster));
		break;
	case MonsterType::SKELETON:
		skeletons.push(dynamic_cast<SkeletonArcher*>(_monster));
		break;
	case MonsterType::ZOMBIE:
		zombies.push(dynamic_cast<Zombie*>(_monster));
		break;
	case MonsterType::SPIDER:
		spiders.push(dynamic_cast<Spider*>(_monster));
		break;
	}
}
