#pragma once
class Animation
{
public:
	UINT					frameMax;
	UINT					boneMax;
	Matrix**				arrFrameBone;//	?????Ӱ???* ??????
	float					tickPerSecond;
	string					file;


	Animation();
	~Animation();
	void LoadFile(string file);
	void SaveFile(string file);
	void AddMotion(Matrix* _motion);
};
enum class AnimationState
{
	LOOP,
	ONCE,
	STOP//Pause
};

class Animations
{
	struct Animator
	{
		float frameWeight = 0.0f;
		UINT  currentFrame = 0;
		UINT  nextFrame = 1;
		UINT  animIdx = 0;
		AnimationState animState = AnimationState::STOP;
	};
	void AnimatorUpdate(Animator& Animator);
public:
	Animations();
	~Animations();
	void Update();
	Animator							currentAnimator;
	Animator							nextAnimator;
	bool								isChanging;
	float								blendtime;
	float								Changedtime;
	vector<shared_ptr<Animation>>		playList;
	Matrix	GetFrameBone(int boneIndex);
	void	PlayAnimation(AnimationState state, UINT idx, float blendtime = 0.2f);
	void	RenderDetail();
};