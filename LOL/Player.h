#pragma once


enum class PLAYER_STATE
{
	IDLE = 0,
	WALK = 1,
	JUMP = 2,
	FALL = 3,
	SUPER = 5,
	SWIM = 6,
	DIVE = 7,
	DEAD = 8
};

enum class ACT_STATE
{
	NORMAL = 0,
	ATTACKING = 1,
	DIGGING = 2
};

class Player : public Actor
{
private:
	PLAYER_STATE	state = PLAYER_STATE::SUPER;
	ACT_STATE		actState = ACT_STATE::NORMAL;
	Vector3			prevPos;
	Vector3			moveForce;

	Int3			curInt3;
	Int3			underInt3;
	const float		gravity = 9.8f * 10.f;
	const float		risingForce = 9.8f * 2.f;
	float			moveSpeed = 50.f;
	float			swimSpeed = 50.f / 3.f;
	float			jumpSpeed = 50.f;
	float			jumppedTime = 0.f;
	float			passedTime = 0.f;

	Int3			targetInt3;
	Int3			prevTarget;
	Actor*			breakingBlock;
	vector<Int3>	rayIntersectOrder;

	int				hp;

public:
	static	Player* user;
	void	Init();
	void	Update();
	void	Release();

	void	Idle();
	void	Walk();
	void	Jump();
	void	Fall();
	void	Super();
	void	Swim();
	void	Dive();

	void	Normal();
	void	Acttacking();
	void	Digging();

	bool	FourWaysMoving();
	bool	GravityMoving();
	bool	FourWaysFloating();
	bool	GravityFloating();

	bool	RenderHierarchy();
	void	Render();

	void	InteractBlock();
	int		FindTarget();
	void	InstallBlock();
	void	UninstallBlock();

	int		GetAttackPoint();
	void	AttackByMonster(int damage);

	void	Collider();

	const char*		StateToString(PLAYER_STATE e);

};

