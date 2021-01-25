#pragma once
#include <vector>
#include <string>
#include <ctime>
#include <random>
#include <iostream>
#include <conio.h>

#include "Mob.h"
#include "Player.h"
#include "Shop.h"
#include "Chest.h"


class Level
{
public:
	Level();

	//Setter
	void setLevelFile(std::string levelFile) { _levelFile = levelFile; }
	template<class T> void setRandomLocation(T &character);
	void setName(std::string name) { _player.setName(name); }

	//Functions
	void initLevelData();
	void spawnCharacters();
	void print();
	bool checkMobList();
	bool checkPlayer();
		//Movement
		void movePlayer(char input);
		void moveMobs();
		char moveToPlayer(Mob& mob);
		//Processing
		bool checkRadius(char symbol, int radius, int x, int y);

	//Templates
	template<class T> void move(T& character, char input);
	template<class T> char moveRandom(T& character);
	

private:
	//Functions
	bool extractCharacters(std::ifstream& inFile);
	bool addMob(char symbol, int x, int y);
	bool addChest(char symbol, int x, int y);
	bool addShop(char symbol, int x, int y);
	bool removeMob(int listIndex);
	bool checkMove(int x, int y);

	//Templates
	template <class T> bool moveUp(T& character);
	template <class T> bool moveDown(T& character);
	template <class T> bool moveRight(T& character);
	template <class T> bool moveLeft(T& character);
	template <class T> void processMove(T& character, int targetX, int targetY);
	template<class T, class U> void battle(T& attacking, U& defending);

	//Getters
	char getTile(int x, int y) { return _levelData[y][x]; }

	//Setters
	void setTile(int x, int y, char symbol) { _levelData[y][x] = symbol; }

	//Variables
	Player _player;
	std::vector <Mob> _mobList;
	std::vector <Chest> _chestList;
	std::vector <Shop> _shopList;
	std::string _levelFile;
	std::vector <std::string> _levelData;
	int _levelWidth;
	int _levelHeight;
};

/*TEMPLATE FUNCTIONS*/

/*PUBLIC*/

//sets random location 
template<class T> void Level::setRandomLocation(T& character)
{
	static std::default_random_engine randomGenerator((unsigned int)time(NULL));

	//randomizer
	std::uniform_int_distribution<int> yRandomizer(1, (_levelHeight - 1));
	std::uniform_int_distribution<int> xRandomizer(1, (_levelWidth - 1));
	//temp coordinates
	int yCoord;
	int xCoord;

	while (true)
	{
		yCoord = yRandomizer(randomGenerator);
		xCoord = xRandomizer(randomGenerator);

		//Check if spot is open
		if (_levelData[yCoord][xCoord] == '.')
		{
			//Check to make sure player is not too close
			if (checkRadius('@', 6, xCoord, yCoord) == false)
			{
				character.setLocation(xCoord, yCoord);
				break;
			}//if end
		}//if end
	}//while end
}

//move character based on input; return char at location
template<class T> void Level::move(T& character, char input)
{
	int x, y;
	//check key pressed
	switch (input)
	{
	case 'W':
		if (moveUp<T>(character))
			break;
		
		character.getLocation(x, y);
		processMove(character, x, (y - 1));
		break;
	case 'A':
		if (moveLeft<T>(character))
			break;

		character.getLocation(x, y);
		processMove(character, (x - 1), y);
		break;
	case 'S':
		if (moveDown<T>(character))
			break;

		character.getLocation(x, y);
		processMove(character, x, (y + 1));
		break;
	case 'D':
		if (moveRight<T>(character))
			break;

		character.getLocation(x, y);
		processMove(character, (x + 1), y);
		break;
	}//switch end
}

//move character in random direction; return char at location; return '.' if move successful
template<class T> char Level::moveRandom(T& character)
{
	static std::default_random_engine randomGenerator((unsigned int)time(NULL));
	std::uniform_int_distribution<int> movement(1, 4);

	int x, y;
	character.getLocation(x, y);
	char tile;

	unsigned int direction = movement(randomGenerator);
	switch (direction)
	{

	case 1:		//move up
		if (checkMove(x, (y - 1)))
		{
			tile = moveUp(character);
			return tile;
		}//if end

		processMove(character, x, (y - 1));
		return getTile(x, (y - 1));

	case 2:		//move down
		if (checkMove(x, (y + 1)))
		{
			tile = moveDown(character);
			return tile;
		}//if end

		processMove(character, x, (y + 1));
		return getTile(x, (y + 1));

	case 3:		//move right
		if (checkMove((x + 1), y))
		{
			tile = moveRight(character);
			return tile;
		}//if end

		processMove(character, (x + 1), y);
		return getTile((x + 1), y);

	case 4:		//move left
		if (checkMove((x - 1), y))
		{
			tile = moveLeft(character);
			return tile;
		}//if end

		processMove(character, (x - 1), y);
		return getTile((x - 1), y);
	}
}


/*PRIVATE*/

//move character up; return true if moved
template <class T> bool Level::moveUp(T& character)
{
	int x, y;
	char symbol;

	character.getLocation(x, y);
	symbol = character.getSymbol();

	if (checkMove(x, (y - 1)))
	{
		setTile(x, y, '.');
		setTile(x, (y - 1), character.getSymbol());
		character.setLocation(x, (y - 1));
		return true;
	}//end if

	return false;
}

//move character down; return true if moved
template <class T> bool Level::moveDown(T& character)
{
	int x, y;
	char symbol;

	character.getLocation(x, y);
	symbol = character.getSymbol();

	if (checkMove(x, (y + 1)))
	{
		setTile(x, y, '.');
		setTile(x, (y + 1), character.getSymbol());
		character.setLocation(x, (y + 1));
		return true;
	}//end if

	return false;
}

//move character right; return true if moved
template <class T> bool Level::moveRight(T& character)
{
	int x, y;
	char symbol;

	character.getLocation(x, y);
	symbol = character.getSymbol();

	if (checkMove((x + 1), y))
	{
		setTile(x, y, '.');
		setTile((x + 1), y, character.getSymbol());
		character.setLocation((x + 1), y);
		return true;
	}//end if

	return false;
}

//move character left; return true if moved
template <class T> bool Level::moveLeft(T& character)
{
	int x, y;
	char symbol;

	character.getLocation(x, y);
	symbol = character.getSymbol();

	if (checkMove((x - 1), y))
	{
		setTile(x, y, '.');
		setTile((x - 1), y, character.getSymbol());
		character.setLocation((x - 1), y);
		return true;
	}//end if

	return false;
}

//process the characters move and checks for attacks
template <class T> void Level::processMove(T& character, int targetX, int targetY)
{
	char tile = getTile(targetX, targetY);

	switch (tile)
	{
	case '.':
	case '#':
	case '|':
	case '_':
	case 'X':
		break;
	case '@':		//mob attacking character
		battle(character, _player);
		break;
	case 's':
	case 'B':
	case 'F':
		if (character.getSymbol() == '@')
		{
			int x, y;

			//check if enter shop
			for (unsigned int i = 0; i < _shopList.size(); i++)
			{
				_shopList[i].getLocation(x, y);
				if (x == targetX && y == targetY)
				{
					_shopList[i].enterShop(_player);
					return;
				}//if end
			}//for end
		}//if end
	case 'C':
		if (character.getSymbol() == '@')
		{
			int x = 0;
			int y = 0;

			//check if opening chest
			for (unsigned int i = 0; i < _chestList.size(); i++)
			{
				//_chestList[i].getLocation(x, y);
				if (x == targetX && y == targetY)
				{
					//_chestList[i].openChest();
				}//if end
			}//for end
		}//if end
	default:		//character attacking mob
		if (character.getSymbol() == '@')
		{
			int x, y;
			int mobNumber;

			//find correct mob
			unsigned int i = 0;
			for (; i < _mobList.size(); i++)
			{
				_mobList[i].getLocation(x, y);
				if ((x == targetX) && (y == targetY))	//find mob in list
				{
					mobNumber = i;
					break;
				}//if end
			}//for end

			if (i <= _mobList.size())					//check if mob is found
			{
				battle(_player, _mobList[mobNumber]);	//do battle
				if (getTile(x, y) == 'X')				//if mob dies, remove from list
					removeMob(mobNumber);
			}
		}//if end
		break;
	}//switch end
}

//do battle between two entities
template<class T, class U> void Level::battle(T& attacking, U& defending)
{

	int attackRoll;
	int attackResult;

	int attackerX, attackerY;
	int defenderX, defenderY;

	//Attackers turn

	attackRoll = attacking.attack();
	attackResult = defending.takeDamage(attackRoll);
	if (attackResult != 0)	//check if defender died and do experience
	{
		if (attacking.getSymbol() == '@')		//if player, add exp
			attacking.addExperience(attackResult);

		defending.getLocation(defenderX, defenderY);	//print information/adjust _levelData
		setTile(defenderX, defenderY, 'X');
		std::cout << defending.getName() << " has died!\n";
		_getch();
	}
	else {
		std::cout << defending.getName() << " has " << defending.getHealth() << " health left.\n";
	}


	//Defenders turn

	attackRoll = defending.attack();
	attackResult = attacking.takeDamage(attackRoll);
	if (attackResult != 0)	//check if attacker died and do experience
	{
		if (defending.getSymbol() == '@')		//if player, add exp
			defending.addExperience(attackResult);

		attacking.getLocation(attackerX, attackerY);	//print information/adjust _levelData
		setTile(attackerX, attackerY, 'X');
		std::cout << attacking.getName() << " has died!\n";
		_getch();
	}
	else {
		std::cout << attacking.getName() << " has " << attacking.getHealth() << " health left.\n";
		_getch();
	}
}
