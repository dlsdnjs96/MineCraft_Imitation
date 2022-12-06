#include "stdafx.h"

//Player* Player::user = nullptr;
void Player::Init()
{
    LoadFile("Player.xml");
    //LoadFile("Monster/Steve.xml");
    breakingBlock = Actor::Create("breakingBlock");
    breakingBlock->LoadFile("breakingBlock.xml");


    for (int i = -3; i <= 3; i++)
    {
        for (int j = -3; j <= 3; j++)
        {
            for (int k = -3; k <= 3; k++)
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


    GameObject* temp = GameObject::Create("testCollider");
    Find("Collider")->AddChild(temp);
    temp->mesh = RESOURCE->meshes.Load("6.blockCollider.mesh");
    temp->shader = RESOURCE->shaders.Load("1.Collider.hlsl");


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

    for (int i = WORLD_HEIGHT - 1; i >= 0; i--)
    {
        if (WORLD->GetBlock(Int3{ 10, i, 10 }).blockType != BlockType::AIR)
        {
            SetWorldPos({ 100.f, 10.f * float(i), 100.f });
            break;
        }
    }
    DATABASE->LoadPlayer();
}

void Player::Update()
{
    passedTime += DELTA;
    //if (INPUT->KeyDown('1'))
    //    hp++;
    //if (INPUT->KeyDown('2'))
    //    hp--;
    //UpdatePlayerUI();
    if (INVENTORY->showInven || CRAFTING->active)
        return;
    Actor::Update();
    Collider();

    if (INPUT->fixedMousePos.x != -1) {
        Find("head")->rotation.x -= (INPUT->moveNDCPos.y * PI) / 2.f;
        Find("head")->rotation.y += (INPUT->moveNDCPos.x * PI) / 2.f;
        //Util::Saturate(Find("head")->rotation.x, -PI / 2.f, PI / 2.f);
        Util::Saturate(Find("head")->rotation.x, -PI / 2.f, PI * 0.1736f);
    }

    Vector3 temp = GetWorldPos() / BLOCK_LENGTH;
    Int3 curPos2 = Int3(temp);
    Int3 curPos = Int3(GetWorldPos() / BLOCK_LENGTH);
    //curPos /= static_cast<int>(BLOCK_LENGTH);
    string str;
    ImGui::Text((str + "State : " + StateToString(state)).c_str());
    ImGui::Text(("Int3 : " + WORLD->GetBlock(curPos).to_string()+" "+to_string(curPos.x) + " " + to_string(curPos.y) + " " + to_string(curPos.z)).c_str());
    ImGui::Text(("Vector3 : " + WORLD->GetBlock(GetWorldPos()).to_string()+" "+to_string(GetWorldPos().x) + " " + to_string(GetWorldPos().y) + " " + to_string(GetWorldPos().z)).c_str());
    ImGui::Text(("renderFace : " + to_string(WORLD->GetBlock(GetWorldPos()).renderFace)).c_str());
    





    curInt3 = Int3(GetWorldPos() / BLOCK_LENGTH);
    underInt3 = { curInt3.x, curInt3.y - 1, curInt3.z };
    moveForce = { 0.f, 0.f, 0.f };
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

    pUI->Update();
    return;
}

void Player::Release()
{
    breakingBlock->Release();
}



void Player::Idle()
{
    if (INPUT->KeyDown('W') or INPUT->KeyDown('S') or INPUT->KeyDown('D') or INPUT->KeyDown('A'))
        state = PLAYER_STATE::WALK;

    if (INPUT->KeyDown(VK_SPACE))
    {
        state = PLAYER_STATE::JUMP;
        jumppedTime = 0.f;
    }

    if (INPUT->KeyDown(VK_LSHIFT))
        state = PLAYER_STATE::SUPER;
}

void Player::Walk()
{

    if (not FourWaysMoving())
        state = PLAYER_STATE::IDLE;

    if (INPUT->KeyDown(VK_SPACE))
    {
        state = PLAYER_STATE::JUMP;
        jumppedTime = 0.f;
    }

    if (WORLD->GetBlock(underInt3).blockType == BlockType::AIR)
    {
        state = PLAYER_STATE::FALL;
        jumppedTime = jumpSpeed / gravity;
    }

}

void Player::Jump()
{
    GravityMoving();
    FourWaysMoving();


    if (jumppedTime >= jumpSpeed / gravity)
    {
        state = PLAYER_STATE::FALL;
        return;
    }
}

void Player::Fall()
{
    GravityMoving();
    FourWaysMoving();

    Int3 currentPos = Int3(GetWorldPos() / BLOCK_LENGTH);

    if (WORLD->GetBlock(currentPos).blockType == BlockType::STILL_WATER)
    {
        state = PLAYER_STATE::DIVE;
    } else if (int(WORLD->GetBlock(currentPos).blockType) >= 2)
    {
        moveForce.y = 0.f;
        SetLocalPosY(static_cast<float>((currentPos.y + 1) * BLOCK_LENGTH));
        state = PLAYER_STATE::WALK;
    }
}

void Player::Super()
{
    Vector3 forward     = Find("head")->GetForward();
    Vector3 right       = Find("head")->GetRight();
    Vector3 up          = Find("head")->GetUp();
    const float moveSpeed = 100.f;

    forward.y = 0;
    right.y = 0;
    up = { 0.f, 1.f, 0.f };
    forward.Normalize();
    right.Normalize();

    if (INPUT->KeyPress('W'))
        MoveWorldPos(forward * moveSpeed * DELTA);
    if (INPUT->KeyPress('S'))
        MoveWorldPos(-forward * moveSpeed * DELTA);
    if (INPUT->KeyPress('D'))
        MoveWorldPos(right * moveSpeed * DELTA);
    if (INPUT->KeyPress('A'))
        MoveWorldPos(-right * moveSpeed * DELTA);
    if (INPUT->KeyPress('E'))
        MoveWorldPos(up * moveSpeed * DELTA);
    if (INPUT->KeyPress('Q'))
        MoveWorldPos(-up * moveSpeed * DELTA);
    if (INPUT->KeyDown(VK_LSHIFT))
        state = PLAYER_STATE::FALL;
}



void Player::Swim()
{
    GravityFloating();
}

void Player::Dive()
{
    GravityFloating();

    if (INPUT->KeyDown('W') or INPUT->KeyDown('S') or INPUT->KeyDown('D') or INPUT->KeyDown('A'))
        state = PLAYER_STATE::SWIM;

    if (WORLD->GetBlock(curInt3).blockType == BlockType::AIR)
    {
        state = PLAYER_STATE::FALL;
        jumppedTime = jumpSpeed / risingForce;
    }
    else if (int(WORLD->GetBlock(curInt3).blockType) >= 2)
    {
        moveForce.y = 0.f;
    }

    if (INPUT->KeyPress(VK_LSHIFT)) { moveForce.y -= swimSpeed * DELTA; }
    if (INPUT->KeyPress(VK_SPACE)) { moveForce.y = swimSpeed * DELTA; }
}

void Player::Normal()
{
    if (INPUT->KeyPress(VK_LBUTTON))
    {
        Ray ray = Util::AimToRay(Camera::main);
        if (MONSTER_MANAGER->AttackWithRay(ray))
            actState = ACT_STATE::ATTACKING;
        else
            actState = ACT_STATE::DIGGING;
    } else if (INPUT->KeyDown(VK_RBUTTON)) {
        Ray ray = Util::AimToRay(Camera::main);
        if (not MONSTER_MANAGER->InteractWithRay(ray))
            InteractBlock();
    }
}

void Player::Acttacking()
{
    passedTime += DELTA;

    if (passedTime > 0.5f)
    {
        passedTime = 0.f;
        actState = ACT_STATE::NORMAL;
        return;
    }
}

void Player::Digging()
{
    static bool firstTime = true;

    if (not INPUT->KeyPress(VK_LBUTTON)) {
        firstTime = true;
        breakingBlock->visible = false;
        actState = ACT_STATE::NORMAL;
        return;
    }

    if (firstTime)
    {
        passedTime = 0.f;
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
    passedTime += DELTA;

    //printf("%f %d %d %d %d\r\n", passedTime, targetInt3.x, targetInt3.y, targetInt3.z, firstTime);


    if (passedTime > 0.9f)
    {
        UninstallBlock();
        passedTime = 0.f;
        firstTime = true;
        breakingBlock->visible = false;
        actState = ACT_STATE::NORMAL;
        return;
    }
    if (int(passedTime / 0.1f) != int((passedTime - DELTA) / 0.1f))
    {
        breakingBlock->material = RESOURCE->materials.Load("breakingBlock/" + to_string(int(passedTime / 0.1f)) + ".mtl");
    }
    if (FindTarget() == -1)
        actState = ACT_STATE::NORMAL;
}

bool Player::FourWaysMoving()
{
    bool moved = false;
    Vector3 forward = Find("head")->GetForward();
    Vector3 right = Find("head")->GetRight();

    forward.y = 0.f;
    right.y = 0.f;
    forward.Normalize();
    right.Normalize();

    if (INPUT->KeyPress('W')) { moveForce += forward * moveSpeed * DELTA; moved = true; }
    if (INPUT->KeyPress('S')) { moveForce -= forward * moveSpeed * DELTA; moved = true; }
    if (INPUT->KeyPress('D')) { moveForce += right * moveSpeed * DELTA; moved = true; }
    if (INPUT->KeyPress('A')) { moveForce -= right * moveSpeed * DELTA; moved = true; }

    Int3 enterBlock = Int3((GetWorldPos() + moveForce) / BLOCK_LENGTH);
    //enterBlock.y++;
    if (WORLD->GetBlock(enterBlock).blockType != BlockType::AIR)
    {
        moveForce.x = 0.f;
        moveForce.z = 0.f;
    }

    return moved;
}

bool Player::GravityMoving()
{
    float prevTime = jumppedTime;
    jumppedTime += DELTA;

    float prevY, curY;
    prevY = jumpSpeed * prevTime - (0.5f * gravity * powf(prevTime, 2.f));
    curY = jumpSpeed * jumppedTime - (0.5f * gravity * powf(jumppedTime, 2.f));
    moveForce.y += curY - prevY;


    return true;
}

bool Player::FourWaysFloating()
{
    bool moved = false;
    Vector3 forward = Find("head")->GetForward();
    Vector3 right = Find("head")->GetRight();

    forward.y = 0.f;
    right.y = 0.f;
    forward.Normalize();
    right.Normalize();
    forward *= 0.8f;
    right *= 0.8f;

    if (INPUT->KeyPress('W')) { moveForce += forward * moveSpeed * DELTA; moved = true; }
    if (INPUT->KeyPress('S')) { moveForce -= forward * moveSpeed * DELTA; moved = true; }
    if (INPUT->KeyPress('D')) { moveForce += right * moveSpeed * DELTA; moved = true; }
    if (INPUT->KeyPress('A')) { moveForce -= right * moveSpeed * DELTA; moved = true; }
    if (INPUT->KeyPress(VK_LSHIFT)) { moveForce.y -= moveSpeed * DELTA; moved = true; }
    if (INPUT->KeyPress(VK_SPACE))  { moveForce.y += moveSpeed * DELTA; moved = true; }

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

bool Player::GravityFloating()
{
    float prevTime = jumppedTime;
    jumppedTime += DELTA;

    float prevY, curY;
    prevY = jumpSpeed * prevTime - (0.5f * risingForce * powf(prevTime, 2.f));
    curY = jumpSpeed * jumppedTime - (0.5f * risingForce * powf(jumppedTime, 2.f));
    moveForce.y += curY - prevY;

    return true;
}

bool Player::RenderHierarchy()
{
    Actor::RenderHierarchy();
    breakingBlock->RenderHierarchy();
    pUI->RenderHierarchy();

    return false;
}

void Player::Render()
{
    Actor::Render();
    if (actState == ACT_STATE::DIGGING)
        breakingBlock->Render();
    pUI->Render();
}

void Player::InteractBlock()
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
    }
    if (INVENTORY->GetPickedItem().itemid < 256)
        InstallBlock();
}

int Player::FindTarget()
{
    Matrix mat = Camera::main->proj;
    Ray rayToAim = Util::AimToRay(Camera::main);

    float dis = FLT_MAX;
    int intersectIndex = -1;

    Int3 intersectInt3;

    for (int i = 0; i < rayIntersectOrder.size(); i++)
    {
        intersectInt3 = curInt3 + rayIntersectOrder[i];
        if (WORLD->GetBlock(intersectInt3).blockType > BlockType::STILL_WATER)
            //    && Util::IsInScreen())
        {
            //float camToBlock = Vector3::Distance(Camera::main->GetWorldPos(), Find("Collider")->GetWorldPos() + (rayIntersectOrder[i].GetVector3() * 10.f));
            float camToBlock = Vector3::Distance(Camera::main->GetWorldPos(), intersectInt3.GetVector3() * 10.f);
            if (dis > camToBlock) {
                Find("testCollider")->SetLocalPos(rayIntersectOrder[i].GetVector3() * 10.f);
                Find("Collider")->Update();
                Find("testCollider")->scale = { 5.1f, 5.1f, 5.1f };
                Find("testCollider")->visible = true;
                int mIndex = Util::RayIntersectSquareNear(rayToAim, Find("testCollider"));
                if (mIndex != -1) {
                    intersectIndex = mIndex;
                    dis = camToBlock;
                    targetInt3 = curInt3 + rayIntersectOrder[i];
                }
            }
        }
    }
    return intersectIndex;
}

void Player::InstallBlock()
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

void Player::UninstallBlock()
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

int Player::GetAttackPoint()
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

void Player::AttackedByMonster(int damage)
{
    hp -= damage;
    UpdatePlayerUI();
    if (hp <= 0)
    {
        state = PLAYER_STATE::DEAD;
        return;
    }
}

void Player::Collider()
{
    Vector3 verifiedPos;
    verifiedPos.x = float(int(int(GetWorldPos().x + 5) / 10) * 10.f);
    verifiedPos.y = float(int(GetWorldPos().y / 10) * 10.f) + 5.f;
    verifiedPos.z = float(int(int(GetWorldPos().z + 5) / 10) * 10.f);

    Int3 curPos = Int3(GetWorldPos() / BLOCK_LENGTH);
    verifiedPos.x = float(curPos.x * 10.f);
    verifiedPos.y = float(curPos.y * 10.f) + 5.f;
    verifiedPos.z = float(curPos.z * 10.f);
    Find("Collider")->SetWorldPos(verifiedPos);
}

void Player::UpdatePlayerUI()
{
    int i;
    for (i = 0; i < hp / 2; i++) {
        pUI->Find("heartF" + to_string(i))->visible = true;
        pUI->Find("heartF" + to_string(i))->material = RESOURCE->materials.Load("heartFront.mtl");
    }
    for (; i < 10; i++)
    {
        pUI->Find("heartF" + to_string(i))->visible = false;
        pUI->Find("heartF" + to_string(i))->material = RESOURCE->materials.Load("heartFront.mtl");
    }
    if (hp % 2 == 1)
    {
        pUI->Find("heartF" + to_string(hp / 2))->visible = true;
        pUI->Find("heartF" + to_string(hp / 2))->material = RESOURCE->materials.Load("heartHalf.mtl");
    }

    for (i = 0; i < hunger / 2; i++) {
        pUI->Find("foodF" + to_string(i))->visible = true;
        pUI->Find("foodF" + to_string(i))->material = RESOURCE->materials.Load("foodFront.mtl");
    }
    for (; i < 10; i++)
    {
        pUI->Find("foodF" + to_string(i))->visible = false;
        pUI->Find("foodF" + to_string(i))->material = RESOURCE->materials.Load("foodFront.mtl");
    }
    if (hunger % 2 == 1)
    {
        pUI->Find("foodF" + to_string(hunger / 2))->visible = true;
        pUI->Find("foodF" + to_string(hunger / 2))->material = RESOURCE->materials.Load("foodHalf.mtl");
    }
    pUI->Update();
}

const char* Player::StateToString(PLAYER_STATE e)
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