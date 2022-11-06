#pragma once


enum class Climate
{
	FREEZE_CLIMATE = 0,
	ICE_CLIMATE = 1,
	COLD_CLIMATE = 2,
	WARM_CLIMATE = 3,
	HOT_CLIMATE = 4,
	MELT_CLIMATE = 5
};

class WorldGenerator : public Singleton<WorldGenerator>
{
private:
	//Int2 mapSize = { 4096, 4096 };
	//Int2 mapSize = { 512, 512 };
	Int2 mapSize = { 32, 32 };
	//Int2 mapSize = { 1024, 1024 };
	//Int2 mapSize = { 2048, 2048 };
	vector<vector<char>> heightMap[2];
	vector<vector<bool>> riverMap[2];
	vector<vector<char>> treeMap;

	int loadingStage = 0;
	function<void(WorldGenerator&)> loadingFunction = nullptr;
public:
	UI* ui;

	WorldGenerator();

	void Init();
	void Update();
	void Render();
	void RenderHierarchy();
	void Release();

	void GenerateWorld();
	void HeightMap();
	void TreeMap();
	void RiverMap();

	void MapToWorld();

	void HeightToMesh(vector<vector<char>>& map);
	void RiverToMesh(vector<vector<bool>>& map);

	template<typename T>
	vector<vector<T>> LerpMap(vector<vector<T>>& map);

	shared_ptr<Mesh> MapToMesh();

};

