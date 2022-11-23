#pragma once
class Chicken : public Monster
{
private:
public:
	Chicken();

	void	Init(Vector3 _pos);
	void	Update();
	void	Render();
	void	RenderHierarchy();
	void	Release();

	void	Idle();
	void	Move();
	void	Fall();
	void	RunAway();
};