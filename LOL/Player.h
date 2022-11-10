#pragma once


enum class PLAYER_STATE
{
	IDLE = 0,
	WALK = 1,
	JUMP = 2,
	FALL = 3,
	ATTACK = 4,
	SUPER = 5,
	SWIM = 6,
	DIVE = 7
};

class Player : public Actor
{
private:
	PLAYER_STATE	state = PLAYER_STATE::SUPER;
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

	//GameObject*		rayIntersectOrder[94];
	vector<Int3>	rayIntersectOrder;
public:
	void Init();
	void Update();
	void Release();

	void Idle();
	void Walk();
	void Jump();
	void Fall();
	void Attack();
	void Super();
	void Swim();
	void Dive();

	bool FourWaysMoving();
	bool GravityMoving();
	bool FourWaysFloating();
	bool GravityFloating();

	bool RenderHierarchy();
	void Render();

	void InstallBlock();
	void UninstallBlock();

	void Collider();

	const char* StateToString(PLAYER_STATE e);

};

