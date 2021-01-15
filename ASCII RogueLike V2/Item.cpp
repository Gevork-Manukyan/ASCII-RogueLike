#include <stdlib.h>
#include <random>
#include <ctime>

#include "Item.h"


Item::Item()
{
	_name = "NOITEMNAME";
	_healthPoints = -1;
	_attack = 0;
	_defense = 0;
	_value = -1;
	_count = 1;
}

Item::Item(std::string name, int value)
{
	_name = name;
	_value = value;
	_count = 1;

}

Item::Item(std::string name, int healthPoints, int value, int attack, int defense)
{
	_name = name;
	_healthPoints = healthPoints;
	_attack = attack;
	_defense = defense;
	_value = value;
	_count = 1;

}

void Item::addOne()
{
	_count++;
}

void Item::removeOne()
{
	if (_count > 0)
		_count--;
}

//copy item in parameter and return address of new item
Item* Item::copyItem(Item* item)
{
	this->setName(item->getName());
	this->setHealthPoints(item->getHealthPoints());
	this->setAttack(item->getAttack());
	this->setDefense(item->getDefense());
	this->setValue(item->getValue());
	this->setCount(item->getCount());

	return this;
}

/*ITEMS*/

/*B = Bronze, I = Iron, G = Gold*/
Item* Item::createSword(char type)
{
	type = toupper(type);

	switch (type)
	{
		//Bronze
	case 'B':
		_name = "Bronze Sword";
		_attack = 1;
		_value = 10;
		return this;

		//Iron
	case 'I':
		_name = "Iron Sword";
		_attack = 3;
		_value = 17;
		return this;

		//Gold
	case 'G':
		_name = "Gold Sword";
		_attack = 5;
		_value = 22;
		return this;

	default:
		exit(1);
		break;
	}//switch end
}

//B = Bronze, I = Iron, G = Gold
Item* Item::createAxe(char type)
{
	type = toupper(type);

	switch (type)
	{
		//Bronze
	case 'B':
		_name = "Bronze Axe";
		_attack = 1;
		_defense = 1;
		_value = 13;
		return this;

		//Iron
	case 'I':
		_name = "Iron Axe";
		_attack = 3;
		_defense = 2;
		_value = 20;
		return this;

		//Gold
	case 'G':
		_name = "Gold Axe";
		_attack = 5;
		_defense = 4;
		_value = 25;
		return this;

	default:
		exit(1);
		break;
	}//switch end
}

//B = Bronze, I = Iron, G = Gold
Item* Item::createShield(char type)
{
	type = toupper(type);

	switch (type)
	{
		//Bronze
	case 'B':
		_name = "Bronze Shield";
		_defense = 3;
		_value = 10;
		return this;

		//Iron
	case 'I':
		_name = "Iron Shield";
		_defense = 6;
		_value = 17;
		return this;

		//Gold
	case 'G':
		_name = "Gold Shield";
		_defense = 10;
		_value = 23;
		return this;

	default:
		exit(1);
		break;
	}//switch end
}

//B = Bronze, I = Iron, G = Gold
Item* Item::createHelmet(char type)
{
	type = toupper(type);

	switch (type)
	{
		//Bronze
	case 'B':
		_name = "Bronze Helmet";
		_defense = 2;
		_value = 8;
		return this;

		//Iron
	case 'I':
		_name = "Iron Helmet";
		_defense = 5;
		_value = 13;
		return this;

		//Gold
	case 'G':
		_name = "Gold Helmet";
		_defense = 8;
		_value = 18;
		return this;

	default:
		exit(1);
		break;
	}//switch end
}

//B = Bronze, I = Iron, G = Gold
Item* Item::createChestPiece(char type)
{
	type = toupper(type);

	switch (type)
	{
		//Bronze
	case 'B':
		_name = "Bronze Chest Piece";
		_defense = 3;
		_value = 11;
		return this;

		//Iron
	case 'I':
		_name = "Iron Chest Piece";
		_defense = 6;
		_value = 16;
		return this;

		//Gold
	case 'G':
		_name = "Gold Chest Piece";
		_defense = 9;
		_value = 21;
		return this;

	default:
		exit(1);
		break;
	}//switch end
}

//B = Bronze, I = Iron, G = Gold
Item* Item::createGauntlet(char type)
{
	type = toupper(type);

	switch (type)
	{
		//Bronze
	case 'B':
		_name = "Bronze Gauntlet";
		_defense = 1;
		_value = 5;
		return this;

		//Iron
	case 'I':
		_name = "Iron Gauntlet";
		_defense = 4;
		_value = 10;
		return this;

		//Gold
	case 'G':
		_name = "Gold Gauntlet";
		_defense = 7;
		_value = 15;
		return this;

	default:
		exit(1);
		break;
	}//switch end
}

//B = Bronze, I = Iron, G = Gold
Item* Item::createBoots(char type)
{
	type = toupper(type);

	switch (type)
	{
		//Bronze
	case 'B':
		_name = "Bronze Boots";
		_defense = 2;
		_value = 8;
		return this;

		//Iron
	case 'I':
		_name = "Iron Boots";
		_defense = 5;
		_value = 13;
		return this;

		//Gold
	case 'G':
		_name = "Gold Boots";
		_defense = 8;
		_value = 18;
		return this;

	default:
		exit(1);
		break;
	}//switch end
}

Item* Item::createApple()
{
	_name = "Apple";
	_healthPoints = 1;
	_value = 5;
	return this;
}

Item* Item::createBannanna()
{
	_name = "Bannanna";
	_healthPoints = 2;
	_value = 7;
	return this;
}

Item* Item::createFruitSalad()
{
	_name = "Fruit Salad";
	_healthPoints = 5;
	_value = 13;
	return this;
}

Item* Item::createKabob()
{
	_name = "Kabob";
	_healthPoints = 20;
	_value = 18;
	return this;
}

//Completely random
Item* Item::randomItem()
{
	static std::default_random_engine randomEngine((unsigned int)time(NULL));
	std::uniform_int_distribution<int> item(1, 4);

	int code = item(randomEngine);

	switch (code)
	{
	case 1:
		return randomBronzeItem();
	case 2:
		return randomIronItem();
	case 3:
		return randomGoldItem();
	case 4:
		return randomFood();
	}//switch end
}

//Random by type
Item* Item::randomBronzeItem()
{
	static std::default_random_engine randomEngineB((unsigned int)time(NULL));
	std::uniform_int_distribution<int> bItem(1, NUM_TYPE_ITEMS);

	int code = bItem(randomEngineB);

	switch (code)
	{
	case 1:
		return createSword('b');
	case 2:
		return createAxe('b');
	case 3:
		return createShield('b');
	case 4:
		return createHelmet('b');
	case 5:
		return createChestPiece('b');
	case 6:
		return createGauntlet('b');
	case 7:
		return createBoots('b');
	}//switch end
}

Item* Item::randomIronItem()
{
	static std::default_random_engine randomEngineI((unsigned int)time(NULL));
	std::uniform_int_distribution<int> bItem(1, NUM_TYPE_ITEMS);

	int code = bItem(randomEngineI);

	switch (code)
	{
	case 1:
		return createSword('i');
	case 2:
		return createAxe('i');
	case 3:
		return createShield('i');
	case 4:
		return createHelmet('i');
	case 5:
		return createChestPiece('i');
	case 6:
		return createGauntlet('i');
	case 7:
		return createBoots('i');
	}//switch end
}

Item* Item::randomGoldItem()
{
	static std::default_random_engine randomEngineG((unsigned int)time(NULL));
	std::uniform_int_distribution<int> bItem(1, NUM_TYPE_ITEMS);

	int code = bItem(randomEngineG);

	switch (code)
	{
	case 1:
		return createSword('g');
	case 2:
		return createAxe('g');
	case 3:
		return createShield('g');
	case 4:
		return createHelmet('g');
	case 5:
		return createChestPiece('g');
	case 6:
		return createGauntlet('g');
	case 7:
		return createBoots('g');
	}//switch end
}

//Random by item
Item* Item::randomWeapon(char type)
{
	static std::default_random_engine randomEngineW((unsigned int)time(NULL));
	std::uniform_int_distribution<int> equipment(1, NUM_WEAPON_ITEMS);
	std::uniform_int_distribution<int> Type(1, 3);

	int code = equipment(randomEngineW);
	int symbol;

	type = toupper(type);
	if (type == 'R')
	{
		symbol = Type(randomEngineW);

		switch (symbol)
		{
		case 1:
			type = 'B';
			break;
		case 2:
			type = 'I';
			break;
		case 3:
			type = 'G';
			break;
		}//switch end
	}//if end

	switch (code)
	{
	case 1:
		return createSword(type);
	case 2:
		return createAxe(type);
	case 3:
		return createShield(type);
	}//switch end
}

Item* Item::randomArmour(char type)
{
	static std::default_random_engine randomEngineA((unsigned int)time(NULL));
	std::uniform_int_distribution<int> armour(1, NUM_ARMOUR_ITEMS);
	std::uniform_int_distribution<int> Type(1, 3);

	int code = armour(randomEngineA);
	int symbol;

	type = toupper(type);
	if (type == 'R')
	{
		symbol = Type(randomEngineA);

		switch (symbol)
		{
		case 1:
			type = 'B';
			break;
		case 2:
			type = 'I';
			break;
		case 3:
			type = 'G';
			break;
		}//switch end
	}//if end

	switch (code)
	{
	case 1:
		return createHelmet(type);
	case 2:
		return createChestPiece(type);
	case 3:
		return createGauntlet(type);
	case 4:
		return createBoots(type);
	}//switch end
}

Item* Item::randomFood()
{
	static std::default_random_engine randomEngineF((unsigned int)time(NULL));
	std::uniform_int_distribution<int> food(1, NUM_FOOD_ITEMS);

	int code = food(randomEngineF);

	switch (code)
	{
	case 1:
		return createApple();
	case 2:
		return createBannanna();
	case 3:
		return createFruitSalad();
	case 4:
		return createKabob();
	}//switch end
}
