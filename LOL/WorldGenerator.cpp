#include "stdafx.h"

WorldGenerator::WorldGenerator()
{
    ui = UI::Create("Climate_Graph");
    ui->shader = RESOURCE->shaders.Load("MapGraph.hlsl");
    ui->SetLocalPos({ -0.75f, -0.8f, 0.f });
    ui->scale = { 0.05f, 0.05f, 0.3f };

}

void WorldGenerator::Update()
{
    static int st = 0;
    HeightMap(st);
    ui->Update();
    st++;
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

void WorldGenerator::HeightMap(int stage)
{
    Int2 sectorSize = mapSize;

    srand(time(NULL));

    static vector<vector<char>> first_climate_map;
    static vector<vector<char>> tableMap[2];

    static int _x = rand(), _y = rand();


    if (stage == 0) {
        first_climate_map.resize(sectorSize.x);
        for (int i = 0; i < sectorSize.x; i++)
            first_climate_map[i].resize(sectorSize.y);

        for (int i = 0; i < sectorSize.x; i++)
        {
            for (int j = 0; j < sectorSize.y; j++)
            {
                //first_climate_map[i][j] = static_cast<char>((rand() % 20));

                float noise = Util::SmoothNoise(_x + i, _y + j) + 1.f;
                noise *= 10.f;

                first_climate_map[i][j] = static_cast<char>(abs(noise / 2));
                //     if ((int)(Util::noise2(i, j)+1.f)%2 == 0)
                         //first_climate_map[i][j] = static_cast<Climate>(5);
                //     else
                //         first_climate_map[i][j] = static_cast<Climate>(0);
            }
        }
        ui->mesh = MapToMesh(first_climate_map, char(10));
        printf("first_climate_map\r\n");

        tableMap[0].resize(sectorSize.x);
        for (int i = 0; i < sectorSize.x; i++)
            tableMap[0][i].resize(sectorSize.y);
        tableMap[1].resize(sectorSize.x);
        for (int i = 0; i < sectorSize.x; i++)
            tableMap[1][i].resize(sectorSize.y);
    }
    else if (stage == 1)
    {
        tableMap[0] = LerpMap(first_climate_map);
        ui->mesh = MapToMesh(tableMap[0], char(10));
    }
    else if (stage == 2)
    {
        tableMap[1] = LerpMap(tableMap[0]);
        ui->mesh = MapToMesh(tableMap[1], char(10));
    }
    else if (stage == 3)
    {
        tableMap[0] = LerpMap(tableMap[1]);
        ui->mesh = MapToMesh(tableMap[0], char(10));
    }
    else if (stage == 4)
    {
        tableMap[1] = LerpMap(tableMap[0]);
        ui->mesh = MapToMesh(tableMap[1], char(10));
    }
    else if (stage == 5)
    {
        tableMap[0] = LerpMap(tableMap[1]);
        ui->mesh = MapToMesh(tableMap[0], char(10));
    }
    else if (stage == 6)
    {
        //sectorSize = { 0, 0 };
        for (int i = 0; i < tableMap[0].size(); i++)
        {
            for (int j = 0; j < tableMap[0][0].size(); j++) {
                for (int k = 0; k < tableMap[0][i][j]; k++)
                    WORLD->SetBlockType({ i - (sectorSize.x / 2), k, j - (sectorSize.y / 2) }, BlockType::STONE);
                if (char(tableMap[0][i][j]) < 5)
                    WORLD->SetBlockType({ i - (sectorSize.x / 2), tableMap[0][i][j], j - (sectorSize.y / 2) }, BlockType::WATER);
                else
                    WORLD->SetBlockType({ i - (sectorSize.x / 2), tableMap[0][i][j], j - (sectorSize.y / 2) }, BlockType::GRASS);
                continue;
                if (char(tableMap[0][i][j]) < 5) {
                    for (int k = 0;k < 5;k++)
                        WORLD->SetBlockType({ i - (sectorSize.x / 2), k, j - (sectorSize.y / 2) }, BlockType::STONE);
                }
                else {
                    for (int k = 0; k < tableMap[0][i][j] - 1; k++)
                        WORLD->SetBlockType({ i - (sectorSize.x / 2), k, j - (sectorSize.y / 2) }, BlockType::STONE);
                    WORLD->SetBlockType({ i - (sectorSize.x / 2), tableMap[0][i][j] - 1, j - (sectorSize.y / 2) }, BlockType::GRASS);
                }
            }
        }


        //for (int i = -1; i < 1; i++)
        //{
        //    for (int j = -1;j < 1;j++)
        //        WORLD->SetBlockType(Int3{ i*2, 1, j * 2 }, BlockType::WOOD_OAK);
        //}
        //WORLD->SetBlockType(Int3{ 0, 1, 0 }, BlockType::EMPTY);
        //
        //WORLD->SetBlockType(Int3{ 10, 1, 10 }, BlockType::STONE);
        //WORLD->SetBlockType(Int3{ -10, 1, 10 }, BlockType::STONE);
        //WORLD->SetBlockType(Int3{ 10, 1, -10 }, BlockType::STONE);
        //WORLD->SetBlockType(Int3{ -10, 1, -10 }, BlockType::STONE);
        //WORLD->SetBlockType(Int3{ 10, 2, 10 }, BlockType::STONE);
        //WORLD->SetBlockType(Int3{ -10, 2, 10 }, BlockType::STONE);
        //WORLD->SetBlockType(Int3{ 10, 2, -10 }, BlockType::STONE);
        //WORLD->SetBlockType(Int3{ -10, 2, -10 }, BlockType::STONE);
        //WORLD->SetBlockType(Int3{ 0, 0, 0 }, BlockType::WATER);
        //WORLD->SetBlockType(Int3{ 1, 1, 1 }, BlockType::WATER);
        //WORLD->SetBlockType(Int3{ -1, 1, 1 }, BlockType::STONE);
        //WORLD->SetBlockType(Int3{ 1, 1, -1 }, BlockType::GRASS);
        //WORLD->SetBlockType(Int3{ -1, 1, -1 }, BlockType::WOOD_OAK);
        ui->mesh = MapToMesh(tableMap[0], char(10));
    }

    return;
}


void WorldGenerator::DecideClimate()
{
	Int2 sectorSize = mapSize;

    srand(time(NULL));

	vector<vector<Climate>> first_climate_map;

	first_climate_map.resize(sectorSize.x);
	for (int i = 0; i < sectorSize.x; i++)
		first_climate_map[i].resize(sectorSize.y);

	for (int i = 0; i < sectorSize.x; i++)
	{
        for (int j = 0; j < sectorSize.y; j++)
        {
			first_climate_map[i][j] = static_cast<Climate>((rand() % 2) * 5);
       //     if ((int)(Util::noise2(i, j)+1.f)%2 == 0)
			    //first_climate_map[i][j] = static_cast<Climate>(5);
       //     else
       //         first_climate_map[i][j] = static_cast<Climate>(0);
        }
	}
    //ui->mesh = ClimateMapToMesh(first_climate_map);
    printf("first_climate_map\r\n");

	sectorSize = mapSize;
    vector<vector<Climate>> tableMap[2];

    tableMap[0].resize(sectorSize.x);
    for (int i = 0; i < sectorSize.x; i++)
        tableMap[0][i].resize(sectorSize.y);
    tableMap[1].resize(sectorSize.x);
    for (int i = 0; i < sectorSize.x; i++)
        tableMap[1][i].resize(sectorSize.y);

    tableMap[0] = LerpMap(first_climate_map);


    for (int i = 0; i < 6; i++)
    {
        if (i%2 == 0)
            tableMap[1] = LerpMap(tableMap[0]);
        else
            tableMap[0] = LerpMap(tableMap[1]);
    }


    ui->mesh = MapToMesh(tableMap[0], Climate::WARM_CLIMATE);
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
shared_ptr<Mesh> WorldGenerator::MapToMesh(vector<vector<T>>& map, T maxV)
{
    VertexPC* vertices;
    UINT vertexCount = 4 * map.size() * map[0].size();
    UINT* indices;
    UINT indexCount = 3 * (vertexCount / 2);
    VertexType type = VertexType::PC;

    vertices = new VertexPC[vertexCount];
    indices = new UINT[indexCount];

    float vertexDistance = 10.f / map.size();

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            float _x = i * vertexDistance - 5.f;
            float _y = j * vertexDistance - 5.f;
            vertices[(((i * map.size()) + j) * 4) + 0].position = { _x, _y, 0.f };
            vertices[(((i * map.size()) + j) * 4) + 1].position = { _x, _y + vertexDistance, 0.f };
            vertices[(((i * map.size()) + j) * 4) + 2].position = { _x + vertexDistance, _y + vertexDistance, 0.f };
            vertices[(((i * map.size()) + j) * 4) + 3].position = { _x + vertexDistance, _y, 0.f };

            //vertices[(((i * map.size()) + j) * 4) + 0].color = { static_cast<float>(map[i][j]) / static_cast<float>(maxV), static_cast<float>(map[i][j]) / static_cast<float>(maxV), static_cast<float>(map[i][j]) / static_cast<float>(maxV) };
            //vertices[(((i * map.size()) + j) * 4) + 1].color = { static_cast<float>(map[i][j]) / static_cast<float>(maxV), static_cast<float>(map[i][j]) / static_cast<float>(maxV), static_cast<float>(map[i][j]) / static_cast<float>(maxV) };
            //vertices[(((i * map.size()) + j) * 4) + 2].color = { static_cast<float>(map[i][j]) / static_cast<float>(maxV), static_cast<float>(map[i][j]) / static_cast<float>(maxV), static_cast<float>(map[i][j]) / static_cast<float>(maxV) };
            //vertices[(((i * map.size()) + j) * 4) + 3].color = { static_cast<float>(map[i][j]) / static_cast<float>(maxV), static_cast<float>(map[i][j]) / static_cast<float>(maxV), static_cast<float>(map[i][j]) / static_cast<float>(maxV) };
            Color cc;
            
            if (char(map[i][j]) < 5)
                cc = { 0.f, 0.f, static_cast<float>(map[i][j]) / static_cast<float>(maxV) };
            else
                cc = { 0.f, static_cast<float>(map[i][j]) / static_cast<float>(maxV), 0.f };

            vertices[(((i * map.size()) + j) * 4) + 0].color = cc;
            vertices[(((i * map.size()) + j) * 4) + 1].color = cc;
            vertices[(((i * map.size()) + j) * 4) + 2].color = cc;
            vertices[(((i * map.size()) + j) * 4) + 3].color = cc;
        }
    }

    int idx = 0;
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[0].size(); j++)
        {
            indices[idx] = (((i * map.size()) + j) * 4) + 0;
            idx++;
            indices[idx] = (((i * map.size()) + j) * 4) + 1;
            idx++;
            indices[idx] = (((i * map.size()) + j) * 4) + 2;
            idx++;

            indices[idx] = (((i * map.size()) + j) * 4) + 0;
            idx++;
            indices[idx] = (((i * map.size()) + j) * 4) + 2;
            idx++;
            indices[idx] = (((i * map.size()) + j) * 4) + 3;
            idx++;
        }
    }

    shared_ptr<Mesh> newMesh = make_shared<Mesh>(vertices, vertexCount, indices, indexCount, type);
    return newMesh;
}
