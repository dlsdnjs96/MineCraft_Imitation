#pragma once

#define BLOCK_LENGTH 10.f

enum class BlockType
{
	EMPTY = 0,
	GRASS = 1,
	WOOD = 2
};

struct Block
{
	BlockType	blockType;
	Vector3		position;
};

struct Sector
{
	BlockType blocks[10][130][10];
};

struct SectorCheck
{
	bool isVisited[10][127][10];
};

class World
{
private:
	map<int, map<int, Sector>> sector;
	map<int, map<int, SectorCheck>> sectorCheck;
	map<int, map<int, set<int>>> check;

	Actor* actor;
	Block rangedBlocks[10000];
	GameObject* Box;
	GameObject* bPool[10000];

	vector<Block> dectableBlocks;
	int dectableBlockIndex = 0;

	UINT rbIndex;
	UINT idx;

public:
	void Init();
	void Update();
	void UpdateSector(int iIdx, int jIdx, int kIdx);
	bool RenderHierarchy();
	void Render();


	void LoadWorld();
	void SaveWorld();


	void SelectDectableBlocks();
	void BlockToObject();
	

	BlockType GetBlock(Vector3 pos);
	void SetBlock(Vector3 pos, BlockType bt);
	void SetCheck(Vector3& pos, bool chk);
	bool GetCheck(Vector3& pos);
};

