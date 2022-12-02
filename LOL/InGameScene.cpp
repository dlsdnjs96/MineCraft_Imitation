#include "stdafx.h"

InGameScene::InGameScene()
{
    sky = Sky::Create();
    sky->texCube->LoadFile("sky3.dds");
    TestBlock = Actor::Create();
    TestBlock->LoadFile("TestBlock.xml");

    Grid = Actor::Create();
    Grid->LoadFile("Grid.xml");

    //player = new Player();
    //player->Init();
    //Player::user = player;



    //WORLD->LoadWorld();
    //WORLD->SaveWorld();
    resume = UI::Create("Resume");
    resume->LoadFile("Ingame/Resume.xml");
    setting = UI::Create("Setting");
    setting->LoadFile("Ingame/Setting.xml");
    exit = UI::Create("Exit");
    exit->LoadFile("Ingame/Exit.xml");

    aim = UI::Create("Aim");
    aim->LoadFile("Ingame/Aim.xml");

    Init();
}

InGameScene::~InGameScene()
{
    RESOURCE->ReleaseAll();
    Grid->Release();
    //player->Release();
    Cam->Release();
    resume->Release();
    setting->Release();
    exit->Release();
    aim->Release();
    TestBlock->Release();
    ITEM_DETAIL->Release();
    MONSTER_MANAGER->Release();
    FURNACE_MANAGER->Release();
    sky->Release();
}

void InGameScene::Init()
{
    playerModel = new PlayerModel();
    playerModel->Init();
    PlayerModel::user = playerModel;
    playerView = new PlayerView(playerModel);
    playerController = new PlayerController(playerModel);

    Camera::main->nearZ = 0.3f;
    Camera::main->farZ = 5000.f;

    WORLD->Init();
    menuTab = false;

    resume->mouseOver = [=]() { resume->material = RESOURCE->materials.Load("button2.mtl"); };
    resume->mouseNotOver = [=]() { resume->material = RESOURCE->materials.Load("button1.mtl"); };
    resume->mouseDown = [=]() {
        SOUND->Play("click");
        POINT cursor;
        if (GetCursorPos(&cursor)) {
            INPUT->fixedMousePos.x = cursor.x;
            INPUT->fixedMousePos.y = cursor.y;
            INPUT->prevPosition = INPUT->position;
        }
        Util::CursorVisible(false);
        aim->visible = true;
        menuTab = false; };

    setting->mouseOver = [=]() { setting->material = RESOURCE->materials.Load("button2.mtl"); };
    setting->mouseNotOver = [=]() { setting->material = RESOURCE->materials.Load("button1.mtl"); };

    exit->mouseOver = [=]() { exit->material = RESOURCE->materials.Load("button2.mtl"); };
    exit->mouseNotOver = [=]() { exit->material = RESOURCE->materials.Load("button1.mtl"); };
    exit->mouseDown = [=]() { SOUND->Play("click"); WORLD->SaveWorld(); SCENE->ChangeScene("MENU", 0.1f)->Init(); };

    INVENTORY->Init();
    CRAFTING->Init();
    ITEM_DETAIL->Init();
    MONSTER_MANAGER->Init();
    FURNACE_MANAGER->Init();

    //SOUND->AddSound("Henesys.wav", "Henesys", false);
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
    //static bool first_lock = Util::LockMouse();

    if (INPUT->KeyDown('T')) {
        MONSTER_MANAGER->Spawn(MonsterType::COW, Camera::main->GetWorldPos());
    }
    if (INPUT->KeyDown('Y')) {
        MONSTER_MANAGER->Spawn(MonsterType::SHEEP, Camera::main->GetWorldPos());
    }
    if (INPUT->KeyDown('U')) {
        MONSTER_MANAGER->Spawn(MonsterType::PIG, Camera::main->GetWorldPos());
    }
    if (INPUT->KeyDown(VK_ESCAPE)) {
        menuTab = true;
        CRAFTING->active = false;
        INVENTORY->showInven = false;
        Util::UnLockMouse();
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
    playerModel->RenderHierarchy();
    Camera::main->RenderHierarchy();
    TestBlock->RenderHierarchy();
    WORLD->RenderHierarchy();
    ITEM_MANAGER->RenderHierarchy();
    INVENTORY->RenderHierarchy();
    CRAFTING->RenderHierarchy();
    ITEM_DETAIL->RenderHierarchy();
    MONSTER_MANAGER->RenderHierarchy();
    FURNACE_MANAGER->RenderHierarchy();
    sky->RenderHierarchy();

    resume->RenderHierarchy();
    setting->RenderHierarchy();
    exit->RenderHierarchy();
    aim->RenderHierarchy();
    ImGui::End();

    if (menuTab)
    {
        resume->Update();
        setting->Update();
        exit->Update();
    }
    else {
        Grid->Update();

        Camera::main->Update();
        WORLD->Update();
        aim->Update();
        TestBlock->Update();
    }
    playerController->Update();
    playerModel->Update();
    playerView->Update();
    ITEM_MANAGER->Update();
    INVENTORY->Update();
    CRAFTING->Update();
    ITEM_DETAIL->Update();
    MONSTER_MANAGER->Update();
    FURNACE_MANAGER->Update();
    sky->Update();

    //if (INPUT->KeyDown(VK_LBUTTON))
    //{
    //    Vector3 temp = INPUT->movePosition;
    //    Ray rayToAim = Util::AimToRay(Cam);
    //    int mIndex = Util::RayIntersectSquareNear(rayToAim, TestBlock);
    //    printf("mIndex %d\r\n", mIndex);
    //}
}

void InGameScene::LateUpdate()
{
}

void InGameScene::PreRender()
{
}

void InGameScene::Render()
{
    Camera::main->Set();
    sky->Render();
    Grid->Render();

    playerView->Render();
    WORLD->PreRender();

    BLEND->Set(true);
    WORLD->Render();
    BLEND->Set(false);
    aim->Render();
    TestBlock->Render();
    ITEM_MANAGER->Render();
    INVENTORY->Render();
    CRAFTING->Render();
    ITEM_DETAIL->Render();
    MONSTER_MANAGER->Render();
    FURNACE_MANAGER->Render();

    if (menuTab)
    {
        resume->Render();
        setting->Render();
        exit->Render();
    }
}

void InGameScene::ResizeScreen()
{
    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();
}

