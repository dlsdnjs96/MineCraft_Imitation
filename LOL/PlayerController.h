#pragma once
class PlayerController
{
private:
	PlayerModel* model;
public:
	PlayerController(PlayerModel* _model);
	~PlayerController();

	void	Update();

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
	bool	FourWaysFloating();
};

