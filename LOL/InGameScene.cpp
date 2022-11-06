#include "stdafx.h"

InGameScene::InGameScene()
{

    Grid = Actor::Create();
    Grid->LoadFile("Grid.xml");

    player = new Player();
    player->Init();

    Cam = dynamic_cast<Camera*>(player->Find("camHead"));
    //WORLD->LoadWorld();
    //WORLD->SaveWorld();
    resume = UI::Create("Resume");
    resume->LoadFile("Ingame/Resume.xml");
    setting = UI::Create("Setting");
    setting->LoadFile("Ingame/Setting.xml");
    exit = UI::Create("Exit");
    exit->LoadFile("Ingame/Exit.xml");
}

InGameScene::~InGameScene()
{
    RESOURCE->ReleaseAll();
    Grid->Release();
    player->Release();
}

void InGameScene::Init()
{
    Cam = dynamic_cast<Camera*>(player->Find("camHead"));
    Cam->nearZ = 0.3f;
    Cam->farZ = 5000.f;
    Camera::main = Cam;
    WORLD->Init();
    menuTab = false;

    resume->mouseOver = [=]() { resume->material = RESOURCE->materials.Load("button2.mtl"); };
    resume->mouseNotOver = [=]() { resume->material = RESOURCE->materials.Load("button1.mtl"); };
    resume->mouseDown = [=]() { menuTab = false; };

    setting->mouseOver = [=]() { setting->material = RESOURCE->materials.Load("button2.mtl"); };
    setting->mouseNotOver = [=]() { setting->material = RESOURCE->materials.Load("button1.mtl"); };

    exit->mouseOver = [=]() { exit->material = RESOURCE->materials.Load("button2.mtl"); };
    exit->mouseNotOver = [=]() { exit->material = RESOURCE->materials.Load("button1.mtl"); };
    exit->mouseDown = [=]() { WORLD->SaveWorld(); SCENE->ChangeScene("MENU", 0.f)->Init(); };
}

void InGameScene::Release()
{
    //Grid->Release();
    //player->Release();
    //Cam->Release();
    //resume->Release();
    //setting->Release();
    //exit->Release();
}

void InGameScene::Update()
{
    if (INPUT->KeyDown(VK_ESCAPE)) {
        menuTab = true;
        INPUT->fixedMousePos.x = -1;
    }

    if (INPUT->KeyDown(VK_F1)) {
        POINT cursor;
        if (GetCursorPos(&cursor)) {
            INPUT->fixedMousePos.x = cursor.x;
            INPUT->fixedMousePos.y = cursor.y;
            INPUT->prevPosition = INPUT->position;
        }
    }

    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    ImGui::Begin("Hierarchy");
    Grid->RenderHierarchy();
    player->RenderHierarchy();
    Cam->RenderHierarchy();
    WORLD->RenderHierarchy();

    resume->RenderHierarchy();
    setting->RenderHierarchy();
    exit->RenderHierarchy();
    ImGui::End();

    if (menuTab)
    {
        resume->Update();
        setting->Update();
        exit->Update();
    }
    else {
        Grid->Update();

        Cam->Update();
        WORLD->Update();
        player->Update();
    }

}

void InGameScene::LateUpdate()
{
}

void InGameScene::PreRender()
{
}

void InGameScene::Render()
{
    Cam->Set();
    Grid->Render();

    player->Render();
    WORLD->PreRender();

    BLEND->Set(true);
    WORLD->Render();
    BLEND->Set(false);

    if (menuTab)
    {
        resume->Render();
        setting->Render();
        exit->Render();
    }
}

void InGameScene::ResizeScreen()
{
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();
}
