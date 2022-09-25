#pragma once


class Shop
{
public:
	//그려줄객체
	UI* Ui;
	//수량 가격
	map<string, Item*> inven;

	string OverName;
	UI* Mouse;

	bool active = false;

private:
	void invenUpdate();

public:
	void Init();
	void Update();
	void Render();
};