#include <random>
#include <ctime>

#include "Mob.h"


Mob::Mob(char symbol, int x, int y)
{
	switch (symbol)
	{
	case 'S':
		createSnake(x, y);
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

void Mob::createSnake(int x, int y)
{
	_name = "Snake";
	_health = 5;
	_attack = 3;
	_defense = 0;
	setLocation(x, y);
	_symbol = 'S';
	_experienceValue = 3;
}//end function