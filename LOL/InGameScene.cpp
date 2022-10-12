#include "stdafx.h"

InGameScene::InGameScene()
{
    Cam = Camera::Create();
    Cam->LoadFile("Cam.xml");

    Sphere = Actor::Create();
    Sphere->LoadFile("Sphere.xml");

    Grid = Actor::Create();
    Grid->LoadFile("Grid.xml");

    player = new Player();
    player->Init();
    Camera::main = dynamic_cast<Camera*>(player->body->Find("camBody"));


    world.Init();
}

InGameScene::~InGameScene()
{
    RESOURCE->ReleaseAll();
    Sphere->Release();
    Cam->Release();
    Grid->Release();
    player->Release();
}

void InGameScene::Init()
{
}

void InGameScene::Release()
{
}

void InGameScene::Update()
{
    Camera::ControlMainCam();

    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    ImGui::Begin("Hierarchy");
    Sphere->RenderHierarchy();
    Cam->RenderHierarchy();
    Grid->RenderHierarchy();
    player->RenderHierarchy();
    world.RenderHierarchy();
    ImGui::End();


    Cam->Update();
    Sphere->Update();
    Grid->Update();
    player->Update();

    world.Update();
}

void InGameScene::LateUpdate()
{
}

void InGameScene::Render()
{
    Camera::main->Set();
    Sphere->Render();
    Grid->Render();
    player->Render();

    world.Render();
}

void InGameScene::ResizeScreen()
{
    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();
}
