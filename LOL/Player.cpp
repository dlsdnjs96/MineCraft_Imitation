#include "stdafx.h"

void Player::Init()
{
    LoadFile("Player.xml");


    //for (int x = -2; x < 3; x++)
    //{
    //    for (int z = -2; z < 3; z++)
    //    {
    //        for (int y = -2; y < 3; y++)
    //        {
    //            if (x != 0 || y != 0 || z != 0)
    //            {
    //                GameObject* temp = GameObject::Create(to_string(x) + ", " + to_string(y) + ", " + to_string(z));
    //                Find("Collider")->AddChild(temp);
    //                temp->SetLocalPos({ float(x * 2.f), float(y * 2.f), float(z * 2.f) });
    //                temp->mesh = RESOURCE->meshes.Load("1.BoxCollider.mesh");
    //                temp->shader = RESOURCE->shaders.Load("1.Collider.hlsl");
    //            }
    //        }
    //    }
    //}

    //const Int3 sixPos[6] = { {1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1} };
    //for (int i = 0;i < 6;i++)
    //    rayIntersectOrder.push_back(sixPos[i]);
    //for (int i = -1; i <= 1; i += 2)
    //{
    //    for (int j = -1; j <= 1; j += 2)
    //    {
    //        for (int l = -1; l <= 1; l += 2)
    //            rayIntersectOrder.push_back({i, j, l});
    //    }
    //}
    //for (int i = -2; i <= 2; i++)
    //{
    //    for (int j = -2; j <= 2; j++)
    //    {
    //        rayIntersectOrder.push_back({ i, j, 2 });
    //        rayIntersectOrder.push_back({ i, j, -2 });
    //    }
    //}
    //for (int i = -2; i <= 2; i++)
    //{
    //    for (int j = -1; j <= 1; j++) {
    //        rayIntersectOrder.push_back({ i, 2, j });
    //        rayIntersectOrder.push_back({ i, -2, j });
    //        rayIntersectOrder.push_back({ 2, i, j });
    //        rayIntersectOrder.push_back({ -2, i, j });
    //    }
    //}

    for (int i = -2; i <= 2; i++)
    {
        for (int j = -2; j <= 2; j++)
        {
            for (int k = -2; k <= 2; k++)
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

    //for (int i = 0; i < rayIntersectOrder.size(); i++)
    //{
    //    GameObject* temp = GameObject::Create("t" + to_string(i));
    //    Find("Collider")->AddChild(temp);
    //    temp->SetLocalPos(rayIntersectOrder[i].GetVector3() * 2.f);
    //    temp->mesh = RESOURCE->meshes.Load("1.BoxCollider.mesh");
    //    temp->shader = RESOURCE->shaders.Load("1.Collider.hlsl");
    //
    //}
}

void Player::Update()
{
    Actor::Update();
    Collider();

    if (INPUT->fixedMousePos.x != -1) {
        Find("head")->rotation.x -= (INPUT->moveNDCPos.y * PI) / 2.f;
        Find("head")->rotation.y += (INPUT->moveNDCPos.x * PI) / 2.f;
        Util::Saturate(Find("head")->rotation.x, -PI / 2.f, PI / 2.f);
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
    
    if (INPUT->KeyDown('T')) {
        WORLD->SetBlockType(curPos2, BlockType::WOOD_OAK);
        WORLD->UpdateMesh(temp);
    }
    if (INPUT->KeyDown('R')) {
        WORLD->SetBlockType(curPos2, BlockType::EMPTY);
        WORLD->UpdateMesh(temp);
    }
    if (INPUT->KeyDown(VK_RBUTTON))
        InstallBlock();
    if (INPUT->KeyDown(VK_LBUTTON))
        UninstallBlock();


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
    case PLAYER_STATE::ATTACK:
        Attack();
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

    return;
}

void Player::Release()
{
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

    if (WORLD->GetBlock(underInt3).blockType == BlockType::EMPTY)
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

    if (WORLD->GetBlock(currentPos).blockType == BlockType::WATER)
    {
        state = PLAYER_STATE::DIVE;
    } else if (int(WORLD->GetBlock(currentPos).blockType) >= 2)
    {
        moveForce.y = 0.f;
        SetLocalPosY(static_cast<float>((currentPos.y + 1) * BLOCK_LENGTH));
        state = PLAYER_STATE::WALK;
    }
}

void Player::Attack()
{
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

    if (WORLD->GetBlock(curInt3).blockType == BlockType::EMPTY)
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
    if (WORLD->GetBlock(enterBlock).blockType != BlockType::EMPTY)
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
    if (WORLD->GetBlock(enterBlock).blockType == BlockType::EMPTY)
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

    return false;
}

void Player::Render()
{
    Actor::Render();
}

void Player::InstallBlock()
{
    Matrix mat = Camera::main->proj;
    Ray rayToAim = Util::AimToRay(Camera::main);

    float dis = FLT_MAX;
    int intersectIndex = -1;

    Int3 intersectInt3;
    Int3 targetInt3;
    for (int i = 0; i < rayIntersectOrder.size(); i++)
    {
        intersectInt3 = curInt3 + rayIntersectOrder[i];
        if (WORLD->GetBlock(intersectInt3).blockType > BlockType::WATER)
        //    && Util::IsInScreen())
        {
            float camToBlock = Vector3::Distance(Camera::main->GetWorldPos(), Find("Collider")->GetWorldPos() + (rayIntersectOrder[i].GetVector3() * 10.f));
            if (dis > camToBlock) {
                Find("testCollider")->SetLocalPos(rayIntersectOrder[i].GetVector3() * 10.f);
                Find("Collider")->Update();
                Find("testCollider")->scale = { 5.1f, 5.1f, 5.1f };
                Find("testCollider")->visible = true;
                int mIndex = Util::RayIntersectSquareNear(rayToAim, Find("testCollider"));
                if (mIndex != -1) {
                    intersectIndex = mIndex;
                    dis = camToBlock;
                    targetInt3 = rayIntersectOrder[i];
                    printf("mIndex %d %d %d %d\r\n", rayIntersectOrder[i].x, rayIntersectOrder[i].y, rayIntersectOrder[i].z, mIndex);
                    //break;
                }
            }
        }
    }
    if (dis != FLT_MAX) {
        Int3 sixPos[6] = { {0, 1, 0}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0}, {0, 0, -1}, {0, 0, 1} };
        intersectInt3 = curInt3 + targetInt3; 
        printf("intersectInt2 %d %d %d\r\n", intersectInt3.x, intersectInt3.y, intersectInt3.z);
        intersectInt3 = intersectInt3 + sixPos[intersectIndex];
        printf("intersectInt3 %d %d %d\r\n", intersectInt3.x, intersectInt3.y, intersectInt3.z);
        WORLD->SetBlockType(intersectInt3, BlockType::STONE);
        WORLD->UpdateMesh(intersectInt3);
    }
}

void Player::UninstallBlock()
{
    Matrix mat = Camera::main->proj;
    Ray rayToAim = Util::AimToRay(Camera::main);

    float dis = FLT_MAX;
    int mIndex = -1;

    Int3 intersectInt3;
    Int3 targetInt3;
    for (int i = 0; i < rayIntersectOrder.size(); i++)
    {
        intersectInt3 = curInt3 + rayIntersectOrder[i];
        if (WORLD->GetBlock(intersectInt3).blockType > BlockType::WATER)
            //    && Util::IsInScreen())
        {
            float camToBlock = Vector3::Distance(Camera::main->GetWorldPos(), Find("Collider")->GetWorldPos() + (rayIntersectOrder[i].GetVector3() * 10.f));
            if (dis > camToBlock) {
                Find("testCollider")->SetLocalPos(rayIntersectOrder[i].GetVector3() * 10.f);
                Find("Collider")->Update();
                Find("testCollider")->scale = { 5.1f, 5.1f, 5.1f };
                Find("testCollider")->visible = true;
                mIndex = Util::RayIntersectSquareNear(rayToAim, Find("testCollider"));
                if (mIndex != -1) {
                    dis = camToBlock;
                    targetInt3 = rayIntersectOrder[i];
                    printf("mIndex %d %d %d %d\r\n", rayIntersectOrder[i].x, rayIntersectOrder[i].y, rayIntersectOrder[i].z, mIndex);
                    //break;
                }
            }
        }
    }
    if (dis != FLT_MAX) {
        intersectInt3 = curInt3 + targetInt3;
        printf("intersectInt3 %d %d %d\r\n", intersectInt3.x, intersectInt3.y, intersectInt3.z);
        WORLD->SetBlockType(intersectInt3, BlockType::EMPTY);
        WORLD->UpdateMesh(intersectInt3);
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

const char* Player::StateToString(PLAYER_STATE e)
{
    const std::map<PLAYER_STATE, const char*> MyEnumStrings{
        { PLAYER_STATE::IDLE, "IDLE" },
        { PLAYER_STATE::WALK, "WALK" },
        { PLAYER_STATE::JUMP, "JUMP" },
        { PLAYER_STATE::FALL, "FALL" },
        { PLAYER_STATE::ATTACK, "ATTACK" },
        { PLAYER_STATE::SUPER, "SUPER" },
        { PLAYER_STATE::SWIM, "SWIM" },
        { PLAYER_STATE::DIVE, "DIVE" }
    };

    auto   it = MyEnumStrings.find(e);
    return it == MyEnumStrings.end() ? "Out of range" : it->second;
}