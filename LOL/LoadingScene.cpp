#include "stdafx.h"

LoadingScene::LoadingScene()
{
    Cam = Camera::Create();
    Cam->LoadFile("Cam.xml");
    //Camera::main = Cam;



    //SCENE->SetCurrentScene(SCENE->GetScene("INGAME"));
    return;
}

LoadingScene::~LoadingScene()
{
    RESOURCE->ReleaseAll();
    WORLD_GENERATOR->Release();
    Cam->Release();
}

void LoadingScene::Init()
{
    Camera::main = Cam;
    WORLD_GENERATOR->Init();
}

void LoadingScene::Release()
{
}

void LoadingScene::Update()
{
    Camera::ControlMainCam();

    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    ImGui::Begin("Hierarchy");
    WORLD_GENERATOR->RenderHierarchy();
    Cam->RenderHierarchy();
    ImGui::End();


    Cam->Update();

    WORLD_GENERATOR->Update();
}

void LoadingScene::LateUpdate()
{
}

void LoadingScene::PreRender()
{
}

void LoadingScene::Render()
{
    Cam->Set();
    WORLD_GENERATOR->Render();
}

void LoadingScene::ResizeScreen()
{
    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();
}
