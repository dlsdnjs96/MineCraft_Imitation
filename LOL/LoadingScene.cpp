#include "stdafx.h"

LoadingScene::LoadingScene()
{
    Init();

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
    WORLD_GENERATOR->Init();

    Cam = Camera::Create();
    Cam->LoadFile("Loading/Cam.xml");
    Camera::main = Cam;

    stage = Text::Create("Stage");
    stage->SetLocalPos({ 0.45f, 0.75f, 0.f });
    stage->scale = { 0.3f, 0.5f, 1.f, };

    backGround = Actor::Create("Background");
    backGround->LoadFile("Loading/background.xml");
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
    stage->RenderHierarchy();
    backGround->RenderHierarchy();
    ImGui::End();


    Cam->Update();
    WORLD_GENERATOR->Update();
    stage->ChangeText(WORLD_GENERATOR->GetStageName());
    stage->Update();
    backGround->Update();
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
    stage->Render();
    backGround->Render();
}

void LoadingScene::ResizeScreen()
{
    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();
}
