#include "stdafx.h"

void MonsterManager::Init()
{
}

void MonsterManager::Release()
{
}

void MonsterManager::Update()
{
	if (prevSector != currSector) {
		distinguishSectors();
		currSector = { int((Camera::main->GetWorldPos().x / BLOCK_LENGTH) / SECTOR_SIZE), 0,
			int((Camera::main->GetWorldPos().z / BLOCK_LENGTH) / SECTOR_SIZE) };
	}


	for (auto& it : activeMonster)
	{
		auto iter = monsters[it.first][it.second].begin();
		while (iter != monsters[it.first][it.second].end())
		{
			(*iter)->Update();
			if (!((*iter)->isAlive)) {
				MONSTER_FACTORY->ReturnMonster(*iter);
				iter = monsters[it.first][it.second].erase(iter);
			}
			else ++iter;
		}
	}

	queue<Monster*> changedMonsters;
	for (auto& it : activeMonster)
	{
		for (auto iter = monsters[it.first][it.second].begin(); iter != monsters[it.first][it.second].end();)
		{
			if ((*iter)->prevSector.x == (*iter)->currSector.x
				&& (*iter)->prevSector.z == (*iter)->currSector.z) {
				++iter;
				continue;
			}

			changedMonsters.push(*iter);
			iter = monsters[it.first][it.second].erase(iter);
		}
	}

	while (not changedMonsters.empty())
	{
		Monster* temp = changedMonsters.front();
		changedMonsters.pop();
		temp->prevSector = temp->currSector;
		monsters[temp->currSector.x][temp->currSector.z].push_back(temp);
	}
}

void MonsterManager::RenderHierarchy()
{
	for (auto& it : monsters)
	{
		for (auto& it2 : it.second)
		{
			for (auto& it3 : it2.second)
				it3->RenderHierarchy();
		}
	}
}

void MonsterManager::Render()
{
	for (auto& it : monsters)
	{
		for (auto& it2 : it.second)
		{
			for (auto& it3 : it2.second)
				it3->Render();
		}
	}
}

void MonsterManager::distinguishSectors()
{
	activeMonster.clear();
	for (auto& it : monsters)
	{
		for (auto& it2 : it.second)
		{
			if (Vector2::Distance({ float(it.first) * BLOCK_LENGTH * SECTOR_SIZE, float(it2.first) * BLOCK_LENGTH * SECTOR_SIZE },
				{ Camera::main->GetWorldPos().x, Camera::main->GetWorldPos().z }) <= 3200.f)
				activeMonster.push_back({ it.first, it2.first });
		}
	}
}

void MonsterManager::Spawn(MonsterType _monsterType, Vector3 _pos)
{
	Monster* tMonster = MONSTER_FACTORY->GetMonster(_monsterType);
	
	switch (_monsterType)
	{
	case MonsterType::PIG:
		tMonster = dynamic_cast<Pig*>(tMonster);
		break;
	case MonsterType::COW:
		tMonster = dynamic_cast<Cow*>(tMonster);
		break;
	case MonsterType::CHICKEN:
		tMonster = dynamic_cast<Chicken*>(tMonster);
		break;
	case MonsterType::SHEEP:
		tMonster = dynamic_cast<Sheep*>(tMonster);
		break;
	case MonsterType::SKELETON:
		tMonster = dynamic_cast<SkeletonArcher*>(tMonster);
		break;
	case MonsterType::ZOMBIE:
		tMonster = dynamic_cast<Zombie*>(tMonster);
		break;
	}

	tMonster->Init(_pos);
	Int3 sector = (_pos / BLOCK_LENGTH) / SECTOR_SIZE;
	monsters[sector.x][sector.z].push_back(tMonster);
	//if (activeMonsters.find(sector.x) == activeMonsters.end()
	//	or activeMonsters.find(sector.x)->second.find(sector.z) == activeMonsters[sector.x].end())
	//	activeMonsters[sector.x][sector.z] = &monsters[sector.x][sector.z];
}

void MonsterManager::RemoveMonster(Int3& _int3, Monster* _monster)
{
	auto iter = monsters[_int3.x][_int3.z].begin();
	while (iter != monsters[_int3.x][_int3.z].end())
	{
		if ((*iter) == _monster) {
			iter = monsters[_int3.x][_int3.z].erase(iter);
			return;
		}
		++iter;
	}
	return;
}

void MonsterManager::AddMonster(Int3& _int3, Monster* _monster)
{
	monsters[_int3.x][_int3.z].push_back(_monster);
}

bool MonsterManager::AttackWithRay(Ray& _ray)
{
	Int3 centerSector;

	centerSector = (_ray.position / BLOCK_LENGTH) / SECTOR_SIZE;

	for (int x = centerSector.x - 1; x <= centerSector.x + 1; x++)
	{
		for (int z = centerSector.z - 1; z <= centerSector.z + 1; z++)
		{
			for (auto& it2 : monsters[x][z])
			{
				if (it2->collider and it2->collider->Intersect(_ray))
				{
					it2->HitByPlayer(90);
					return true;
				}
			}
		}
	}

	return false;
}

void MonsterManager::DropItem(MonsterType _monsterType, Vector3 _pos)
{
	switch (_monsterType)
	{
	case MonsterType::PIG:
		ITEM_MANAGER->Spawn(_pos, Item{ ITEM_MANAGER->GetItemId("porkchop_raw"), (rand() % 3) + 1});
		break;
	case MonsterType::COW:
		ITEM_MANAGER->Spawn(_pos, Item{ ITEM_MANAGER->GetItemId("beef_raw"), (rand() % 3) + 1 });
		ITEM_MANAGER->Spawn(_pos, Item{ ITEM_MANAGER->GetItemId("leather"), (rand() % 3) });
		break;
	case MonsterType::ZOMBIE:
		ITEM_MANAGER->Spawn(_pos, Item{ ITEM_MANAGER->GetItemId("rotten_flesh"), (rand() % 3) });
		break;
	case MonsterType::SHEEP:
		ITEM_MANAGER->Spawn(_pos, Item{ ITEM_MANAGER->GetItemId("mutton_raw"), (rand() % 3) + 1 });
		ITEM_MANAGER->Spawn(_pos, Item{ int(BlockType::WHITE_WOOL), 1 });
		break;
	case MonsterType::CHICKEN:
		ITEM_MANAGER->Spawn(_pos, Item{ ITEM_MANAGER->GetItemId("chicken_raw"), 1 });
		ITEM_MANAGER->Spawn(_pos, Item{ ITEM_MANAGER->GetItemId("feather"), rand() % 3 });
		break;
	}
}
