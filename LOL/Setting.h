#pragma once

class Setting : public Singleton<Setting>
{
private:
	bool*	verticalSync = nullptr;
	float	visualRange = 5000.f;

public:
	Setting();
	~Setting();

	void Init();
	void Release();

	float GetVisualRange();

	void Load();
	void Save();
};

