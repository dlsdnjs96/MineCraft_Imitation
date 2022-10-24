#include "stdafx.h"

InGameScene::InGameScene()
{

    Grid = Actor::Create();
    Grid->LoadFile("Grid.xml");

    player = new Player();
    player->Init();
    Camera::main = dynamic_cast<Camera*>(player->Find("camHead"));


   // WORLD->Init();
    //WORLD->SaveWorld();
}

InGameScene::~InGameScene()
{
    RESOURCE->ReleaseAll();
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
    Grid->RenderHierarchy();
    player->RenderHierarchy();
    WORLD->RenderHierarchy();
    ImGui::End();


    Grid->Update();

    WORLD->Update();
    player->Update();
}

void InGameScene::LateUpdate()
{
}

void InGameScene::Render()
{
    Camera::main->Set();
    Grid->Render();

    WORLD->Render();
    player->Render();
}

void InGameScene::ResizeScreen()
{
    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();
}
