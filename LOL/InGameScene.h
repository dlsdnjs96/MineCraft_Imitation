#pragma once



class InGameScene : public Scene
{
private:
	Actor* Grid;

	Player* player;
	Actor* player2;

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

