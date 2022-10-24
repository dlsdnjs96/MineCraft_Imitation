#include "stdafx.h"

LoadingScene::LoadingScene()
{
    Cam = Camera::Create();
    Cam->LoadFile("Cam.xml");
    //Camera::main = Cam;


    t1 = new thread([=]()
        { WORLD_GENERATOR->GenerateWorld(); });

    t1->join();
    //WORLD->SaveWorld();

    SCENE->SetCurrentScene(SCENE->GetScene("INGAME"));
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
}

void LoadingScene::Release()
{
}

void LoadingScene::Update()
{
    printf("LoadingScene Update\r\n");
    Camera::ControlMainCam();

    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    ImGui::Begin("Hierarchy");
    WORLD_GENERATOR->RenderHierarchy();
    Cam->RenderHierarchy();
    ImGui::End();


    Cam->Update();
    WORLD_GENERATOR->Update();
    static int st = 0;
    st++;
    if (st >= 7) {
        WORLD->CreateDumpBlocks();
        WORLD->distinguishBlocks(Int3{0,0,0}, 1024);
        WORLD->UpdateMesh();
        SCENE->SetCurrentScene(SCENE->GetScene("INGAME"));
    }
}

void LoadingScene::LateUpdate()
{
}

void LoadingScene::Render()
{
    Camera::main->Set();
    WORLD_GENERATOR->Render();
}

void LoadingScene::ResizeScreen()
{
    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();
}
