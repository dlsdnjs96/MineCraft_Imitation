#include "stdafx.h"

template<typename T>
void Swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}


void Inven::invenUpdate()
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

void Inven::Init()
{
	OverName = " ";
	Ui = UI::Create();
	Ui->LoadFile("Inven.xml");

	Item* temp = new Item();
	temp->num = 3;
	temp->name = "redPotion";
	temp->imgFile = "2000000.png";
	inven["00"] = temp;
	

	temp = new Item();
	temp->num = 1;
	temp->name = "bluePotion";
	temp->imgFile = "2000003.png";
	inven["01"] = temp;

	temp = new Item(*temp);
	//temp->num = 1;
	//temp->name = "whitePotion";
	//temp->imgFile = "2000002.png";
	inven["10"] = temp;

	temp = new Item(*temp);
	//temp->num = 0;
	//temp->name = " ";
	//temp->imgFile = " ";
	inven["11"] = temp;

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

			if(OverName != "None")
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
	((UI*)Ui->Find("meso"))->mouseDown = [this]() {this->meso += 100; };
	((UI*)Ui->Find("exit"))->mouseDown = [this]() {this->active = false; };

	invenUpdate();
	Mouse = UI::Create("Mouse");
	Mouse->shader = Ui->shader; 
	Mouse->mesh = Ui->mesh;
	Mouse->visible = false;
	Mouse->scale = Vector3(0.2f, 0.2f, 0.2f);
}

void Inven::Update()
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

void Inven::Render()
{
	if (!active)
		return;
	for (auto it = inven.begin(); it != inven.end(); it++)
	{
		if (it->second->num > 0)
		{
			//ndc
			Vector3 Pos = Ui->Find(it->first)->GetWorldPos();
			Pos.x += 0.02f;
			//Pos.y -= 0.031f;

			//ndc to screen
			Pos.x =(Pos.x + 1.0f)* App.GetHalfWidth();
			Pos.y =( -Pos.y + 1.0f )* App.GetHalfHeight();
			RECT rc{ Pos.x ,Pos.y,Pos.x + 1000,Pos.y + 1000 };
			DWRITE->RenderText(to_wstring(it->second->num), rc,20.0f,
				L"µ¸¿òÃ¼",Color(1,0,0),DWRITE_FONT_WEIGHT_BOLD);
		}
	}

	Vector3 Pos = Ui->Find("meso")->GetWorldPos();
	Pos.x = (Pos.x + 1.0f) * App.GetHalfWidth();
	Pos.y = (-Pos.y + 1.0f) * App.GetHalfHeight();
	RECT rc{ Pos.x - 40.f ,Pos.y - 20.f,Pos.x + 1000,Pos.y + 1000 };
	DWRITE->RenderText(to_wstring(meso), rc, 30, L"Verdana", Color(1, 0, 0, 1),
		DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_ITALIC);


	DEPTH->Set(false);
	Ui->Render();
	Mouse->Render();
	DEPTH->Set(true);
}
