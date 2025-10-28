#include "gameUI.h"
#include "gameConfig.h"
#include "general.h"
#include "tetromino.h"
#include <Windows.h>
#include <iostream>

using namespace std;

void GameUI::drawBorder()
{
	for (int col = 0; col <= GameConfig::SCREEN_BORDER_WIDTH; col++) //Top and Bottom border
	{
		gotoxy(col, 0);
		cout << "=";

		gotoxy(col, GameConfig::SCREEN_BORDER_HEIGHT);
		cout << "=";
	}
	for (int row = 0; row <= GameConfig::SCREEN_BORDER_HEIGHT; row++) //Left and Right border
	{
		gotoxy(0, row);
		cout << "||";

		gotoxy(GameConfig::SCREEN_BORDER_WIDTH, row);
		cout << "||";
	}
}

void GameUI::drawBoards()
{
	//Players' name position
	gotoxy(GameConfig::PLAYER1_NAME_X, GameConfig::PLAYER1_NAME_Y);
	cout << "Player 1";

	gotoxy(GameConfig::PLAYER2_NAME_X, GameConfig::PLAYER2_NAME_Y);
	cout << "Player 2";

	//Players' score position
	gotoxy(GameConfig::PLAYER1_SCORE_X, GameConfig::PLAYER1_SCORE_Y);
	cout << "Score:";

	gotoxy(GameConfig::PLAYER2_SCORE_X, GameConfig::PLAYER2_SCORE_Y);
	cout << "Score:";

	gotoxy(GameConfig::PLAYER1_SCORE_X, GameConfig::PLAYER1_SCORE_Y + 1);
	cout << "0";

	gotoxy(GameConfig::PLAYER2_SCORE_X, GameConfig::PLAYER2_SCORE_Y + 1);
	cout << "0";

	// Draw the vertical borders
	for (int row = 0; row < GameConfig::BOARD_HEIGHT; row++)
	{
		gotoxy(GameConfig::PLAYER1_BOARD_X, GameConfig::PLAYER1_BOARD_Y + row);
		cout << "|";

		gotoxy(GameConfig::PLAYER2_BOARD_X, GameConfig::PLAYER2_BOARD_Y + row);
		cout << "|";

		gotoxy(GameConfig::PLAYER1_BOARD_X + GameConfig::BOARD_WIDTH + 1, GameConfig::PLAYER1_BOARD_Y + row);
		cout << "|";

		gotoxy(GameConfig::PLAYER2_BOARD_X + GameConfig::BOARD_WIDTH + 1, GameConfig::PLAYER2_BOARD_Y + row);
		cout << "|";
	}
	// Draw the horizontal borders
	for (int col = 0; col <= GameConfig::BOARD_WIDTH + 1; col++)
	{
		gotoxy(GameConfig::PLAYER1_BOARD_X + col, GameConfig::PLAYER1_BOARD_Y - 1);
		cout << "-";

		gotoxy(GameConfig::PLAYER2_BOARD_X + col, GameConfig::PLAYER2_BOARD_Y - 1);
		cout << "-";

		gotoxy(GameConfig::PLAYER1_BOARD_X + col, GameConfig::PLAYER1_BOARD_Y + GameConfig::BOARD_HEIGHT);
		cout << "-";

		gotoxy(GameConfig::PLAYER2_BOARD_X + col, GameConfig::PLAYER2_BOARD_Y + GameConfig::BOARD_HEIGHT);
		cout << "-";
	}
}

void GameUI::drawTitle()
{
	//ASCII art for TETRIS logo
	gotoxy(GameConfig::TITLE_X, GameConfig::TITLE_Y);
	std::cout << " TTTTTTT   EEEEEE  TTTTTTT  RRRR    IIIII     SSSS";
	gotoxy(GameConfig::TITLE_X, GameConfig::TITLE_Y + 1);
	std::cout << "    T      E          T     R   R     I      S";
	gotoxy(GameConfig::TITLE_X, GameConfig::TITLE_Y + 2);
	std::cout << "    T      EEEE       T     RRRR      I       SSS ";
	gotoxy(GameConfig::TITLE_X, GameConfig::TITLE_Y + 3);
	std::cout << "    T      E          T     R  R      I          S";
	gotoxy(GameConfig::TITLE_X, GameConfig::TITLE_Y + 4);
	std::cout << "    T      EEEEEE     T     R   R   IIIII    SSSS ";
}

void GameUI::showBootScreen()
{
	clrscr();

	//Border
	drawBorder();

	//Title
	drawTitle();

	//Authors
	gotoxy(GameConfig::AUTHOR_X, GameConfig::AUTHOR_Y);
	cout << "By: Liel Chibotero & Amir Sofer";

	//Press any key to start
	gotoxy(GameConfig::PRESS_KEY_X, GameConfig::PRESS_KEY_Y);
	cout << "Press enter to start";

}

void GameUI::showMenuScreen()
{
	clrscr();
	drawBorder();
	drawTitle();

	//Menu
	gotoxy(GameConfig::MENU_X, GameConfig::MENU_Y);
	cout << "MENU";

	//Start
	gotoxy(GameConfig::START_X, GameConfig::START_Y);
	cout << "(1) Start a new game";

	//Instructions & Keys
	gotoxy(GameConfig::INSTRUCTIONS_X, GameConfig::INSTRUCTIONS_Y);
	cout << "(8) Instructions & Keys";

	//Exit
	gotoxy(GameConfig::EXIT_X, GameConfig::EXIT_Y);
	cout << "(9) EXIT";
}

void GameUI::showPauseScreen()
{
	clrscr();
	drawBorder();
	drawTitle();

	//Menu
	gotoxy(GameConfig::MENU_X, GameConfig::MENU_Y);
	cout << "MENU";

	//Start
	gotoxy(GameConfig::START_X, GameConfig::START_Y);
	cout << "(1) Start a new game";

	//Continue
	gotoxy(GameConfig::CONTINUE_X, GameConfig::CONTINUE_Y);
	cout << "(2) Continue";

	//Instructions & Keys
	gotoxy(GameConfig::PAUSE_INSTRUCTIONS_X, GameConfig::PAUSE_INSTRUCTIONS_Y);
	cout << "(8) Instructions & Keys";

	//Exit
	gotoxy(GameConfig::PAUSE_EXIT_X, GameConfig::PAUSE_EXIT_Y);
	cout << "(9) EXIT";

}

void GameUI::showGameModeScreen()
{
	clrscr();
	drawBorder();
	drawTitle();

	//Game Mode
	gotoxy(GameConfig::GAME_MODE_X, GameConfig::GAME_MODE_Y);
	cout << "GAME MODE";

	//Human vs Human
	gotoxy(GameConfig::HVH_X, GameConfig::HVH_Y);
	cout << "(1) Human vs Human";

	//Human vs Computer
	gotoxy(GameConfig::HVC_X, GameConfig::HVC_Y);
	cout << "(2) Human vs Computer";

	//Computer vs Computer
	gotoxy(GameConfig::CVC_X, GameConfig::CVC_Y);
	cout << "(3) Computer vs Computer";

	//Back
	gotoxy(GameConfig::BACK_X, GameConfig::BACK_Y);
	cout << "(9) Back to Menu";
}

void GameUI::showComp1DiffScreen()
{
	clrscr();
	drawBorder();
	drawTitle();

	//Comp1 Diff
	gotoxy(GameConfig::COMP_DIFF_X, GameConfig::COMP_DIFF_Y);
	cout << "COMPUTER1 DIFFICULTY";

	//Easy diff
	gotoxy(GameConfig::EASY_X, GameConfig::EASY_Y);
	cout << "(1) Easy ";

	//Medium diff
	gotoxy(GameConfig::MEDIUM_X, GameConfig::MEDIUM_Y);
	cout << "(2) Medium";

	//Hard diff
	gotoxy(GameConfig::HARD_X, GameConfig::HARD_Y);
	cout << "(3) Hard";

	//Back
	gotoxy(GameConfig::BACK_X, GameConfig::BACK_Y);
	cout << "(9) Back to Menu";
}

void GameUI::showComp2DiffScreen()
{
	clrscr();
	drawBorder();
	drawTitle();

	//Comp 2 Diff
	gotoxy(GameConfig::COMP_DIFF_X, GameConfig::COMP_DIFF_Y);
	cout << "COMPUTER1 DIFFICULTY";

	//Easy diff
	gotoxy(GameConfig::EASY_X, GameConfig::EASY_Y);
	cout << "(1) Easy ";

	//Medium diff
	gotoxy(GameConfig::MEDIUM_X, GameConfig::MEDIUM_Y);
	cout << "(2) Medium";

	//Hard diff
	gotoxy(GameConfig::HARD_X, GameConfig::HARD_Y);
	cout << "(3) Hard";

	//Back
	gotoxy(GameConfig::BACK_X, GameConfig::BACK_Y);
	cout << "(9) Back to Menu";
}

void GameUI::showGameScreen()
{
	clrscr();
	drawBorder();
	drawBoards();
}

void GameUI::showInstructions()
{
	clrscr();
	drawBorder();

	//ASCII art for the game instructions

	gotoxy(31, 2);
	cout << " Game Instructions";
	gotoxy(31, 3);
	cout << " =================";

	gotoxy(6, 4);
	cout << "Player1 Keys";
	gotoxy(6, 5);
	cout << "^^^^^^^^^^^^";
	gotoxy(6, 6);
	cout << "A or a - Left";
	gotoxy(6, 7);
	cout << "D or d - Right";
	gotoxy(6, 8);
	cout << "X or x - Drop";
	gotoxy(6, 9);
	cout << "S or s - Rotate Clockwise";
	gotoxy(6, 10);
	cout << "W or a - Rotate Counter Clockwise";

	gotoxy(6, 12);
	cout << "Player2 Keys";
	gotoxy(6, 13);
	cout << "^^^^^^^^^^^^";
	gotoxy(6, 14);
	cout << "J or j - Left";
	gotoxy(6, 15);
	cout << "L or l - Right";
	gotoxy(6, 16);
	cout << "K or k - Drop";
	gotoxy(6, 17);
	cout << "I or i - Rotate Clockwise";
	gotoxy(6, 18);
	cout << "M or m - Rotate Counter Clockwise";

	gotoxy(50, 5);
	cout << "     +---+";
	gotoxy(50, 6);
	cout << "     | W |";
	gotoxy(50, 7);
	cout << " +---+---+---+";
	gotoxy(50, 8);
	cout << " | A | S | D |";
	gotoxy(50, 9);
	cout << " +---+---+---+";
	gotoxy(50, 10);
	cout << "     | X |";
	gotoxy(50, 11);
	cout << "     +---+";


	gotoxy(50, 13);
	cout << "     +---+";
	gotoxy(50, 14);
	cout << "     | I |";
	gotoxy(50, 15);
	cout << " +---+---+---+";
	gotoxy(50, 16);
	cout << " | J | K | L |";
	gotoxy(50, 17);
	cout << " +---+---+---+";
	gotoxy(50, 18);
	cout << "   | M |";
	gotoxy(50, 19);
	cout << "   +---+";


	//Input loop until the user chooses to go back to the menu
	bool instFlag = true;
	gotoxy(24, 23);
	cout << "Press ESC to return to main menu";

	while (instFlag)
	{
		if (_kbhit())
		{
			int keyPressed = _getch();
			if (keyPressed == (int)GameConfig::p1Keys::ESC)
				instFlag = false;
		}
	}

}

void GameUI::showGameOver()
{
	clrscr();
	drawBorder();

	//Drawing Game Over
	gotoxy(15, 4);
	cout << "  ____                         ___                 \n";
	gotoxy(15, 5);
	cout << " / ___| __ _ _ __ ___   ___   / _ \\__   _____ _ __ \n";
	gotoxy(15, 6);
	cout << "| |  _ / _` | '_ ` _ \\ / _ \\ | | | \\ \\ / / _ \\ '__|\n";
	gotoxy(15, 7);
	cout << "| |_| | (_| | | | | | |  __/ | |_| |\\ V /  __/ |   \n";
	gotoxy(15, 8);
	cout << " \\____|\\__,_|_| |_| |_|\\___|  \\___/  \\_/ \\___|_|   \n";
}

void GameUI::gameOver(Board board)
{
	showGameOver();
	if (board.getSide() == Side::LEFT)
	{
		gotoxy(4, 12);
		cout << "    ____  __                         ___     _       _______   _______ __\n";
		gotoxy(4, 13);
		cout << "   / __ \\/ ____ ___  _____  _____   |__ \\   | |     / /  _/ | / / ___// /\n";
		gotoxy(4, 14);
		cout << "  / /_/ / / __ `/ / / / _ \\/ ___/   __/ /   | | /| / // //  |/ /\\__ \\/ / \n";
		gotoxy(4, 15);
		cout << " / ____/ / /_/ / /_/ /  __/ /      / __/    | |/ |/ _/ // /|  /___/ /_/  \n";
		gotoxy(4, 16);
		cout << "/_/   /_/\\__,_/\\__, /\\___/_/      /____/    |__/|__/___/_/ |_//____(_)\n";
		gotoxy(4, 17);
		cout << "              /____/                                                    \n";

		gotoxy(35, 21);
		cout << "Score: " << board.getScore();

		gotoxy(0, 30);
	}

	else
	{
		gotoxy(4, 12);
		cout << "    ____  __                         ___       _       _______   _______ __\n";
		gotoxy(4, 13);
		cout << "   / __ \\/ ____ ___  _____  _____   <  /      | |     / /  _/ | / / ___// /\n";
		gotoxy(4, 14);
		cout << "  / /_/ / / __ `/ / / / _ \\/ ___/   / /       | | /| / // //  |/ /\\__ \\/ / \n";
		gotoxy(4, 15);
		cout << " / ____/ / /_/ / /_/ /  __/ /      / /        | |/ |/ _/ // /|  /___/ /_/  \n";
		gotoxy(4, 16);
		cout << "/_/   /_/\\__,_/\\__, /\\___/_/      /_/         |__/|__/___/_/ |_//____(_)\n";
		gotoxy(4, 17);
		cout << "              /____/                                                       \n";

		gotoxy(35, 21);
		cout << "Score: " << board.getScore();

		gotoxy(0, 30);
	}
	gotoxy(22, 23);
	cout << "Press any Key to return to main menu";

	while (true)
	{
		if (_kbhit())
			break;
	}

}