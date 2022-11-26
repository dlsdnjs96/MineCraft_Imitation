#include "stdafx.h"

PlayerView::PlayerView(PlayerModel* _model)
{
    model = _model;
}

PlayerView::~PlayerView()
{
}

void PlayerView::Update()
{
    Int3 curPos = Int3(model->GetWorldPos() / BLOCK_LENGTH);
    //curPos /= static_cast<int>(BLOCK_LENGTH);
    string str;
    ImGui::Text((str + "State : " + model->StateToString(model->state)).c_str());
    ImGui::Text(("Int3 : " + WORLD->GetBlock(curPos).to_string() + " " + to_string(curPos.x) + " " + to_string(curPos.y) + " " + to_string(curPos.z)).c_str());
    ImGui::Text(("Vector3 : " + WORLD->GetBlock(model->GetWorldPos()).to_string() + " " + to_string(model->GetWorldPos().x) + " " + to_string(model->GetWorldPos().y) + " " + to_string(model->GetWorldPos().z)).c_str());
    ImGui::Text(("renderFace : " + to_string(WORLD->GetBlock(model->GetWorldPos()).renderFace)).c_str());



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

    if (model->hp != hp)
        UpdateHpUI();
    if (model->hunger != hunger)
        UpdateHungerUI();

    return;
}

void PlayerView::Idle()
{
}

void PlayerView::Walk()
{
}

void PlayerView::Jump()
{
}

void PlayerView::Fall()
{
}

void PlayerView::Super()
{
}

void PlayerView::Swim()
{
}

void PlayerView::Dive()
{
}

void PlayerView::Normal()
{
}

void PlayerView::Acttacking()
{
}

void PlayerView::Digging()
{
}

void PlayerView::UpdateHpUI()
{
    model->hp = hp;
    int i;
    for (i = 0; i < hp / 2; i++) {
        model->pUI->Find("heartF" + to_string(i))->visible = true;
        model->pUI->Find("heartF" + to_string(i))->material = RESOURCE->materials.Load("heartFront.mtl");
    }
    for (; i < 10; i++)
    {
        model->pUI->Find("heartF" + to_string(i))->visible = false;
        model->pUI->Find("heartF" + to_string(i))->material = RESOURCE->materials.Load("heartFront.mtl");
    }
    if (hp % 2 == 1)
    {
        model->pUI->Find("heartF" + to_string(hp / 2))->visible = true;
        model->pUI->Find("heartF" + to_string(hp / 2))->material = RESOURCE->materials.Load("heartHalf.mtl");
    }
    model->pUI->Update();
}

void PlayerView::UpdateHungerUI()
{
    model->hunger = hunger;
    int i;
    for (i = 0; i < hunger / 2; i++) {
        model->pUI->Find("foodF" + to_string(i))->visible = true;
        model->pUI->Find("foodF" + to_string(i))->material = RESOURCE->materials.Load("foodFront.mtl");
    }
    for (; i < 10; i++)
    {
        model->pUI->Find("foodF" + to_string(i))->visible = false;
        model->pUI->Find("foodF" + to_string(i))->material = RESOURCE->materials.Load("foodFront.mtl");
    }
    if (hunger % 2 == 1)
    {
        model->pUI->Find("foodF" + to_string(hunger / 2))->visible = true;
        model->pUI->Find("foodF" + to_string(hunger / 2))->material = RESOURCE->materials.Load("foodHalf.mtl");
    }
    model->pUI->Update();
}
