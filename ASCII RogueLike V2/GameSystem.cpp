#include <string>

#include "GameSystem.h"
#include "Level.h"

using namespace std;

GameSystem::GameSystem()
{
	
}

/*PUBLIC*/

void GameSystem::playGame()
{
	while (true)
	{
		//Title and Menu
		printTitle();
		printPressEnter();
		int option;

		//Menu Options
		bool menuIsDone = false;
		while (menuIsDone == false)
		{
			option = printMenu();
			switch (option)
			{
			case 1:
				menuIsDone = true;
				system("CLS");
				printTitle();
				printIntro();
				system("CLS");
				break;
			case 2:
				printHowToPlay();
				break;
			default:
				option = 0;
				break;
			}//switch end;
		}//while end

		setPlayerName();

		//Game loop
		bool isDone = false;
		while (isDone == false)
		{
			_level.print();
			char input;
			input = _getch();

			//Pause button
			if (input == 27)
			{
				int i = pauseMenu();
				if (i == 1)		//if return is 1 go to title
					break;
				system("CLS");
				continue;
			}

			_level.movePlayer(input);
			_level.moveMobs();

			if (_level.checkMobList())		//check if all mobs defeated
				levelComplete();

			if (_level.checkPlayer())		//check if player is dead
				gameOver();


			system("CLS");
		}//while end
	}//while end
}

void GameSystem::loadLevel(std::string levelFile)
{
	_level.setLevelFile(levelFile);
	_level.initLevelData();
	_level.spawnCharacters();
}

int GameSystem::pauseMenu()
{
	while (true)
	{
		printPauseMenu();
		int input;
		cin >> input;
		cin.clear();
		cin.ignore(10000, '\n');

		switch (input)
		{
		case 1:			//resume
			return 0;
		case 2:			//how to play menu
			system("CLS");
			printHowToPlay();
			system("CLS");
			break;
		case 3:			//exit game
			return 1;
		default:
			break;
		}//switch end
	}//while end

}

/*PRIVATE*/

//title
void GameSystem::printTitle()
{
	system("CLS");

	/*TITLE*/
	printf("%*s", 24, "");	cout << string(140, '*') << "\n";
	printf("%*s**    ############    ################    ##                ##     #############       ##############	##           ##	   ####         ##**\n", 24, "");
	printf("%*s**  ##                ##            ##    ##                ##     ##                  ##          ##	##           ##	   ## ##        ##**\n", 24, "");
	printf("%*s**##                  ##            ##    ##                ##     ##                  ##          ##	##           ##	   ##  ##       ##**\n", 24, "");
	printf("%*s**##                  ##            ##     ##              ##      ##                  ##          ##	##           ##	   ##   ##      ##**\n", 24, "");
	printf("%*s**##                  ##            ##      ##            ##       ##                  ##          ##	##           ##	   ##    ##     ##**\n", 24, "");
	printf("%*s**##                  ################       ##          ##        ########            ##############	##           ##	   ##     ##    ##**\n", 24, "");
	printf("%*s**##                  ##            ##        ##        ##         ##                  ##   ##       	##           ##	   ##      ##   ##**\n", 24, "");
	printf("%*s**##                  ##            ##         ##      ##          ##                  ##     ##     	##           ##	   ##       ##  ##**\n", 24, "");
	printf("%*s**  ##                ##            ##          ##    ##           ##                  ##       ##    	##           ##	   ##        ## ##**\n", 24, "");
	printf("%*s**    ############    ##            ##           ######            #############       ##         ##  	###############	   ##         ####**\n", 24, "");
	printf("%*s", 24, "");	cout << string(140, '*') << "\n";

	printf("\n\n");	
}

//start menu
void GameSystem::printPressEnter()
{
	/*PRESS ENTER TO START*/
	printf("%*s", 59, ""); cout << string(70, '_') << "\n";
	for (int i = 0; i <= 3; i++)
	{
		if (i == 2)
		{
			printf("%*s", 59, ""); printf("|%*s%s%*s|\n", 28, "", "Press  Enter", 28, "");
		}
		else
		{
			printf("%*s", 59, ""); printf("|%*s|\n", 68, "");
		}//if-else end
	}//for end
	printf("%*s|", 59, ""); cout << string(68, '_') << "|\n";
	printf("%*s", 93, "");

	//Input
	while (true)
	{
		if (cin.get() == '\n')
			break;
	}
}

//return's menu option
int GameSystem::printMenu()
{
	system("CLS");
	printTitle();

	/*MENU*/
	printf("%*s", 59, ""); cout << string(70, '_') << "\n";
	for (int i = 1; i <= 10; i++)
	{
		switch (i) {
		case 5:
			printf("%*s", 59, ""); printf("|%*s%s%*s|\n", 30, "", "(1) Play", 30, "");
			break;
		case 7:
			printf("%*s", 59, ""); printf("|%*s%s%*s|\n", 26, "", "(2) How to Play", 27, "");
			break;
		default:
			printf("%*s", 59, ""); printf("|%*s|\n", 68, "");
			break;
		}//switch end
	}//for end
	printf("%*s|", 59, ""); cout << string(68, '_') << "|\n";

	/*PLAYER INPUT*/
	printf("%*s", 59, ""); printf("%*s%s", 27, "", "Enter Number: ");
	int input;
	cin >> input;
	cin.clear();
	cin.ignore(10000, '\n');
	return input;
}

//about game controls
void GameSystem::printHowToPlay()
{

}

//introductory story before game starts
void GameSystem::printIntro()
{
	printf("%*s", 59, ""); cout << string(70, '_') << "\n";
	for (int i = 0; i < 2; i++)
	{
		printf("%*s", 59, ""); printf("|%*s|\n", 68, "");
	}
	printf("%*s", 59, ""); printf("|%*s%s%*s|\n", 12, "", "Greetings Adventurer! You are about to enter", 12, "");
	printf("%*s", 59, ""); printf("|%*s%s%*s|\n", 12, "", "a labyrinth of treachours dungeons. There ", 14, "");
	printf("%*s", 59, ""); printf("|%*s%s%*s|\n", 12, "", "will be many dangers and many treasures.", 16, "");
	printf("%*s", 59, ""); printf("|%*s%s%*s|\n", 12, "", "But remember, none of that matters if you're", 12, "");
	printf("%*s", 59, ""); printf("|%*s%s%*s|\n", 12, "", "dead! Now, I'm sure you are growing impatient", 11, "");
	printf("%*s", 59, ""); printf("|%*s%s%*s|\n", 12, "", "and your hands are growing excited for", 18, "");
	printf("%*s", 59, ""); printf("|%*s%s%*s|\n", 12, "", "battle, but before you go, please tell me", 15, "");
	printf("%*s", 59, ""); printf("|%*s%s%*s|\n", 12, "", "your name so that I may write it down for the", 11, "");
	printf("%*s", 59, ""); printf("|%*s%s%*s|\n", 12, "", "books.", 50, "");

	printf("%*s", 59, ""); printf("|%*s|\n", 68, "");
	printf("%*s|", 59, ""); cout << string(68, '_') << "|\n";

	/*PLAYER INPUT*/
	printf("%*s", 59, ""); printf("%*s%s", 27, "", "Enter Name: ");
	std::string input;
	std::getline(std::cin, input);
	/*cin.ignore(10000, '\n');
	cin.clear();*/
	_playerName = input;

	printf("\n%*s", 59, ""); printf("%*s%s", 28, "", "Good Luck "); cout << _playerName << "!";
	_getch();
}

void GameSystem::printPauseMenu()
{
	system("CLS");
	std::cout << string(10, '\n');
	printf("\t\t\t%*s", 30, " "); printf("--------------------\n");
	printf("\t\t\t%*s", 30, " "); printf("|                  |\n");
	printf("\t\t\t%*s", 30, " "); printf("|   1. Resume      |\n");
	printf("\t\t\t%*s", 30, " "); printf("|                  |\n");
	printf("\t\t\t%*s", 30, " "); printf("|   2. Controls    |\n");
	printf("\t\t\t%*s", 30, " "); printf("|                  |\n");
	printf("\t\t\t%*s", 30, " "); printf("|   3. Exit Game   |\n");
	printf("\t\t\t%*s", 30, " "); printf("|                  |\n");
	printf("\t\t\t%*s", 30, " "); printf("--------------------\n");
	printf("\t\t\t%*s", 30, " "); printf(" Enter Number: ");
}

//
void GameSystem::levelComplete()
{

}

//game over message
void GameSystem::gameOver()
{

}