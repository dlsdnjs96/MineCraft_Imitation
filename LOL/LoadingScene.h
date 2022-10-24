#pragma once

class LoadingScene : public Scene
{
private:
	Camera* Cam;
	UI* ui;
	thread* t1;


public:
	LoadingScene();
	~LoadingScene();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};