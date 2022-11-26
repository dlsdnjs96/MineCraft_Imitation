#include "stdafx.h"

void Furnace::Init()
{
	ui = UI::Create("Furnace");
	ui->LoadFile("Ingame/Furnace.xml");

	fire_time = 0.f;
}

void Furnace::Update()
{
	fire_time += DELTA;

	fire_time = fmod(fire_time, 6.f);
	SetFire(int(fire_time / 1.f));
	ui->Update();
}

void Furnace::Render()
{
	ui->Render();
}

void Furnace::RenderHierarchy()
{
	ui->RenderHierarchy();
}

void Furnace::Release()
{
	ui->Release();
}

void Furnace::SetFire(int _fire)
{
	ui->Find("fire")->SetWorldPos({ -0.125f , 0.37f + (0.014f * float(_fire)), 0.4f });
	ui->Find("fire")->scale = { 0.1f, 0.1f - (0.02f * float(_fire)), 0.1f};
}

void Furnace::SetProgress(int _progress)
{
}
