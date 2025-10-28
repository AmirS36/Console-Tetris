#include "gameLoop.h"
#include "general.h"

void GameLoop::run()
{
	bool bootScreenFlag = true;
	bool menuScreenFlag = false;
	bool gameModeFlag = false;
	bool playGameFlag = false;
	bool shutDown = false;
	GameConfig::whichPlayers computerFlag = GameConfig::whichPlayers::ONLY_HUMANS;
	

	do
	{
		if (bootScreenFlag)
			bootScreen(bootScreenFlag, menuScreenFlag, shutDown);

		if (menuScreenFlag) 
			menuScreen(menuScreenFlag, gameModeFlag, shutDown);

		if (gameModeFlag)
			gameModeScreen(gameModeFlag, playGameFlag, menuScreenFlag, computerFlag);

		if (computerFlag != GameConfig::whichPlayers::ONLY_HUMANS)
			chooseDifficultyScreen(gameModeFlag, playGameFlag, computerFlag);

		if (playGameFlag)
			playGame(playGameFlag, gameModeFlag, shutDown, menuScreenFlag);

		
	} while (!shutDown);

	gotoxy(0, GameConfig::SCREEN_BORDER_HEIGHT + 1);
}

void GameLoop::playGame(bool& playGameFlag, bool& gameModeFlag, bool& shutDown, bool& menuScreenFlag)
{
	if (playGameFlag)
	{
		if (LBoard.getPtype() == PlayerType::HUMAN && RBoard.getPtype() == PlayerType::HUMAN)
		{
			playHvH(gameModeFlag, shutDown, menuScreenFlag);
			playGameFlag = false;
		}
		else if (LBoard.getPtype() == PlayerType::HUMAN && RBoard.getPtype() == PlayerType::COMPUTER)
		{
			playHvC(gameModeFlag, shutDown, menuScreenFlag);
			playGameFlag = false;
		}
		else
		{	
			playCvC(gameModeFlag, shutDown, menuScreenFlag);
			playGameFlag = false;
		}
	}
}

void GameLoop::playHvH(bool& gameModeFlag, bool& shutDown, bool& menuScreenFlag)
{
	_gameUI.showGameScreen();

	Tetromino* pTetrominoL = new Tetromino(1);
	Tetromino* pTetrominoR = new Tetromino(2);
	bool gameLoop = true;

	while (gameLoop)
	{
		//Moving P1 Shape down
		bool canMoveDownL = pTetrominoL->tetroValidDown(LBoard);

		if (canMoveDownL)
			pTetrominoL->moveDown(false);

		//Tetromino cannot move down, adding P1 Tetromino to his board
		else
		{
			if (pTetrominoL->getTetroShape() == GameConfig::shapes::BOMB)
			{
				LBoard.bombBoard(pTetrominoL);
				delete pTetrominoL;
				pTetrominoL = new Tetromino(1);
			}
			else
			{
				LBoard.addTetro(pTetrominoL);
				delete pTetrominoL;
				pTetrominoL = new Tetromino(1);
			}
			if (!LBoard.checkColl(pTetrominoL))
			{
				_gameUI.gameOver(LBoard);
				gameLoop = false;
				menuScreenFlag = true;
			}
		}

		//Moving P2 Shape down
		bool canMoveDownR = pTetrominoR->tetroValidDown(RBoard);

		if (canMoveDownR)
			pTetrominoR->moveDown(false);

		//Tetromino cannot move down, adding P2 Tetromino to his board
		else
		{
			//add curr tetro to board
			RBoard.addTetro(pTetrominoR);
			delete pTetrominoR;
			pTetrominoR = new Tetromino(2);

			if (!RBoard.checkColl(pTetrominoR))
			{
				_gameUI.gameOver(RBoard);
				gameLoop = false;
				menuScreenFlag = true;
			}
		}

		if (gameLoop)
			for (int i = 0; i < 2; i++)
			{
				if (_kbhit())
				{
					int keyPressed = _getch();

					if (whichPlayerHitKb(keyPressed) == 1)
						pTetrominoL->moveTetro((GameConfig::p1Keys)keyPressed, LBoard);

					else if (whichPlayerHitKb(keyPressed) == 2)
						pTetrominoR->moveTetro((GameConfig::p1Keys)keyPressed, RBoard);

					else if (whichPlayerHitKb(keyPressed) == 0)
						pauseScreen(pTetrominoL, pTetrominoR, gameLoop, gameModeFlag, shutDown, i);
				}
			}

		Sleep(500);
	}
}

void GameLoop::playHvC(bool& gameModeFlag, bool& shutDown, bool& menuScreenFlag)
{
	_gameUI.showGameScreen();
	RBoard.printBoard();


	Tetromino* pTetrominoL = new Tetromino(1);
	Tetromino* pTetrominoR = new Tetromino(2);
	bool gameLoop = true;
	bool calcNewMove = true;
	bool pcTurn = true;

	int dest_col, rotations;

	while (gameLoop)
	{
		//Moving P1 Shape down
		bool canMoveDownL = pTetrominoL->tetroValidDown(LBoard);

		if (canMoveDownL)
			pTetrominoL->moveDown(false);

		//Tetromino cannot move down, adding P1 Tetromino to his board
		else
		{
			if (pTetrominoL->getTetroShape() == GameConfig::shapes::BOMB)
			{
				LBoard.bombBoard(pTetrominoL);
				delete pTetrominoL;
				pTetrominoL = new Tetromino(1);
			}
			else
			{
				LBoard.addTetro(pTetrominoL);
				delete pTetrominoL;
				pTetrominoL = new Tetromino(1);
			}
			if (!LBoard.checkColl(pTetrominoL))
			{
				_gameUI.gameOver(LBoard);
				gameLoop = false;
				menuScreenFlag = true;
			}
		}

		if (calcNewMove)
		{
			RBoard.calcBestMove(pTetrominoR, dest_col, rotations);
			calcNewMove = false;
		}

		//Moving P2 Shape down
		bool canMoveDownR = pTetrominoR->tetroValidDown(RBoard);

		if (canMoveDownR)
			pTetrominoR->moveDown(false);

		else
		{
			if (pTetrominoR->getTetroShape() == GameConfig::shapes::BOMB)
			{
				RBoard.bombBoard(pTetrominoR);
				delete pTetrominoR;
				pTetrominoR = new Tetromino(2);
				calcNewMove = true;
			}
			else
			{
				RBoard.addTetro(pTetrominoR);
				delete pTetrominoR;
				pTetrominoR = new Tetromino(2);
				calcNewMove = true;
			}
			if (!RBoard.checkColl(pTetrominoR))
			{
				_gameUI.gameOver(RBoard);
				gameLoop = false;
				menuScreenFlag = true;
			}
		}

		if (gameLoop)
			for (int i = 0; i < 2; i++)
			{
				pcTurn = true;

				if (_kbhit())
				{
					int keyPressed = _getch();

					if (whichPlayerHitKb(keyPressed) == 1)
						pTetrominoL->moveTetro((GameConfig::p1Keys)keyPressed, LBoard);

					else if (whichPlayerHitKb(keyPressed) == 0)
						pauseScreen(pTetrominoL, pTetrominoR, gameLoop, gameModeFlag, shutDown, i);

					i++;
				}
				if (pcTurn)
				{
					if (dest_col < 0 && pcTurn)
					{
						if (pTetrominoR->tetroValidLeft(RBoard))
						{
							pTetrominoR->moveTetro(GameConfig::p1Keys::P2_LEFT2, RBoard);
							dest_col++;
							pcTurn = false;
						}
					}
					else if (dest_col > 0 && pcTurn)
					{
						if (pTetrominoR->tetroValidRight(RBoard))
						{
							pTetrominoR->moveTetro(GameConfig::p1Keys::P2_RIGHT2, RBoard);
							dest_col--;
							pcTurn = false;
						}
					}
					if (rotations != 0 && pcTurn)
					{
						if (pTetrominoR->tetroValidRotateClockWise(RBoard))
						{
							pTetrominoR->moveTetro(GameConfig::p1Keys::P2_RC2, RBoard);
							rotations--;
							pcTurn = false;
						}
					}
					i++;
				}
			}
		Sleep(500);
			
	}
}

void GameLoop::playCvC(bool& gameModeFlag, bool& shutDown, bool& menuScreenFlag)
{
	_gameUI.showGameScreen();
	LBoard.printBoard();
	RBoard.printBoard();

	Tetromino* pTetrominoL = new Tetromino(1);
	Tetromino* pTetrominoR = new Tetromino(2);

	bool gameLoop = true;
	bool pcTurn1 = true;
	bool pcTurn2 = true;

	bool calcNewMoveP1 = true;
	int dest_col1, rotations1;

	bool calcNewMoveP2 = true;
	int dest_col2, rotations2;

	while (gameLoop)
	{
		if (calcNewMoveP1)
		{
			LBoard.calcBestMove(pTetrominoL, dest_col1, rotations1);
			calcNewMoveP1 = false;
		}

		//Moving P1 Shape down
		bool canMoveDownL = pTetrominoL ->tetroValidDown(LBoard);

		if (canMoveDownL)
			pTetrominoL->moveDown(false);

		else
		{
			if (pTetrominoL->getTetroShape() == GameConfig::shapes::BOMB)
			{
				LBoard.bombBoard(pTetrominoL);
				delete pTetrominoL;
				pTetrominoL = new Tetromino(1);
				calcNewMoveP1 = true;
			}
			else
			{
				LBoard.addTetro(pTetrominoL);
				delete pTetrominoL;
				pTetrominoL = new Tetromino(1);
				calcNewMoveP1 = true;
			}
			if (!LBoard.checkColl(pTetrominoL))
			{
				_gameUI.gameOver(LBoard);
				gameLoop = false;
				menuScreenFlag = true;
			}
		}

		if (calcNewMoveP2)
		{
			RBoard.calcBestMove(pTetrominoR, dest_col2, rotations2);
			calcNewMoveP2 = false;
		}

		//Moving P2 Shape down
		bool canMoveDownR = pTetrominoR->tetroValidDown(RBoard);

		if (canMoveDownR)
			pTetrominoR->moveDown(false);

		else
		{
			if (pTetrominoR->getTetroShape() == GameConfig::shapes::BOMB)
			{
				RBoard.bombBoard(pTetrominoR);
				delete pTetrominoR;
				pTetrominoR = new Tetromino(2);
				calcNewMoveP2 = true;
			}
			else
			{
				RBoard.addTetro(pTetrominoR);
				delete pTetrominoR;
				pTetrominoR = new Tetromino(2);
				calcNewMoveP2 = true;
			}
			if (!RBoard.checkColl(pTetrominoR))
			{
				_gameUI.gameOver(RBoard);
				gameLoop = false;
				menuScreenFlag = true;
			}
		}

		if (gameLoop)
			for (int i = 0; i < 2; i++)
			{
				pcTurn1 = true;
				pcTurn2 = true;

				if (_kbhit())
				{
					int keyPressed = _getch();

					if (whichPlayerHitKb(keyPressed) == 0)
						pauseScreen(pTetrominoL, pTetrominoR, gameLoop, gameModeFlag, shutDown, i);

				}
				if (pcTurn1)
				{
					if (dest_col1 < 0 && pcTurn1)
					{
						if (pTetrominoL->tetroValidLeft(LBoard))
						{
							pTetrominoL->moveTetro(GameConfig::p1Keys::P1_LEFT2, LBoard);
							dest_col1++;
							pcTurn1 = false;
						}
					}
					else if (dest_col1 > 0 && pcTurn1)
					{
						if (pTetrominoL->tetroValidRight(LBoard))
						{
							pTetrominoL->moveTetro(GameConfig::p1Keys::P1_RIGHT2, LBoard);
							dest_col1--;
							pcTurn1 = false;
						}
					}
					if (rotations1 != 0 && pcTurn1)
					{
						if (pTetrominoL->tetroValidRotateClockWise(LBoard))
						{
							pTetrominoL->moveTetro(GameConfig::p1Keys::P1_RC2, LBoard);
							rotations1--;
							pcTurn1 = false;
						}
					}
					i++;
				}
				if (pcTurn2)
				{
					if (dest_col2 < 0 && pcTurn2)
					{
						if (pTetrominoR->tetroValidLeft(RBoard))
						{
							pTetrominoR->moveTetro(GameConfig::p1Keys::P2_LEFT2, RBoard);
							dest_col2++;
							pcTurn2 = false;
						}
					}
					else if (dest_col2 > 0 && pcTurn2)
					{
						if (pTetrominoR->tetroValidRight(RBoard))
						{
							pTetrominoR->moveTetro(GameConfig::p1Keys::P2_RIGHT2, RBoard);
							dest_col2--;
							pcTurn2 = false;
						}
					}
					if (rotations2 != 0 && pcTurn2)
					{
						if (pTetrominoR->tetroValidRotateClockWise(RBoard))
						{
							pTetrominoR->moveTetro(GameConfig::p1Keys::P2_RC2, RBoard);
							rotations2--;
							pcTurn2 = false;
						}
					}
					i++;
				}
			}
		Sleep(500);
	}
}

void GameLoop::gameModeScreen(bool& gameModeFlag, bool& playGameFlag, bool& menuScreenFlag, GameConfig::whichPlayers& computerFlag)
{
	while (gameModeFlag)
	{
		_gameUI.showGameModeScreen();
		switch (_getch())
		{
			//User pressed 1 - Human vs Human
		case (int)GameConfig::p1Keys::INPUT1:
			//Set player1 to H & player2 to H
			LBoard.setBoard(Side::LEFT, PlayerType::HUMAN);
			RBoard.setBoard(Side::RIGHT, PlayerType::HUMAN);
			gameModeFlag = false;
			playGameFlag = true;
			break;

			//User pressed 2 - Human vs Computer
		case (int)GameConfig::p1Keys::INPUT2:
			//Set player1 to H & player2 to C & Show difficulty selection screen for computer
			LBoard.setBoard(Side::LEFT, PlayerType::HUMAN);
			RBoard.setBoard(Side::RIGHT, PlayerType::COMPUTER);
			gameModeFlag = false;
			playGameFlag = true;
			computerFlag = GameConfig::whichPlayers::ONE_COMPUTER;
			break;

			//User pressed 3 - Computer vs Computer
		case (int)GameConfig::p1Keys::INPUT3:
			//Set both players to computer & Show difficulty selection screen for both
			LBoard.setBoard(Side::LEFT, PlayerType::COMPUTER);
			RBoard.setBoard(Side::RIGHT, PlayerType::COMPUTER);
			gameModeFlag = false;
			playGameFlag = true;
			computerFlag = GameConfig::whichPlayers::TWO_COMPUTERS;
			break;

			//User pressed 9 - back to Main Menu
		case (int)GameConfig::p1Keys::INPUT9:
			gameModeFlag = false;
			menuScreenFlag = true;
			break;
		}
	}
}

void GameLoop::chooseDifficultyScreen(bool& gameModeFlag, bool& playGameFlag, GameConfig::whichPlayers& computerFlag)
{
	_gameUI.showComp1DiffScreen();
	//Handle Comp1 diff input

	switch (_getch())
	{
		//User pressed 1 - EASY
	case (int)GameConfig::p1Keys::INPUT1:
		//Set Comp1 difficulty to Easy
		RBoard.setDifficulty(Difficulty::EASY);
		break;

		//User pressed 2 - MEDIUM
	case (int)GameConfig::p1Keys::INPUT2:
		//Set Comp1 difficulty to Medium
		RBoard.setDifficulty(Difficulty::MEDIUM);
		break;

		//User pressed 3 - HARD
	case (int)GameConfig::p1Keys::INPUT3:
		//Set Comp1 difficulty to Hard
		RBoard.setDifficulty(Difficulty::HARD);
		break;

		//User pressed 9 - back to Mode Menu
	case (int)GameConfig::p1Keys::INPUT9:
		gameModeFlag = true;
		playGameFlag = false;
		computerFlag = GameConfig::whichPlayers::ONLY_HUMANS;
		break;
	}

	if (computerFlag == GameConfig::whichPlayers::TWO_COMPUTERS && gameModeFlag == false)
	{
		_gameUI.showComp2DiffScreen();
		switch (_getch())
		{
			//User pressed 1 - EASY
		case (int)GameConfig::p1Keys::INPUT1:
			//Set Comp2 difficulty to Easy
			LBoard.setDifficulty(Difficulty::EASY);
			break;

			//User pressed 2 - MEDIUM
		case (int)GameConfig::p1Keys::INPUT2:
			//Set Comp2 difficulty to Medium
			LBoard.setDifficulty(Difficulty::MEDIUM);
			break;

			//User pressed 3 - HARD
		case (int)GameConfig::p1Keys::INPUT3:
			//Set Comp2 difficulty to Hard
			LBoard.setDifficulty(Difficulty::HARD);
			break;

			//User pressed 9 - back to Comp1 diff Menu
		case (int)GameConfig::p1Keys::INPUT9:
			chooseDifficultyScreen(gameModeFlag, playGameFlag, computerFlag);
			break;
		}
	}
}
void GameLoop::pauseScreen(Tetromino* pTetroL, Tetromino* pTetroR, bool& inGameFlag ,bool& gameModeFlag, bool& shutDown ,int& i)
{
	_gameUI.showPauseScreen();
	switch (_getch())
	{

	case (int)GameConfig::p1Keys::INPUT1: //User pressed 1 -- Start new game 
		gameModeFlag = true;
		inGameFlag = false;
		delete pTetroL;
		delete pTetroR;
		i = 2;
		break;

	case (int)GameConfig::p1Keys::INPUT2: //User pressed 2 -- Continue 
		_gameUI.showGameScreen();
		LBoard.printBoard();
		RBoard.printBoard();
		pTetroL->drawTetro();
		pTetroR->drawTetro();
		i--;
		break;

	case (int)GameConfig::p1Keys::INPUT8: //User pressed 8 - Instructions
		_gameUI.showInstructions();
		pauseScreen(pTetroL, pTetroR, inGameFlag, gameModeFlag, shutDown, i);
		break;

	case (int)GameConfig::p1Keys::INPUT9: //User pressed 9 - Exit
		inGameFlag = false;
		shutDown = true;
		break;
	}
}

void GameLoop::bootScreen(bool& bootScreenFlag, bool& menuScreenFlag, bool& shutDown)
{
	_gameUI.showBootScreen();
	switch (_getch())
	{
		//ESC - Exit the game from starting screen
	case (int)GameConfig::p1Keys::ESC:
		bootScreenFlag = false;
		shutDown = true;
		break;

		//Enter - show menu screen
	case (int)GameConfig::p1Keys::ENTER:
		menuScreenFlag = true;
		bootScreenFlag = false;
		break;
	}
}

void GameLoop::menuScreen(bool& menuScreenFlag, bool& gameModeFlag, bool& shutDown)
{
	_gameUI.showMenuScreen();
	switch (_getch())
	{
		//User pressed 1 - Select Game Mode
	case (int)GameConfig::p1Keys::INPUT1:
		menuScreenFlag = false;
		gameModeFlag = true;
		break;

		//User pressed 8 - Instructions
	case (int)GameConfig::p1Keys::INPUT8:
		_gameUI.showInstructions();
		break;

		//User pressed 9 - Exit
	case (int)GameConfig::p1Keys::INPUT9:
		menuScreenFlag = false;
		shutDown = true;
		break;
	}
}

int GameLoop::whichPlayerHitKb(int keyPressed)
{
	if (keyPressed == (int)GameConfig::p1Keys::P1_LEFT1 ||
		keyPressed == (int)GameConfig::p1Keys::P1_LEFT2 ||
		keyPressed == (int)GameConfig::p1Keys::P1_RIGHT1 ||
		keyPressed == (int)GameConfig::p1Keys::P1_RIGHT2 ||
		keyPressed == (int)GameConfig::p1Keys::P1_RC1 ||
		keyPressed == (int)GameConfig::p1Keys::P1_RC2 ||
		keyPressed == (int)GameConfig::p1Keys::P1_RCC1 ||
		keyPressed == (int)GameConfig::p1Keys::P1_RCC2 ||
		keyPressed == (int)GameConfig::p1Keys::P1_DROP1 ||
		keyPressed == (int)GameConfig::p1Keys::P1_DROP2)
	{
		return 1;
	}
	else if (keyPressed == (int)GameConfig::p1Keys::P2_LEFT1 ||
		keyPressed == (int)GameConfig::p1Keys::P2_LEFT2 ||
		keyPressed == (int)GameConfig::p1Keys::P2_RIGHT1 ||
		keyPressed == (int)GameConfig::p1Keys::P2_RIGHT2 ||
		keyPressed == (int)GameConfig::p1Keys::P2_RC1 ||
		keyPressed == (int)GameConfig::p1Keys::P2_RC2 ||
		keyPressed == (int)GameConfig::p1Keys::P2_RCC1 ||
		keyPressed == (int)GameConfig::p1Keys::P2_RCC2 ||
		keyPressed == (int)GameConfig::p1Keys::P2_DROP1 ||
		keyPressed == (int)GameConfig::p1Keys::P2_DROP2)
	{
		return 2;
	}
	else if (keyPressed == (int)GameConfig::p1Keys::ESC)
	{
		return 0;
	}
	else // other input
	{
		return -1;
	}
}
