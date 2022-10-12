#include "stdafx.h"

void World::Init()
{
	int range = 100;
	for (float i = -range; i < range; i++)
	{
		for (float j = -range; j < range; j++)
		{
			for (float k = 0; k < 2; k++)
				SetBlock({ i, k, j }, BlockType::GRASS);
			for (float k = 2; k < 9; k++)
				SetBlock({ i, k, j }, BlockType::EMPTY);
			for (float k = 9; k < 10; k++)
				SetBlock({ i, k, j }, BlockType::GRASS);
			for (float k = 10; k < 20; k++)
				SetBlock({ i, k, j }, BlockType::EMPTY);
		}
	}

	float arr[10][2] = { {1, 3}, {11, 3}, {5, 2}, {3, 7}, {-6, 3}, {4, -3}, {-5, -5}, {-16, -4}, {-11, -22}, {-21, 13} };
	for (int i = 0; i < 10; i++)
	{
		for (float j = 0;j <10;j++)
			SetBlock({ arr[i][0], j, arr[i][1] }, BlockType::WOOD);
	}


	actor = Actor::Create();
	actor->scale = { 3.f, 3.f, 3.f };
	for (int i = 0; i < 10000; i++) {
		bPool[i] = GameObject::Create(to_string(i));
		bPool[i]->scale = { 5.f, 5.f, 5.f };
		bPool[i]->mesh = make_shared<Mesh>();
		//bPool[i]->mesh = RESOURCE->meshes.Load("1.BoxCollider.mesh");
		bPool[i]->mesh = RESOURCE->meshes.Load("TestCube.mesh");
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
	actor->AddChild(Camera::main);

	dectableBlocks.resize(100000);
}

void World::Update()
{
	const float updateRange = 200.f;
	Vector3 myPosition;

	rbIndex = 0;

	static Vector3 prev = { 100.f, 100.f, 100.f };

	if (Vector3::Distance(prev, Camera::main->GetWorldPos()) > 5.f * BLOCK_LENGTH) {
		printf("SelectDectableBlocks\r\n");
		SelectDectableBlocks();
		prev = Camera::main->GetWorldPos();
	}
	BlockToObject();
	

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


bool World::RenderHierarchy()
{
	ImGui::PushID(this);
	if (ImGui::TreeNode("World"))
	{
		if (ImGui::IsItemToggledOpen() or
			ImGui::IsItemClicked())
		{
			GUI->target = actor;
		}
		if (ImGui::Button("addChild"))
		{
			ImGui::OpenPopup("childName");
		}
		if (ImGui::BeginPopup("childName"))
		{
			static char childName[32] = "None";
			ImGui::InputText("childName", childName, 32);
			if (ImGui::Button("G.O"))
			{
				actor->AddChild(GameObject::Create(childName));
			}
			ImGui::SameLine();
			if (ImGui::Button("Actor"))
			{
				actor->AddChild(Actor::Create(childName));
			}
			ImGui::SameLine();
			if (ImGui::Button("Camera"))
			{
				actor->AddChild(Camera::Create(childName));
			}
			ImGui::SameLine();
			if (ImGui::Button("Terrain"))
			{
				actor->AddChild(Terrain::Create(childName));
			}
			ImGui::SameLine();
			if (ImGui::Button("UI"))
			{
				actor->AddChild(UI::CreateChild(childName));
			}
			ImGui::EndPopup();
		}

		ImGui::SameLine();
		if (ImGui::Button("delete"))
		{
			actor->root->DeleteObject(actor->name);
			GUI->target = nullptr;
			ImGui::TreePop();
			ImGui::PopID();
			return true; //하위자식까지는 접근하지 않기
		}
		// l->r
		for (int i = 0; i < idx; i++)
		{
			if (bPool[i]->RenderHierarchy())
			{
				ImGui::TreePop();
				ImGui::PopID();
				GUI->target = nullptr;
				return true;
			}
		}
		ImGui::TreePop();
	}
	ImGui::PopID();
	return false;
}

void World::Render()
{
	for (int i = 0; i < idx; i++)
		bPool[i]->Render();
}

void World::LoadWorld()
{
}

void World::SaveWorld()
{
}


void World::BlockToObject()
{
	Matrix camMatrix = Camera::main->view * Camera::main->proj;

	idx = 0;
	for (int i = 0; i < dectableBlockIndex; i++)
	{
		if (Util::IsInScreen(dectableBlocks[i].position, camMatrix)) {
			bPool[idx]->SetLocalPos(dectableBlocks[i].position);
			bPool[idx]->material = RESOURCE->materials.Load("Blocks/"+to_string(int(dectableBlocks[i].blockType)) + ".mtl");
			bPool[idx]->Update();
			idx++;
		}
	}
}

void World::SelectDectableBlocks()
{
	Vector3 startPosition = Camera::main->GetWorldPos();
	Vector3 currentPos;
	Block block;
	BlockType blockType;
	vector<Vector3> stack;
	const float visibleRange = 20;

	ImGui::Text(("Cam : "+to_string(startPosition.x) + " " + to_string(startPosition.y) + " " + to_string(startPosition.z)).c_str());

	startPosition.x = int(startPosition.x / BLOCK_LENGTH);
	startPosition.y = int(startPosition.y / BLOCK_LENGTH);
	startPosition.z = int(startPosition.z / BLOCK_LENGTH);

	dectableBlockIndex = 0;


	for (float i = startPosition.x - visibleRange; i < startPosition.x + visibleRange; i++)
	{
		currentPos.x = i;
		for (float j = startPosition.z - visibleRange; j < startPosition.z + visibleRange; j++)
		{
			currentPos.z = j;
			for (float k = 1; k < 53; k++)
			{
				currentPos.y = k;
				if (GetBlock(currentPos) == BlockType::EMPTY)
					continue;
				//if (GetBlock({ i + 1, k, j }) == BlockType::EMPTY
				//	or GetBlock({ i - 1, k, j }) == BlockType::EMPTY
				//	or GetBlock({ i, k + 1, j }) == BlockType::EMPTY
				//	or GetBlock({ i, k - 1, j }) == BlockType::EMPTY
				//	or GetBlock({ i, k, j + 1 }) == BlockType::EMPTY
				//	or GetBlock({ i, k, j - 1 }) == BlockType::EMPTY)
				{
					dectableBlocks[dectableBlockIndex].position = { currentPos.x * BLOCK_LENGTH, currentPos.y * BLOCK_LENGTH, currentPos.z * BLOCK_LENGTH };
					dectableBlocks[dectableBlockIndex].blockType = GetBlock(currentPos);
					dectableBlockIndex++;
				}
			}
		}
	}

	return;

	//dectableBlocks.clear();
	stack.push_back(startPosition);

	while (!stack.empty())
	{
		currentPos = stack.back();
		stack.pop_back();

		//ImGui::Text((to_string(currentPos.x) + " " + to_string(currentPos.y) + " " + to_string(currentPos.z) + " " + to_string(int(blockType))).c_str());

		if (GetCheck(currentPos) || abs(currentPos.x - startPosition.x) > 10.f || abs(currentPos.z - startPosition.z) > 10.f || currentPos.y > 12 || currentPos.y < 0)
			continue;
		
		blockType = GetBlock(currentPos);
		if (blockType != BlockType::EMPTY)
		{
			dectableBlocks[dectableBlockIndex].position = currentPos;
			dectableBlocks[dectableBlockIndex].blockType = blockType;
			dectableBlockIndex++;
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

	check.clear();
	return;
}





BlockType World::GetBlock(Vector3 pos)
{
	return sector[int(pos.x / 10)][int(pos.z / 10)].blocks[abs((int)(pos.x) % 10)][(int)pos.y][abs((int)pos.z % 10)];
}

void World::SetBlock(Vector3 pos, BlockType bt)
{
	sector[int(pos.x / 10)][int(pos.z / 10)].blocks[abs((int)(pos.x) % 10)][(int)pos.y][abs((int)pos.z % 10)] = bt;
}

//void World::SetCheck(Vector3& pos, bool chk)
//{
//	sectorCheck[int(pos.x / 10)][int(pos.z / 10)].isVisited[abs((int)(pos.x) % 10)][(int)pos.y][abs((int)pos.z % 10)] = chk;
//}
//
//bool World::GetCheck(Vector3& pos)
//{
//	return sectorCheck[int(pos.x / 10)][int(pos.z / 10)].isVisited[abs((int)(pos.x) % 10)][(int)pos.y][abs((int)pos.z % 10)];
//}

void World::SetCheck(Vector3& pos, bool chk)
{
	check[int(pos.x)][int(pos.z)].insert(int(pos.y));
}

bool World::GetCheck(Vector3& pos)
{
	return check[int(pos.x)][int(pos.z)].find(int(pos.y)) != check[int(pos.x)][int(pos.z)].end();
}