#include "stdafx.h"
#include "Main.h"

Main::Main()
{
    //float min = FLT_MAX, max = FLT_MIN, temp;
    //
    //for (int i = 0; i < 40000; i++)
    //{
    //    for (int j = 0; j < 40000; j++)
    //    {
    //        temp = Util::SmoothNoise(i, j);
    //        //printf("%f\r\n", Util::SmoothNoise(i, j));
    //        if (min > temp)
    //            min = temp;
    //        if (max < temp)
    //            max = temp;
    //    }
    //}
    //printf("max %f\r\n", max);
    //printf("min %f\r\n", min);

    //Actor* actor = Actor::Create("Block");
    //for (int i = 1; i < 200; i++)
    //{
    //    if (TEXTURE_DATA->blockUV.find(BlockType(i)) != TEXTURE_DATA->blockUV.end())
    //    {
    //        EditObject* editObject = EditObject::Create(to_string(i));
    //        editObject->imgSize = { 1.f, 1.f };
    //
    //
    //        editObject->uvUp.first = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_UP];
    //        editObject->uvDown.first = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_DOWN];
    //        editObject->uvRight.first = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_RIGHT];
    //        editObject->uvLeft.first = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_LEFT];
    //        editObject->uvFront.first = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_FORWARD];
    //        editObject->uvBack.first = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_BEHIND];
    //
    //        editObject->uvUp.second = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_UP] + Vector2{ 1.f / 16.f, 1.f / 16.f };
    //        editObject->uvDown.second = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_DOWN] + Vector2{ 1.f / 16.f, 1.f / 16.f };
    //        editObject->uvRight.second = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_RIGHT] + Vector2{ 1.f / 16.f, 1.f / 16.f };
    //        editObject->uvLeft.second = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_LEFT] + Vector2{ 1.f / 16.f, 1.f / 16.f };
    //        editObject->uvFront.second = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_FORWARD] + Vector2{ 1.f / 16.f, 1.f / 16.f };
    //        editObject->uvBack.second = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_BEHIND] + Vector2{ 1.f / 16.f, 1.f / 16.f };
    //
    //        actor->AddChild(editObject);
    //
    //        editObject->mesh = editObject->EditMesh();
    //        editObject->mesh->SaveFile(editObject->root->name + "/" + editObject->name + ".mesh");
    //    }
    //}
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