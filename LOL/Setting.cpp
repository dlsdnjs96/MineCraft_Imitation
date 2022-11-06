#include "stdafx.h"

Setting::Setting()
{
	Load();
}

Setting::~Setting()
{
	Save();
}

void Setting::Init()
{
	verticalSync = &App.vSync;
}

void Setting::Release()
{
}

float Setting::GetVisualRange()
{
	return visualRange;
}

void Setting::Load()
{
}

void Setting::Save()
{

}
