#pragma once
#include <string>
#include <list>

#include "Item.h"

class Player
{
public:
	Player();

	void equipItem(Item* item);

	//Getters
	std::string getName() { return _name; }
	int getMoney() { return _money; }
	int getHealth() { return _health; }
	int getAttack() { return _attack; }
	int getDefense() { return _defense; }
	int getX() { return _x; }
	int getY() { return _y; }
	void getLocation(int& x, int& y) { x = _x; y = _y; }
	char getSymbol() { return _symbol; }
	Item* getItem(int index);

	//Setters
	void setLocation(int x, int y) { _x = x; _y = y; }
	void setName(std::string name) { _name = name; }

	//Inventory
	void printInventory();
	bool canAffordItem(Item* item);
	Item* addItem(Item* newItem);
	Item* addItemCopy(Item* item, int count = -1);
	void removeItem(Item* item);
	void addMoney(int amount) { _money += amount; }
	void removeMoney(int amount) { _money -= amount; }

	//Battle
	int attack();
	int takeDamage(int attack);
	void addExperience(int experience);

private:
	//Player name
	std::string _name;
	//Player Money
	int _money = 50;
	//Hit points
	int _health = 10;
	//Damage output
	int _attack = 5;
	//Damage block
	int _defense = 1;
	//Experience
	int _experience = 0;
	int _expCap = 10;
	//Level
	int _level = 1;
	//Location
	int _x = -1;
	int _y = -1;
	//Icon
	char _symbol = '@';
	//Player Inventory
	std::list<Item*> _inventoryList;
	//Equiped Item
	Item* _heldItem;
};

