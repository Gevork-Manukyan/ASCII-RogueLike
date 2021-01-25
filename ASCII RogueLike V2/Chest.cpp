#include "Chest.h"
#include <iostream>

//A chest with a status true has not been openned

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
	item.randomItem();
}

//add specific item
void Chest::addItem(Item& item)
{
	_item.copyItem(&item);
}

