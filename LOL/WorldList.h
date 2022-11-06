#pragma once

struct WorldIcon
{
	string name;
	string path;
};

class WorldList : public UI
{
private:
	bool pickedScroll;
	vector<WorldIcon> wList;
	string selectedWorld;
public:
	void Init();
	void Update();
	void Render();

	void LoadWorldList();
};

