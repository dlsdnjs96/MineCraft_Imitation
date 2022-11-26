#include "stdafx.h"

PlayerController::PlayerController(PlayerModel* _model)
{
	model = _model;
}

PlayerController::~PlayerController()
{
}

void PlayerController::Update()
{
    model->moveForce = { 0.f, 0.f, 0.f };
    switch (model->state)
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

    switch (model->actState)
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
}


void PlayerController::Idle()
{
    if (INPUT->KeyDown('W') or INPUT->KeyDown('S') or INPUT->KeyDown('D') or INPUT->KeyDown('A'))
        model->state = PLAYER_STATE::WALK;

    if (INPUT->KeyDown(VK_SPACE))
    {
        model->state = PLAYER_STATE::JUMP;
        model->jumppedTime = 0.f;
    }

    if (INPUT->KeyDown(VK_LSHIFT))
        model->state = PLAYER_STATE::SUPER;
}

void PlayerController::Walk()
{

    if (not FourWaysMoving())
        model->state = PLAYER_STATE::IDLE;

    if (INPUT->KeyDown(VK_SPACE))
    {
        model->state = PLAYER_STATE::JUMP;
        model->jumppedTime = 0.f;
    }
}

void PlayerController::Jump()
{
    FourWaysMoving();
}

void PlayerController::Fall()
{
    FourWaysMoving();
}

void PlayerController::Super()
{
    Vector3 forward = model->Find("head")->GetForward();
    Vector3 right = model->Find("head")->GetRight();
    Vector3 up = model->Find("head")->GetUp();
    const float moveSpeed = 100.f;

    forward.y = 0;
    right.y = 0;
    up = { 0.f, 1.f, 0.f };
    forward.Normalize();
    right.Normalize();

    if (INPUT->KeyPress('W'))
        model->MoveWorldPos(forward * moveSpeed * DELTA);
    if (INPUT->KeyPress('S'))
        model->MoveWorldPos(-forward * moveSpeed * DELTA);
    if (INPUT->KeyPress('D'))
        model->MoveWorldPos(right * moveSpeed * DELTA);
    if (INPUT->KeyPress('A'))
        model->MoveWorldPos(-right * moveSpeed * DELTA);
    if (INPUT->KeyPress('E'))
        model->MoveWorldPos(up * moveSpeed * DELTA);
    if (INPUT->KeyPress('Q'))
        model->MoveWorldPos(-up * moveSpeed * DELTA);
    if (INPUT->KeyDown(VK_LSHIFT))
        model->state = PLAYER_STATE::FALL;
}



void PlayerController::Swim()
{
}

void PlayerController::Dive()
{

    if (INPUT->KeyDown('W') or INPUT->KeyDown('S') or INPUT->KeyDown('D') or INPUT->KeyDown('A'))
        model->state = PLAYER_STATE::SWIM;

    if (INPUT->KeyPress(VK_LSHIFT)) { model->moveForce.y -= model->swimSpeed * DELTA; }
    if (INPUT->KeyPress(VK_SPACE)) { model->moveForce.y = model->swimSpeed * DELTA; }
}

void PlayerController::Normal()
{
    if (INPUT->KeyPress(VK_LBUTTON))
    {
        Ray ray = Util::AimToRay(Camera::main);
        if (MONSTER_MANAGER->AttackWithRay(ray))
            model->actState = ACT_STATE::ATTACKING;
        else
            model->actState = ACT_STATE::DIGGING;
    }
    else if (INPUT->KeyDown(VK_RBUTTON)) {
        Ray ray = Util::AimToRay(Camera::main);
        if (not MONSTER_MANAGER->InteractWithRay(ray))
            model->InteractBlock();
    }
}

void PlayerController::Acttacking()
{
}

void PlayerController::Digging()
{
    if (not INPUT->KeyPress(VK_LBUTTON)) {
        model->firstTime = true;
        model->breakingBlock->visible = false;
        model->actState = ACT_STATE::NORMAL;
        return;
    }
}

bool PlayerController::FourWaysMoving()
{
    bool moved = false;
    Vector3 forward = model->Find("head")->GetForward();
    Vector3 right = model->Find("head")->GetRight();

    forward.y = 0.f;
    right.y = 0.f;
    forward.Normalize();
    right.Normalize();

    if (INPUT->KeyPress('W')) { model->moveForce += forward * model->moveSpeed * DELTA; moved = true; }
    if (INPUT->KeyPress('S')) { model->moveForce -= forward * model->moveSpeed * DELTA; moved = true; }
    if (INPUT->KeyPress('D')) { model->moveForce += right * model->moveSpeed * DELTA; moved = true; }
    if (INPUT->KeyPress('A')) { model->moveForce -= right * model->moveSpeed * DELTA; moved = true; }

    Int3 enterBlock = Int3((model->GetWorldPos() + model->moveForce) / BLOCK_LENGTH);
    //enterBlock.y++;
    if (WORLD->GetBlock(enterBlock).blockType != BlockType::AIR)
    {
        model->moveForce.x = 0.f;
        model->moveForce.z = 0.f;
    }

    return moved;
}



bool PlayerController::FourWaysFloating()
{
    bool moved = false;
    Vector3 forward = model->Find("head")->GetForward();
    Vector3 right = model->Find("head")->GetRight();

    forward.y = 0.f;
    right.y = 0.f;
    forward.Normalize();
    right.Normalize();
    forward *= 0.8f;
    right *= 0.8f;

    if (INPUT->KeyPress('W')) { model->moveForce += forward * model->moveSpeed * DELTA; moved = true; }
    if (INPUT->KeyPress('S')) { model->moveForce -= forward * model->moveSpeed * DELTA; moved = true; }
    if (INPUT->KeyPress('D')) { model->moveForce += right * model->moveSpeed * DELTA; moved = true; }
    if (INPUT->KeyPress('A')) { model->moveForce -= right * model->moveSpeed * DELTA; moved = true; }
    if (INPUT->KeyPress(VK_LSHIFT)) { model->moveForce.y -= model->moveSpeed * DELTA; moved = true; }
    if (INPUT->KeyPress(VK_SPACE)) { model->moveForce.y += model->moveSpeed * DELTA; moved = true; }

    Int3 enterBlock = Int3((model->GetWorldPos() + model->moveForce) / BLOCK_LENGTH);
    //enterBlock.y++;
    if (WORLD->GetBlock(enterBlock).blockType == BlockType::AIR)
    {
        model->state = PLAYER_STATE::FALL;
    }
    if (int(WORLD->GetBlock(enterBlock).blockType) < 2)
    {
        model->moveForce.x = 0.f;
        model->moveForce.y = 0.f;
        model->moveForce.z = 0.f;
    }

    return moved;
}

