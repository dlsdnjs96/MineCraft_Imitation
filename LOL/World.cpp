#include "stdafx.h"

void World::Init()
{
	CreateDumpBlocks();
	distinguishBlocks({ 0, 0, 0 }, 1024);
}

void World::Update()
{
	const float updateRange = 200.f;
	Vector3 myPosition;




	static bool chk = true;

	if (INPUT->KeyDown(VK_F1))
			chk = true;

	if (chk) {
		chk = false;
		UpdateMesh();
		for (auto& it : sector)
		{
			for (auto& it2 : it.second) {
				it2.second.Update();
			}
		}
	}

	if (Vector2::Distance(prevPos, { Camera::main->GetWorldPos().x, Camera::main->GetWorldPos().z }) > 10.f * BLOCK_LENGTH) {
		distinguishSectors();
		prevPos = { Camera::main->GetWorldPos().x, Camera::main->GetWorldPos().z };
	}

	if (ImGui::Button("SaveWorld"))
		SaveWorld();

}



bool World::RenderHierarchy()
{
	actor->RenderHierarchy();
	return false;
}

void World::PreRender()
{
	for (auto& it : activeSectors)
	{
		for (auto& it2 : it.second) {
			it2.second->PreRender();
		}
	}

	return;
}

void World::Render()
{
	for (auto& it : activeSectors)
	{
		for (auto& it2 : it.second) {
			it2.second->Render();
		}
	}

	return;
}

void World::Release()
{
}

void World::LoadWorld()
{
	BinaryReader in;
	wstring path = L"../Contents/Map/" + Util::ToWString(name) + L"/map";
	UINT sectorSize = 0;

	in.Open(path);

	sectorSize = in.UInt();
	for (UINT i = 0; i < sectorSize; i++)
	{
		Int2 key = in.Int_2();
		sector[key.x][key.y].Load(in);
	}

	in.Close();
}

void World::SaveWorld()
{
	BinaryWriter out;
	wstring path = L"../Contents/Map/" + Util::ToWString(name) + L"/map";
	out.Open(path);

	UINT sectorSize = 0;

	sectorSize = 0;
	for (auto& it : sector) { for (auto& it2 : it.second) sectorSize++; }
	out.UInt(sectorSize);
	for (auto& it : sector)
	{
		for (auto& it2 : it.second) {
			out.Int_2(Int2{it.first, it2.first});
			it2.second.Save(out);
		}
	}
	out.Close();
}



void World::UpdateMesh()
{
	for (auto& it : sector)
	{
		for (auto& it2 : it.second) {
			it2.second.SetLocalPos({ float(it.first * BLOCK_LENGTH * SECTOR_SIZE), 0.5f * BLOCK_LENGTH, float(it2.first * BLOCK_LENGTH * SECTOR_SIZE) });
			it2.second.UpdateBlockMesh();
			it2.second.UpdateWaterMesh();
		}
	}
}

void World::CreateDumpBlocks()
{
	name = "testWorld";


	actor = Actor::Create();

	for (auto& it : sector)
	{
		for (auto& it2 : it.second) {
			it2.second.name = "("+to_string(it.first) + ", " + to_string(it2.first) + ")";
			actor->AddChild(dynamic_cast<GameObject*>(&it2.second));
		}
	}
}

void World::distinguishSectors()
{
	activeSectors.clear();
	for (auto& it : sector)
	{
		for (auto& it2 : it.second)
		{
			if (Vector2::Distance({ it2.second.GetWorldPos().x, it2.second.GetWorldPos().z }, 
				{ Camera::main->GetWorldPos().x, Camera::main->GetWorldPos().z }) <= SETTING->GetVisualRange())
				activeSectors[it.first][it2.first] = &(it2.second);
		}
	}
}

void World::distinguishBlocks(Int3 from, int range)
{

	for (int i = from.x - range; i <= from.x + range; i++)
	{
		for (int j = from.z - range; j <= from.z + range; j++)
		{
			for (int k = 1; k < WORLD_HEIGHT; k++)
			{
				//printf("%d %d %d : %d\r\n", i, k, j, GetBlock(Int3{ i, k, j }).blockType);

				if (GetBlock(Int3{ i, k, j }).blockType == BlockType::EMPTY)
					continue;

				if (GetBlock(Int3{ i, k, j }).blockType == BlockType::WATER)
				{
					int renderFace = 0;
					if (int(GetBlock(Int3{ i + 1, k, j }).blockType) >= 1000 || GetBlock(Int3{ i + 1, k, j }).blockType == BlockType::EMPTY)
						renderFace |= BLOCK_FACE_RIGHT;
					if (int(GetBlock(Int3{ i - 1, k, j }).blockType) >= 1000 || GetBlock(Int3{ i - 1, k, j }).blockType == BlockType::EMPTY)
						renderFace |= BLOCK_FACE_LEFT;
					if (int(GetBlock(Int3{ i, k + 1, j }).blockType) >= 1000 || GetBlock(Int3{ i, k + 1, j }).blockType == BlockType::EMPTY)
						renderFace |= BLOCK_FACE_UP;
					if (int(GetBlock(Int3{ i, k - 1, j }).blockType) >= 1000 || GetBlock(Int3{ i, k - 1, j }).blockType == BlockType::EMPTY)
						renderFace |= BLOCK_FACE_DOWN;
					if (int(GetBlock(Int3{ i, k, j + 1 }).blockType) >= 1000 || GetBlock(Int3{ i, k, j + 1 }).blockType == BlockType::EMPTY)
						renderFace |= BLOCK_FACE_BEHIND;
					if (int(GetBlock(Int3{ i, k, j - 1 }).blockType) >= 1000 || GetBlock(Int3{ i, k, j - 1 }).blockType == BlockType::EMPTY)
						renderFace |= BLOCK_FACE_FORWARD;

					if (renderFace)
						SetBlockDectec(Int3{ i, k, j }, renderFace);
				}
				else if (int(GetBlock(Int3{ i, k, j }).blockType) >= 2)
				{
					int renderFace = 0;
					if (int(GetBlock(Int3{ i + 1, k, j }).blockType) < 1000)
						renderFace |= BLOCK_FACE_RIGHT;
					if (int(GetBlock(Int3{ i - 1, k, j }).blockType) < 1000)
						renderFace |= BLOCK_FACE_LEFT;
					if (int(GetBlock(Int3{ i, k + 1, j }).blockType) < 1000)
						renderFace |= BLOCK_FACE_UP;
					if (int(GetBlock(Int3{ i, k - 1, j }).blockType) < 1000)
						renderFace |= BLOCK_FACE_DOWN;
					if (int(GetBlock(Int3{ i, k, j + 1 }).blockType) < 1000)
						renderFace |= BLOCK_FACE_BEHIND;
					if (int(GetBlock(Int3{ i, k, j - 1 }).blockType) < 1000)
						renderFace |= BLOCK_FACE_FORWARD;

					if (renderFace)
						SetBlockDectec(Int3{ i, k, j }, renderFace);
				}
			
			}
		}
	}
}





WorldBlock World::GetBlock(Vector3 pos)
{
	return GetBlock(Int3(pos / BLOCK_LENGTH));
}

WorldBlock World::GetBlock(Int3 pos)
{
	int sectorX, sectorZ;
	int blockX, blockZ;

	if (pos.x >= 0.f) {
		sectorX = int(pos.x / SECTOR_SIZE);
		blockX = pos.x % SECTOR_SIZE;
	}
	else {
		sectorX = int((pos.x - SECTOR_SIZE + 0.00001f) / SECTOR_SIZE);
		blockX = int((pos.x - (floor(float(pos.x) / SECTOR_SIZE) * SECTOR_SIZE)));
	}
	if (pos.z >= 0.f) {
		sectorZ = int(pos.z / SECTOR_SIZE);
		blockZ = pos.z % SECTOR_SIZE;
	}
	else {
		sectorZ = int((pos.z - SECTOR_SIZE + 0.00001f) / SECTOR_SIZE);
		blockZ = int((pos.z - (floor(float(pos.z) / SECTOR_SIZE) * SECTOR_SIZE)));
	}

	return sector[sectorX][sectorZ].blocks[blockX][pos.y % WORLD_HEIGHT][blockZ];
}

void World::SetBlock(Int3 pos, WorldBlock bt)
{
	int sectorX, sectorZ;
	int blockX, blockZ;

	if (pos.x >= 0.f) {
		sectorX = int(pos.x / SECTOR_SIZE);
		blockX = pos.x % SECTOR_SIZE;
	}
	else {
		sectorX = int((pos.x - SECTOR_SIZE + 0.00001f) / SECTOR_SIZE);
		blockX = int((pos.x - (floor(float(pos.x) / SECTOR_SIZE) * SECTOR_SIZE)));
	}
	if (pos.z >= 0.f) {
		sectorZ = int(pos.z / SECTOR_SIZE);
		blockZ = pos.z % SECTOR_SIZE;
	}
	else {
		sectorZ = int((pos.z - SECTOR_SIZE + 0.00001f) / SECTOR_SIZE);
		blockZ = int((pos.z - (floor(float(pos.z) / SECTOR_SIZE) * SECTOR_SIZE)));
	}

	sector[sectorX][sectorZ].blocks[blockX][pos.y % WORLD_HEIGHT][blockZ] = bt;

	return;
}

void World::SetBlockType(Int3 pos, BlockType bt)
{
	int sectorX, sectorZ;
	int blockX, blockZ;

	if (pos.x >= 0.f) {
		sectorX = int(pos.x / SECTOR_SIZE);
		blockX = pos.x % SECTOR_SIZE;
	}
	else {
		sectorX = int((pos.x + 0.00001f) / SECTOR_SIZE);
		blockX = int((pos.x - (floor(float(pos.x) / SECTOR_SIZE) * SECTOR_SIZE)));
	}
	if (pos.z >= 0.f) {
		sectorZ = int(pos.z / SECTOR_SIZE);
		blockZ = pos.z % SECTOR_SIZE;
	}
	else {
		sectorZ = int((pos.z - SECTOR_SIZE + 0.00001f) / SECTOR_SIZE);
		blockZ = int((pos.z - (floor(float(pos.z) / SECTOR_SIZE) * SECTOR_SIZE)));
	}

	sector[sectorX][sectorZ].blocks[blockX][pos.y % WORLD_HEIGHT][blockZ].blockType = bt;

	return;
}

void World::SetBlockDectec(Int3 pos, int bt)
{
	//printf("%d %d %d : %d\r\n", pos.x, pos.y, pos.z, bt);
	int sectorX, sectorZ;
	int blockX, blockZ;

	if (pos.x >= 0.f) {
		sectorX = int(pos.x / SECTOR_SIZE);
		blockX = pos.x % SECTOR_SIZE;
	}
	else {
		sectorX = int((pos.x - SECTOR_SIZE + 0.00001f) / SECTOR_SIZE);
		blockX = int((pos.x - (floor(float(pos.x) / SECTOR_SIZE) * SECTOR_SIZE)));
	}
	if (pos.z >= 0.f) {
		sectorZ = int(pos.z / SECTOR_SIZE);
		blockZ = pos.z % SECTOR_SIZE;
	}
	else {
		sectorZ = int((pos.z - SECTOR_SIZE + 0.00001f) / SECTOR_SIZE);
		blockZ = int((pos.z - (floor(float(pos.z) / SECTOR_SIZE) * SECTOR_SIZE)));
	}

	sector[sectorX][sectorZ].blocks[blockX][pos.y % WORLD_HEIGHT][blockZ].renderFace = bt;
	

	return;
}

