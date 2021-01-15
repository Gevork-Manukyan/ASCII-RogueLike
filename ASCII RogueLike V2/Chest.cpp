#include "Chest.h"


Chest::Chest(int x, int y)
{
	_x = x;
	_y = y;
	_status = true;
	addRandomItem(_item);
}

Chest::Chest(int x, int y, Item item)
{
	_x = x;
	_y = y;
	_status = true;
	addItem(item);
}

//randomly create and add item
void Chest::addRandomItem(Item& item)
{
	//item.random();
}

//add specific item
void Chest::addItem(Item& item)
{
	//_item = item;
}