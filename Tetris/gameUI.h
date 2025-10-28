#pragma once
#include "board.h"

class Board;

class GameUI
{
private:
	void drawBorder(); //Draws the border of the given screen
	void drawTitle();  //Draws the game logo
	void drawBoards(); //Draws the players' boards

public:
	void showBootScreen(); //Shows the starting screen
	void showMenuScreen(); //Shows menu  
	void showGameModeScreen(); //Shows the 3 game options
	void showComp1DiffScreen();
	void showComp2DiffScreen();	
	void showPauseScreen(); //Pauses the game
	void showGameScreen(); //Starts the game
	void showInstructions(); // Shows instructions
	void showGameOver(); //Shows ending screen
	void gameOver(Board board);


};

