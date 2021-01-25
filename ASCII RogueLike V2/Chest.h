#pragma once

#include "Item.h"
#include "Player.h"


class Chest
{
public:
	Chest(int x, int y);
	Chest(int x, int y, Item item);

	//Getters
	bool getStatus() { return _status; }//returns true if chest is closed
	void getLocation(int& x, int& y) { x = _x; y = _y; }

	void addRandomItem(Item& item);
	void addItem(Item& item);
	template <class T> void openChest(T& player);

private:
	int _x;
	int _y;
	bool _status;//if true then chest is closed
	Item _item;
	int _itemAmount;
};

//open chest, add item to player inventory, mark chest as openned
template <class T> void Chest::openChest(T& player) {
	std::cout << "You obtained a: " << _item.getName();
	player.addItem(&_item);
	_status = false;
}