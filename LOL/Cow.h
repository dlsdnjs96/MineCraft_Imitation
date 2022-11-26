#pragma once
class Cow : public Monster
{
private:
public:
	Cow();

	void	Init(Vector3 _pos);
	void	Update();
	void	Render();
	void	RenderHierarchy();
	void	Release();
	void	Interact(int _itemid);

	void	Idle();
	void	Move();
	void	Jump();
	void	Fall();
	void	RunAway();
	void	Follow();
};