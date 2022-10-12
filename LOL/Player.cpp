#include "stdafx.h"

void Player::Init()
{
    body = Actor::Create();
    body->LoadFile("Player.xml");
}

void Player::Update()
{
    body->Update();
    body->Find("camBody")->rotation.x += INPUT->movePosition.y * DELTA / 30.f;
    body->Find("camBody")->rotation.y += INPUT->movePosition.x * DELTA / 30.f;

    return;
    if (INPUT->NDCPosition.x <= -0.98f)
        body->Find("camBody")->rotation.y -= DELTA;
    else if (INPUT->NDCPosition.x >= 0.98f)
        body->Find("camBody")->rotation.y += DELTA;

    if (INPUT->NDCPosition.y <= -0.98f)
        body->Find("camBody")->rotation.x += DELTA;
    else if (INPUT->NDCPosition.y >= 0.98f)
        body->Find("camBody")->rotation.x -= DELTA;

    //printf("INPUT->NDCPosition %f %f\r\n", INPUT->NDCPosition.x, INPUT->NDCPosition.y);
}

void Player::Release()
{
}

bool Player::RenderHierarchy()
{
    body->RenderHierarchy();

    return false;
}

void Player::Render()
{
    body->Render();
}
