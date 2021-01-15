#pragma once

#include "Item.h"


class Chest
{
public:
	Chest(int x, int y);
	Chest(int x, int y, Item item);

	//Getters
	bool getStatus() { return _status; }//returns true if chest is closed

	void addRandomItem(Item& item);
	void addItem(Item& item);

private:
	int _x;
	int _y;
	bool _status;//if true then chest is closed
	Item _item;
};

