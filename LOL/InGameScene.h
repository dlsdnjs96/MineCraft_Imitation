#pragma once



class InGameScene : public Scene
{
private:
	Actor* Grid;
	Actor* TestBlock;
	Camera* Cam;
	//Player* player;
	PlayerModel*		playerModel;
	PlayerView*			playerView;
	PlayerController*	playerController;

	Sky* sky;

	UI* resume;
	UI* setting;
	UI* exit;
	UI* aim;

	bool menuTab = false;
public:
	InGameScene();
	~InGameScene();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;


};

