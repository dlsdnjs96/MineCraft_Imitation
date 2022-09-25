#include "stdafx.h"

template<typename T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}


void Shop::invenUpdate()
{
	for (auto it = inven.begin(); it != inven.end(); it++)
	{
		if (it->second->num > 0)
		{
			SafeReset(Ui->Find(it->first)->material->diffuseMap);
			Ui->Find(it->first)->material->diffuse.w = 1.0f;
			Ui->Find(it->first)->material->diffuseMap = make_shared<Texture>();
			Ui->Find(it->first)->material->diffuseMap->
				LoadFile(it->second->imgFile);
		}
		else
		{
			SafeReset(Ui->Find(it->first)->material->diffuseMap);
			Ui->Find(it->first)->material->diffuse.w = 0.0f;
		}
	}
}

void Shop::Init()
{
	OverName = " ";
	Ui = UI::Create();
	Ui->LoadFile("Shop.xml");

	Item* temp = new Item();
	temp->num = 3;
	temp->name = "redPotion";
	temp->imgFile = "2000000.png";
	inven["_00"] = temp;


	temp = new Item();
	temp->num = 1;
	temp->name = "bluePotion";
	temp->imgFile = "2000003.png";
	inven["_01"] = temp;

	temp = new Item(*temp);
	//temp->num = 1;
	//temp->name = "whitePotion";
	//temp->imgFile = "2000002.png";
	inven["_10"] = temp;

	temp = new Item(*temp);
	//temp->num = 0;
	//temp->name = " ";
	//temp->imgFile = " ";
	inven["_11"] = temp;

	//Ui->mouseOver = [this]() {OverName = "None"; };
	for (auto it = inven.begin(); it != inven.end(); it++)
	{
		((UI*)Ui->Find(it->first))->mouseOver = [it, this]() {this->OverName = it->first; };
		((UI*)Ui->Find(it->first))->mouseDown = [=]()
		{
			Mouse->visible = true;
			Swap(Mouse->material, Ui->Find(it->first)->material);
		};
		((UI*)Ui->Find(it->first))->mouseUp = [=]()
		{
			Mouse->visible = false;
			Swap(Mouse->material, Ui->Find(it->first)->material);

			if (OverName != "None")
			{
				//  second <- > second
				//
				if (it->second->name == inven[OverName]->name)
				{
					it->second->num--;
					inven[OverName]->num++;
					if (it->second->num == 0)
					{
						it->second->name = " ";
					}
				}
				else
				{
					Swap(it->second, inven[OverName]);
				}
			}
			invenUpdate();
		};
	}

	((UI*)Ui->Find("exit"))->mouseDown = [this]() {this->active = false; };

	invenUpdate();
	Mouse = UI::Create("Mouse");
	Mouse->shader = Ui->shader;
	Mouse->mesh = Ui->mesh;
	Mouse->visible = false;
	Mouse->scale = Vector3(0.2f, 0.2f, 0.2f);
}

void Shop::Update()
{
	if (!active)
		return;
	Ui->Update();


	Mouse->SetWorldPos(INPUT->NDCPosition);
	Mouse->Update();

	ImGui::Begin("Hierarchy");
	Ui->RenderHierarchy();
	Mouse->RenderHierarchy();
	ImGui::End();
}

void Shop::Render()
{
	if (!active)
		return;
	for (auto it = inven.begin(); it != inven.end(); it++)
	{
		if (it->second->num > 0)
		{
			//ndc
			Vector3 Pos = Ui->Find(it->first)->GetWorldPos();
			Pos.x += 0.1f;
			Pos.y -= 0.1f;

			//ndc to screen
			Pos.x = (Pos.x + 1.0f) * App.GetHalfWidth();
			Pos.y = (-Pos.y + 1.0f) * App.GetHalfHeight();
			RECT rc{ Pos.x ,Pos.y,Pos.x + 1000,Pos.y + 1000 };
			DWRITE->RenderText(to_wstring(it->second->num), rc, 40.0f,
				L"µ¸¿òÃ¼", Color(1, 0, 0), DWRITE_FONT_WEIGHT_BOLD);
		}
	}



	DEPTH->Set(false);
	Ui->Render();
	Mouse->Render();
	DEPTH->Set(true);
}
