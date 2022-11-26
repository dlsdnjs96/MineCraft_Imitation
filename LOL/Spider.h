#pragma once
class Spider : public Monster
{
private:
public:
	Spider();

	void	Init(Vector3 _pos);
	void	Update();
	void	Render();
	void	RenderHierarchy();
	void	Release();
	void	Interact(int _itemid);

	void	Idle();
	void	Move();
	void	Fall();
	void	Follow();
	void	Attack();


	void	AniReset() override;
};