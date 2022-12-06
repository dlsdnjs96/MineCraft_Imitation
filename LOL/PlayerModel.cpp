#include "stdafx.h"

PlayerModel* PlayerModel::user = nullptr;
void PlayerModel::Init()
{
    LoadFile("Monster/Steve.xml");
    //LoadFile("Monster/Steve.xml");
    breakingBlock = Actor::Create("breakingBlock");
    breakingBlock->LoadFile("breakingBlock.xml");


    for (int i = -4; i <= 4; i++)
    {
        for (int j = -4; j <= 4; j++)
        {
            for (int k = -4; k <= 4; k++)
            {
                if (i != 0 || j != 0 || k != 0)
                    rayIntersectOrder.push_back({ i, j, k });
            }
        }
    }
    for (int i = 0; i < rayIntersectOrder.size(); i++)
    {
        for (int j = i + 1; j < rayIntersectOrder.size(); j++)
        {
            if (pow(rayIntersectOrder[i].x, 2) + pow(rayIntersectOrder[i].y, 2) + pow(rayIntersectOrder[i].z, 2)
        > pow(rayIntersectOrder[j].x, 2) + pow(rayIntersectOrder[j].y, 2) + pow(rayIntersectOrder[j].z, 2))
            {
                Int3 temp = rayIntersectOrder[i];
                rayIntersectOrder[i] = rayIntersectOrder[j];
                rayIntersectOrder[j] = temp;
            }
        }
    }


    //GameObject* temp = GameObject::Create("testCollider");
    //Find("Collider")->AddChild(temp);
    Find("testCollider")->mesh = RESOURCE->meshes.Load("6.blockCollider.mesh");
    Find("testCollider")->shader = RESOURCE->shaders.Load("1.Collider.hlsl");

    //mainPerson = Find("theFirstPerson");

    hp = 20;
    hunger = 20;

    pUI = UI::Create("PlayerUI");
    pUI->LoadFile("Ingame/PlayerUI.xml");

    for (int i = 0; i < 10; i++)
    {
        UI* temp = UI::Create("heartB" + to_string(i));
        temp->scale = { 0.046f, 0.065f, 1.f };
        temp->SetLocalPos({ -0.45f + (i * 0.0444f), 0.1f, 0.f });
        temp->material = RESOURCE->materials.Load("heartBack.mtl");
        pUI->AddChild(temp);

        UI* temp2 = UI::Create("heartF" + to_string(i));
        temp2->scale = { 0.7777f, 0.7777f, 1.f };
        temp2->SetLocalPos({ 0.f, 0.f, -0.1f });
        temp2->material = RESOURCE->materials.Load("heartFront.mtl");
        pUI->Find("heartB" + to_string(i))->AddChild(temp2);
    }

    for (int i = 0; i < 10; i++)
    {
        UI* temp = UI::Create("foodB" + to_string(i));
        temp->scale = { 0.046f, 0.065f, 1.f };
        temp->SetLocalPos({ 0.45f - (i * 0.0444f), 0.1f, 0.f });
        temp->material = RESOURCE->materials.Load("foodBack.mtl");
        pUI->AddChild(temp);

        UI* temp2 = UI::Create("foodF" + to_string(i));
        temp2->scale = { 0.7777f, 0.7777f, 1.f };
        temp2->SetLocalPos({ 0.f, 0.f, -0.1f });
        temp2->material = RESOURCE->materials.Load("foodFront.mtl");
        pUI->Find("foodB" + to_string(i))->AddChild(temp2);
    }
    theFirstPerson = true;
    Camera::main = dynamic_cast<Camera*>(Find("fCam"));
    mainPerson = Find("mainPerson");
    //mainPerson = GameObject::Create("mainPerson");
    //root->AddChild(mainPerson);
}

void PlayerModel::Update()
{
    //if (INPUT->KeyDown('1'))
    //    hp++;
    //if (INPUT->KeyDown('2'))
    //    hp--;
    //UpdatePlayerUI();

    Actor::Update();
    Collider();

    if (INPUT->fixedMousePos.x != -1) {
        if (theFirstPerson) {
            Find("theFirstPerson")->rotation.x -= (INPUT->moveNDCPos.y * PI) / 2.f;
            Find("theFirstPerson")->rotation.y += (INPUT->moveNDCPos.x * PI) / 2.f;
            Util::Saturate(Find("theFirstPerson")->rotation.x, -PI_DIV2, PI_DIV2);

            mainPerson->rotation.x = Find("theFirstPerson")->rotation.x;
            mainPerson->rotation.y = Find("theFirstPerson")->rotation.y;
        }
        else {
            Find("head")->rotation.x -= (INPUT->moveNDCPos.y * PI) / 2.f;
            Find("body")->rotation.y += (INPUT->moveNDCPos.x * PI) / 2.f;
            Util::Saturate(Find("head")->rotation.x, -PI_DIV2, PI_DIV2);

            mainPerson->rotation.x = Find("head")->rotation.x;
            mainPerson->rotation.y = Find("body")->rotation.y;
        }
        
        //rotation.y = mainPerson.y;
        //if (theFirstPerson) {
        //    Find("theFirstPerson")->rotation.x = mainPerson.x;
        //}
        //else {
        //    Find("head")->rotation.x = mainPerson.x;
        //}
        //Find("head")->rotation.x -= (INPUT->moveNDCPos.y * PI) / 2.f;
        //Find("head")->rotation.y += (INPUT->moveNDCPos.x * PI) / 2.f;
        //Util::Saturate(Find("head")->rotation.x, -PI / 2.f, PI * 0.1736f);
    }

    Vector3 temp = GetWorldPos() / BLOCK_LENGTH;
    Int3 curPos2 = Int3(temp);
    Int3 curPos = Int3(GetWorldPos() / BLOCK_LENGTH);
    //curPos /= static_cast<int>(BLOCK_LENGTH);
    passedTime += DELTA;



    curInt3 = Int3(GetWorldPos() / BLOCK_LENGTH);
    underInt3 = { curInt3.x, curInt3.y - 1, curInt3.z };
    switch (state)
    {
    case PLAYER_STATE::IDLE:
        Idle();
        break;
    case PLAYER_STATE::WALK:
        Walk();
        break;
    case PLAYER_STATE::JUMP:
        Jump();
        break;
    case PLAYER_STATE::FALL:
        Fall();
        break;
    case PLAYER_STATE::SUPER:
        Super();
        break;
    case PLAYER_STATE::SWIM:
        Swim();
        break;
    case PLAYER_STATE::DIVE:
        Dive();
        break;
    }
    MoveWorldPos(moveForce);

    switch (actState)
    {
    case ACT_STATE::NORMAL:
        Normal();
        break;
    case ACT_STATE::ATTACKING:
        Acttacking();
        break;
    case ACT_STATE::DIGGING:
        Digging();
        break;
    }

    return;
}

void PlayerModel::Release()
{
    breakingBlock->Release();
}



void PlayerModel::Idle()
{
}

void PlayerModel::Walk()
{

    if (not FourWaysMoving()) {
        state = PLAYER_STATE::IDLE;
        SOUND->Stop("walk");
    }


    if (WORLD->GetBlock(underInt3).blockType == BlockType::AIR)
    {
        state = PLAYER_STATE::FALL;
        SOUND->Stop("walk");
        jumppedTime = jumpSpeed / gravity;
    }

}

void PlayerModel::Jump()
{
    GravityMoving();
    FourWaysMoving();


    if (jumppedTime >= jumpSpeed / gravity)
    {
        state = PLAYER_STATE::FALL;
        return;
    }
}

void PlayerModel::Fall()
{
    GravityMoving();
    FourWaysMoving();

    Int3 currentPos = Int3(GetWorldPos() / BLOCK_LENGTH);

    if (WORLD->GetBlock(currentPos).blockType == BlockType::STILL_WATER)
    {
        state = PLAYER_STATE::DIVE;
    }
    else if (int(WORLD->GetBlock(currentPos).blockType) >= 2)
    {
        moveForce.y = 0.f;
        SetLocalPosY((static_cast<float>((currentPos.y + 1) * BLOCK_LENGTH) + 1.f));
        state = PLAYER_STATE::IDLE;
    }
}

void PlayerModel::Super()
{
}



void PlayerModel::Swim()
{
    GravityFloating();
}

void PlayerModel::Dive()
{
    GravityFloating();



    if (WORLD->GetBlock(curInt3).blockType == BlockType::AIR)
    {
        state = PLAYER_STATE::FALL;
        jumppedTime = jumpSpeed / risingForce;
    }
    else if (int(WORLD->GetBlock(curInt3).blockType) >= 2)
    {
        moveForce.y = 0.f;
    }

}

void PlayerModel::Normal()
{
}

void PlayerModel::Acttacking()
{
    passedTime += DELTA;

    if (passedTime > 0.5f)
    {
        passedTime = 0.f;
        actState = ACT_STATE::NORMAL;
        return;
    }
}

void PlayerModel::Digging()
{

    if (firstTime)
    {
        diggedTime = 0.f;
        int intersectIndex = FindTarget();
        if (intersectIndex == -1)
        {
            actState = ACT_STATE::NORMAL;
            return;
        }
        breakingBlock->SetLocalPos(targetInt3.GetVector3() * 10.f);
        breakingBlock->MoveLocalPos({ 0.f, 5.f, 0.f });
        breakingBlock->Update();
        breakingBlock->visible = true;
        breakingBlock->material = RESOURCE->materials.Load("breakingBlock/0.mtl");
        prevTarget = targetInt3;
        firstTime = false;
    }
    //passedTime += DELTA;

    //printf("%f %d %d %d %d\r\n", passedTime, targetInt3.x, targetInt3.y, targetInt3.z, firstTime);
    if (WORLD->GetBlock(targetInt3).blockType == BlockType::GRASS)
        diggedTime += 1.f;
    diggedTime += DELTA;
    if (diggedTime > 0.9f)
    {
        SOUND->Play("destroyBlock01");
        UninstallBlock();
        diggedTime = 0.f;
        firstTime = true;
        breakingBlock->visible = false;
        actState = ACT_STATE::NORMAL;
        return;
    }
    if (int(diggedTime / 0.1f) != int((diggedTime - DELTA) / 0.1f))
    {
        breakingBlock->material = RESOURCE->materials.Load("breakingBlock/" + to_string(int(diggedTime / 0.1f)) + ".mtl");
    }
    if (FindTarget() == -1)
        actState = ACT_STATE::NORMAL;
}

bool PlayerModel::FourWaysMoving()
{
    bool moved = true;

    Int3 enterBlock = Int3((GetWorldPos() + moveForce) / BLOCK_LENGTH);
    //enterBlock.y++;
    if (WORLD->GetBlock(enterBlock).blockType != BlockType::AIR)
    {
        moveForce.x = 0.f;
        moveForce.z = 0.f;
    }

    return moved;
}

bool PlayerModel::GravityMoving()
{
    float prevTime = jumppedTime;
    jumppedTime += DELTA;

    float prevY, curY;
    prevY = jumpSpeed * prevTime - (0.5f * gravity * powf(prevTime, 2.f));
    curY = jumpSpeed * jumppedTime - (0.5f * gravity * powf(jumppedTime, 2.f));
    moveForce.y += curY - prevY;


    return true;
}

bool PlayerModel::FourWaysFloating()
{
    bool moved = false;


    Int3 enterBlock = Int3((GetWorldPos() + moveForce) / BLOCK_LENGTH);
    //enterBlock.y++;
    if (WORLD->GetBlock(enterBlock).blockType == BlockType::AIR)
    {
        state = PLAYER_STATE::FALL;
    }
    if (int(WORLD->GetBlock(enterBlock).blockType) < 2)
    {
        moveForce.x = 0.f;
        moveForce.y = 0.f;
        moveForce.z = 0.f;
    }

    return moved;
}

bool PlayerModel::GravityFloating()
{
    float prevTime = jumppedTime;
    jumppedTime += DELTA;

    float prevY, curY;
    prevY = jumpSpeed * prevTime - (0.5f * risingForce * powf(prevTime, 2.f));
    curY = jumpSpeed * jumppedTime - (0.5f * risingForce * powf(jumppedTime, 2.f));
    moveForce.y += curY - prevY;

    return true;
}

bool PlayerModel::RenderHierarchy()
{
    Actor::RenderHierarchy();
    breakingBlock->RenderHierarchy();
    pUI->RenderHierarchy();

    return false;
}

void PlayerModel::Render()
{
    //Actor::Render();
    //if (actState == ACT_STATE::DIGGING)
    //    breakingBlock->Render();
    //pUI->Render();
}

void PlayerModel::InteractBlock()
{
    int intersectIndex = FindTarget();
    if (intersectIndex < 0)
        return;

    switch (WORLD->GetBlock(targetInt3).blockType)
    {
    case BlockType::CRAFTING_TABLE:
        if (not CRAFTING->active) {
            Util::UnLockMouse();
            CRAFTING->ShowCraftTable(true);
        }
        else {
            Util::LockMouse();
            CRAFTING->ShowCraftTable(false);
        }
        break;
    case BlockType::FURNACE:
    case BlockType::BURNING_FURNACE:
        Util::UnLockMouse();
        FURNACE_MANAGER->OnFurnace(targetInt3);
        break;
    }
    if (INVENTORY->GetPickedItem().itemid < 256) {
        InstallBlock();
        SOUND->Play("installBlock");
    }
}

int PlayerModel::FindTarget()
{
    Matrix mat = Camera::main->proj;
    Ray rayToAim = Util::AimToRay(Camera::main);
    //rayToAim.position =  Find("theFirstPerson")->GetWorldPos();
    //rayToAim.direction = Find("theFirstPerson")->GetForward();

    float dis = FLT_MAX;
    int intersectIndex = -1;

    Int3 intersectInt3;
    Int3 fromInt3 = Int3(mainPerson->GetWorldPos() / BLOCK_LENGTH);

    for (int i = 0; i < rayIntersectOrder.size(); i++)
    {
        intersectInt3 = fromInt3 + rayIntersectOrder[i];
        if (WORLD->GetBlock(intersectInt3).blockType > BlockType::STILL_WATER)
            //    && Util::IsInScreen())
        {
            //float camToBlock = Vector3::Distance(Camera::main->GetWorldPos(), Find("Collider")->GetWorldPos() + (rayIntersectOrder[i].GetVector3() * 10.f));
            float camToBlock = Vector3::Distance(Camera::main->GetWorldPos(), intersectInt3.GetVector3() * 10.f);
            if (dis > camToBlock) {
                //Find("testCollider")->SetLocalPos(rayIntersectOrder[i].GetVector3() * 10.f);
                Find("testCollider")->SetWorldPos(intersectInt3.GetVector3() * 10.f);
                Find("Collider")->Update();
                Find("testCollider")->scale = { 5.1f, 5.1f, 5.1f };
                Find("testCollider")->visible = true;
                int mIndex = Util::RayIntersectSquareNear(rayToAim, Find("testCollider"));
                if (mIndex != -1) {
                    intersectIndex = mIndex;
                    dis = camToBlock;
                    targetInt3 = fromInt3 + rayIntersectOrder[i];
                }
            }
        }
    }
    Find("testCollider")->SetWorldPos(targetInt3.GetVector3() * 10.f);
    Find("testCollider")->MoveLocalPos({ 0.f, 5.f, 0.f });
    Find("testCollider")->Update();
    return intersectIndex;
}

void PlayerModel::InstallBlock()
{
    if (INVENTORY->GetPickedItem().ea == 0)
    {
        return;
    }
    int intersectIndex = FindTarget();

    if (intersectIndex != -1) {
        Int3 sixPos[6] = { {0, 1, 0}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0}, {0, 0, -1}, {0, 0, 1} };
        Int3 intersectInt3 = targetInt3 + sixPos[intersectIndex];
        WORLD->SetBlockType(intersectInt3, static_cast<BlockType>(INVENTORY->GetPickedItem().itemid));
        WORLD->UpdateMesh(intersectInt3);
        INVENTORY->UsePickedItem();
    }
}

void PlayerModel::UninstallBlock()
{


    int intersectIndex = FindTarget();

    if (intersectIndex != -1) {
        Vector3 temp = targetInt3.GetVector3() * BLOCK_LENGTH;
        temp.y += 5.f;
        ITEM_MANAGER->Spawn(temp, ITEM_MANAGER->GetDropItem(WORLD->GetBlock(targetInt3).blockType));
        WORLD->SetBlockType(targetInt3, BlockType::AIR);
        WORLD->UpdateMesh(targetInt3);
    }
}

int PlayerModel::GetAttackPoint()
{

    switch (INVENTORY->GetPickedItem().itemid)
    {
    case 270:
    case 285:
    case 269:
    case 284:
    case 290:
    case 294:
        return 2;
    case 274:
    case 273:
    case 291:
        return 3;
    case 271:
    case 286:
    case 257:
    case 256:
    case 292:
        return 4;
    case 275:
    case 278:
    case 277:
    case 293:
        return 5;
    case 258:
        return 6;
    case 279:
        return 7;
    }
    return 1;
}

void PlayerModel::AttackedByMonster(int damage)
{
    hp -= damage;
    if (hp <= 0)
    {
        state = PLAYER_STATE::DEAD;
        return;
    }
}

void PlayerModel::Collider()
{
    Vector3 verifiedPos;
    verifiedPos.x = float(int(int(Find("head")->GetWorldPos().x + 5) / 10) * 10.f);
    verifiedPos.y = float(int(Find("head")->GetWorldPos().y / 10) * 10.f) + 5.f;
    verifiedPos.z = float(int(int(Find("head")->GetWorldPos().z + 5) / 10) * 10.f);

    Int3 curPos = Int3(Find("mainPerson")->GetWorldPos() / BLOCK_LENGTH);
    //Int3 curPos = Int3(Camera::main->GetWorldPos() / BLOCK_LENGTH);
    verifiedPos.x = float(curPos.x * 10.f);
    verifiedPos.y = float(curPos.y * 10.f) + 5.f;
    verifiedPos.z = float(curPos.z * 10.f);
    Find("Collider")->SetWorldPos(verifiedPos);
}

const char* PlayerModel::StateToString(PLAYER_STATE e)
{
    const std::map<PLAYER_STATE, const char*> MyEnumStrings{
        { PLAYER_STATE::IDLE, "IDLE" },
        { PLAYER_STATE::WALK, "WALK" },
        { PLAYER_STATE::JUMP, "JUMP" },
        { PLAYER_STATE::FALL, "FALL" },
        { PLAYER_STATE::SUPER, "SUPER" },
        { PLAYER_STATE::SWIM, "SWIM" },
        { PLAYER_STATE::DIVE, "DIVE" }
    };

    auto   it = MyEnumStrings.find(e);
    return it == MyEnumStrings.end() ? "Out of range" : it->second;
}