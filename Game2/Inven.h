#pragma once

struct Item
{
	string	name;
	string	imgFile;
	int		num;
	//GameObject* temp;
	//int		price;
};


class Inven
{
public:
	//�׷��ٰ�ü
	UI* Ui;
	//���� ����
	map<string,Item*> inven;

	string OverName;
	UI* Mouse;

	bool active = false;
	int meso = 0;
private:
	void invenUpdate();

public:
	void Init();
	void Update();
	void Render();
};

