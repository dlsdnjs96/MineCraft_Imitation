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
    SCENE->AddScene("LOADING", new LoadingScene());
    SCENE->AddScene("MENU", new MenuScene());

    SCENE->SetCurrentScene(SCENE->GetScene("MENU"));

    ResizeScreen();
    SETTING->Init();
}

void Main::Release()
{
    SCENE->Release();
    WORLD->Release();
    SETTING->Release();
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
    int wParam = (int)WIN->Run(main);
    main->Release();
    SafeDelete(main);
    D3D->DeleteSingleton();
    WIN->DeleteSingleton();

    return wParam;
}