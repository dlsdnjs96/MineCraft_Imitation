#pragma once



class MonsterManager : public Singleton<MonsterManager>
{
private:
	ObjectPool<Monster> pool;
	unordered_map<int, unordered_map<int, list<Monster*>>> monsters;
	unordered_map<int, unordered_map<int, list<Monster*>*>> activeMonsters;
	vector<pair<int, int>> activeMonster;


	Vector2			prevPos = { 0.f, 0.f };
	Int3			prevSector = { 0, 0, 0 };
	Int3			currSector = { 1, 1, 1 };

public:
	void	Init();
	void	Release();
	void	Update();
	void	RenderHierarchy();
	void	Render();

	void	distinguishSectors();
	void	Spawn(MonsterType _monsterType, Vector3 _pos);
	void	RemoveMonster(Int3& _int3, Monster* _monster);
	void	AddMonster(Int3& _int3, Monster* _monster);

	bool	AttackWithRay(Ray& _ray);

	void	DropItem(MonsterType _monsterType, Vector3 _pos);
};

