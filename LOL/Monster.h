#pragma once


enum class MonsterState
{
	IDLE,
	MOVE,
	JUMP,
	FALL,
	RUN_AWAY,
	HIT,
	ATTACK,
	SWIM,
	FLY
};

class Monster : public Actor
{
private:
public:
	virtual void	Release();
	virtual void	RenderDetail();
	virtual void	Update();

	virtual void	Idle();
	virtual void	Move();
	virtual void	Jump();
	virtual void	Fall();
	virtual void	RunAway();
	virtual void	Hit();
	virtual void	Attack();
	virtual void	Swim();
	virtual void	Fly();
};

