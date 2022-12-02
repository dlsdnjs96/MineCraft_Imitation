#include "stdafx.h"
#include "Main.h"


#include <filesystem>


#define BLOCK_FACE_UP		0b000001 // blue
#define BLOCK_FACE_DOWN		0b000010 // gray
#define BLOCK_FACE_RIGHT	0b000100 // pink
#define BLOCK_FACE_LEFT		0b001000 // red
#define BLOCK_FACE_FORWARD	0b010000 // green
#define BLOCK_FACE_BEHIND	0b100000 // orange


Main::Main()
{
    Init();
}

Main::~Main()
{

}


void Main::Init()
{
    cam = Camera::Create("Camera");
    cam->LoadFile("EditCam.xml");
    
    Grid = Actor::Create();
    Grid->LoadFile("Grid.xml");

    model = Actor::Create("Spider");
    model->LoadFile("Monster/Spider.xml");

    player = Actor::Create("Player2");
    BlockTexture();
    return;
    //player->LoadFile("Player.xml");

    //MESH_FACTORY->ItemMesh();
    //TextureToMaterial();

    //FILE* fp2 = nullptr;
    //freopen_s(&fp2, "output.txt", "w", stdout);
    //for (int i = 265; i < 3000; i++)
    //{
    //    if (ITEM_MANAGER->GetItemName(i) != "Unknown")
    //    {
    //        printf("{ \"%s\", %d }, \n", ITEM_MANAGER->GetItemName(i), i);
    //    }
    //}
    //return;

    FILE* fp1 = nullptr;
    //freopen_s(&fp1, "input.txt", "r", stdin);

    string filename("input.txt");
    ifstream input_file(filename);
    for (int i = 0; i < 441; i++)
    {
        string n;
        char tmp[1001];
        string str;

        

        getline(input_file, n);  // getline(cin, str, '\n')과 같음 
        getline(input_file, str);  // getline(cin, str, '\n')과 같음 
        //scanf_s("%[^\n]\n", tmp);
        //string a = tmp;
        for (int j = 0; j < str.size(); j++) {
            str[j] = toupper(str[j]);
            if (str[j] == ' ')
                str[j] = '_';
        }
        printf("{ %s, \"%s\" },\n", n.c_str(), str.c_str());
        getline(input_file, str);
        //printf("-%s\r\n", str.c_str());
        //cin.ignore();
    }
}

void Main::Release()
{
    cam->Release();
    Grid->Release();
    model->Release();
    player->Release();
}


void Main::Update()
{
    cam->RenderHierarchy();
    Grid->RenderHierarchy();
    model->RenderHierarchy();
    player->RenderHierarchy();

    cam->Update();
    Grid->Update();
    model->Update();
    player->Update();
}

void Main::LateUpdate()
{
}

void Main::PreRender()
{
}

void Main::Render()
{
    cam->Set();
    //Grid->Render();
    model->Render();
    player->Render();
}

void Main::ResizeScreen()
{
    cam->width = App.GetWidth();
    cam->height = App.GetHeight();
    cam->viewport.width = App.GetWidth();
    cam->viewport.height = App.GetHeight();
}

void Main::TextureToMaterial()
{
    FILE* fp = nullptr;
    freopen_s(&fp, "output.txt", "w", stdout);
    if (filesystem::exists("../Contents/Texture"))
    {
        for (filesystem::path const& path : filesystem::directory_iterator("../Contents/Texture/items/"))
        {
            if (filesystem::is_regular_file(path))
            {
                string worldName = path.string().substr(path.string().find_last_of('/') + 1);
                shared_ptr<Material> temp = make_shared<Material>();
                temp->diffuseMap = RESOURCE->textures.Load("items/"+ worldName.substr(0, worldName.find_last_of('.'))+".png");
                temp->file = "/Items/" + worldName.substr(0, worldName.find_last_of('.')) +".mtl";
                printf("{ 0, \"%s\" },\n", worldName.substr(0, worldName.find_last_of('.')).c_str());
                temp->diffuse.w = 1.0f;
                temp->SaveFile(temp->file);
            }
        }
    }
}

void Main::BlockTexture()
{
    Actor* actor = Actor::Create("Block");
    for (int i = 1; i < 200; i++)
    {
        //if (TEXTURE_DATA->blockUV.find(BlockType(i)) != TEXTURE_DATA->blockUV.end())
        //{
        //    EditObject* editObject = EditObject::Create(to_string(i));
        //    editObject->imgSize = { 1.f, 1.f };
        //
        //
        //    editObject->uvUp.first      = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_UP];
        //    editObject->uvDown.first    = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_DOWN];
        //    editObject->uvRight.first   = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_RIGHT];
        //    editObject->uvLeft.first    = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_LEFT];
        //    editObject->uvFront.first   = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_FORWARD];
        //    editObject->uvBack.first    = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_BEHIND];
        //
        //    editObject->uvUp.second     = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_UP] + Vector2{ 1.f / 16.f, 1.f / 16.f };
        //    editObject->uvDown.second   = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_DOWN] + Vector2{ 1.f / 16.f, 1.f / 16.f };
        //    editObject->uvRight.second  = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_RIGHT] + Vector2{ 1.f / 16.f, 1.f / 16.f };
        //    editObject->uvLeft.second   = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_LEFT] + Vector2{ 1.f / 16.f, 1.f / 16.f };
        //    editObject->uvFront.second  = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_FORWARD] + Vector2{ 1.f / 16.f, 1.f / 16.f };
        //    editObject->uvBack.second   = TEXTURE_DATA->blockUV[BlockType(i)][BLOCK_FACE_BEHIND] + Vector2{ 1.f / 16.f, 1.f / 16.f };
        //
        //    actor->AddChild(editObject);
        //
        //    editObject->mesh = editObject->EditMesh();
        //    editObject->mesh->SaveFile(editObject->root->name + "/" + editObject->name + ".mesh");
        //}
    }
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

    return 0;
}