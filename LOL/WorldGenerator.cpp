#include "stdafx.h"

WorldGenerator::WorldGenerator()
{
    ui = UI::Create("Climate_Graph");
    ui->shader = RESOURCE->shaders.Load("MapGraph.hlsl");
    ui->SetLocalPos({ 0.f, 0.f, 0.f });
    ui->scale = { 0.05f, 0.05f, 0.3f };
    ui->mesh = MapToMesh();

    loadingStage = 0;
    loadingFunction = &WorldGenerator::HeightMap;
}

void WorldGenerator::Init()
{
    //loadingFunction(*GetInstance());
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

void WorldGenerator::HeightMap()
{
    printf("HeightMap stage %d\r\n", loadingStage);
    Int2 sectorSize = mapSize;

    //srand(time(NULL));

    static int _x = rand(), _y = rand();

    loadingStage++;

    switch (loadingStage) {
        case 1:
        {
            heightMap[0].resize(mapSize.x);
            for (int i = 0; i < mapSize.x; i++)
                heightMap[0][i].resize(mapSize.y);
            heightMap[1].resize(mapSize.x);
            for (int i = 0; i < mapSize.x; i++)
                heightMap[1][i].resize(mapSize.y);

            for (int i = 0; i < mapSize.x; i++)
            {
                for (int j = 0; j < mapSize.y; j++)
                {
                    float noise = Util::SmoothNoise(_x + i, _y + j) + 1.f;
                    noise *= 20.f;

                    heightMap[0][i][j] = static_cast<char>(abs(noise));
                }
            }
            HeightToMesh(heightMap[0]);
            break;
        }
        case 2:
        case 4:
        case 6:
        {
            heightMap[1] = LerpMap(heightMap[0]);
            HeightToMesh(heightMap[1]);
            break;
        }
        case 3:
        case 5:
        {
            heightMap[0] = LerpMap(heightMap[1]);
            HeightToMesh(heightMap[0]);
            break;
        }
        case 7:
        {
            loadingFunction = &WorldGenerator::TreeMap;
            HeightToMesh(heightMap[1]);

            loadingStage = 0;
            break;
        }
    }

    return;
}

void WorldGenerator::TreeMap()
{
    printf("TreeMap stage %d\r\n", loadingStage);

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
    MapToWorld();
    SCENE->ChangeScene("INGAME", 0.f)->Init();
}

void WorldGenerator::RiverMap()
{
    printf("RiverMap stage %d\r\n", loadingStage);
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
            riverMap[1] = LerpMap(riverMap[0]);
            RiverToMesh(riverMap[1]);
            break;
        }
        case 3:
        case 5:
        {
            riverMap[0] = LerpMap(riverMap[1]);
            RiverToMesh(riverMap[1]);
            break;
        }
        case 7:
        {
            loadingFunction = &WorldGenerator::RiverMap;
            RiverToMesh(riverMap[1]);
            loadingStage = 0;
            break;
        }
     }
    loadingStage++;
}

void WorldGenerator::MapToWorld()
{
    // Height Map
    {
        for (int i = 0; i < heightMap[1].size(); i++)
        {
            for (int j = 0; j < heightMap[1][0].size(); j++) {
                for (int k = 0; k < heightMap[1][i][j]; k++)
                    WORLD->SetBlockType({ i - (mapSize.x / 2), k, j - (mapSize.y / 2) }, BlockType::DIRT);
                if (char(heightMap[1][i][j]) < WATER_HEIGHT) {
                    for (int k = 0; k < heightMap[1][i][j]; k++)
                        WORLD->SetBlockType({ i - (mapSize.x / 2), k, j - (mapSize.y / 2) }, BlockType::DIRT);
                    for (int k = heightMap[1][i][j]; k <= WATER_HEIGHT; k++)
                        WORLD->SetBlockType({ i - (mapSize.x / 2), k, j - (mapSize.y / 2) }, BlockType::WATER);
                }
                else
                    WORLD->SetBlockType({ i - (mapSize.x / 2), heightMap[1][i][j], j - (mapSize.y / 2) }, BlockType::GRASS);
            }
        }
    }

    // Tree Map
    {
        for (int i = 0; i < mapSize.x; i++)
        {
            for (int j = 0; j < mapSize.y; j++) {
                if (treeMap[i][j] > 1) {
                    int groundHeight = heightMap[1][i][j] + 1;
                    int leafRadius = 3;

                    for (int k = 0; k < treeMap[i][j]; k++)
                        WORLD->SetBlockType({ i - (mapSize.x / 2), groundHeight + k, j - (mapSize.y / 2) }, BlockType::WOOD_OAK);

                    for (int _x = 0; _x < leafRadius; _x++)
                    {
                        for (int _z = 0; _z < leafRadius; _z++)
                        {
                            if (_x == 0 && _z == 0)
                                continue;
                            for (int _y = treeMap[i][j] - 2; _y < treeMap[i][j]; _y++) {
                                WORLD->SetBlockType({ i + _x - (mapSize.x / 2), groundHeight + _y, j + _z - (mapSize.y / 2) }, BlockType::LEAF);
                                WORLD->SetBlockType({ i + _x - (mapSize.x / 2), groundHeight + _y, j - _z - (mapSize.y / 2) }, BlockType::LEAF);
                                WORLD->SetBlockType({ i - _x - (mapSize.x / 2), groundHeight + _y, j + _z - (mapSize.y / 2) }, BlockType::LEAF);
                                WORLD->SetBlockType({ i - _x - (mapSize.x / 2), groundHeight + _y, j - _z - (mapSize.y / 2) }, BlockType::LEAF);
                            }
                        }
                    }
                    for (int _x = 0; _x < leafRadius-1; _x++)
                    {
                        for (int _z = 0; _z < leafRadius - 1; _z++)
                        {
                            for (int _y = treeMap[i][j]; _y < treeMap[i][j] + 2; _y++) {
                                WORLD->SetBlockType({ i + _x - (mapSize.x / 2), groundHeight + _y, j + _z - (mapSize.y / 2) }, BlockType::LEAF);
                                WORLD->SetBlockType({ i + _x - (mapSize.x / 2), groundHeight + _y, j - _z - (mapSize.y / 2) }, BlockType::LEAF);
                                WORLD->SetBlockType({ i - _x - (mapSize.x / 2), groundHeight + _y, j + _z - (mapSize.y / 2) }, BlockType::LEAF);
                                WORLD->SetBlockType({ i - _x - (mapSize.x / 2), groundHeight + _y, j - _z - (mapSize.y / 2) }, BlockType::LEAF);
                            }
                        }
                    }
                }
            }
        }
    }
    heightMap[0].clear();
    heightMap[1].clear();
    riverMap[0].clear();
    riverMap[1].clear();
    treeMap.clear();
    WORLD->CreateDumpBlocks();
    WORLD->distinguishBlocks({ 0, 0, 0 }, mapSize.x / 2);
    SCENE->SetCurrentScene(SCENE->GetScene("INGAME"));
}




void WorldGenerator::HeightToMesh(vector<vector<char>>& map)
{
    for (int i = 0; i < mapSize.x; i++)
    {
        for (int j = 0; j < mapSize.y; j++)
        {
            Color cc = { 255.f, 255.f, 255.f };
            float colorRGB = 255.f;// *static_cast<float>(map[i][j] / 10);

            if (map[i][j] < 5)
                cc = { 0.f, 0.f, colorRGB };
            else
                cc = { 0.f, colorRGB, 0.f };

            ((VertexPC*)(ui->mesh->vertices))[(((i * mapSize.x) + j) * 4) + 0].color = cc;
            ((VertexPC*)(ui->mesh->vertices))[(((i * mapSize.x) + j) * 4) + 1].color = cc;
            ((VertexPC*)(ui->mesh->vertices))[(((i * mapSize.x) + j) * 4) + 2].color = cc;
            ((VertexPC*)(ui->mesh->vertices))[(((i * mapSize.x) + j) * 4) + 3].color = cc;
        }
    }
    ui->mesh->UpdateMesh();
}

void WorldGenerator::RiverToMesh(vector<vector<bool>>& map)
{
    for (int i = 0; i < mapSize.x; i++)
    {
        for (int j = 0; j < mapSize.y; j++)
        {
            Color cc = { 255.f, 255.f, 255.f };
            if (map[i][j])
                cc = { 255.f, 255.f, 255.f };
            else
                cc = { 0.f, 0.f, 0.f };

            ((VertexPC*)(ui->mesh->vertices))[(((i * mapSize.x) + j) * 4) + 0].color = cc;
            ((VertexPC*)(ui->mesh->vertices))[(((i * mapSize.x) + j) * 4) + 1].color = cc;
            ((VertexPC*)(ui->mesh->vertices))[(((i * mapSize.x) + j) * 4) + 2].color = cc;
            ((VertexPC*)(ui->mesh->vertices))[(((i * mapSize.x) + j) * 4) + 3].color = cc;
        }
    }
    ui->mesh->UpdateMesh();
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
