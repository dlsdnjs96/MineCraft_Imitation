#pragma once




class World : public Singleton<World>
{
private:

	unordered_map<int, unordered_map<int, Sector>> sector;
	unordered_map<int, unordered_map<int, Sector*>> activeSectors;

	Vector2 prevPos = { 100.f, 100.f };
	Actor* actor;



public:
	int		id;
	string	name = "";
	string	createdDate = "";
	string	lastConnected = "";


	void Init();
	void Update();
	bool RenderHierarchy();
	void PreRender();
	void Render();
	void Release();


	void LoadWorld();
	void SaveWorld();
	void LoadWorldBinary();
	void SaveWorldBinary();

	void CreateDumpBlocks();
	void distinguishSectors();
	void distinguishBlocks(Int3 from, int range);
	void distinguishBlock(Int3 from);
	void UpdateMesh();
	void UpdateMesh(Int3 _pos);
	

	WorldBlock GetBlock(Vector3 pos);
	WorldBlock GetBlock(Int3 pos);
	void SetBlock(Int3 pos, WorldBlock bt);
	void SetBlockType(Int3 pos, BlockType bt);
	void SetBlockDectec(Int3 pos, int bt);
};

