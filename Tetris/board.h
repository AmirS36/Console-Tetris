#pragma once
#include "point.h"
#include "gameConfig.h"
#include "tetromino.h"
#include "general.h"
#include "player.h"
#include <iostream>

using namespace std;

enum Side { LEFT, RIGHT};

class Board
{
private:

	char mat[GameConfig::BOARD_HEIGHT][GameConfig::BOARD_WIDTH];
	int score;
	Side side;
	Player* player;

public:
	Board();
	Board(const Board& other);
	//~Board();
	void setBoard(Side side, PlayerType playerType);
	void reset(Side side);

	void setSide(Side side) { this->side = side; }
	Side getSide() const { return side; }
	void setDifficulty(Difficulty diff);
	string getDifficulty() const;
	PlayerType getPtype() const { return player->getType(); }
	int getScore() const { return score; }
	char getMat(int y, int x) const { return mat[y][x]; }

	bool isPointInBounds(int row, int col);
	bool isPointGrounded(int row, int col, bool(&visitedPointsMat)[GameConfig::BOARD_HEIGHT][GameConfig::BOARD_WIDTH]);
	void bombBoard(Tetromino* pTetro);
	void bombBoard(Tetromino* pTetro, int& pointsCleared, bool flagAI);

	void addTetro(Tetromino* pTetro);
	void addTetroCopy(Tetromino* pTetro);
	void removeTetroCopy(Tetromino* pTetro);
	bool checkColl(Tetromino* pTetro) const;
	void printBoard() const;
	void updateBoard();
	void deleteRow(int row);
	void deleteRowEffect(int row) const;

	//Computer methods
	void calcBestMove(Tetromino* pTetro, int& dest_col , int& rotations);
	int calcFilledLines() const;

};

