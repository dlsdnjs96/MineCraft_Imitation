#include "stdafx.h"

InGameScene::InGameScene()
{
    Cam = Camera::Create();
    Cam->LoadFile("Cam.xml");
    Camera::main = Cam;

    Sphere = Actor::Create();
    Sphere->LoadFile("Sphere.xml");

    world.Init();
}

InGameScene::~InGameScene()
{
    RESOURCE->ReleaseAll();
    Sphere->Release();
    Cam->Release();
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
    world.RenderHierarchy();
    ImGui::End();


    Cam->Update();
    Sphere->Update();

    world.Update();
}

void InGameScene::LateUpdate()
{
}

void InGameScene::Render()
{
    Cam->Set();
    Sphere->Render();

    world.Render();
}

void InGameScene::ResizeScreen()
{
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();
}
