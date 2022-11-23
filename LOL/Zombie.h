#pragma once
class Zombie : public Monster
{
private:
public:
	Zombie();

	void	Init(Vector3 _pos);
	void	Update();
	void	Render();
	void	RenderHierarchy();
	void	Release();

	void	Idle();
	void	Move();
	void	Fall();
	void	Follow();
	void	Attack();

};