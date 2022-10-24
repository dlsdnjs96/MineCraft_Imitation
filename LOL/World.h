#pragma once


//struct Sector
//{
//	WorldBlock blocks[SECTOR_SIZE][WORLD_HEIGHT][SECTOR_SIZE];
//
//
//	Sector()
//	{
//		for (int x = 0; x < SECTOR_SIZE; x++)
//		{
//			for (int z = 0; z < SECTOR_SIZE; z++)
//			{
//				for (int y = 0; y < 3; y++)
//					blocks[x][y][z].blockType = BlockType::DIRT;
//				for (int y = 3; y < 10; y++)
//					blocks[x][y][z].blockType = BlockType::EMPTY;
//				for (int y = 10; y < WORLD_HEIGHT; y++)
//					blocks[x][y][z].blockType = BlockType::EMPTY;
//			}
//		}
//
//	}
//	void Save(BinaryWriter& out)
//	{
//        for (int x = 0; x < SECTOR_SIZE; x++)
//        {
//            for (int z = 0; z < SECTOR_SIZE; z++)
//            {
//                for (int y = 0; y < WORLD_HEIGHT; y++)
//                {
//                    out.Char(static_cast<char>(blocks[x][y][z].blockType));
//                }
//            }
//        }
//    }
//
//	void Load(BinaryReader& in)
//	{
//		for (int x = 0; x < SECTOR_SIZE; x++)
//		{
//			for (int z = 0; z < SECTOR_SIZE; z++)
//			{
//				for (int y = 0; y < WORLD_HEIGHT; y++)
//				{
//					blocks[x][y][z].blockType = static_cast<BlockType>(in.Char());
//					blocks[x][y][z].renderFace = 0;
//				}
//			}
//		}
//	}
//};

struct SectorCheck
{
	bool isVisited[SECTOR_SIZE][WORLD_HEIGHT][SECTOR_SIZE];
};

class World : public Singleton<World>
{
private:
	string name;

	unordered_map<int, unordered_map<int, Sector>> sector;
	unordered_map<int, unordered_map<int, Sector*>> activeSectors;

	Vector2 prevPos = { 100.f, 100.f };
	Actor* actor;


	UINT rbIndex;
	UINT idx;

public:
	void Init();
	void Update();
	bool RenderHierarchy();
	void Render();


	void LoadWorld();
	void SaveWorld();

	void CreateDumpBlocks();
	void distinguishSectors();
	void distinguishBlocks(Int3 from, int range);
	void UpdateMesh();
	

	WorldBlock GetBlock(Vector3 pos);
	WorldBlock GetBlock(Int3 pos);
	void SetBlock(Int3 pos, WorldBlock bt);
	void SetBlockType(Int3 pos, BlockType bt);
	void SetBlockDectec(Int3 pos, int bt);


	void SetCheck(Vector3& pos, bool chk);
	bool GetCheck(Vector3& pos);
};

