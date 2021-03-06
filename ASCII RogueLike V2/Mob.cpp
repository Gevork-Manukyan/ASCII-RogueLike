#include <random>
#include <ctime>

#include "Mob.h"


Mob::Mob(char symbol, int x, int y)
{
	static int mobIDCount = 0;

	switch (symbol)
	{
	case 'S':
		createSnake(x, y, mobIDCount);
		mobIDCount++;
		break;
	case 'O':
		createOgre(x, y, mobIDCount);
		mobIDCount++;
		break;
	default:
		_name = "NULL";
		 _health = -1;
		 _attack = -1;
		 _defense = -1;
		 _x = -1;
		 _y = -1;
		 _symbol = ' ';
		 _experienceValue = -999;
		 _ID = -999;
		break;
	}//end switch
}

/*PUBLIC*/

//returns random attack value
int Mob::attack()
{
	static std::default_random_engine randomEngine((unsigned) time(NULL));
	std::uniform_real_distribution<double> attackRoll(1, _attack);
	
	return (int)attackRoll(randomEngine);
}

//calculate damage taken; return exp if dead and 0 if not
int Mob::takeDamage(int attack)
{
	attack -= _defense;
	_health -= attack;
	if (_health <= 0)		//check death
		return _experienceValue;
	return 0;
}


/*PRIVATE*/

void Mob::createSnake(int x, int y, int ID)
{
	_name = "Snake";
	_health = 5;
	_attack = 3;
	_defense = 0;
	setLocation(x, y);
	_symbol = 'S';
	_experienceValue = 3;
	_ID = ID;
}

void Mob::createOgre(int x, int y, int ID)
{
	_name = "Ogre";
	_health = 10;
	_attack = 5;
	_defense = 2;
	setLocation(x, y);
	_symbol = 'O';
	_experienceValue = 7;
	_ID = ID;
}