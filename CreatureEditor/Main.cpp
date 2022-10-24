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
    VertexPTN* vertices;
    UINT vertexCount = 4;
    UINT* indices;
    UINT indexCount = 6;
    VertexType type = VertexType::PTN;

    vertices = new VertexPTN[vertexCount];
    indices = new UINT[indexCount];

    vertices[0].position = { 5.0f, -5.0f, 5.0f };
    vertices[1].position = { 5.0f, 5.0f, 5.0f };
    vertices[2].position = { -5.0f, 5.0f, 5.0f };
    vertices[3].position = { -5.0f, -5.0f, 5.0f };




    float _x = 3.f / 6.f, _y = 0.f;

    float arr[4][2] = { { 0.f, 0.f }, { 0.f, 1.f }, { 1.f / 6.f, 1.f }, { 1.f / 6.f, 0.f } };
    for (int j = 0; j < 4; j++)
        vertices[j].uv = { _x + arr[j][0], _y + arr[j][1] };
    

    //int arr2[6] = { 2, 1, 0, 2, 0, 3 };
    int arr2[6] = { 0, 1, 2, 0, 2, 3 };
    for (int j = 0; j < 6; j++)
        indices[j] = arr2[j] + 0;

    


    Mesh* newMesh = new Mesh(vertices, vertexCount, indices, indexCount, type);
    newMesh->SaveFile("Block/"+to_string(int(BLOCK_FACE_BEHIND)) + ".mesh");

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