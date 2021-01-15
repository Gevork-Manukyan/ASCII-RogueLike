#pragma once
#include <string>

class Item
{
public:
	Item();
	Item(std::string name, int value);
	Item(std::string name, int healthPoints, int value, int attack, int defense);

	void addOne();
	void removeOne();
	Item* copyItem(Item* item);

	/*Specific Item*/

	const int NUM_TYPE_ITEMS = 7;

	//Weapons
	const int NUM_WEAPON_ITEMS = 3;
	Item* createSword(char type);
	Item* createAxe(char type);
	Item* createShield(char type);

	//Armour
	const int NUM_ARMOUR_ITEMS = 4;
	Item* createHelmet(char type);
	Item* createChestPiece(char type);
	Item* createGauntlet(char type);
	Item* createBoots(char type);

	//Food
	const int NUM_FOOD_ITEMS = 4;
	Item* createApple();
	Item* createBannanna();
	Item* createFruitSalad();
	Item* createKabob();

	/*Random Items*/

	//Completely random
	Item* randomItem();

	//Random by type
	Item* randomBronzeItem();
	Item* randomIronItem();
	Item* randomGoldItem();

	//Random by item
	Item* randomWeapon(char type = 'R');
	Item* randomArmour(char type = 'R');
	Item* randomFood();

	//Getters

	std::string getName() { return _name; }
	int getHealthPoints() { return _healthPoints; }
	int getAttack() { return _attack; }
	int getDefense() { return _defense; }
	int getValue() { return _value; }
	int getCount() { return _count; }

	//Setters
	void setCount(int count) { _count = count; }

private:
	std::string _name;
	int _healthPoints;
	int _attack;
	int _defense;
	int _value;
	int _count;

	//Setters
	void setName(std::string name) { _name = name; }
	void setHealthPoints(int healthPoints) { _healthPoints = healthPoints; }
	void setAttack(int attack) { _attack = attack; }
	void setDefense(int defense) { _defense = defense; }
	void setValue(int value) { _value = value; }
};