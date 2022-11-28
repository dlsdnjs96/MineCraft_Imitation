#include "stdafx.h"

PlayerView::PlayerView(PlayerModel* _model)
{
    model = _model;
    hp = 0;
    hunger = 0;
    passedTime = 0.f;
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
    ImGui::Text(("target : " + WORLD->GetBlock(model->targetInt3).to_string() + " " + to_string(model->targetInt3.x) + " " + to_string(model->targetInt3.y) + " " + to_string(model->targetInt3.z)).c_str());

    passedTime += DELTA;

    static PLAYER_STATE prev = model->state;
    static ACT_STATE prevA = model->actState;
    if (prev != model->state || prevA != model->actState)
    {
        AniReset();
        prev = model->state;
        prevA = model->actState;
    }

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

    //model->Actor::Update();

    return;
}

void PlayerView::Render()
{
    //model->Actor::Render();

    if (model->theFirstPerson)
        model->Find("theFirstPerson")->Render();
    else
        model->Find("body")->Render();
    model->Find("Collider")->Render();

    if (model->actState == ACT_STATE::DIGGING)
        model->breakingBlock->Render();
    model->pUI->Render();
}

void PlayerView::AniReset()
{
    for (auto& it : model->obList)
        it.second->rotation = { 0.f, 0.f, 0.f };
}

void PlayerView::Idle()
{
}

void PlayerView::Walk()
{
    const float duration = 0.3f;
    float tTime = passedTime + duration;
    if (int(tTime / (duration * 2.f)) % 2 == 0)
    {
        tTime = fmod(tTime, duration * 2.f);

        model->Find("hipL")->rotation.x = tTime - duration;
        model->Find("hipR")->rotation.x = duration - tTime;
        model->Find("shoulderR")->rotation.x = tTime - duration;
        model->Find("shoulderL")->rotation.x = duration - tTime;
    }
    else {
        tTime = fmod(tTime, duration * 2.f);

        model->Find("hipL")->rotation.x = duration - tTime;
        model->Find("hipR")->rotation.x = tTime - duration;
        model->Find("shoulderR")->rotation.x = duration - tTime;
        model->Find("shoulderL")->rotation.x = tTime - duration;
    }
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
    if (INPUT->KeyPress(VK_LBUTTON)) {
        const float duration = 0.15f;
        float tTime = passedTime + duration;
        if (int(tTime / (duration * 2.f)) % 2 == 0)
        {
            tTime = fmod(tTime, duration * 2.f);

            model->Find("shoulderR")->rotation.x = -(1.5f * PI_DIV2) + ((tTime - duration) * 2.f);
        }
        else {
            tTime = fmod(tTime, duration * 2.f);

            model->Find("shoulderR")->rotation.x = -(1.5f * PI_DIV2) + ((duration - tTime) * 2.f);
        }
    }
}

void PlayerView::Acttacking()
{
    const float duration = 0.15f;
    float tTime = passedTime + duration;
    if (int(tTime / (duration * 2.f)) % 2 == 0)
    {
        tTime = fmod(tTime, duration * 2.f);

        model->Find("shoulderR")->rotation.x = -(1.5f * PI_DIV2) + ((tTime - duration) * 2.f);
    }
    else {
        tTime = fmod(tTime, duration * 2.f);

        model->Find("shoulderR")->rotation.x = -(1.5f * PI_DIV2) + ((duration - tTime) * 2.f);
    }
}

void PlayerView::Digging()
{
    const float duration = 0.15f;
    float tTime = passedTime + duration;
    if (int(tTime / (duration * 2.f)) % 2 == 0)
    {
        tTime = fmod(tTime, duration * 2.f);

        model->Find("shoulderR")->rotation.x = -(1.5f * PI_DIV2) + ((tTime - duration) * 2.f);
    }
    else {
        tTime = fmod(tTime, duration * 2.f);

        model->Find("shoulderR")->rotation.x = -(1.5f * PI_DIV2) + ((duration - tTime) * 2.f);
    }
}

void PlayerView::UpdateHpUI()
{
    hp = model->hp;
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
    hunger = model->hunger;
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
