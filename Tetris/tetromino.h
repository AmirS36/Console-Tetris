#pragma once
#include "point.h"
#include "board.h"

enum { NUM_OF_PIECES = 7, POINTS_PER_PIECE = 4 };
class Board;

class Tetromino
{
private:
	Point piece[POINTS_PER_PIECE];
	int playerNum;
	GameConfig::shapes tType;

public:
	Tetromino(int playerSide);
	Tetromino(const Tetromino& other);

	void initBomb();
	void initP1();
	void initP2();
	void initP3();
	void initP4();
	void initP5();
	void initP6();
	void initP7();

	void drawTetro() const;

	Point* getPoints();											//Getting Tetromino's position per Point
	Tetromino* createCopyPostDown();

	void moveTetro(GameConfig::p1Keys input, Board board);
	GameConfig::shapes getTetroShape() { return tType; };

	//Tetro validations==================================================
	//for each method we create a copy of the piece and make the move on the copy (using Copy moves methods)
	//copy verification is with checkCollision and borders limit check
	bool checkCollision(Tetromino* temp, Board board) const;
	bool tetroValidLeft(Board board) const;
	bool tetroValidRight(Board board) const;
	bool tetroValidDown(Board board) const;
	bool tetroValidRotateClockWise(Board board) const;
	bool tetroValidRotateCounterClockWise(Board board) const;

	//Copy moves =========================================================
	void moveCopyLeft(Tetromino* temp) const;
	void moveCopyRight(Tetromino* temp) const;
	void moveCopyDown(Tetromino* temp) const;
	void rotateCopyClockWise(Tetromino* temp) const;
	void rotateCopyCounterClockWise(Tetromino* temp) const;

	//Tetro move =========================================================
	void moveLeft(bool flagAI);
	void moveRight(bool flagAI);
	void moveDown(bool flagAI);
	void rotateClockWise(bool flagAI);
	void rotateCounterClockWise(bool flagAI);

	//AI Move Calculation




};
