#pragma once


enum class ClimateType
{
	ICE_CLIMATE = 1,
	COLD_CLIMATE = 2,
	MEDIUM_CLIMATE = 3,
	WARM_CLIMATE = 4,
	HOT_CLIMATE = 5
};
enum class BiomeType
{
	TUNDRA			= 1,
	TUNDRA_OF_SNOW	= 2,
	FOREST			= 3,
	FOREST_DARK		= 4,
	MOUNTAIN		= 5,
	PLAIN			= 6,
	FOREST_BIRCH	= 7,
	DESERT			= 8,
	SAVANA			= 9,
	JUNGLE			= 10,
	TAIGA			= 11
};

class WorldGenerator : public Singleton<WorldGenerator>
{
private:
	//Int2 mapSize = { 4096, 4096 };
	//Int2 mapSize = { 128, 128 };
	//Int2 mapSize = { 32, 32 };
	Int2 mapSize = { 1024, 1024 };
	//Int2 mapSize = { 2048, 2048 };
	vector<vector<char>> oceanMap[2];
	vector<vector<char>> climateMap[2];
	vector<vector<char>> biomeMap;
	vector<vector<char>> heightMap[2];
	vector<vector<bool>> riverMap[2];
	vector<vector<char>> treeMap;

	string stageName = "";

	int loadingStage = 0;
	function<void(WorldGenerator&)> loadingFunction = nullptr;


	float xSize;
	float ySize;
	float colorRGB;
	Color cc = { 255.f, 255.f, 255.f };
	int arr[6] = { 0, 1, 2, 0, 2, 3 };
public:
	UI* ui;

	WorldGenerator();

	void	Init();
	void	Update();
	void	Render();
	void	RenderHierarchy();
	void	Release();

	void	GenerateWorld();
	void	OceanMap();
	void	ClimateMap();
	void	MinimizeClimateMap();
	void	BiomeMap();
	void	HeightMap();
	void	TreeMap();
	void	RiverMap();

	void	MapToWorld();

	void	OceanToMesh(vector<vector<char>>& map);
	void	ClimateToMesh(vector<vector<char>>& map);
	void	BiomeToMesh(vector<vector<char>>& map);
	void	HeightToMesh(vector<vector<char>>& map);
	void	RiverToMesh(vector<vector<bool>>& map);

	vector<vector<char>> LerpMapClimate(vector<vector<char>>& map);

	template<typename T>
	vector<vector<T>> LerpMap(vector<vector<T>>& map);

	template<typename T>
	vector<vector<T>> ExtendMap(vector<vector<T>>& _map);

	shared_ptr<Mesh> MapToMesh();

	string GetStageName();
};

