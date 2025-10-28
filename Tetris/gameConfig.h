#pragma once

class GameConfig
{
public:
	static constexpr int SCREEN_BORDER_WIDTH = 80;
	static constexpr int SCREEN_BORDER_HEIGHT = 25;

	//==============================Boot Screen======================================
	//Title
	static constexpr int TITLE_X = (SCREEN_BORDER_WIDTH - 50) / 2; // Centered horizontally for a 10-character title
	static constexpr int TITLE_Y = 5;

	//by: Liel Chobotaro & Amir Sofer
	static constexpr int AUTHOR_X = (SCREEN_BORDER_WIDTH - 30) / 2; // Centered horizontally for a 30-character title
	static constexpr int AUTHOR_Y = TITLE_Y + 7;

	//Press any key to start
	static constexpr int PRESS_KEY_X = (SCREEN_BORDER_WIDTH - 20) / 2; // Centered horizontally for a 24-character title
	static constexpr int PRESS_KEY_Y = SCREEN_BORDER_HEIGHT - 3;
	//==============================Boot Screen======================================


	//==============================Main Menu======================================
	//Menu
	static constexpr int MENU_X = (SCREEN_BORDER_WIDTH - 4) / 2;
	static constexpr int MENU_Y = SCREEN_BORDER_HEIGHT - 7;

	//Start a new game
	static constexpr int START_X = (SCREEN_BORDER_WIDTH - 20) / 2;
	static constexpr int START_Y = SCREEN_BORDER_HEIGHT - 6;

	//Instructions & Keys - Starting Screen
	static constexpr int INSTRUCTIONS_X = (SCREEN_BORDER_WIDTH - 22) / 2;
	static constexpr int INSTRUCTIONS_Y = SCREEN_BORDER_HEIGHT - 5;

	//EXIT - Starting Screen
	static constexpr int EXIT_X = (SCREEN_BORDER_WIDTH - 8) / 2;
	static constexpr int EXIT_Y = SCREEN_BORDER_HEIGHT - 4;
	//==============================Main Menu======================================


	//==============================Game Mode Selection======================================
	//Choose your game mode
	static constexpr int GAME_MODE_X = (SCREEN_BORDER_WIDTH - 9) / 2;
	static constexpr int GAME_MODE_Y = SCREEN_BORDER_HEIGHT - 7;

	//Human vs Human
	static constexpr int HVH_X = (SCREEN_BORDER_WIDTH - 17) / 2;
	static constexpr int HVH_Y = SCREEN_BORDER_HEIGHT - 6;

	//Human vs Computer
	static constexpr int HVC_X = (SCREEN_BORDER_WIDTH - 21) / 2;
	static constexpr int HVC_Y = SCREEN_BORDER_HEIGHT - 5;

	//Copmuter vs Computer
	static constexpr int CVC_X = (SCREEN_BORDER_WIDTH - 24) / 2;
	static constexpr int CVC_Y = SCREEN_BORDER_HEIGHT - 4;

	//Back
	static constexpr int BACK_X = (SCREEN_BORDER_WIDTH - 16) / 2;
	static constexpr int BACK_Y = SCREEN_BORDER_HEIGHT - 3;
	//==============================Game Mode Selection=======================================

	//==============================Computer Difficulty Selection=============================
	//Choose Computer Difficulty
	static constexpr int COMP_DIFF_X = (SCREEN_BORDER_WIDTH - 19) / 2;
	static constexpr int COMP_DIFF_Y = SCREEN_BORDER_HEIGHT - 7;

	//Easy
	static constexpr int EASY_X = (SCREEN_BORDER_WIDTH - 8) / 2;
	static constexpr int EASY_Y = SCREEN_BORDER_HEIGHT - 6;

	//Medium
	static constexpr int MEDIUM_X = (SCREEN_BORDER_WIDTH - 10) / 2;
	static constexpr int MEDIUM_Y = SCREEN_BORDER_HEIGHT - 5;

	//Hard
	static constexpr int HARD_X = (SCREEN_BORDER_WIDTH - 8) / 2;
	static constexpr int HARD_Y = SCREEN_BORDER_HEIGHT - 4;

	//==============================Computer Difficulty Selection=============================

	//==============================Pause Screen======================================
	//Continue
	static constexpr int CONTINUE_X = (SCREEN_BORDER_WIDTH - 12) / 2;
	static constexpr int CONTINUE_Y = SCREEN_BORDER_HEIGHT - 5;

	//Instructions & Keys - Pasue Screen
	static constexpr int PAUSE_INSTRUCTIONS_X = (SCREEN_BORDER_WIDTH - 22) / 2;
	static constexpr int PAUSE_INSTRUCTIONS_Y = SCREEN_BORDER_HEIGHT - 4;

	//EXIT - Pause Screen
	static constexpr int PAUSE_EXIT_X = (SCREEN_BORDER_WIDTH - 8) / 2;
	static constexpr int PAUSE_EXIT_Y = SCREEN_BORDER_HEIGHT - 3;
	//==============================Pause Screen======================================

	//==============================
	//Game 
	static constexpr int BOARD_HEIGHT = 18;
	static constexpr int BOARD_WIDTH = 12;

	static constexpr int PLAYER1_BOARD_X = 23;
	static constexpr int PLAYER1_BOARD_Y = 4;

	static constexpr int PLAYER2_BOARD_X = 43;
	static constexpr int PLAYER2_BOARD_Y = 4;

	//Players' name under their boards
	static constexpr int PLAYER1_NAME_X = PLAYER1_BOARD_X + 3;
	static constexpr int PLAYER1_NAME_Y = SCREEN_BORDER_HEIGHT - 2;

	static constexpr int PLAYER2_NAME_X = PLAYER2_BOARD_X + 3;
	static constexpr int PLAYER2_NAME_Y = SCREEN_BORDER_HEIGHT - 2;

	//Players' score
	static constexpr int PLAYER1_SCORE_X = PLAYER1_BOARD_X - 7;
	static constexpr int PLAYER1_SCORE_Y = PLAYER1_BOARD_Y;

	static constexpr int PLAYER2_SCORE_X = PLAYER2_BOARD_X + 15;
	static constexpr int PLAYER2_SCORE_Y = PLAYER2_BOARD_Y;


	//==============================
	//Game essentials 
	static constexpr int POINTS_PER_TETRO = 4;

	//==============================
	//keys
	enum class p1Keys
	{
		P1_LEFT1 = 'A', P1_LEFT2 = 'a', P1_RIGHT1 = 'D', P1_RIGHT2 = 'd',
		P1_RC1 = 'S', P1_RC2 = 's', P1_RCC1 = 'W', P1_RCC2 = 'w', P1_DROP1 = 'X', P1_DROP2 = 'x',
		P2_LEFT1 = 'J', P2_LEFT2 = 'j', P2_RIGHT1 = 'L', P2_RIGHT2 = 'l',
		P2_RC1 = 'K', P2_RC2 = 'k', P2_RCC1 = 'I', P2_RCC2 = 'i', P2_DROP1 = 'M', P2_DROP2 = 'm',
		ESC = 27, ENTER = 13, INPUT1 = 49, INPUT2 = 50, INPUT3 = 51, INPUT4 =52, INPUT8 = 56, INPUT9 = 57
	};


	//==============================
	//Scoring system - maybe - add difficulty
	enum class scoring
	{
		EASY_LINE1 = 40, EASY_LINE2 = 100, EASY_LINE3 = 300, EASY_LINE4 = 1200,
		MED_LINE1 = 80, MED_LINE2 = 200, MED_LINE3 = 600, MED_LINE4 = 2400,
		HARD_LINE1 = 120, HARD_LINE2 = 300, HARD_LINE3 = 900, HARD_LINE4 = 3600
	};


	enum class shapes
	{
		INIT = 10, SQUARE = 0, LSHAPE = 1, NOT_LSHAPE = 2, TSHAPE = 3, ZSHAPE = 4, NOT_ZSHAPE = 5, ISHAPE= 6, BOMB = 7
	};

	enum class whichPlayers
	{
		ONLY_HUMANS = 0, ONE_COMPUTER = 1, TWO_COMPUTERS = 2
	};
};