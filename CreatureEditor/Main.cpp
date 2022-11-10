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
    VertexP cubeEdges[8] = { 
        {{ -1.f, 1.f,  -1.f }},
        {{ -1.f, 1.f,  1.f }},
        {{ 1.f,  1.f,  1.f }},
        {{ 1.f,  1.f,  -1.f }},
        {{ -1.f, -1.f, -1.f }},
        {{ -1.f, -1.f, 1.f }},
        {{ 1.f,  -1.f, 1.f }},
        {{ 1.f,  -1.f, -1.f }}
    };

    int edgesIndex[6][4] = {
        { 3, 2, 1, 0 },
        { 6, 7, 4, 5 },
        { 6, 2, 3, 7 },
        { 4, 0, 1, 5 },
        { 7, 3, 0, 4 },
        { 5, 1, 2, 6 }
    };

    VertexP* vertices;
    UINT vertexCount = 6 * 4;
    UINT* indices;
    UINT indexCount = 6 * 6;
    VertexType type = VertexType::P;

    vertices = new VertexP[vertexCount];
    indices = new UINT[indexCount];

    int vIndex = 0, iIndex = 0;


    for (int j = 0; j < 6; j++) {

        for (int i = 0; i < 4; i++) {
            vertices[vIndex].position = cubeEdges[edgesIndex[j][i]].position;
            vertices[vIndex].position *= 1.f;
            vIndex++;
        }
        int arr[6] = { 0, 1, 2, 0, 2, 3 };

        for (int i = 0; i < 6; i++) {
            indices[iIndex] = arr[i] + vIndex - 4;
            iIndex++;
        }
    }


    


    Mesh* newMesh = new Mesh(vertices, vertexCount, indices, indexCount, type);
    newMesh->SaveFile("6.blockCollider.mesh");

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