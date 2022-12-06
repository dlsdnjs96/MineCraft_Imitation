#include "stdafx.h"

WorldGenerator::WorldGenerator()
{
    ui = UI::Create("Climate_Graph");
    ui->shader = RESOURCE->shaders.Load("1.Cube.hlsl");
    ui->SetLocalPos({ 0.f, 0.f, 0.2f });
    ui->scale = { 1.5f, 1.5f, 1.5f };
    ui->mesh = MapToMesh();

}

void WorldGenerator::Init()
{
    //loadingFunction(*GetInstance());
    loadingStage = 0;
    loadingFunction = &WorldGenerator::OceanMap;

    xSize = float(mapSize.x / 2) / 4.f;
    ySize = float(mapSize.y / 2) / 4.f;
}

void WorldGenerator::Update()
{
    loadingFunction(*this);
    ui->Update();
}

void WorldGenerator::Render()
{
    ui->Render();
}

void WorldGenerator::RenderHierarchy()
{
    ui->RenderHierarchy();
}

void WorldGenerator::Release()
{
    ui->Release();
}

void WorldGenerator::GenerateWorld()
{
	//DecideClimate();
    //HeightMap();
}

void WorldGenerator::OceanMap()
{
    printf("OceanMap stage %d\r\n", loadingStage);
    loadingStage++;
    stageName = "Making OceanMap... (" + to_string(loadingStage) + "/7)";
    Int2 sectorSize = mapSize;

    //srand(time(NULL));

    static int _x = rand(), _y = rand();


    switch (loadingStage) {
    case 1:
    {
        oceanMap[0].resize(mapSize.x);
        for (int i = 0; i < mapSize.x; i++)
            oceanMap[0][i].resize(mapSize.y);
        oceanMap[1].resize(mapSize.x);
        for (int i = 0; i < mapSize.x; i++)
            oceanMap[1][i].resize(mapSize.y);

        for (int i = 0; i < mapSize.x; i++)
        {
            for (int j = 0; j < mapSize.y; j++)
            {
                float noise = Util::SmoothNoise(_x + i, _y + j) + 1.f;
                noise *= 20.f;

                oceanMap[0][i][j] = static_cast<char>(abs(noise));
            }
        }
        OceanToMesh(oceanMap[0]);
        break;
    }
    case 2:
    case 4:
    case 6:
    {
        oceanMap[1] = ExtendMap(oceanMap[0]);
        OceanToMesh(oceanMap[1]);
        break;
    }
    case 3:
    case 5:
    {
        oceanMap[0] = ExtendMap(oceanMap[1]);
        OceanToMesh(oceanMap[0]);
        break;
    }
    case 7:
    {
        loadingFunction = &WorldGenerator::ClimateMap;
        OceanToMesh(oceanMap[1]);

        loadingStage = 0;
        break;
    }
    }

    return;
}

void WorldGenerator::ClimateMap()
{
    printf("ClimateMap stage %d\r\n", loadingStage);
    loadingStage++;
    stageName = "Making ClimateMap... (" + to_string(loadingStage) + "/9)";
    Int2 sectorSize = mapSize;

    //srand(time(NULL));

    static int _x = rand(), _y = rand();


    switch (loadingStage) {
    case 1:
    {
        climateMap[0].resize(mapSize.x);
        for (int i = 0; i < mapSize.x; i++)
            climateMap[0][i].resize(mapSize.y);
        climateMap[1].resize(mapSize.x);
        for (int i = 0; i < mapSize.x; i++)
            climateMap[1][i].resize(mapSize.y);

        for (int i = 0; i < mapSize.x; i++)
        {
            for (int j = 0; j < mapSize.y; j++)
            {
                int rnd = rand()%6;
                //if (oceanMap[1][i][j] >= 20)
                //    climateMap[0][i][j] = static_cast<char>(0);
               
                if (rnd == 0)
                    climateMap[0][i][j] = static_cast<char>(ClimateType::ICE_CLIMATE);
                else if (rnd == 1)
                    climateMap[0][i][j] = static_cast<char>(ClimateType::COLD_CLIMATE);
                else
                    climateMap[0][i][j] = static_cast<char>(ClimateType::WARM_CLIMATE);
            }
        }
        ClimateToMesh(climateMap[0]);
        break;
    }
    case 2:
    {
        climateMap[1] = LerpMapClimate(climateMap[0]);
        ClimateToMesh(climateMap[1]);
        break;
    }
    case 4:
    case 6:
    case 8:
    {
        climateMap[1] = ExtendMap(climateMap[0]);
        ClimateToMesh(climateMap[1]);
        break;
    }
    case 3:
    case 5:
    case 7:
        climateMap[0] = ExtendMap(climateMap[1]);
        ClimateToMesh(climateMap[0]);
        break;
    case 9:
    {
        climateMap[0] = ExtendMap(climateMap[1]);
        ClimateToMesh(climateMap[0]);
        loadingFunction = &WorldGenerator::BiomeMap;
        //MinimizeClimateMap();
        loadingStage = 0;
        break;
    }
    }

    return;
}

void WorldGenerator::MinimizeClimateMap()
{
    for (int i = 0; i < mapSize.x; i++)
    {
        for (int j = 0; j < mapSize.y; j++)
        {
            if (climateMap[0][i][j] <= 15)
                climateMap[0][i][j] = 1;
            else if (climateMap[0][i][j] <= 25)
                climateMap[0][i][j] = 2;
            else if (climateMap[0][i][j] <= 35)
                climateMap[0][i][j] = 3;
            else if (climateMap[0][i][j] <= 45)
                climateMap[0][i][j] = 4;
            else if (climateMap[0][i][j] <= 55)
                climateMap[0][i][j] = 5;
        }
    }
}

void WorldGenerator::BiomeMap()
{
    printf("BiomeMap stage %d\r\n", loadingStage);
    loadingStage++;
    stageName = "Making BiomeMap... ";

    if (loadingStage > 1)
        return;

    biomeMap.resize(mapSize.x);
    for (int i = 0; i < mapSize.x; i++)
        biomeMap[i].resize(mapSize.y);

    for (int i = 0; i < mapSize.x; i++)
    {
        for (int j = 0; j < mapSize.y; j++)
            biomeMap[i][j] = 0;
    }

    for (int i = 0; i < mapSize.x; i++)
    {
        for (int j = 0; j < mapSize.y; j++)
        {
            if (biomeMap[i][j] > 0)
                continue;

            BiomeType biomeType = BiomeType::PLAIN;
            int rnd = rand();

            if (climateMap[0][i][j] == 1) {
                biomeType = BiomeType::TUNDRA;
            }
            else if (climateMap[0][i][j] == 2) {
                if (rnd % 4 == 0)
                    biomeType = BiomeType::FOREST;
                else if (rnd % 4 == 1)
                    biomeType = BiomeType::FOREST_DARK;
                else if (rnd % 4 == 1)
                    biomeType = BiomeType::MOUNTAIN;
                else
                    biomeType = BiomeType::PLAIN;
            }
            else if (climateMap[0][i][j] == 3) {
                if (rnd % 3 == 0)
                    biomeType = BiomeType::DESERT;
                else
                    biomeType = BiomeType::PLAIN;
            }
            else if (climateMap[0][i][j] == 4) {
                biomeType = BiomeType::DESERT;
            }
            else
            {
                biomeType = BiomeType::JUNGLE;
            }

            vector<pair<int, int>> que;
            que.push_back({ i, j });



            while (not que.empty())
            {
                pair<int, int> top = que.back();
                que.pop_back();

                if (oceanMap[1][top.first][top.second] < WATER_HEIGHT)
                    continue;
                
                biomeMap[top.first][top.second] = static_cast<char>(biomeType);


                if (top.first + 1 < mapSize.x && climateMap[0][i][j] == climateMap[0][top.first + 1][top.second] && biomeMap[top.first + 1][top.second] == 0)
                    que.push_back({ top.first + 1 , top.second });
                if (top.first - 1 >= 0 && climateMap[0][i][j] == climateMap[0][top.first - 1][top.second] && biomeMap[top.first - 1][top.second] == 0)
                    que.push_back({ top.first - 1 , top.second });
                if (top.second + 1 < mapSize.y && climateMap[0][i][j] == climateMap[0][top.first][top.second + 1] && biomeMap[top.first][top.second + 1] == 0)
                    que.push_back({ top.first , top.second + 1 });
                if (top.second - 1 >= 0 && climateMap[0][i][j] == climateMap[0][top.first][top.second - 1] && biomeMap[top.first][top.second - 1] == 0)
                    que.push_back({ top.first , top.second - 1 });
            }
        }
    }
    BiomeToMesh(biomeMap);
    //MapToWorld();
    loadingFunction = &WorldGenerator::RiverMap;
    loadingStage = 0;
}

void WorldGenerator::HeightMap()
{
    printf("HeightMap stage %d\r\n", loadingStage);
    loadingStage++;
    stageName = "Making HeightMap... ("+to_string(loadingStage)+"/11)";
    Int2 sectorSize = mapSize;

    //srand(time(NULL));

    static int _x = rand(), _y = rand();


    switch (loadingStage) {
        case 1:
        {
            heightMap[0].resize(mapSize.x);
            for (int i = 0; i < mapSize.x; i++)
                heightMap[0][i].resize(mapSize.y);
            heightMap[1].resize(mapSize.x);
            for (int i = 0; i < mapSize.x; i++)
                heightMap[1][i].resize(mapSize.y);

            float noise;
            for (int i = 0; i < mapSize.x; i++)
            {
                for (int j = 0; j < mapSize.y; j++)
                {
                    if (oceanMap[1][i][j] < WATER_HEIGHT || riverDepthMap[i][j] > 0) {
                        heightMap[0][i][j] = WATER_HEIGHT;
                        continue;
                    }
                    noise = Util::SmoothNoise(_x + i, _y + j);
                    noise += 4.f;
                    //noise = (noise + 4.f) / 8.f;
                    //noise *= GetBiomeDeviation(BiomeType(biomeMap[i][j]));
                    heightMap[0][i][j] = GetBiomeHeight(BiomeType(biomeMap[i][j])) + static_cast<char>(noise);
                }
            }
            HeightToMesh(heightMap[0]);
            break;
        }
        case 2:
        case 4:
        case 6:
        case 8:
        case 10:
        {
            heightMap[1] = LerpMap(heightMap[0]);
            HeightToMesh(heightMap[1]);
            break;
        }
        case 3:
        case 5:
        case 7:
        case 9:
        {
            for (int i = 0; i < mapSize.x; i++)
            {
                for (int j = 0; j < mapSize.y; j++)
                {
                    if (oceanMap[1][i][j] < WATER_HEIGHT || riverDepthMap[i][j] > 0)
                        heightMap[1][i][j] = 0;
                }
            }
            heightMap[0] = LerpMap(heightMap[1]);
            HeightToMesh(heightMap[0]);
            break;
        }
        case 11:
        {
            HeightToMesh(heightMap[1]);
            loadingStage = 0;
            loadingFunction = &WorldGenerator::TreeMap;
            break;
        }
    }

    return;
}

void WorldGenerator::TreeMap()
{
    stageName = "Making TreeMap... ";

    treeMap.resize(mapSize.x);
    for (int i = 0; i < mapSize.x; i++)
        treeMap[i].resize(mapSize.y);
    treeMap.resize(mapSize.x);
    for (int i = 0; i < mapSize.x; i++)
        treeMap[i].resize(mapSize.y);
    
    for (int i = 0; i < mapSize.x; i+=16)
    {
        for (int j = 0; j < mapSize.y; j+=16)
        {
                
            for (int k = 0; k < 10; k++)
            {
                int x = static_cast<int>(rand() % 16);
                int y = static_cast<int>(rand() % 16);
    
                if (heightMap[1][i + x][j + y] > WATER_HEIGHT && treeMap[i + x][j + y] == 0)
                {
                    char leafBoundary = (2 + (rand() % 2));
                    char treeHeight = 5 + (rand() % 3);
    
                    for (int _x = 0; _x < leafBoundary; _x++)
                    {
                        for (int _y = 0; _y < leafBoundary; _y++)
                        {
                            if ((i + x) + _x >= mapSize.x || (i + x) - _x < 0
                                || (j + y) + _y >= mapSize.y || (j + y) - _y < 0)
                                continue;
                            treeMap[(i + x) + _x][(j + y) + _y] = 1;
                            treeMap[(i + x) + _x][(j + y) - _y] = 1;
                            treeMap[(i + x) - _x][(j + y) + _y] = 1;
                            treeMap[(i + x) - _x][(j + y) - _y] = 1;
                        }
                    }
                    treeMap[i + x][j + y] = treeHeight;
                }
            }
        }
    }

    loadingStage = 0;
    loadingFunction = &WorldGenerator::TreeMap;
    TreeToMesh(treeMap);

    MapToWorld();
}

void WorldGenerator::RiverMap()
{
    printf("RiverMap stage %d\r\n", loadingStage);
    loadingStage++;
    stageName = "Making RiverMap... (" + to_string(loadingStage) + "/7)";
    

     switch (loadingStage) {
        case 1:
        {
            riverMap[0].resize(mapSize.x);
            for (int i = 0; i < mapSize.x; i++)
                riverMap[0][i].resize(mapSize.y);
            riverMap[1].resize(mapSize.x);
            for (int i = 0; i < mapSize.x; i++)
                riverMap[1][i].resize(mapSize.y);

            for (int i = 0; i < mapSize.x; i++)
            {
                for (int j = 0; j < mapSize.y; j++)
                {
                    riverMap[0][i][j] = static_cast<bool>(rand() % 2);
                }
            }
            RiverToMesh(riverMap[0]);
            break;
        }
        case 2:
        case 4:
        case 6:
        {
            riverMap[1] = ExtendMap(riverMap[0]);
            RiverToMesh(riverMap[1]);
            break;
        }
        case 3:
        case 5:
        {
            riverMap[0] = ExtendMap(riverMap[1]);
            RiverToMesh(riverMap[0]);
            break;
        }
        case 7:
        {
            riverMap[0] = ExtendMap(riverMap[1]);
            loadingFunction = &WorldGenerator::RiverDepthMap;
            RiverToMesh(riverMap[0]);
            //loadingStage = 0;
            break;
        }
     }
}

void WorldGenerator::RiverDepthMap()
{
    printf("RiverDepthMap stage %d\r\n", loadingStage);
    loadingStage++;
    stageName = "Making RiverDepthMap...";

    riverDepthMap.resize(mapSize.x);
    for (int i = 0; i < mapSize.x; i++)
        riverDepthMap[i].resize(mapSize.y);

    vector<vector<bool>>* _map = &riverMap[0];


    for (int i = 0; i < (*_map).size() - 1; i++)
    {
        for (int j = 0; j < (*_map)[0].size() - 1; j++) {
            if ((*_map)[i][j] == (*_map)[i + 1][j] && (*_map)[i][j] == (*_map)[i][j + 1])
                continue;


            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    if (i + k >= 0 && i + k < mapSize.x && j + l >= 0 && j + l < mapSize.y)
                        riverDepthMap[i + k][j + l] += 2 - min(abs(k), abs(l));
                }
            }
        }
    }
    RiverDepthToMesh(riverDepthMap);
    loadingFunction = &WorldGenerator::FlowerMap;
    loadingStage = 0;
}

void WorldGenerator::FlowerMap()
{
    stageName = "Making FlowerMap... ";

    flowerMap.resize(mapSize.x+1);
    for (int i = 0; i < mapSize.x+1; i++)
        flowerMap[i].resize(mapSize.y+1);


    for (int i = 0; i < flowerMap.size()-1; i += SECTOR_SIZE)
    {
        for (int j = 0; j < flowerMap[0].size()-1; j += SECTOR_SIZE) {

            int count = 0, x = 0, y = 0, fType;
            fType = rand() % 2;

            while (count < 64)
            {
                count++;
                if (rand() % 80 > count + 64)
                    break;
                x = rand() % 16;
                y = rand() % 16;

                if (oceanMap[1][i + x][j + y] < WATER_HEIGHT || riverDepthMap[i + x][j + y] > 0
                    || (BiomeType(climateMap[1][i + x][j + y]) != BiomeType::MOUNTAIN
                        && BiomeType(climateMap[1][i + x][j + y]) != BiomeType::PLAIN
                        && BiomeType(climateMap[1][i + x][j + y]) != BiomeType::FOREST
                        && BiomeType(climateMap[1][i + x][j + y]) != BiomeType::FOREST_BIRCH))
                    continue;
                flowerMap[i + x][j + y] = 37 + fType;
                flowerMap[i + x + 1][j + y] = 37 + fType;
                flowerMap[i + x][j + y+1] = 37 + fType;
                flowerMap[i + x+1][j + y+1] = 37 + fType;
            }                                                                               
                
        }
    }

    FlowerToMesh(flowerMap);
    loadingFunction = &WorldGenerator::GrassMap;
    loadingStage = 0;
}

void WorldGenerator::GrassMap()
{
    stageName = "Making GrassMap... ";

    grassMap.resize(mapSize.x);
    for (int i = 0; i < mapSize.x; i++)
        grassMap[i].resize(mapSize.y);



    for (int i = 0; i < grassMap.size(); i++)
    {
        for (int j = 0; j < grassMap[0].size(); j++) {

            switch (BiomeType(biomeMap[i][j])) {
                case BiomeType::FOREST:
                case BiomeType::FOREST_DARK:
                case BiomeType::PLAIN:
                case BiomeType::FOREST_BIRCH:
                    if (rand() % 12 == 0)
                        grassMap[i][j] = true;
            }
                
        }
    }

    loadingFunction = &WorldGenerator::HeightMap;
    loadingStage = 0;
}

void WorldGenerator::MapToWorld()
{
    stageName = "Making Mincraft World... ";
    //BlockType arr[100] = { BlockType::GRASS_DIRT,
    //    BlockType::DIRT,
    //    BlockType::STILL_WATER
    //    , BlockType::OAK_WOOD
    //    , BlockType::LEAVE
    //    , BlockType::STONE
    //    , BlockType::OAK_WOOD_PLANK
    //    , BlockType::BRICKS
    //    , BlockType::TNT
    //    , BlockType::COBBLESTONE
    //    , BlockType::BEDROCK
    //    , BlockType::SAND
    //    , BlockType::GRAVEL
    //    , BlockType::IRON_BLOCK
    //    , BlockType::GOLD_BLOCK
    //    , BlockType::DIAMOND_BLOCK
    //    , BlockType::GOLD_ORE
    //    , BlockType::IRON_ORE
    //    , BlockType::COAL_ORE
    //    , BlockType::BOOKSHELF
    //    , BlockType::OBSIDIAN
    //    , BlockType::CRAFTING_TABLE
    //    , BlockType::FURNACE
    //    , BlockType::BURNING_FURNACE
    //    , BlockType::WHITE_WOOL
    //    , BlockType::SNOW_BLOCK
    //    , BlockType::ICE
    //    , BlockType::FARMLAND
    //    , BlockType::FARMLAND_WET
    //    , BlockType::PUMPKIN
    //    , BlockType::PUMPKIN_CARVED
    //    , BlockType::JUNGLE_WOOD
    //    , BlockType::SPRUCE_WOOD
    //    , BlockType::BIRCH_WOOD
    //    , BlockType::LAPIS_LAZULI_ORE
    //    , BlockType::SANDSTONE
    //    , BlockType::GLOWSTONE
    //    , BlockType::JUNGLE_LEAVES
    //    , BlockType::SPRUCE_LEAVES
    //    , BlockType::BIRCH_LEAVES
    //    , BlockType::BIRCH_LEAVES
    //, BlockType::SPRUCE_WOOD_PLANK 
    //, BlockType::JUNGLE_WOOD_PLANK
    //, BlockType::GLASS
    //, BlockType::SNOW_DIRT
    //, BlockType::GRASS
    //, BlockType::DANDELION
    //, BlockType::ROSE
    //};
    //
    //for (int i = 0;i < 48;i++)
    //    WORLD->SetBlockType({ i * 2, 10, 1 }, arr[i]);
    //
    //WORLD->CreateDumpBlocks();
    //WORLD->distinguishBlocks({ 0, 0, 0 }, mapSize.x / 2);
    //SCENE->ChangeScene("INGAME", 0.f)->Init();
    //return;

    // Biome Map
    printf("Biome Map to World\r\n");
    {
        for (int i = 0; i < biomeMap.size(); i++)
        {
            for (int j = 0; j < biomeMap[0].size(); j++) {
                if (heightMap[1][i][j] < WATER_HEIGHT) {
                    for (int k = 0; k < heightMap[1][i][j]; k++)
                        WORLD->SetBlockType({ i - (mapSize.x / 2), k, j - (mapSize.y / 2) }, BlockType::SAND);
                    for (int k = heightMap[1][i][j]; k < WATER_HEIGHT; k++)
                        WORLD->SetBlockType({ i - (mapSize.x / 2), k, j - (mapSize.y / 2) }, BlockType::STILL_WATER);
                }
                else {
                    switch (BiomeType(biomeMap[i][j]))
                    {
                    case BiomeType::TUNDRA:
                        for (int k = 0; k < heightMap[1][i][j] - 3; k++)
                            WORLD->SetBlockType({ i - (mapSize.x / 2), k, j - (mapSize.y / 2) }, BlockType::STONE);
                        if (heightMap[1][i][j] - 3 > 0) {
                            for (int k = heightMap[1][i][j] - 3; k < heightMap[1][i][j]; k++)
                                WORLD->SetBlockType({ i - (mapSize.x / 2), k, j - (mapSize.y / 2) }, BlockType::SANDSTONE_SHAVED);
                        }
                        break;
                    case BiomeType::DESERT:
                        for (int k = 0; k < heightMap[1][i][j] - 3; k++)
                            WORLD->SetBlockType({ i - (mapSize.x / 2), k, j - (mapSize.y / 2) }, BlockType::STONE);
                        if (heightMap[1][i][j] - 3 > 0) {
                            for (int k = heightMap[1][i][j] - 3; k < heightMap[1][i][j]; k++)
                                WORLD->SetBlockType({ i - (mapSize.x / 2), k, j - (mapSize.y / 2) }, BlockType::SANDSTONE_SHAVED);
                        }
                        break;
                    default:
                        for (int k = 0; k < heightMap[1][i][j] - 3; k++)
                            WORLD->SetBlockType({ i - (mapSize.x / 2), k, j - (mapSize.y / 2) }, BlockType::STONE);
                        if (heightMap[1][i][j] - 3 > 0) {
                            for (int k = heightMap[1][i][j] - 3; k < heightMap[1][i][j]; k++)
                                WORLD->SetBlockType({ i - (mapSize.x / 2), k, j - (mapSize.y / 2) }, BlockType::DIRT);
                        }
                    }

                    switch (BiomeType(biomeMap[i][j]))
                    {
                    case BiomeType::TUNDRA:
                        WORLD->SetBlockType({ i - (mapSize.x / 2), heightMap[1][i][j], j - (mapSize.y / 2) }, BlockType::SNOW_DIRT);
                        break;
                    case BiomeType::FOREST:
                        WORLD->SetBlockType({ i - (mapSize.x / 2), heightMap[1][i][j], j - (mapSize.y / 2) }, BlockType::GRASS_DIRT);
                        break;
                    case BiomeType::FOREST_DARK:
                        WORLD->SetBlockType({ i - (mapSize.x / 2), heightMap[1][i][j], j - (mapSize.y / 2) }, BlockType::GRASS_DIRT);
                        break;
                    case BiomeType::MOUNTAIN:
                        WORLD->SetBlockType({ i - (mapSize.x / 2), heightMap[1][i][j], j - (mapSize.y / 2) }, BlockType::GRASS_DIRT);
                        break;
                    case BiomeType::PLAIN:
                        WORLD->SetBlockType({ i - (mapSize.x / 2), heightMap[1][i][j], j - (mapSize.y / 2) }, BlockType::GRASS_DIRT);
                        break;
                    case BiomeType::FOREST_BIRCH:
                        WORLD->SetBlockType({ i - (mapSize.x / 2), heightMap[1][i][j], j - (mapSize.y / 2) }, BlockType::GRASS_DIRT);
                        break;
                    case BiomeType::DESERT:
                        WORLD->SetBlockType({ i - (mapSize.x / 2), heightMap[1][i][j], j - (mapSize.y / 2) }, BlockType::SAND);
                        break;
                    case BiomeType::JUNGLE:
                        WORLD->SetBlockType({ i - (mapSize.x / 2), heightMap[1][i][j], j - (mapSize.y / 2) }, BlockType::JUNGLE_LEAVES);
                        WORLD->SetBlockType({ i - (mapSize.x / 2), heightMap[1][i][j]+1, j - (mapSize.y / 2) }, BlockType::JUNGLE_LEAVES);
                        break;
                    default:
                        WORLD->SetBlockType({ i - (mapSize.x / 2), heightMap[1][i][j], j - (mapSize.y / 2) }, BlockType::GRASS_DIRT);
                    }
                    switch (BiomeType(biomeMap[i][j]))
                    {
                    case BiomeType::FOREST:
                    case BiomeType::FOREST_DARK:
                    case BiomeType::MOUNTAIN:
                    case BiomeType::PLAIN:
                    case BiomeType::FOREST_BIRCH:
                        if (grassMap[i][j])
                            WORLD->SetBlockType({ i - (mapSize.x / 2), heightMap[1][i][j] + 1, j - (mapSize.y / 2) }, BlockType::GRASS);
                        if (flowerMap[i][j] > 0)
                            WORLD->SetBlockType({ i - (mapSize.x / 2), heightMap[1][i][j] + 1, j - (mapSize.y / 2) }, BlockType(flowerMap[i][j]));
                        break;
                    }

                }

                //WORLD->SetBlockType({ i - (mapSize.x / 2), 1, j - (mapSize.y / 2) }, BlockType::STONE);
            }
        }
    }


    // Tree Map
    printf("Tree Map to World\r\n");
    {
        for (int i = 0; i < mapSize.x; i++)
        {
            for (int j = 0; j < mapSize.y; j++) {
                if (treeMap[i][j] <= 1 || heightMap[1][i][j] < WATER_HEIGHT)
                    continue;

                BlockType root = BlockType::OAK_WOOD;
                BlockType leaves = BlockType::LEAVE;
                int rootHeight = 2;
                int treeHeight = 2;
                int leafRadius = 3;

                switch (BiomeType(biomeMap[i][j]))
                {
                case BiomeType::FOREST:
                case BiomeType::PLAIN:
                    root = BlockType::OAK_WOOD;
                    leaves = BlockType::LEAVE;
                    treeHeight = (rand() % 3) + 4;
                    rootHeight = (rand() % 2) + 2;
                    leafRadius = 2 + (rand() % 2);
                    break;
                case BiomeType::FOREST_DARK:
                    root = BlockType::SPRUCE_WOOD;
                    leaves = BlockType::SPRUCE_LEAVES;
                    treeHeight = (rand() % 3) + 6;
                    rootHeight = (rand() % 2) + 4;
                    leafRadius = 4 + (rand()%2);
                    break;
                case BiomeType::FOREST_BIRCH:
                    root = BlockType::BIRCH_WOOD;
                    leaves = BlockType::BIRCH_LEAVES;
                    treeHeight = (rand() % 2) + 3;
                    rootHeight = (rand() % 2) + 2;
                    leafRadius = 2 + (rand() % 2);
                    break;
                case BiomeType::JUNGLE:
                    root = BlockType::JUNGLE_WOOD;
                    leaves = BlockType::JUNGLE_LEAVES;
                    treeHeight = (rand() % 7) + 13;
                    rootHeight = (rand() % 3) + 10;
                    leafRadius = 5 + (rand() % 2);
                    break;
                default:
                    continue;
                }
                treeMap[i][j] = treeHeight;
                int groundHeight = heightMap[1][i][j] + 1;

                if (BiomeType(biomeMap[i][j]) == BiomeType::JUNGLE)
                {
                    for (int k = 0; k < treeMap[i][j]; k++) {
                        WORLD->SetBlockType({ i - (mapSize.x / 2), groundHeight + k, j - (mapSize.y / 2) }, root);
                        WORLD->SetBlockType({ i - (mapSize.x / 2) + 1, groundHeight + k, j - (mapSize.y / 2) }, root);
                        WORLD->SetBlockType({ i - (mapSize.x / 2), groundHeight + k, j - (mapSize.y / 2) + 1 }, root);
                        WORLD->SetBlockType({ i - (mapSize.x / 2) + 1, groundHeight + k, j - (mapSize.y / 2) + 1 }, root);
                    }
                }
                else {
                    for (int k = 0; k < treeMap[i][j]; k++)
                        WORLD->SetBlockType({ i - (mapSize.x / 2), groundHeight + k, j - (mapSize.y / 2) }, root);
                }

                for (int _x = 0; _x < leafRadius; _x++)
                {
                    for (int _z = 0; _z < leafRadius; _z++)
                    {
                        if (_x == 0 && _z == 0)
                            continue;
                        for (int _y = rootHeight; _y < treeMap[i][j]; _y++) {
                            WORLD->SetBlockType({ i + _x - (mapSize.x / 2), groundHeight + _y, j + _z - (mapSize.y / 2) }, leaves);
                            WORLD->SetBlockType({ i + _x - (mapSize.x / 2), groundHeight + _y, j - _z - (mapSize.y / 2) }, leaves);
                            WORLD->SetBlockType({ i - _x - (mapSize.x / 2), groundHeight + _y, j + _z - (mapSize.y / 2) }, leaves);
                            WORLD->SetBlockType({ i - _x - (mapSize.x / 2), groundHeight + _y, j - _z - (mapSize.y / 2) }, leaves);
                        }
                    }
                }
                for (int _x = 0; _x < leafRadius-1; _x++)
                {
                    for (int _z = 0; _z < leafRadius - 1; _z++)
                    {
                        for (int _y = treeMap[i][j]; _y < treeMap[i][j] + 2; _y++) {
                            WORLD->SetBlockType({ i + _x - (mapSize.x / 2), groundHeight + _y, j + _z - (mapSize.y / 2) }, leaves);
                            WORLD->SetBlockType({ i + _x - (mapSize.x / 2), groundHeight + _y, j - _z - (mapSize.y / 2) }, leaves);
                            WORLD->SetBlockType({ i - _x - (mapSize.x / 2), groundHeight + _y, j + _z - (mapSize.y / 2) }, leaves);
                            WORLD->SetBlockType({ i - _x - (mapSize.x / 2), groundHeight + _y, j - _z - (mapSize.y / 2) }, leaves);
                        }
                    }
                }
                
            }
        }
    }


    // Monster
    printf("Monster Map to World\r\n");
    {
        for (int i = 0; i < mapSize.x; i += SECTOR_SIZE)
        {
            for (int j = 0; j < mapSize.y; j += SECTOR_SIZE) {

                if (treeMap[i][j] <= 1 || heightMap[1][i][j] < WATER_HEIGHT)
                    continue;
                if (rand() % 10 < 1)
                    continue;

                float x = float(i - (mapSize.x / 2)) * 10.f;
                float y = float(heightMap[1][i][j] * 10.f) + 10.f;
                float z = float(j - (mapSize.y / 2)) * 10.f;

                switch (BiomeType(biomeMap[i][j]))
                {
                case BiomeType::FOREST:
                    MONSTER_MANAGER->Spawn(MonsterType::COW, Vector3{ x, y, z }, MonsterState::IDLE);
                    MONSTER_MANAGER->Spawn(MonsterType::COW, Vector3{ x, y, z }, MonsterState::IDLE);
                    MONSTER_MANAGER->Spawn(MonsterType::COW, Vector3{ x, y, z }, MonsterState::IDLE);
                    MONSTER_MANAGER->Spawn(MonsterType::COW, Vector3{ x, y, z }, MonsterState::IDLE);
                    break;
                case BiomeType::PLAIN:
                    MONSTER_MANAGER->Spawn(MonsterType::PIG, Vector3{ x, y, z }, MonsterState::IDLE);
                    MONSTER_MANAGER->Spawn(MonsterType::PIG, Vector3{ x, y, z }, MonsterState::IDLE);
                    MONSTER_MANAGER->Spawn(MonsterType::PIG, Vector3{ x, y, z }, MonsterState::IDLE);
                    MONSTER_MANAGER->Spawn(MonsterType::PIG, Vector3{ x, y, z }, MonsterState::IDLE);
                    break;
                case BiomeType::FOREST_DARK:
                    MONSTER_MANAGER->Spawn(MonsterType::SHEEP, Vector3{ x, y, z }, MonsterState::IDLE);
                    MONSTER_MANAGER->Spawn(MonsterType::SHEEP, Vector3{ x, y, z }, MonsterState::IDLE);
                    MONSTER_MANAGER->Spawn(MonsterType::SHEEP, Vector3{ x, y, z }, MonsterState::IDLE);
                    MONSTER_MANAGER->Spawn(MonsterType::SHEEP, Vector3{ x, y, z }, MonsterState::IDLE);
                    break;
                case BiomeType::FOREST_BIRCH:
                case BiomeType::JUNGLE:
                    MONSTER_MANAGER->Spawn(MonsterType::CHICKEN, Vector3{ x, y, z }, MonsterState::IDLE);
                    MONSTER_MANAGER->Spawn(MonsterType::CHICKEN, Vector3{ x, y, z }, MonsterState::IDLE);
                    MONSTER_MANAGER->Spawn(MonsterType::CHICKEN, Vector3{ x, y, z }, MonsterState::IDLE);
                    MONSTER_MANAGER->Spawn(MonsterType::CHICKEN, Vector3{ x, y, z }, MonsterState::IDLE);
                    break;
                default:
                    continue;
                }



                
            }
        }
    }

    oceanMap[0].clear();
    oceanMap[1].clear();
    climateMap[0].clear();;
    climateMap[1].clear();;
    heightMap[0].clear();
    heightMap[1].clear();
    riverMap[0].clear();
    riverMap[1].clear();
    biomeMap.clear();
    riverDepthMap.clear();
    treeMap.clear();
    flowerMap.clear();

    WORLD->CreateDumpBlocks();
    WORLD->distinguishBlocks({ 0, 0, 0 }, mapSize.x / 2);
    SCENE->ChangeScene("INGAME", 0.f)->Init();
    return;
}






void WorldGenerator::OceanToMesh(vector<vector<char>>& map)
{
    VertexPC*   vertices = 0;
    UINT*       indicies = 0;
    UINT        vIndex = 0;
    UINT        iIndex = 0;

    vertices = new VertexPC[map.size() * map[0].size() * 4];
    indicies = new UINT[map.size() * map[0].size() * 6];


    for (int i = 0; i < mapSize.x; i++)
    {
        for (int j = 0; j < mapSize.y; j++)
        {
            if (map[i][j] < 20) 
                cc = { 0.f, 0.f, 1.f };
            else
                cc = { 0.f, 1.f, 0.f };
            

            vertices[vIndex].position = { float(i - (mapSize.x / 2) + 1) / xSize, float(j - (mapSize.y / 2) + 1) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2) + 1) / xSize, float(j - (mapSize.y / 2)) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2)) / xSize, float(j - (mapSize.y / 2)) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2)) / xSize, float(j - (mapSize.y / 2) + 1) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;



            for (int k = 0; k < 6; k++) {
                indicies[iIndex] = arr[k] + vIndex - 4;
                iIndex++;
            }
        }
    }


    ui->mesh = make_shared<Mesh>(vertices, vIndex, indicies, iIndex, VertexType::PC);
}

void WorldGenerator::ClimateToMesh(vector<vector<char>>& map)
{
    VertexPC* vertices = 0;
    UINT* indicies = 0;
    UINT        vIndex = 0;
    UINT        iIndex = 0;

    vertices = new VertexPC[map.size() * map[0].size() * 4];
    indicies = new UINT[map.size() * map[0].size() * 6];


    for (int i = 0; i < mapSize.x; i++)
    {
        for (int j = 0; j < mapSize.y; j++)
        {
            if (map[i][j] == 0)
                cc = { 1.f, 1.f, 1.f };
            else if (map[i][j] <= 1)
                cc = { 0.5976f, 0.8632f, 1.f };
            else if (map[i][j] <= 2)
                cc = { 0.f, 0.5f, 1.f };
            else if (map[i][j] <= 3)
                cc = { 0.5039, 0.7539f, 0.2773f };
            else if (map[i][j] <= 4)
                cc = { 1.f, 0.5f, 0.f };
            else if (map[i][j] <= 5)
                cc = { 0.f, 0.f, 0.f };


            vertices[vIndex].position = { float(i - (mapSize.x / 2) + 1) / xSize, float(j - (mapSize.y / 2) + 1) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2) + 1) / xSize, float(j - (mapSize.y / 2)) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2)) / xSize, float(j - (mapSize.y / 2)) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2)) / xSize, float(j - (mapSize.y / 2) + 1) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;



            for (int k = 0; k < 6; k++) {
                indicies[iIndex] = arr[k] + vIndex - 4;
                iIndex++;
            }
        }
    }


    ui->mesh = make_shared<Mesh>(vertices, vIndex, indicies, iIndex, VertexType::PC);
}

void WorldGenerator::BiomeToMesh(vector<vector<char>>& map)
{
    VertexPC*   vertices = 0;
    UINT*       indicies = 0;
    UINT        vIndex = 0;
    UINT        iIndex = 0;

    vertices = new VertexPC[map.size() * map[0].size() * 4];
    indicies = new UINT[map.size() * map[0].size() * 6];


    for (int i = 0; i < mapSize.x; i++)
    {
        for (int j = 0; j < mapSize.y; j++)
        {
            switch (BiomeType(map[i][j]))
            {
            case BiomeType::TUNDRA:
                cc = { 235.f / 255.f, 235.f / 255.f, 235.f / 255.f };
                break;
            case BiomeType::FOREST:
                cc = { 36.f / 255.f, 103.f / 255.f, 11.f / 255.f };
                break;
            case BiomeType::FOREST_DARK:
                cc = { 13.f / 255.f, 47.f / 255.f, 0.f / 255.f };
                break;
            case BiomeType::MOUNTAIN:
                cc = { 17.f / 255.f, 66.f / 255.f, 27.f / 255.f };
                break;
            case BiomeType::PLAIN:
                cc = { 0.f / 255.f, 255.f / 255.f, 52.f / 255.f };
                break;
            case BiomeType::FOREST_BIRCH:
                cc = { 0.f / 255.f, 255.f / 255.f, 52.f / 255.f };
                break;
            case BiomeType::DESERT:
                cc = { 255.f / 255.f, 215.f / 255.f, 0.f / 255.f };
                break;
            case BiomeType::JUNGLE:
                cc = { 0.f / 255.f, 30.f / 255.f, 0.f / 255.f };
                break;
            }
            


            vertices[vIndex].position = { float(i - (mapSize.x / 2) + 1) / xSize, float(j - (mapSize.y / 2) + 1) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2) + 1) / xSize, float(j - (mapSize.y / 2)) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2)) / xSize, float(j - (mapSize.y / 2)) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2)) / xSize, float(j - (mapSize.y / 2) + 1) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;



            for (int k = 0; k < 6; k++) {
                indicies[iIndex] = arr[k] + vIndex - 4;
                iIndex++;
            }
        }
    }


    ui->mesh = make_shared<Mesh>(vertices, vIndex, indicies, iIndex, VertexType::PC);
}


void WorldGenerator::HeightToMesh(vector<vector<char>>& map)
{
    VertexPC*   vertices = 0;
    UINT*       indicies = 0;
    UINT        vIndex = 0;
    UINT        iIndex = 0;

    vertices = new VertexPC[map.size() * map[0].size() * 4];
    indicies = new UINT[map.size() * map[0].size() * 6];

    float xSize = float(mapSize.x / 2) / 4.f;
    float ySize = float(mapSize.y / 2) / 4.f;

    float colorRGB;
    Color cc = { 255.f, 255.f, 255.f };
    int arr[6] = { 0, 1, 2, 0, 2, 3 };



    for (int i = 0; i < mapSize.x; i++)
    {
        for (int j = 0; j < mapSize.y; j++)
        {
            if (map[i][j] < WATER_HEIGHT) {
                colorRGB = static_cast<float>((WATER_HEIGHT - map[i][j]) / 40.f) + 0.5f;
                cc = { 0.f, 0.f, colorRGB };
            }
            else
            {
                colorRGB = (static_cast<float>(map[i][j]) / (22.f)) + 0.5f;
                cc = { 0.f, colorRGB, 0.f };
            }
            colorRGB = (static_cast<float>(map[i][j]) / (160.f));
            cc = { colorRGB, colorRGB, colorRGB };

            vertices[vIndex].position = { float(i - (mapSize.x / 2) + 1) / xSize, float(j - (mapSize.y / 2) + 1) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2) + 1) / xSize, float(j - (mapSize.y / 2)) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2)) / xSize, float(j - (mapSize.y / 2)) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2)) / xSize, float(j - (mapSize.y / 2) + 1) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;



            for (int k = 0; k < 6; k++) {
                indicies[iIndex] = arr[k] + vIndex - 4;
                iIndex++;
            }
        }
    }


    ui->mesh = make_shared<Mesh>(vertices, vIndex, indicies, iIndex, VertexType::PC);
}

void WorldGenerator::RiverToMesh(vector<vector<bool>>& map)
{
    VertexPC* vertices = 0;
    UINT* indicies = 0;
    UINT        vIndex = 0;
    UINT        iIndex = 0;

    vertices = new VertexPC[map.size() * map[0].size() * 4];
    indicies = new UINT[map.size() * map[0].size() * 6];

    float xSize = float(mapSize.x / 2) / 4.f;
    float ySize = float(mapSize.y / 2) / 4.f;

    float colorRGB;
    Color cc = { 1.f, 1.f, 1.f };
    int arr[6] = { 0, 1, 2, 0, 2, 3 };


    for (int i = 0; i < mapSize.x; i++)
    {
        for (int j = 0; j < mapSize.y; j++)
        {
            if (oceanMap[1][i][j] < 20)
                cc = { 1.f, 1.f, 1.f };
            else 
                if (map[i][j])
                cc = { 0.5f, 0.5f, 0.5f };
            else
                cc = { 0.f, 0.f, 0.f };


            vertices[vIndex].position = { float(i - (mapSize.x / 2) + 1) / xSize, float(j - (mapSize.y / 2) + 1) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2) + 1) / xSize, float(j - (mapSize.y / 2)) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2)) / xSize, float(j - (mapSize.y / 2)) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2)) / xSize, float(j - (mapSize.y / 2) + 1) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;



            for (int k = 0; k < 6; k++) {
                indicies[iIndex] = arr[k] + vIndex - 4;
                iIndex++;
            }
        }
    }
    ui->mesh = make_shared<Mesh>(vertices, vIndex, indicies, iIndex, VertexType::PC);
}

void WorldGenerator::RiverDepthToMesh(vector<vector<char>>& map)
{
    VertexPC* vertices = 0;
    UINT* indicies = 0;
    UINT        vIndex = 0;
    UINT        iIndex = 0;

    vertices = new VertexPC[map.size() * map[0].size() * 4];
    indicies = new UINT[map.size() * map[0].size() * 6];

    float xSize = float(mapSize.x / 2) / 4.f;
    float ySize = float(mapSize.y / 2) / 4.f;

    float colorRGB;
    Color cc = { 1.f, 1.f, 1.f };
    int arr[6] = { 0, 1, 2, 0, 2, 3 };


    for (int i = 0; i < mapSize.x; i++)
    {
        for (int j = 0; j < mapSize.y; j++)
        {
            if (oceanMap[1][i][j] < 20)
                cc = { 1.f, 1.f, 1.f };
            else if (map[i][j] > 0)
                cc = { 0.f, 0.f, (float(map[i][j]) / 10.f) };
            else
                cc = { 0.5f, 0.5f, 0.5f };


            vertices[vIndex].position = { float(i - (mapSize.x / 2) + 1) / xSize, float(j - (mapSize.y / 2) + 1) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2) + 1) / xSize, float(j - (mapSize.y / 2)) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2)) / xSize, float(j - (mapSize.y / 2)) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2)) / xSize, float(j - (mapSize.y / 2) + 1) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;



            for (int k = 0; k < 6; k++) {
                indicies[iIndex] = arr[k] + vIndex - 4;
                iIndex++;
            }
        }
    }
    ui->mesh = make_shared<Mesh>(vertices, vIndex, indicies, iIndex, VertexType::PC);
}

void WorldGenerator::TreeToMesh(vector<vector<char>>& map)
{
    VertexPC* vertices = 0;
    UINT* indicies = 0;
    UINT        vIndex = 0;
    UINT        iIndex = 0;

    vertices = new VertexPC[map.size() * map[0].size() * 4];
    indicies = new UINT[map.size() * map[0].size() * 6];

    float xSize = float(mapSize.x / 2) / 4.f;
    float ySize = float(mapSize.y / 2) / 4.f;

    float colorRGB;
    Color cc = { 1.f, 1.f, 1.f };
    int arr[6] = { 0, 1, 2, 0, 2, 3 };


    for (int i = 0; i < mapSize.x; i++)
    {
        for (int j = 0; j < mapSize.y; j++)
        {
            if (oceanMap[1][i][j] < 20)
                cc = { 1.f, 1.f, 1.f };
            else if (map[i][j] > 0)
                cc = { 0.f, 0.8f, 0.f };
            else
                cc = { 0.5f, 0.5f, 0.5f };


            vertices[vIndex].position = { float(i - (mapSize.x / 2) + 1) / xSize, float(j - (mapSize.y / 2) + 1) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2) + 1) / xSize, float(j - (mapSize.y / 2)) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2)) / xSize, float(j - (mapSize.y / 2)) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2)) / xSize, float(j - (mapSize.y / 2) + 1) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;



            for (int k = 0; k < 6; k++) {
                indicies[iIndex] = arr[k] + vIndex - 4;
                iIndex++;
            }
        }
    }
    ui->mesh = make_shared<Mesh>(vertices, vIndex, indicies, iIndex, VertexType::PC);
}

void WorldGenerator::FlowerToMesh(vector<vector<char>>& map)
{
    VertexPC* vertices = 0;
    UINT* indicies = 0;
    UINT        vIndex = 0;
    UINT        iIndex = 0;

    vertices = new VertexPC[map.size() * map[0].size() * 4];
    indicies = new UINT[map.size() * map[0].size() * 6];

    float xSize = float(mapSize.x / 2) / 4.f;
    float ySize = float(mapSize.y / 2) / 4.f;

    float colorRGB;
    Color cc = { 1.f, 1.f, 1.f };
    int arr[6] = { 0, 1, 2, 0, 2, 3 };


    for (int i = 0; i < mapSize.x; i++)
    {
        for (int j = 0; j < mapSize.y; j++)
        {
            if (oceanMap[1][i][j] < 20)
                cc = { 1.f, 1.f, 1.f };
            else if (map[i][j] == 37)
                cc = { 1.f, 0.f, 0.f };
            else if (map[i][j] == 38)
                cc = { 1.f, 1.f, 0.f };
            else
                cc = { 0.5f, 0.5f, 0.5f };


            vertices[vIndex].position = { float(i - (mapSize.x / 2) + 1) / xSize, float(j - (mapSize.y / 2) + 1) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2) + 1) / xSize, float(j - (mapSize.y / 2)) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2)) / xSize, float(j - (mapSize.y / 2)) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;
            vertices[vIndex].position = { float(i - (mapSize.x / 2)) / xSize, float(j - (mapSize.y / 2) + 1) / ySize, 0.f };
            vertices[vIndex].color = cc;
            vIndex++;



            for (int k = 0; k < 6; k++) {
                indicies[iIndex] = arr[k] + vIndex - 4;
                iIndex++;
            }
        }
    }
    ui->mesh = make_shared<Mesh>(vertices, vIndex, indicies, iIndex, VertexType::PC);
}

vector<vector<char>> WorldGenerator::LerpMapClimate(vector<vector<char>>& map)
{
    vector<vector<char>> resultMap;

    resultMap.resize(mapSize.x);
    for (int i = 0; i < mapSize.x; i++)
        resultMap[i].resize(mapSize.y);

    char temp;
    //for (int i = 0; i < mapSize.x; i++)
    //{
    //    resultMap[i][0] = map[i][0];
    //    resultMap[i][mapSize.y - 1] = map[i][mapSize.y - 1];
    //}
    //for (int i = 0; i < mapSize.y; i++)
    //{
    //    resultMap[0][i] = map[0][i];
    //    resultMap[mapSize.x - 1][i] = map[mapSize.x - 1][i];
    //}
    for (int i = 0; i < mapSize.x; i++)
    {
        for (int j = 0; j < mapSize.y; j++) {
            int x = (i / 2) + 1;
            int y = (j / 2) + 1;

            temp = map[x][y];
            
            if (temp == 4)
            {
                if (map[x + 1][y - 1] == 2 || map[x + 1][y] == 2
                    || map[x + 1][y + 1] == 2 || map[x][y + 1] == 2)
                    temp = 3;
            }
            else if (temp == 1)
            {
                if (map[x + 1][y - 1] == 4 || map[x + 1][y] == 4
                    || map[x + 1][y + 1] == 4 || map[x][y + 1] == 4)
                    temp = 3;
            }
            if (rand()%13 == 0)
                resultMap[i][j] = 5;
            else
                resultMap[i][j] = temp;
        }
    }

    return resultMap;
}

int WorldGenerator::GetBiomeHeight(BiomeType _biomeType)
{
    switch (_biomeType) {
        case BiomeType::TUNDRA:
            return 20;
        case BiomeType::FOREST:
            return 30;
        case BiomeType::FOREST_DARK:
            return 33;
        case BiomeType::MOUNTAIN:
            return 50;
        case BiomeType::PLAIN:
            return 27;
        case BiomeType::FOREST_BIRCH:
            return 31;
        case BiomeType::DESERT:
            return 25;
        case BiomeType::JUNGLE:
            return 41;
    }
    return 0;
}

int WorldGenerator::GetBiomeDeviation(BiomeType _biomeType)
{
    switch (_biomeType) {
        case BiomeType::TUNDRA:
            return 5;
        case BiomeType::FOREST:
            return 10;
        case BiomeType::FOREST_DARK:
            return 8;
        case BiomeType::MOUNTAIN:
            return 40;
        case BiomeType::PLAIN:
            return 17;
        case BiomeType::FOREST_BIRCH:
            return 13;
        case BiomeType::DESERT:
            return 7;
        case BiomeType::JUNGLE:
            return 22;
    }
    return 0;
}

template<typename T>
vector<vector<T>> WorldGenerator::LerpMap(vector<vector<T>>& map)
{
    Int2 sectorSize = { int(map.size()), int(map[0].size()) };
    vector<vector<T>> resultMap;

    resultMap.resize(sectorSize.x);
    for (int i = 0; i < sectorSize.x; i++)
        resultMap[i].resize(sectorSize.y);

    for (int i = 0; i < sectorSize.x; i++)
    {
        for (int j = 0; j < sectorSize.y; j++) {
            int ave = 0, x, y;

            x = (i / 2) + 1;
            y = (j / 2) + 1;

            ave += static_cast<int>(map[x][y]) * 4;
            ave += static_cast<int>(map[x + 1][y + 1]) * 2;
            ave += static_cast<int>(map[x + 1][y - 1]) * 2;
            ave += static_cast<int>(map[x - 1][y + 1]) * 2;
            ave += static_cast<int>(map[x - 1][y - 1]) * 2;
            ave += static_cast<int>(map[x + 1][y]);
            ave += static_cast<int>(map[x - 1][y]);
            ave += static_cast<int>(map[x][y + 1]);
            ave += static_cast<int>(map[x][y - 1]);
            resultMap[i][j] = static_cast<T>(ave / 16);
        }
    }

    return resultMap;
}

template<typename T>
vector<vector<T>> WorldGenerator::ExtendMap(vector<vector<T>>& _map)
{
    Int2 sectorSize = { int(_map.size()), int(_map[0].size()) };
    vector<vector<T>> resultMap;

    resultMap.resize(sectorSize.x);
    for (int i = 0; i < sectorSize.x; i++)
        resultMap[i].resize(sectorSize.y);

    for (int i = 0; i < sectorSize.x / 2; i++)
    {
        for (int j = 0; j < sectorSize.y / 2; j++) {
            int ave = 0, x, y;

            x = (i * 2);
            y = (j * 2);

            resultMap[x][y] = _map[i][j];
            if (rand()%2 == 0)
                resultMap[x + 1][y] = _map[i][j];
            else
                resultMap[x + 1][y] = _map[i + 1][j];
            if (rand()%2 == 0)
                resultMap[x][y + 1] = _map[i][j];
            else
                resultMap[x][y + 1] = _map[i][j + 1];
            if (rand()%4 == 0)
                resultMap[x + 1][y + 1] = _map[i + 1][j + 1];
            else                              
                resultMap[x + 1][y + 1] = _map[i][j];

        }
    }

    return resultMap;
}

shared_ptr<Mesh> WorldGenerator::MapToMesh()
{
    VertexPC* vertices;
    UINT vertexCount = 4 * mapSize.x * mapSize.y;
    UINT* indices;
    UINT indexCount = 3 * (vertexCount / 2);
    VertexType type = VertexType::PC;

    vertices = new VertexPC[vertexCount];
    indices = new UINT[indexCount];

    float vertexDistance = 10.f / mapSize.x;

    for (int i = 0; i < mapSize.x; i++)
    {
        for (int j = 0; j < mapSize.y; j++)
        {
            float _x = (i * vertexDistance) - 5.f;
            float _y = (j * vertexDistance) - 5.f;
            vertices[(((i * mapSize.x) + j) * 4) + 0].position = { _x + vertexDistance, _y, 0.f };
            vertices[(((i * mapSize.x) + j) * 4) + 1].position = { _x + vertexDistance, _y + vertexDistance, 0.f };
            vertices[(((i * mapSize.x) + j) * 4) + 2].position = { _x, _y + vertexDistance, 0.f };
            vertices[(((i * mapSize.x) + j) * 4) + 3].position = { _x, _y, 0.f };


            Color cc = { 0.f, 0.f, 0.f };
            vertices[(((i * mapSize.x) + j) * 4) + 0].color = cc;
            vertices[(((i * mapSize.x) + j) * 4) + 1].color = cc;
            vertices[(((i * mapSize.x) + j) * 4) + 2].color = cc;
            vertices[(((i * mapSize.x) + j) * 4) + 3].color = cc;
        }
    }

    int idx = 0;
    for (int i = 0; i < mapSize.x; i++)
    {
        for (int j = 0; j < mapSize.y; j++)
        {
            indices[idx] = (((i * mapSize.x) + j) * 4) + 0;
            idx++;
            indices[idx] = (((i * mapSize.x) + j) * 4) + 1;
            idx++;
            indices[idx] = (((i * mapSize.x) + j) * 4) + 2;
            idx++;

            indices[idx] = (((i * mapSize.x) + j) * 4) + 0;
            idx++;
            indices[idx] = (((i * mapSize.x) + j) * 4) + 2;
            idx++;
            indices[idx] = (((i * mapSize.x) + j) * 4) + 3;
            idx++;
        }
    }
    
    shared_ptr<Mesh> newMesh = make_shared<Mesh>(vertices, vertexCount, indices, indexCount, type);

    return newMesh;
}


string WorldGenerator::GetStageName()
{
    return stageName;
}
