#include "GameSystem.h"

int main()
{

	GameSystem gameSystem;
	gameSystem.loadLevel("level1.txt");
	gameSystem.playGame();

	return 0;
}