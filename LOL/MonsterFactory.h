#pragma once
class MonsterFactory : public Singleton<MonsterFactory>
{
private:
	queue<Monster*> pigs;
	queue<Monster*> cows;
	queue<Monster*> sheeps;
	queue<Monster*> chickens;
	queue<Monster*> zombies;
	queue<Monster*> spiders;
	queue<Monster*> skeletons;
public:

	Monster* GetMonster(MonsterType _monsterType);
	void ReturnMonster(Monster* _monster);
};

