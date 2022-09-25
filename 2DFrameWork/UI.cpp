#include "framework.h"

UI* UI::Create(string name)
{
	UI* temp = new UI();
	temp->name = name;
	temp->type = ObType::UI;
	return temp;
}

UI* UI::CreateChild(string name)
{
	UI* temp = new UI();
	temp->name = name;
	temp->type = ObType::UI;

	temp->mesh = make_shared<Mesh>();
	temp->mesh->LoadFile("6.UI.mesh");

	temp->shader = make_shared<Shader>();
	temp->shader->LoadFile("6.Cube.hlsl");

	temp->material = make_shared<Material>();
	return temp;
}

void UI::Update()
{
	float left = GetWorldPos().x - S._11 *0.5f;
	float right = GetWorldPos().x + S._11 * 0.5f;
	float top = GetWorldPos().y + S._22 * 0.5f;
	float bottom = GetWorldPos().y - S._22 * 0.5f;

	if (material)
		ImGui::Text((name +" : " + (material->diffuseMap->file)).c_str());

	if (left < INPUT->NDCPosition.x and INPUT->NDCPosition.x < right
		and bottom < INPUT->NDCPosition.y and
		INPUT->NDCPosition.y < top)
	{
		Over = true;
		//함수포인터가 할당 되었다면 실행
		if (mouseOver) mouseOver();

		if (INPUT->KeyDown(VK_LBUTTON))
		{
			Press = true;
			if (mouseDown) mouseDown();
		}

	}
	else
		Over = false;

	if (Press)
	{
		if (INPUT->KeyPress(VK_LBUTTON))
		{
			if (mousePress) mousePress();
		}
		if (INPUT->KeyUp(VK_LBUTTON))
		{
			Press = false;

			if (mouseUp) mouseUp();
		}
	}

	Actor::Update();

	

	
	
}
