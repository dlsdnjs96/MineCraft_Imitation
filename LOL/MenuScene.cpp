#include "stdafx.h"


MenuScene::MenuScene()
{
    Init();
    DATABASE;
}

MenuScene::~MenuScene()
{
}

void MenuScene::Init()
{
    sky = Sky::Create();
    //sky->texCube->LoadFile("sky.dds");

    Cam = Camera::Create("Camera");
    Camera::main = Cam;


    //phase 1///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    title = UI::Create("Title");
    title->LoadFile("Menu/Title.xml");

    singlePlay = UI::Create("SinglePlay");
    singlePlay->LoadFile("Menu/SinglePlay.xml");

    setting = UI::Create("Setting");
    setting->LoadFile("Menu/Setting.xml");

    exit = UI::Create("Exit");
    exit->LoadFile("Menu/Exit.xml");


    singlePlay->mouseOver = [=]() { singlePlay->material = RESOURCE->materials.Load("button2.mtl"); };
    singlePlay->mouseNotOver = [=]() { singlePlay->material = RESOURCE->materials.Load("button1.mtl"); };
    singlePlay->mouseDown = [=]() { ChangePage(2); };

    setting->mouseOver = [=]() { setting->material = RESOURCE->materials.Load("button2.mtl"); };
    setting->mouseNotOver = [=]() { setting->material = RESOURCE->materials.Load("button1.mtl"); };

    exit->mouseOver = [=]() { exit->material = RESOURCE->materials.Load("button2.mtl"); };
    exit->mouseNotOver = [=]() { exit->material = RESOURCE->materials.Load("button1.mtl"); };
    exit->mouseDown = [=]() { PostQuitMessage(0); };


    //phase 2///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    worldList = new WorldList();
    worldList->Init();

    createWorld = UI::Create("CreateWorld");
    createWorld->LoadFile("Menu/CreateWorld.xml");

    prev = UI::Create("Prev");
    prev->LoadFile("Menu/Prev.xml");


    createWorld->mouseOver = [=]() { createWorld->material = RESOURCE->materials.Load("button2.mtl"); };
    createWorld->mouseNotOver = [=]() { createWorld->material = RESOURCE->materials.Load("button1.mtl"); };
    createWorld->mouseDown = [=]() { 
        time_t timer = time(NULL);
        struct tm pLocal;
        localtime_s(&pLocal, &timer);
        //WORLD->name = "NewWorld_"+to_string(pLocal.tm_year) + to_string(pLocal.tm_mon) + to_string(pLocal.tm_mday)
        //    + "_" + to_string(pLocal.tm_hour) + to_string(pLocal.tm_min) + to_string(pLocal.tm_sec);
        WORLD->name = "NewWorld";
        DATABASE->SaveWolrd();
        DATABASE->UpdateWolrdId();
        SCENE->ChangeScene("LOADING", 0.1f)->Init(); };

    prev->mouseOver = [=]() { prev->material = RESOURCE->materials.Load("button2.mtl"); };
    prev->mouseNotOver = [=]() { prev->material = RESOURCE->materials.Load("button1.mtl"); };
    prev->mouseDown = [=]() { ChangePage(1); };

    ChangePage(1);
}

void MenuScene::Release()
{
    sky->Release();
    Cam->Release(); 
    singlePlay->Release();
    setting->Release();
    exit->Release();
    title->Release();
    prev->Release();
}

void MenuScene::Update()
{
    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());

    ImGui::Begin("Hierarchy");
    Cam->RenderHierarchy();

    for (auto iter : activeObj)
        iter->RenderHierarchy();
    ImGui::End();

    Cam->rotation.y += DELTA / 5.f;
    Cam->Update();
    for (auto iter : activeObj)
        iter->Update();

}

void MenuScene::LateUpdate()
{
}

void MenuScene::PreRender()
{
}

void MenuScene::Render()
{
    Cam->Set();
    for (auto iter : activeObj)
        iter->Render();
}

void MenuScene::ResizeScreen()
{
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();
}

void MenuScene::ChangePage(int _page)
{
    page = _page;
    activeObj.clear();

    switch (page)
    {
        case 1:
        {
            activeObj.push_back(sky);
            //DEPTH->Set(false);
            activeObj.push_back(singlePlay);
            activeObj.push_back(setting);
            activeObj.push_back(exit);
            activeObj.push_back(title);
            //DEPTH->Set(true);
            break;
        }
        case 2:
        {
            activeObj.push_back(worldList);
            activeObj.push_back(createWorld);
            activeObj.push_back(prev);
            break;
        }
    }
}
