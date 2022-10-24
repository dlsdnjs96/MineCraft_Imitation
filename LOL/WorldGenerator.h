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
	//Int2 mapSize = { 32, 32 };
	Int2 mapSize = { 1024, 1024 };
	//Int2 mapSize = { 2048, 2048 };
	UI* ui;

public:
	WorldGenerator();

	void Update();
	void Render();
	void RenderHierarchy();
	void Release();

	void GenerateWorld();
	void HeightMap(int stage);
	void DecideClimate();

	template<typename T>
	vector<vector<T>> LerpMap(vector<vector<T>>& map);

	template<typename T>
	shared_ptr<Mesh> MapToMesh(vector<vector<T>>& map, T maxV);

};

