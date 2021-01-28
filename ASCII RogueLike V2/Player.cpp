#include <random>
#include <ctime>
#include <math.h>
#include <iostream>

#include "Player.h"

Player::Player()
{

}

//equip an item
void Player::equipItem(Item* item)
{
	_heldItem = item;
}

//returns address of item in list
Item* Player::getItem(int index)
{
	std::list<Item*>::iterator lit;
	lit = _inventoryList.begin();
	for (int i = 0; i < index; i++)
	{
		lit++;
	}
	return (*lit);
}

//Prints inventory
void Player::printInventoryList(int version)
{
	std::list<Item*>::iterator lit;
	int i = 1;

	if (version == 0) {

		std::string listItem;
		int spaces;
		for (lit = _inventoryList.begin(); lit != _inventoryList.end(); lit++)
		{

			printf("\t\t%*s", 30, " ");
			listItem = "   " + std::to_string(i) + ". [" + std::to_string((*lit)->getValue()) + " GP] " + (*lit)->getName() + " x" + std::to_string((*lit)->getCount());
			spaces = 52 - listItem.length();
			printf("|%s%s|\n", listItem.c_str(), std::string(spaces, ' ').c_str());
			i++;

		}
	}
	else {

		for (lit = _inventoryList.begin(); lit != _inventoryList.end(); lit++)
		{
			if ((*lit) == _heldItem)	//Write (E) next to equipped item
			{
				std::cout << "(" << i << ") " << "[" << (*lit)->getValue() << " GP] " << (*lit)->getName() << " x" << (*lit)->getCount() << " (E)\n";
				i++;
				continue;
			}
			std::cout << "(" << i << ") " << "[" << (*lit)->getValue() << " GP] " << (*lit)->getName() << " x" << (*lit)->getCount() << "\n";
			i++;
		}
	}
}


bool Player::canAffordItem(Item* item)
{
	if (getMoney() >= (*item).getValue())
	{
		return true;
	}
	return false;
}

//Add item to inventory; return item address
Item* Player::addItem(Item* newItem)
{
	std::list<Item*>::iterator lit;
	for (lit = _inventoryList.begin(); lit != _inventoryList.end(); lit++)
	{
		if ((*lit)->getName() == (*newItem).getName())
		{
			(*lit)->addOne();
			delete newItem;
			return (*lit);
		}
	}//for end

	_inventoryList.push_back(newItem);
	return newItem;
}

//Add new instance of item to inventory; return new item address
Item* Player::addItemCopy(Item* item, int count)
{
	std::list<Item*>::iterator lit;
	for (lit = _inventoryList.begin(); lit != _inventoryList.end(); lit++)
	{
		if ((*lit)->getName() == (*item).getName())
		{
			(*lit)->addOne();
			return (*lit);
		}
	}//for end

	//create new item, copy the current one, and return new item address
	Item* newItem = new Item;
	newItem->copyItem(item);
	if (count != -1)				//if count not specified use item's count
		newItem->setCount(count);
	_inventoryList.push_back(newItem);
	return newItem;
}

//Remove item from inventory
void Player::removeItem(Item* item)
{
	std::list<Item*>::iterator lit;
	for (lit = _inventoryList.begin(); lit != _inventoryList.end(); lit++)
	{
		if ((*lit)->getName() == (*item).getName())
		{
			(*lit)->removeOne();
			if ((*lit)->getCount() <= 0)
				lit = _inventoryList.erase(lit);
			return;
		}
	}//for end
}

//returns random attack value
int Player::attack()
{
	static std::default_random_engine randomEngine((unsigned) time(NULL));
	std::uniform_real_distribution<double> attackRoll(1, _attack);

	return (int)attackRoll(randomEngine);
}

//calculate damage taken; return current level if dead and 0 if not
int Player::takeDamage(int attack)
{
	attack -= _defense;
	_health -= attack;
	if (_health <= 0)		//check death
		return _level;
	return 0;
}

//add experience and leveling up player
void Player::addExperience(int experience)
{
	_experience += experience;

	//check if level up
	if (experience >= _expCap)
	{
		_health = (int)round(_health * 1.2f);
		_attack = (int)round(_attack * 1.15f);
		_defense = (int)round(_defense * 1.17f);
		_level++;
		_expCap += 2;
	}
}