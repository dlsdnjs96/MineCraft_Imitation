#include "stdafx.h"
#include "Main.h"
Main::Main()
{
}
Main::~Main()
{
}

//struct A
//{
//	string name = "name";
//	void Print()
//	{
//		cout << name << endl;
//	}
//};
//
//A a;

void Main::Init()
{
	Cam = Camera::Create();
	Cam->LoadFile("Cam.xml");
	Camera::main = Cam;
	Grid = Actor::Create();
	Grid->LoadFile("Grid.xml");

	ShopSphere = Actor::Create();

	ShopSphere->LoadFile("Sphere.xml");

	inv.Init();
	shop.Init();



	Cam->width = App.GetWidth();
	Cam->height = App.GetHeight();
	Cam->viewport.width = App.GetWidth();
	Cam->viewport.height = App.GetHeight();

	/*Ui->mouseDown = [&]() {PrevMouse = INPUT->NDCPosition; };
	Ui->mousePress = bind(&Main::Resize, this);*/
}
//void Main::Resize()
//{
//	Vector3 mov = INPUT->NDCPosition - PrevMouse;
//	Ui->MoveWorldPos(mov * 0.5f);
//	Ui->scale.x += mov.x;
//
//	PrevMouse = INPUT->NDCPosition;
//}

void Main::Release()
{
	
}


void Main::Update()
{
	Camera::ControlMainCam();
	
	//ImGui::Begin("Hierarchy");
	////Ui->RenderHierarchy();
	//ImGui::End();


	Cam->Update();
	Grid->Update();
	ShopSphere->Update();
	inv.Update();
	shop.Update();



	ImGui::Begin("Hierarchy");
	ShopSphere->RenderHierarchy();
	ImGui::End();
	ImGui::Text("Mouse  X: %f Y: %f", INPUT->NDCPosition.x,
		INPUT->NDCPosition.y);

}

void Main::LateUpdate()
{
	Ray Mouse = Util::MouseToRay(INPUT->position, Camera::main);
	Vector3 hit;
	if (Util::RayIntersectTri(Mouse, ShopSphere, hit) && INPUT->KeyPress(VK_LBUTTON))
	{
		inv.active = true;
		shop.active = true;
	}

	/*float left = Ui->GetWorldPos().x - Ui->S._11 * 0.5f;
	float right = Ui->GetWorldPos().x + Ui->S._11 * 0.5f;
	float top = Ui->GetWorldPos().y + Ui->S._22 * 0.5f;
	float bottom = Ui->GetWorldPos().y - Ui->S._22 * 0.5f;

	if (left < INPUT->NDCPosition.x and INPUT->NDCPosition.x < right
		and bottom < INPUT->NDCPosition.y and
		INPUT->NDCPosition.y < top)
	{
		if (INPUT->KeyPress(VK_LBUTTON))
		{
			Vector3 mov = INPUT->NDCPosition - PrevMouse;
			Ui->MoveWorldPos(mov * 0.5f);
			Ui->scale.x += mov.x;
		}
	}*/

	

	//PrevMouse = INPUT->NDCPosition;
}
void Main::Render()
{
	Cam->Set();
	ShopSphere->Render();
	Grid->Render();
	//깊이 렌더링 끄고 그리는 순서에따라 렌더링
	
	inv.Render();
	shop.Render();
	Vector3 vTemp = { ShopSphere->W._11, ShopSphere->W._22, ShopSphere->W._33 };
	Vector2 sTemp;

	if (Util::WorldToScreen(vTemp, sTemp, Cam->view * Cam->proj, App.GetWidth(), App.GetHeight()) && !shop.active)
	{
		RECT rc{ sTemp.x, sTemp.y, sTemp.x + 150, sTemp.y + 100 };
		DWRITE->RenderText(L"상점주인", rc, 30, L"Verdana", Color(1,0,0,1),
			DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_ITALIC);
	}
}

void Main::ResizeScreen()
{
	Cam->width = App.GetWidth();
	Cam->height = App.GetHeight();
	Cam->viewport.width = App.GetWidth();
	Cam->viewport.height = App.GetHeight();
}


int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	App.SetAppName(L"Game2");
	App.SetInstance(instance);
	WIN->Create();
	D3D->Create();
	Main* main = new Main();
	main->Init();
	int wParam = (int)WIN->Run(main);
	main->Release();
	SafeDelete(main);
	D3D->DeleteSingleton();
	WIN->DeleteSingleton();
	return wParam;
}
