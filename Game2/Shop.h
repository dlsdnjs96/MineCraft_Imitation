#pragma once


class Shop
{
public:
	//�׷��ٰ�ü
	UI* Ui;
	//���� ����
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