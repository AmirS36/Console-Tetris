#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

#include "gameLoop.h"
#include "gameConfig.h"
#include "general.h"

int main()
{
	srand(time(NULL));
	GameLoop game;
	game.run();
}