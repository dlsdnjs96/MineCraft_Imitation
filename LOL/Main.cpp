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
    printf("Block2 %d\r\n", sizeof(Block2));

    SCENE->AddScene("INGAME", new InGameScene());
//    SCENE->SetCurrentScene(SCENE->GetScene("INGAME"));

    SCENE->AddScene("LOADING", new LoadingScene());
    SCENE->SetCurrentScene(SCENE->GetScene("LOADING"));

    ResizeScreen();
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