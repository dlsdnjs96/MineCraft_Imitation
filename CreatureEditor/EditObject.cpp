#include "stdafx.h"

void EditObject::Release()
{
}

void EditObject::Update()
{
	GameObject::Update();
}

void EditObject::Render(Shader* otherShader)
{
	GameObject::Render();
}

void EditObject::RenderDetail()
{
	GameObject::RenderDetail();
	if (ImGui::BeginTabBar("MyTabBar"))
	{
		if (ImGui::BeginTabItem("EditObject"))
		{
			ImGui::InputFloat("uvUp from X", &uvUp.first.x);
			ImGui::InputFloat("uvUp from Y", &uvUp.first.y);
			ImGui::InputFloat("uvUp to X", &uvUp.second.x);
			ImGui::InputFloat("uvUp to Y", &uvUp.second.y);
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
}
