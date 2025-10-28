#pragma once
#include "gameUI.h"
#include "gameConfig.h"
#include "board.h"
#include <vector>

class GameLoop
{
private:
	GameUI _gameUI;
	Board LBoard;
	Board RBoard;

	int whichPlayerHitKb(int keyPressed);

public:
	GameLoop() {}
	void run();

	void playGame(bool& playGameFlag, bool& gameModeFlag, bool& shutDown, bool& menuScreenFlag);
	void playHvH(bool& gameModeFlag, bool& shutDown, bool& menuScreenFlag);
	void playHvC(bool& gameModeFlag, bool& shutDown, bool& menuScreenFlag);
	void playCvC(bool& gameModeFlag, bool& shutDown, bool& menuScreenFlag);


	void gameModeScreen(bool& gameModeFlag, bool& playGameFlag, bool& menuScreenFlag, GameConfig::whichPlayers& computerFlag);
	void chooseDifficultyScreen(bool& gameModeFlag, bool& playGameFlag, GameConfig::whichPlayers& computerFlag);
	void bootScreen(bool& bootScreenFlag, bool& menuScreenFlag, bool& shutDown);
	void menuScreen(bool& menuScreenFlag, bool& gameModeFlag, bool& shutDown);
	void pauseScreen(Tetromino* pTetroL, Tetromino* pTetroR, bool& inGameFlag, bool& gameModeFlag, bool& shutDown, int& i);
	

};

