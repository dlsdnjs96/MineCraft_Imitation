#pragma once

class MenuScene : public Scene
{
private:
	int page = 1;

	Sky*		sky;
	Camera*		Cam;

	UI*			title;
	UI*			singlePlay;
	UI*			setting;
	UI*			exit;

	WorldList*	worldList;
	UI*			createWorld;
	UI*			playWorld;
	UI*			prev;

	vector<GameObject*> activeObj;
public:
	MenuScene();
	~MenuScene();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void ChangePage(int _page);
};