#pragma once
#include <string>

#include "Level.h"


class GameSystem
{
public:
	GameSystem();

	void playGame();
	void loadLevel(std::string levelFile);
	int pauseMenu();
	
	//Setters
	void setPlayerName() { _level.setName(_playerName); }

private:
	Level _level;
	std::string _playerName;

	void printTitle();
	void printPressEnter();
	int printMenu();
	void printHowToPlay();
	void printIntro();
	void printPauseMenu();
	void levelComplete();
	void gameOver();
};

