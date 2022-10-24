#include "stdafx.h"

void Player::Init()
{
    LoadFile("Player.xml");
}

void Player::Update()
{
    Actor::Update();
    if (INPUT->KeyPress(VK_LBUTTON)) {
        Find("head")->rotation.x -= INPUT->moveNDCPosition.y * PI / 2.f;
        Find("head")->rotation.y += INPUT->moveNDCPosition.x * PI / 2.f;
        Util::Saturate(Find("head")->rotation.x, -PI / 2.f, PI / 2.f);
    }

    Vector3 temp = GetWorldPos() / BLOCK_LENGTH;
    Int3 curPos2 = Int3(temp);
    Int3 curPos = Int3(GetWorldPos() / BLOCK_LENGTH);
    //curPos /= static_cast<int>(BLOCK_LENGTH);
    ImGui::Text(("Int3 : " + WORLD->GetBlock(curPos).to_string()+" "+to_string(curPos.x) + " " + to_string(curPos.y) + " " + to_string(curPos.z)).c_str());
    ImGui::Text(("Vector3 : " + WORLD->GetBlock(GetWorldPos()).to_string()+" "+to_string(GetWorldPos().x) + " " + to_string(GetWorldPos().y) + " " + to_string(GetWorldPos().z)).c_str());
    
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

    Int3 curp = Int3(GetWorldPos() / BLOCK_LENGTH);


    if (WORLD->GetBlock(curp).blockType != BlockType::EMPTY)
    {
        moveForce.y = 0.f;
        SetLocalPosY(static_cast<float>((curp.y + 1) * BLOCK_LENGTH));
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
    Vector3 up = Find("head")->GetUp();
    const float moveSpeed = 1000.f;

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
        printf("unenterable\r\n");
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

bool Player::RenderHierarchy()
{
    Actor::RenderHierarchy();

    return false;
}

void Player::Render()
{
    Actor::Render();
}
