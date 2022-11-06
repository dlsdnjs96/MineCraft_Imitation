#include "stdafx.h"
#include "Main.h"


#define BLOCK_FACE_UP		0b000001 // blue
#define BLOCK_FACE_DOWN		0b000010 // gray
#define BLOCK_FACE_RIGHT	0b000100 // pink
#define BLOCK_FACE_LEFT		0b001000 // red
#define BLOCK_FACE_FORWARD	0b010000 // green
#define BLOCK_FACE_BEHIND	0b100000 // orange


Main::Main()
{
    Init();
}

Main::~Main()
{

}


void Main::Init()
{
    VertexPT* vertices;
    UINT vertexCount = 4;
    UINT* indices;
    UINT indexCount = 6;
    VertexType type = VertexType::PT;

    vertices = new VertexPT[vertexCount];
    indices = new UINT[indexCount];

    vertices[0].position = { 1.0f, -1.0f, 0.f };
    vertices[1].position = { 1.0f, 1.0f, 0.f };
    vertices[2].position = { -1.0f, 1.0f, 0.f };
    vertices[3].position = { -1.0f, -1.0f, 0.f };

    vertices[0].uv = { 1.f, 1.f };
    vertices[1].uv = { 1.f, 0.f };
    vertices[2].uv = { 0.f, 0.f };
    vertices[3].uv = { 0.f, 1.f };


    int arr[6] = { 0, 1, 2, 0, 2, 3 };
    for (int j = 0; j < 6; j++)
        indices[j] = arr[j] + 0;

    


    Mesh* newMesh = new Mesh(vertices, vertexCount, indices, indexCount, type);
    newMesh->SaveFile("6.button0.mesh");

    printf("Saved mesh\r\n");
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

void Main::PreRender()
{
    SCENE->PreRender();
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
    //int wParam = (int)WIN->Run(main);
    main->Release();
    SafeDelete(main);
    D3D->DeleteSingleton();
    WIN->DeleteSingleton();

    return 0;
}