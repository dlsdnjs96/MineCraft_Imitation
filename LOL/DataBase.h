#pragma once


class DataBase : public Singleton<DataBase>
{
private:

	MYSQL mysql;
	MYSQL* conn;
	
	MYSQL_RES* result;
	MYSQL_ROW row;
public:
	DataBase();
	~DataBase();

	void	UpdateWolrd();
	void	UpdateWolrdId();
	void	LoadWolrd();
	void	SaveWolrd();

	void	LoadPlayer();
	void	SavePlayer();

	void	LoadInventory();
	void	SaveInventory();

	void	LoadItemObject();
	void	SaveItemObject();

	void	LoadMonster();
	void	SaveMonster();

	void	LoadFurnace();
	void	SaveFurnace();
};

