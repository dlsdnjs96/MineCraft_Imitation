#pragma once


enum class MonsterState
{
	IDLE,
	MOVE,
	JUMP,
	FALL,
	RUN_AWAY,
	HIT,
	FOLLOW,
	ATTACK,
	SWIM,
	FLY,
	DEAD
};

enum class MonsterType {
	PIG,
	COW,
	SHEEP,
	CHICKEN,
	SKELETON,
	ZOMBIE
};

class Monster : public Actor
{
private:
protected:
	const float		gravity = 9.8f * 10.f;
	const float		risingForce = 9.8f * 2.f;
	float			moveSpeed = 50.f;
	float			swimSpeed = 50.f / 3.f;
	float			jumpSpeed = 50.f;
public:
	Vector3			moveForce;
	Vector3			dir;
	float			jumppedTime = 0.f;

	Int3			curInt3;
	Int3			underInt3;
	Int3			prevSector;
	Int3			currSector;
	MonsterState	state;
	MonsterType		type;
	float			passedTime;
	bool			isAlive;
	float			leftTime = 0.f;

	int				hp;
	int				maxHp;

	virtual void	Init(Vector3 _pos) = 0;
	virtual void	Update() = 0;
	virtual void	Render() = 0;
	virtual void	RenderHierarchy() = 0;
	virtual void	Release() = 0;


	void		HitByPlayer(int damage);

	void		Hit();
	void		Dead();

	void		PreInit();
	void		PreUpdate();


	bool		DectectPlayer(float dis);
	void		FollowPlayer();
	void		FollowWheet();
	void		CheckBlockHeight();
	void		CheckFloor();
	void		HorizontalMove(float boost = 1.f);
	void		FallingDown();
	void		BackAndForthDir();
};

