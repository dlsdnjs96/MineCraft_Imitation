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
    cam = Camera::Create("Camera");
    cam->LoadFile("EditCam.xml");
    
    Grid = Actor::Create();
    Grid->LoadFile("Grid.xml");

    model = Actor::Create("Model");
    model->LoadFile("model.xml");

}

void Main::Release()
{
    cam->Release();
    Grid->Release();
    model->Release();
}


void Main::Update()
{
    cam->RenderHierarchy();
    Grid->RenderHierarchy();
    model->RenderHierarchy();

    cam->Update();
    Grid->Update();
    model->Update();
}

void Main::LateUpdate()
{
}

void Main::PreRender()
{
}

void Main::Render()
{
    cam->Set();
    Grid->Render();
    model->Render();
}

void Main::ResizeScreen()
{
    cam->width = App.GetWidth();
    cam->height = App.GetHeight();
    cam->viewport.width = App.GetWidth();
    cam->viewport.height = App.GetHeight();
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

    return 0;
}