#include "stdafx.h"

void World::Init()
{

	for (float i = -10; i < 10; i++)
	{
		for (float j = -10; j < 10; j++)
		{
			for (float k = 0; k < 2; k++)
				SetBlock({ i, k, j }, BlockType::GRASS);
			for (float k = 2; k < 20; k++)
				SetBlock({ i, k, j }, BlockType::EMPTY);
		}
	}
	

	actor = Actor::Create();
	actor->scale = { 3.f, 3.f, 3.f };
	for (int i = 0; i < 10000; i++) {
		bPool[i] = GameObject::Create(to_string(i));
		bPool[i]->scale = { 3.f, 3.f, 3.f };
		bPool[i]->mesh = make_shared<Mesh>();
		bPool[i]->mesh = RESOURCE->meshes.Load("1.BoxCollider.mesh");
		bPool[i]->shader = make_shared<Shader>();
		bPool[i]->shader = RESOURCE->shaders.Load("block.hlsl");
		bPool[i]->material = make_shared<Material>();
		bPool[i]->material = RESOURCE->materials.Load("test.mtl");
		actor->AddChild(bPool[i]);
	}
	Box = GameObject::Create("box");
	Box->mesh = make_shared<Mesh>();
	Box->mesh = RESOURCE->meshes.Load("1.BoxCollider.mesh");
	Box->shader = make_shared<Shader>();
	Box->shader = RESOURCE->shaders.Load("block.hlsl");
	Box->material = make_shared<Material>();
	Box->material = RESOURCE->materials.Load("test.mtl");
	actor->AddChild(Box);

	dectableBlocks.resize(10000);
}

void World::Update()
{
	const float updateRange = 200.f;
	Vector3 myPosition;

	idx = 0;
	rbIndex = 0;
	//visibleBlocks.clear();
	//for (int i = 0; i < 1; i++)
	//{
	//	for (int j = 0; j < 1; j++) {
	//		for (int k = 0;k < 4;k++)
	//			UpdateSector(i ,j , k);
	//	}
	//}
	SelectDectableBlocks();
	//SelectVisibleBlocks();
	BlockToObject();
	//actor->Update();
}

void World::UpdateSector(int iIdx, int jIdx, int kIdx)
{
	//Sector* tSector = sector[kIdx][iIdx][jIdx];
	//Vector3 pos = { iIdx * 100.f, 0.f, jIdx * 100.f };
	//Vector3 way = { 1.f, 1.f, 1.f };
	//Vector3 tempBlock;

	//way.x = kIdx < 2 ? 1.f : -1.f;
	//way.z = kIdx%2 == 0 ? 1.f : -1.f;
	//Matrix camMatrix = Camera::main->view * Camera::main->proj;

	//for (int i = 0; i < 10; i++)
	//{
	//	for (int j = 0; j < 10; j++)
	//	{
	//		for (int k = 0; k < 127; k++)
	//		{
	//			if (tSector->blocks[i][j][k] != BlockType::EMPTY)
	//			{
	//				tempBlock = { (pos.x + (i * BLOCK_LENGTH)) * way.x, (float)k * BLOCK_LENGTH, (pos.z + (j * BLOCK_LENGTH)) * way.z };

	//				if (Util::IsInScreen(tempBlock, camMatrix)) {
	//					rangedBlocks[rbIndex].blockType = tSector->blocks[i][j][k];
	//					rangedBlocks[rbIndex].position = tempBlock;
	//					//visibleBlocks.push_back(&rangedBlocks[rbIndex]);
	//					rbIndex++;
	//				}
	//			}
	//		}
	//	}
	//}
}


void World::RenderHierarchy()
{
	for (int i = 0; i < idx; i++)
		bPool[i]->RenderHierarchy();
}

void World::Render()
{
	for (int i = 0; i < idx; i++)
		bPool[i]->Render();
}


void World::SelectVisibleBlocks()
{
	auto it = visibleBlocks.begin();
	Vector3 HitPoint;
	Ray ray;
	while (it != visibleBlocks.end())
	{
		auto it2 = it;
		it2++;
		while (it2 != visibleBlocks.end() and idx < 10000)
		{
			//Box->SetLocalPos((*it2)->position);
			Box->Update();
			ray.position = Camera::main->GetWorldPos();
			ray.direction = Box->GetWorldPos() - Camera::main->GetWorldPos();
			ray.direction.Normalize();
			if (Util::RayIntersectTri(ray, Box, HitPoint))
			{
				if (Vector3::Distance(HitPoint, ray.position) > Vector3::Distance(Box->GetWorldPos(), ray.position))
				{
					//visibleBlocks.erase(it2++);
					//(*it2)->blockType = BlockType::WOOD;
					//continue;
				}
			}
			it2++;
		}
		it++;
	}
}

void World::SelectDectableBlocks()
{
	Vector3 startPosition = Camera::main->GetWorldPos();
	Vector3 currentPos;
	Block block;
	BlockType blockType;
	vector<Vector3> stack;
	stack.resize(1000);

	dectableBlocks.clear();
	stack.push_back({float(int(startPosition.x)), float(int(startPosition.y)) , float(int(startPosition.z)) });
	ImGui::Text((to_string(startPosition.x) + " " + to_string(startPosition.y) + " " + to_string(startPosition.z)).c_str());

	while (!stack.empty())
	{
		currentPos = stack.back();
		stack.pop_back();

		blockType = GetBlock(currentPos);

		//ImGui::Text((to_string(currentPos.x) + " " + to_string(currentPos.y) + " " + to_string(currentPos.z) + " " + to_string(int(blockType))).c_str());

		if (GetCheck(currentPos) || Vector3::Distance(currentPos, startPosition) > 10.f || currentPos.y > 100 || currentPos.y < 0)
		{
			continue;
		} 
		else if (blockType != BlockType::EMPTY)
		{
			block.position = currentPos;
			block.blockType = blockType;
			dectableBlocks.push_back(block);
		}
		else
		{
			stack.push_back({ currentPos.x + 1, currentPos .y, currentPos.z });
			stack.push_back({ currentPos.x - 1, currentPos .y, currentPos.z });
			stack.push_back({ currentPos.x, currentPos .y + 1, currentPos.z });
			stack.push_back({ currentPos.x, currentPos .y - 1, currentPos.z });
			stack.push_back({ currentPos.x, currentPos .y, currentPos.z + 1 });
			stack.push_back({ currentPos.x, currentPos .y, currentPos.z - 1 });
		}

		SetCheck(currentPos, true);
	}

	stack.push_back(startPosition);
	while (!stack.empty())
	{
		currentPos = stack.back();
		stack.pop_back();

		if (GetCheck(currentPos))
		{
			stack.push_back({ currentPos.x + 1, currentPos.y, currentPos.z });
			stack.push_back({ currentPos.x - 1, currentPos.y, currentPos.z });
			stack.push_back({ currentPos.x, currentPos.y + 1, currentPos.z });
			stack.push_back({ currentPos.x, currentPos.y - 1, currentPos.z });
			stack.push_back({ currentPos.x, currentPos.y, currentPos.z + 1 });
			stack.push_back({ currentPos.x, currentPos.y, currentPos.z - 1 });
		}

		SetCheck(currentPos, false);
	}
	printf("%d\r\n", dectableBlocks.size());
}

void World::BlockToObject()
{
	idx = 0;
	//auto it = visibleBlocks.begin();

	//while (it != visibleBlocks.end() and idx < 10000)
	//{
	//	if ((*it)->blockType == BlockType::GRASS)
	//		bPool[idx]->shader = RESOURCE->shaders.Load("Block.hlsl");
	//	else
	//		bPool[idx]->shader = RESOURCE->shaders.Load("Block2.hlsl");
	//	bPool[idx]->SetLocalPos((*it)->position);
	//	bPool[idx]->Update();
	//	idx++;
	//	it++;
	//}

	for (int i = 0; i < dectableBlocks.size();i++)
	{
		bPool[idx]->SetLocalPos({ dectableBlocks[i].position.x * BLOCK_LENGTH, dectableBlocks[i].position.y * BLOCK_LENGTH, dectableBlocks[i].position.z * BLOCK_LENGTH});
		bPool[idx]->Update();
		idx++;
	}
}

BlockType World::GetBlock(Vector3& pos)
{
	return sector[int(pos.x / 10)][int(pos.z / 10)].blocks[abs((int)(pos.x) % 10)][(int)pos.y][abs((int)pos.z % 10)];
}

void World::SetBlock(Vector3 pos, BlockType bt)
{
	sector[int(pos.x / 10)][int(pos.z / 10)].blocks[abs((int)(pos.x) % 10)][(int)pos.y][abs((int)pos.z % 10)] = bt;
}

void World::SetCheck(Vector3& pos, bool chk)
{
	sectorCheck[int(pos.x / 10)][int(pos.z / 10)].isVisited[abs((int)(pos.x) % 10)][(int)pos.y][abs((int)pos.z % 10)] = chk;
}

bool World::GetCheck(Vector3& pos)
{
	return sectorCheck[int(pos.x / 10)][int(pos.z / 10)].isVisited[abs((int)(pos.x) % 10)][(int)pos.y][abs((int)pos.z % 10)];
}