#pragma once
class Main : public Scene
{
private:

	Camera* Cam;
	Actor* Grid;
	Actor* ShopSphere;

	//UI* Ui;
	Vector3 PrevMouse;
	Inven   inv;
	Shop	shop;


public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //????
	virtual void Update() override;
	virtual void LateUpdate() override;//????
	virtual void Render() override;
	virtual void ResizeScreen() override;

	//void Resize();

};
