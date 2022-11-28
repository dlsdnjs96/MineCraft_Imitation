#pragma once
class PlayerView
{
private:
	PlayerModel*	model;
	int				hp;
	int				hunger;
	float			passedTime;
public:
	PlayerView(PlayerModel* _model);
	~PlayerView();

	void	Update();
	void	Render();

	void	AniReset();

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

	void	UpdateHpUI();
	void	UpdateHungerUI();
};

