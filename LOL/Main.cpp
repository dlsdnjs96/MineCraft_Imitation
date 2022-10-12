#include "stdafx.h"
#include "Main.h"

Main::Main()
{

}

Main::~Main()
{

}


void Main::Init()
{
    SCENE->AddScene("INGAME", new InGameScene());
    SCENE->SetCurrentScene(SCENE->GetScene("INGAME"));

    ResizeScreen();

    int faceCount = 6;
    VertexPTN* vertices;
    UINT vertexCount = 4 * faceCount;
    UINT* indices;
    UINT indexCount = 6 * faceCount;
    VertexType type = VertexType::PTN;

    vertices = new VertexPTN[vertexCount];
    indices = new UINT[indexCount];

    vertices[0].position = { -1.f, 1.f, -1.f };
    vertices[1].position = { -1.f, 1.f, 1.f };
    vertices[2].position = { 1.f, 1.f, 1.f };
    vertices[3].position = { 1.f, 1.f, -1.f };

    vertices[4].position = { -1.f, -1.f, -1.f };
    vertices[5].position = { -1.f, 1.f, -1.f };
    vertices[6].position = { 1.f, 1.f, -1.f };
    vertices[7].position = { 1.f, -1.f, -1.f };

    vertices[8].position = { 1.f, -1.f, -1.f };
    vertices[9].position = { 1.f, 1.f, -1.f };
    vertices[10].position = { 1.f, 1.f, 1.f };
    vertices[11].position = { 1.f, -1.f, 1.f };

    vertices[12].position = { 1.f, -1.f, 1.f };
    vertices[13].position = { 1.f, 1.f, 1.f };
    vertices[14].position = { -1.f, 1.f, 1.f };
    vertices[15].position = { -1.f, -1.f, 1.f };

    vertices[16].position = { -1.f, -1.f, 1.f };
    vertices[17].position = { -1.f, 1.f, 1.f };
    vertices[18].position = { -1.f, 1.f, -1.f };
    vertices[19].position = { -1.f, -1.f, -1.f };

    vertices[20].position = { 1.f, -1.f, -1.f };
    vertices[21].position = { 1.f, -1.f, 1.f };
    vertices[22].position = { -1.f, -1.f, 1.f };
    vertices[23].position = { -1.f, -1.f, -1.f };



    for (int i = 0; i < faceCount; i++)
    {
        float arr[4][2] = { { 1.f, 0.f }, { 0.f, 0.f }, { 0.f, 0.166666f }, { 1.f, 0.166666f } };
        for (int j = 0; j < 4; j++)
            vertices[(i * 4) + j].uv = { arr[j][1] + ((i) * 0.166666f), arr[j][0] };
    }

    for (int i = 0; i < faceCount; i++)
    {
        int arr[6] = { 0, 1, 2, 0, 2, 3 };
        for (int j = 0; j < 6; j++)
            indices[(i * 6) + j] = arr[j] + (i * 4);
    }

    Mesh* newMesh = new Mesh(vertices, vertexCount, indices, indexCount, type);
    newMesh->SaveFile("TestCube.mesh");
}

void Main::Release()
{
    SCENE->Release();
}


void Main::Update()
{
    SCENE->Update();
}

void Main::LateUpdate()
{
    SCENE->LateUpdate();
}

void Main::Render()
{
    SCENE->Render();
}

void Main::ResizeScreen()
{
    SCENE->ResizeScreen();
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    App.SetAppName(L"MineCraft");
    App.SetInstance(instance);
    WIN->Create();
    D3D->Create();
    Main* main = new Main();
    main->Init();
    int wParam = (int)WIN->Run(main);
    main->Release();
    SafeDelete(main);
    D3D->DeleteSingleton();
    WIN->DeleteSingleton();

    return wParam;
}