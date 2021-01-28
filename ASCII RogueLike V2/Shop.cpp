#include "Shop.h"
#include <iostream>
#include <conio.h>

Shop::Shop(std::string name, char shopType, int x, int y, int money)
{
	_name = name;
	_shopType = shopType;
	setLocation(x, y);
	_money = money;
	initShop();
}

/*PUBLIC*/

void Shop::pause()
{
	std::cout << "(Press Enter)\n";
	_getch();
}

void Shop::enterShop(Player& player)
{
	system("CLS");
	std::cout << "*** Welcome to " << _name << " ***\n\n";
	std::cout << "Shop's Money: " << _money << " GP\n\n\n";

	//Shop Options
	bool isDone = true;
	while (isDone)
	{
		//Print selection menu
		std::cout << "How can I help you?\n";
		std::cout << "(1) Buy\n";
		std::cout << "(2) Sell\n";
		std::cout << "(3) Exit\n";
		std::cout << "Enter a number: ";
		int input;
		std::cin >> input;
		std::cin.ignore(10000, '\n');
		std::cin.clear();

		//Process selection
		switch (input)
		{
		//BUY FROM SHOP
		case 1:
			printShop(player);
			break;

		//SELL TO SHOP
		case 2:
			system("CLS");
			playerSell(player);

			break;

		//EXIT SHOP
		case 3:
			system("CLS");
			std::cout << "\n\n\nThank You for your business!\n";
			pause();
			isDone = false;
			break;
		default:
			break;
		}//switch end
		system("CLS");
	}//while end
}

void Shop::printShop(Player& player)
{
	std::list<Item*>::iterator lit;

	while (true)
	{
		system("CLS");
		std::cout << "What would you like to buy today?\n";
		int i = 1;														//Print Items in shop
		std::cout << "(0) Exit\n";
		for (lit = _itemList.begin(); lit != _itemList.end(); lit++)	//(ex.) (1) [10 GP] Bronze Sword x1
		{
			std::cout << "(" << i << ") [" << (*lit)->getValue() << " GP] " << (*lit)->getName() << " x" << (*lit)->getCount() << "\n";
			i++;
		}
		std::cout << "\n\n";
		std::cout << player.getName() << "'s GP: " << player.getMoney() << "\n\n";

		std::cout << "Enter Item Number: ";								//user inputs which item they want
		int input;
		std::cin >> input;
		std::cin.ignore();
		std::cin.clear();

		if (input == 0)		//check for exit
			return;

		if (input > _itemList.size())
		{
			continue;
		}

		lit = _itemList.begin();										//go to item in the shop list
		for (int i = 0; i < (input - 1); i++)
		{
			lit++;
		}//for end

		if (player.canAffordItem(*lit))			//Check if player can afford item
		{
			player.addItemCopy((*lit), 1);				//add copy of item to player inventory
			player.removeMoney((*lit)->getValue());	//deduct money from player
			addMoney((*lit)->getValue());			//add money to shop
			std::cout << "Success! You bought a " << (*lit)->getName() << "!\n";		//success message
			std::cout << player.getName() << "'s GP: " << player.getMoney() << "\n\n";	//player remaining balance
			removeItem((*lit));						//remove item from list
			pause();
		}
		else
		{
			std::cout << "You do not have enough money!\n";
			pause();
		}//if end
	}//while end
}

//player can sell to shop
void Shop::playerSell(Player& player)
{
	while (true)
	{
		system("CLS");

		//print player inventory and moneys
		std::cout << "\n\n" << player.getName() << "'s GP: " << player.getMoney();
		std::cout << "\n\nWhat would you like to sell\n";
		std::cout << "(0) Exit\n";
		player.printInventoryList();
		std::cout << "\n\n";
		std::cout << getName() << "'s GP: " << getMoney() << "\n\n";

		//user inputs which item they want
		std::cout << "Enter Item Number: ";								
		int input;
		std::cin >> input;
		std::cin.ignore();
		std::cin.clear();

		if (input == 0)		//check for exit
			return;

		if (canAffordItem(player.getItem(input-1)))			//Check if player can afford item
		{
			addItemCopy(player.getItem(input - 1), 1);				//add copy of item to player inventory
			removeMoney(player.getItem(input - 1)->getValue());	//deduct money from player
			player.addMoney(player.getItem(input - 1)->getValue());			//add money to shop
			std::cout << "Success! You sold a " << player.getItem(input - 1)->getName() << "!\n";		//success message
			std::cout << player.getName() << "'s GP: " << player.getMoney() << "\n\n";	//player remaining balance
			player.removeItem(player.getItem(input - 1));						//remove item from list
			pause();
		}
		else
		{
			std::cout << getName() << "'s does not have enough money!\n";
			pause();
		}//if end

	}//while end
}

//Add item to list; return item address
Item* Shop::addItem(Item* newItem)
{
	std::list<Item*>::iterator lit;
	for (lit = _itemList.begin(); lit != _itemList.end(); lit++)
	{
		if ((*lit)->getName() == (*newItem).getName())
		{
			(*lit)->addOne();
			delete newItem;
			return (*lit);
		}
	}//for end

	_itemList.push_back(newItem);
	return newItem;
}

Item* Shop::addItemCopy(Item* item, int count)
{
	std::list<Item*>::iterator lit;
	for (lit = _itemList.begin(); lit != _itemList.end(); lit++)
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
	_itemList.push_back(newItem);
	return newItem;
}

//Remove one Item from list; if none left delete from list
void Shop::removeItem(Item* item)
{
	std::list<Item*>::iterator lit;
	for (lit = _itemList.begin(); lit != _itemList.end(); lit++)
	{
		if ((*lit)->getName() == (*item).getName())
		{
			(*lit)->removeOne();
			if ((*lit)->getCount() <= 0)
				lit = _itemList.erase(lit);
			return;
		}
	}//for end

}

void Shop::deleteItemList()
{
	std::list<Item*>::iterator lit;
	for (lit = _itemList.begin(); lit != _itemList.end(); lit++)
	{
		delete (*lit);
		(*lit) = nullptr;
	}//for end
}

/*PRIVATE*/

void Shop::initShop()
{
	switch (_shopType)
	{
	case 'B':
		addItem((new Item())->createSword('b'));
		addItem((new Item())->createChestPiece('b'));
		addItem((new Item())->randomBronzeItem());
		addItem((new Item())->randomWeapon());
		addItem((new Item())->randomArmour('b'));
		addItem((new Item())->randomArmour());
		break;
	case 'F':
		addItem((new Item())->randomFood());
		addItem((new Item())->randomFood());
		addItem((new Item())->randomFood());
		addItem((new Item())->randomFood());
		addItem((new Item())->randomFood());
		break;
	}
}


bool Shop::canAffordItem(Item* item)
{
	if (getMoney() >= (*item).getValue())
	{
		return true;
	}
	return false;
}