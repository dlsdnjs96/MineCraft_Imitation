#pragma once

class Item {
private:
public:
	Item();
	Item(int _itemid, int _ea);
	void Remove();
	int itemid;
	int ea;
};