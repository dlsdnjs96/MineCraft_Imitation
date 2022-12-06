#include "stdafx.h"

void World::Init()
{
	CreateDumpBlocks();
	distinguishBlocks({ 0, 0, 0 }, 64);
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
	LoadWorldBinary();
	DATABASE->LoadWolrd();
	DATABASE->LoadPlayer();
	DATABASE->LoadInventory();
	DATABASE->LoadItemObject();
	DATABASE->LoadMonster();
	CreateDumpBlocks();
	distinguishBlocks({ 0, 0, 0 }, 64);
}

void World::SaveWorld()
{
	SaveWorldBinary();
	DATABASE->UpdateWolrd();
	DATABASE->SavePlayer();
	DATABASE->SaveInventory();
	DATABASE->SaveItemObject();
	DATABASE->SaveMonster();
	DATABASE->SaveFurnace();
}

void World::LoadWorldBinary()
{
	BinaryReader in;
	wstring path = L"../Contents/Map/" + Util::ToWString(name) + L"/map";
	UINT sectorSize = 0;

	in.Open(path);

	sectorSize = in.UInt();
	sector.clear();
	for (UINT i = 0; i < sectorSize; i++)
	{
		Int2 key = in.Int_2();
		sector[key.x][key.y].Load(in);
	}

	in.Close();
}

void World::SaveWorldBinary()
{
	BinaryWriter out;
	wstring path = L"../Contents/Map/" + Util::ToWString(name) + L"/map";
	filesystem::create_directory("../Contents/Map/" + name);
	out.Open(path);

	UINT sectorSize = 0;

	sectorSize = 0;
	for (auto& it : sector) { for (auto& it2 : it.second) sectorSize++; }
	out.UInt(sectorSize);

	for (auto& it : sector)
	{
		for (auto& it2 : it.second) {
			out.Int_2(Int2{ it.first, it2.first });
			it2.second.Save(out);
						//if (it2.second.blocks[i][j][k].blockType != BlockType::AIR)
						//	out.Int_4(Int4{ (it.first * 10) + i, j, (it2.first * 10) + k, int(it2.second.blocks[i][j][k].blockType) });
				
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

void World::UpdateMesh(Int3 _pos)
{
	int sectorX, sectorZ;

	if (_pos.x >= 0.f)
		sectorX = int(_pos.x / SECTOR_SIZE);
	else 
		sectorX = int((_pos.x - SECTOR_SIZE + 0.00001f) / SECTOR_SIZE);

	if (_pos.z >= 0.f)
		sectorZ = int(_pos.z / SECTOR_SIZE);
	else 
		sectorZ = int((_pos.z - SECTOR_SIZE + 0.00001f) / SECTOR_SIZE);

	//distinguishBlocks(pos, 5);
	//distinguishBlocks({ 0, 0, 0 }, 64);
	distinguishBlock(_pos);
	distinguishBlock(_pos + Int3{ 1, 0, 0 });
	distinguishBlock(_pos + Int3{ -1, 0, 0 });
	distinguishBlock(_pos + Int3{ 0, 1, 0 });
	distinguishBlock(_pos + Int3{ 0, -1, 0 });
	distinguishBlock(_pos + Int3{ 0, 0, 1 });
	distinguishBlock(_pos + Int3{ 0, 0, -1 });

	sector[sectorX][sectorZ].UpdateBlockMesh();
	sector[sectorX][sectorZ].UpdateWaterMesh();

}

void World::CreateDumpBlocks()
{


	actor = Actor::Create("World");

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
				if (GetBlock(Int3{ i, k, j }).blockType == BlockType::AIR)
					continue;

				distinguishBlock(Int3{ i, k, j });
			}
		}
	}
}

void World::distinguishBlock(Int3 from)
{
	const Int3 sixPos[6] = { {0, 1, 0}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0}, {0, 0, 1}, {0, 0, -1} };
	const int sixFaces[6] = { BLOCK_FACE_UP, BLOCK_FACE_DOWN, BLOCK_FACE_RIGHT, BLOCK_FACE_LEFT, BLOCK_FACE_BEHIND, BLOCK_FACE_FORWARD };

	if (GetBlock(from).blockType == BlockType::STILL_WATER)
	{
		int renderFace = 0;

		for (int i = 0; i < 6; i++) {
			if (unsigned char(GetBlock(from + sixPos[i]).blockType) >= 10 || GetBlock(from + sixPos[i]).blockType == BlockType::AIR)
				renderFace |= sixFaces[i];
		}

		SetBlockDectec(from, renderFace);
	}
	else if (GetBlock(from).blockType > BlockType::STILL_WATER)
	{
		int renderFace = 0;

		for (int i = 0; i < 6; i++) {
			Int3 temp = from + sixPos[i];
			if (unsigned char(GetBlock(from + sixPos[i]).blockType) < 10)
				renderFace |= sixFaces[i];
			if (unsigned char(GetBlock(from + sixPos[i]).blockType) > 10)
				renderFace |= sixFaces[i];
		}

		SetBlockDectec(from, renderFace);
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

	sector[sectorX][sectorZ].blocks[blockX][pos.y][blockZ].blockType = bt;

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

