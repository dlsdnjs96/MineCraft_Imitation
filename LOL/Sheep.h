#pragma once
class Sheep : public Monster
{
private:
	bool shaved;
	float	shavedTime;
public:
	Sheep();

	void	Init(Vector3 _pos);
	void	Update();
	void	Render();
	void	RenderHierarchy();
	void	Release();
	void	Interact(int _itemid);

	void	Idle();
	void	Move();
	void	Fall();
	void	RunAway();
	void	Follow();

	void	CheckWool();
};

