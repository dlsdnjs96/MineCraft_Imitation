#pragma once
class Furnace : public Singleton<Furnace>
{
private:
	UI*		ui;
	float	fire_time;

public:
	void	Init();
	void	Update();
	void	Render();
	void	RenderHierarchy();
	void	Release();

	void	SetFire(int _fire);
	void	SetProgress(int _progress);
};

