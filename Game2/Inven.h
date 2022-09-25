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
	//그려줄객체
	UI* Ui;
	//수량 가격
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

