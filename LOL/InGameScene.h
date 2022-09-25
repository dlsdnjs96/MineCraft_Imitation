#pragma once



class InGameScene : public Scene
{
private:
	Camera* Cam;
	Actor* Sphere;

	World world;

public:
	InGameScene();
	~InGameScene();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

