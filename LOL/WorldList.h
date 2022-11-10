#pragma once


class WorldList : public UI
{
private:
	bool pickedScroll;
	string selectedWorld;
public:
	void Init();
	void Update();
	void Render();

	void LoadWorldList();
};

