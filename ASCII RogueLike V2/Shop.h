#pragma once
#include <string>
#include <list>

#include "Item.h"
#include "Player.h"

class Shop
{
public:
	Shop(std::string name, char shopType, int x, int y, int money);

	void pause();
	void enterShop(Player& player);
	void printShop(Player& player);
	void playerSell(Player& player);
	Item* addItem(Item* newItem);
	Item* addItemCopy(Item* item, int count = -1);
	void removeItem(Item* item);
	void addMoney(int amount) { _money += amount; }
	void removeMoney(int amount) { _money -= amount; }
	void deleteItemList();

	//Setters
	void setLocation(int x, int y) { _x = x; _y = y; }

	//Getters
	std::string getName() { return _name; }
	int getMoney() { return _money; }
	void getLocation(int& x, int& y) { x = _x; y = _y; }

private:
	void initShop();
	bool canAffordItem(Item* item);

	std::string _name;
	int _money;
	char _shopType;
	int _x;
	int _y;

	std::list<Item*> _itemList;
};

