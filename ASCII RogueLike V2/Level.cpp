#include <fstream>
#include <iostream>
#include <cstdio>
#include <random>
#include <ctime>
#include <string>

#include "Level.h"
#include "Item.h"

Level::Level()
{
	
}

/*PUBLIC*/

//read file and store in vector
void Level::initLevelData()
{
	std::ifstream inFile;

	inFile.open(_levelFile);
	if (inFile.fail())
	{
		perror(_levelFile.c_str());
		system("PAUSE");
		exit(1);
	}//if end

	std::string line;
	char letter;
	int xAxis = 0;
	int yAxis = 0;

	//check if file has character
	while (inFile >> std::noskipws >> letter)
	{
		switch (letter)
		{
		case '\t':		//Adding layout
			break;
		case '\n':
			_levelData.push_back(line);
			line.clear();
			yAxis++;
			_levelWidth = xAxis;
			xAxis = 0;
			break;
		case'.':
		case '_':
		case '|':
		case '#':
			line += letter;
			xAxis++;
			break;
		case '%':		//Adding characters by random
			extractCharacters(inFile);
			break;
		case '!':		//Adding characters
		case '?':
			if (letter == '!')
				line += '.';
			if (letter == '?')
				line += '#';
			xAxis++;

			inFile >> std::noskipws >> letter;

			if (letter == '@')		// if player
			{
				_player.setLocation(xAxis, yAxis);
				line += '@';
				xAxis++;
				break;
			}
			else if (addMob(letter, xAxis, yAxis))   //if mob 
			{
				line += letter;
				xAxis++;
				break;
			}

			line += '.';	// if neither, add dot
			xAxis++;
			break;
		case '$':		//Adding items
		case '~':
			if (letter == '$')
				line += '.';
			if (letter == '~')
				line += '#';
			xAxis++;

			inFile >> std::noskipws >> letter;

			if (addShop(letter, xAxis, yAxis))			//check if shop
			{
				line += letter;
				xAxis++;
				break;
			}
			else if (addChest(letter, xAxis, yAxis))	//check if chest
			{
				line += letter;
				xAxis++;
				break;
			}//end if else

			line += '.';	//if neither add dot
			xAxis++;
			break;
		case '(':		//Adding text
		case '[':
			if (letter == '(')
				line += '.';
			if (letter == '[')
				line += '#';
			xAxis++;

			while (true)
			{
				inFile >> std::noskipws >> letter;

				if (letter == ')')	//check if end of writing
				{
					line += '.';
					xAxis++;
					break;
				}//if end
				if (letter == ']')
				{
					line += '#';
					xAxis++;
					break;
				}//if end

				line += letter;		//add writing
				xAxis++;
			}//while end
			break;
		default:
			line += '.';
			xAxis++;
			break;
		}//switch end
	}//while loop end

	if (line.empty() == false)
	{
		_levelData.push_back(line);
		line.clear();
		yAxis++;
	}

	_levelHeight = yAxis;

	inFile.close();
	return;
}//function end

//spawn in characters into vector
void Level::spawnCharacters()
{
	int x, y;

	//if player position not set, then set randomly
	if (_player.getX() == -1 || _player.getY() == -1)
	{
		setRandomLocation<Player> (_player);
		_player.getLocation(x, y);
		_levelData[y][x] = _player.getSymbol();
	}//if end

	for (unsigned int i = 0; i < _mobList.size(); i++)
	{
		if (_mobList[i].getX() == -1 || _mobList[i].getY() == -1)
		{
			setRandomLocation<Mob> (_mobList[i]);
			_mobList[i].getLocation(x, y);
			_levelData[y][x] = _mobList[i].getSymbol();
		}//if end
	}//for end
}

//print the level
void Level::print()
{
	for (unsigned int i = 0; i < _levelData.size(); i++)
	{
		printf("\t\t\t%s\n", _levelData[i].c_str());
	}//for loop end
	printf("\n");
}

//checks if _mobList is empty; return true if it's empty
bool Level::checkMobList()
{
	if (_mobList.size() == 0)
		return true;

	return false;
}

//checks if _player is dead; return true if player is dead
bool Level::checkPlayer()
{
	if (_player.getHealth() <= 0)
		return true;
	return false;
}

//Opens player inventory to the screen
void Level::inventory() {
	printInventory();
}

//Prints player inventory
void Level::printInventory() {
	
	//%[flags][width][.precision][length]specifier
	system("CLS");
	std::cout << std::string(10, '\n');
	printf("\t\t%*s", 30, " "); printf("%s Lv. %i\n", _player.getName().c_str(), _player.getLevel());
	printf("\t\t%*s", 30, " "); printf("|%s|\n", std::string(52, '-').c_str());
	printf("\t\t%*s", 30, " "); printf("| GP: %-6i    health: %3i/%-6i   EXP: %3i/%-6i |\n", _player.getMoney(), _player.getHealth(), _player.getMaxHealth(), _player.getExperience(), _player.getExpCap());
	printf("\t\t%*s", 30, " "); printf("|%s|\n", std::string(52, ' ').c_str());
	printf("\t\t%*s", 30, " "); printf("|%s|\n", std::string(52, ' ').c_str());
	printf("\t\t%*s", 30, " "); printf("| Weapon:  %-10s  Shield:  %-21s|\n", _player.getItem(0)->getName().c_str(), _player.getItem(0)->getName().c_str());
	printf("\t\t%*s", 30, " "); printf("|%s|\n", std::string(52, ' ').c_str());
	printf("\t\t%*s", 30, " "); printf("|     Helmet:  %-38s|\n", _player.getItem(0)->getName().c_str());
	printf("\t\t%*s", 30, " "); printf("| Chestpiece:  %-38s|\n", _player.getItem(0)->getName().c_str());
	printf("\t\t%*s", 30, " "); printf("|   Gauntlet:  %-38s|\n", _player.getItem(0)->getName().c_str());
	printf("\t\t%*s", 30, " "); printf("|      Boots:  %-38s|\n", _player.getItem(0)->getName().c_str());
	printf("\t\t%*s", 30, " "); printf("|%s|\n", std::string(52, ' ').c_str());
	printf("\t\t%*s", 30, " "); printf("|  Attack:   %-4i         Defense:   %-16i|\n", _player.getAttack(), _player.getDefense());
	printf("\t\t%*s", 30, " "); printf("|%s|\n", std::string(52, ' ').c_str());
	printf("\t\t%*s", 30, " "); printf("|%s|\n", std::string(52, '-').c_str());
	printf("\t\t%*s", 30, " "); printf("|%s|\n", std::string(52, ' ').c_str());
	_player.printInventoryList(0);
	printf("\t\t%*s", 30, " "); printf("|%s|\n", std::string(52, ' ').c_str());
	printf("\t\t%*s", 30, " "); printf("|%s|\n", std::string(52, '-').c_str());
	_getch();
}

//moves player
void Level::movePlayer(char input)
{
	input = toupper(input);
	move(_player, input);
}

//moves mobs
void Level::moveMobs()
{
	int x, y;

	for (unsigned int i = 0; i < _mobList.size(); i++)
	{
		_mobList[i].getLocation(x, y);

		//check for player nearby and move towards them
		if (checkRadius('@', 7, x, y))
			moveToPlayer(_mobList[i]);
		else
			moveRandom(_mobList[i]);
	}//for end
}

//move character closer to the player; return char at location
char Level::moveToPlayer(Mob& mob)
{
	int xPlayer, yPlayer;
	_player.getLocation(xPlayer, yPlayer);

	int xMob, yMob;
	mob.getLocation(xMob, yMob);

	int x = (xPlayer - xMob);
	int y = (yPlayer - yMob);
	double slope = ((double)y / x);

	if (x > 0)		//the player is to the right
	{
		if (y > 0)		//the player is below 
		{
			if (slope < 1)	//x is larger, so closer horizontally
			{
				if (moveRight(mob));
				else if (moveDown(mob));
				else if (moveLeft(mob));

				return true;
			}
			else			//y is larger, so closer vertically
			{
				if (moveDown(mob));
				else if (moveRight(mob));
				else if (moveLeft(mob));

				return true;
			}
		}
		else if (y < 0)	//the player is above
		{
			if (slope < 1)	//x is larger, so closer horizontally
			{
				if (moveRight(mob));
				else if (moveUp(mob));
				else if (moveLeft(mob));

				return true;
			}
			else			//y is larger, so closer vertically
			{
				if (moveUp(mob));
				else if (moveRight(mob));
				else if (moveLeft(mob));

				return true;
			}
		}
		else			//the player is directly left or right
		{
			if (slope == -0)	 //the player is directly to the right
			{
				if (moveRight(mob));
				return true;
			}
			else if (slope == 0) //the player is directly to the left
			{
				if (moveLeft(mob));
				return true;
			}
		}

	}
	else if (x < 0)	//the player is to the left
	{
		if (y > 0)		//the player is below 
		{
			if (slope < 1)	//x is larger, so closer horizontally
			{
				if (moveLeft(mob));
				else if (moveDown(mob));
				else if (moveRight(mob));

				return true;
			}
			else			//y is larger, so closer vertically
			{
				if (moveDown(mob));
				else if (moveLeft(mob));
				else if (moveRight(mob));

				return true;
			}
		}
		else if (y < 0)	//the player is above
		{
			if (slope < 1)	//x is larger, so closer horizontally
			{
				if (moveLeft(mob));
				else if (moveUp(mob));
				else if (moveRight(mob));

				return true;
			}
			else			//y is larger, so closer vertically
			{
				if (moveUp(mob));
				else if (moveLeft(mob));
				else if (moveRight(mob));

				return true;
			}
		}
		else			//the player is directly left or right
		{
			if (slope == -0)	 //the player is directly to the left
			{
				moveLeft(mob);
				return true;
			}
			else if (slope == 0) //the player is directly to the right
			{
				moveRight(mob);
				return true;
			}
		}
	}
	else		//the player is directly above or below
	{
		if (slope == -INFINITY)			//the player is directly above
		{
			moveUp(mob);
			return true;
		}
		else if (slope == INFINITY)		//the player is directly below
		{
			moveDown(mob);
			return true;
		}
	}
	return false;
}

//returns true if specified symbol is in the specified radius
bool Level::checkRadius(char symbol, int radius, int x, int y)
{
	//iterate through square area with set radius
	for (int yValue = (y - radius); yValue <= (y + radius); yValue++)
	{
		//check if out-of-bounds
		if (yValue <= 0 || yValue >= _levelHeight)
			continue;

		for (int xValue = (x - radius); xValue <= (x + radius); xValue++)
		{
			//check if out-of-bounds
			if (xValue <= 0 || xValue >= _levelWidth)
				continue;

			//check for symbol
			if (_levelData[yValue][xValue] == symbol)
				return true;
		}//for end
	}//for end
	return false;
}

/*PRIVATE*/

//return true if atleast one character was read
bool Level::extractCharacters(std::ifstream & inFile)
{
	char c = ' ';
	bool status = false;

	while (c != '%')
	{
		c = inFile.get();

		switch (c)
		{
		case ',':
		case '%':
		case ' ':
		case '@':
			break;
		default:
			c = toupper(c);
			if ((c >= 65) && (c <= 90))
			{
				addMob(c, -1, -1); //add mob with no location yet
				status = true;
			}
			break;
		}//switch end
	}//while loop end

	return status;
}

//returns true if mob is created and added to _mobList
bool Level::addMob(char symbol, int x, int y)
{
	switch (symbol)
	{
	case 'S':
		_mobList.push_back(Mob(symbol, x, y));
		return true;
		break;
	default:
		return false;
		break;
	}//switch end
}

//returns true if item is added to _chestList
bool Level::addChest(char symbol, int x, int y)
{
	switch (symbol)
	{
	case 'C':
		_chestList.push_back(Chest(x, y));
		return true;
		break;
	default:
		return false;
		break;
	}//switch end
}

//returns true if shop is added to _shopList
bool Level::addShop(char& symbol, int x, int y)
{
	if (symbol == '&')	//Random shop
	{
		static std::default_random_engine randomEngine((unsigned int)time(NULL));
		std::uniform_int_distribution<int> randomShop(1, 2);

		unsigned int shopNumber = randomShop(randomEngine);

		switch (shopNumber)
		{
		case 1:
			symbol = 'B';
			break;
		case 2:
			symbol = 'F';
			break;
		}
	}

	switch (symbol)
	{
	case 'B':	//Blacksmith
		_shopList.push_back(Shop("Smith's BlackSmith", 'B', x, y, 500));
		return true;
		break;
	case 'F':	//Food Shop
		_shopList.push_back(Shop("Frank's Fruit Shop", 'F', x, y, 250));
		break;
	default:
		return false;
		break;
	}//switch end
}

//returns true if mob is removed from _mobList
bool Level::removeMob(int mobIndex)
{
	if ((mobIndex >= _mobList.size()) || (mobIndex < 0))		//index is too big or too small
		return false;

	_mobList[mobIndex] = _mobList.back();
	_mobList.pop_back();
	return true;
}

//process the player moves and checks for attacks
void Level::processMove(Player& player, int targetX, int targetY)
{
	char tile = getTile(targetX, targetY);
	int x, y = 0;

	switch (tile)
	{
	case '.':
	case '#':
	case '|':
	case '_':
	case 'X':
		break;
	case '&':
	case 'B':
	case 'F':
	
		//check if enter shop
		for (unsigned int i = 0; i < _shopList.size(); i++)
		{
			_shopList[i].getLocation(x, y);
			if (x == targetX && y == targetY)
			{
				_shopList[i].enterShop(_player);
				return;
			}
		}
		break;
	
	case 'C':

		//check if opening chest
		for (unsigned int i = 0; i < _chestList.size(); i++)
		{
			_chestList[i].getLocation(x, y);

			if (x == targetX && y == targetY && _chestList[i].getStatus())
				_chestList[i].openChest(player);
		}
		break;
		
	default:		//player attacking mob

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
			}
		}

		if (i <= _mobList.size())					//check if mob is found
		{
			battle(_player, _mobList[mobNumber]);	//do battle
			if (getTile(x, y) == 'X')				//if mob dies, remove from list
				removeMob(mobNumber);
		}
		break;
	}
}

//process the mob moves and checks for attacks
void Level::processMove(Mob& mob, int targetX, int targetY)
{
	char tile = getTile(targetX, targetY);

	switch (tile)
	{
	case '@':		//mob attacking character
		battle(mob, _player);
		break;

	default:		
		break;
	}//switch end
}



//returns true if player can move there
bool Level::checkMove(int x, int y)
{
	if ((getTile(x, y) == '.') || getTile(x, y) == 'X')
		return true;
	return false;
}