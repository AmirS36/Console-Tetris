#include "tetromino.h"
#include <iostream>
#include <time.h>  

Tetromino::Tetromino(int playerSide)
{
	this->tType = GameConfig::shapes::INIT;
	this->playerNum = playerSide;
	int random = rand();

	if (random % 20 == 0)
		initBomb();

	else
	{
		random %= NUM_OF_PIECES;

		switch (random)
		{
		case (int)GameConfig::shapes::SQUARE:
			initP1(); //Square Shape
			break;

		case (int)GameConfig::shapes::LSHAPE:
			initP2(); //L Shape
			break;

		case (int)GameConfig::shapes::NOT_LSHAPE:
			initP3(); //~L Shape 
			break;

		case (int)GameConfig::shapes::TSHAPE:
			initP4(); //T Shape
			break;

		case (int)GameConfig::shapes::ZSHAPE:
			initP5(); //Z Shape
			break;

		case (int)GameConfig::shapes::NOT_ZSHAPE:
			initP6(); //~Z Shape 
			break;

		case (int)GameConfig::shapes::ISHAPE:
			initP7(); // | Shape
			break;
		}
	}

	for (int i = 0; i < POINTS_PER_PIECE; i++)
	{
		if (this->playerNum == 1)
			piece[i].setStartXY(GameConfig::PLAYER1_BOARD_X, GameConfig::PLAYER1_BOARD_Y);
		else
			piece[i].setStartXY(GameConfig::PLAYER2_BOARD_X, GameConfig::PLAYER2_BOARD_Y);
	}
}

Tetromino::Tetromino(const Tetromino& other)
{
	for (int i = 0; i < POINTS_PER_PIECE; i++)
		piece[i] = other.piece[i];

	tType = other.tType;
	playerNum = other.playerNum;
}

void Tetromino::initBomb() //Bomb
{
	for (int i =0;i<POINTS_PER_PIECE;i++)
	{
		piece[i].set_x(5);
		piece[i].set_y(1);
	}

	tType = GameConfig::shapes::BOMB;
}

void Tetromino::initP1() //Square
{
	piece[0].set_x(6);
	piece[0].set_y(1);

	piece[1].set_x(7);
	piece[1].set_y(1);

	piece[2].set_x(6);
	piece[2].set_y(2);

	piece[3].set_x(7);
	piece[3].set_y(2);

	tType = GameConfig::shapes::SQUARE;
}

void Tetromino::initP2() //L Shape
{
	piece[0].set_x(7);
	piece[0].set_y(1);

	piece[1].set_x(5);
	piece[1].set_y(2);

	piece[2].set_x(6);
	piece[2].set_y(2);

	piece[3].set_x(7);
	piece[3].set_y(2);

	tType = GameConfig::shapes::LSHAPE;
}

void Tetromino::initP3() //~L Shape 
{
	piece[0].set_x(5);
	piece[0].set_y(1);

	piece[1].set_x(5);
	piece[1].set_y(2);

	piece[2].set_x(6);
	piece[2].set_y(2);

	piece[3].set_x(7);
	piece[3].set_y(2);

	tType = GameConfig::shapes::NOT_LSHAPE;
}

void Tetromino::initP4() //T Shape
{
	piece[0].set_x(6);
	piece[0].set_y(2);

	piece[1].set_x(5);
	piece[1].set_y(2);

	piece[2].set_x(6);
	piece[2].set_y(1);

	piece[3].set_x(7);
	piece[3].set_y(2);

	tType = GameConfig::shapes::TSHAPE;
}

void Tetromino::initP5() //Z Shape
{
	piece[0].set_x(5);
	piece[0].set_y(1);

	piece[1].set_x(6);
	piece[1].set_y(1);

	piece[2].set_x(6);
	piece[2].set_y(2);

	piece[3].set_x(7);
	piece[3].set_y(2);

	tType = GameConfig::shapes::ZSHAPE;
}

void Tetromino::initP6() //~Z Shape 
{
	piece[0].set_x(7);
	piece[0].set_y(1);

	piece[1].set_x(6);
	piece[1].set_y(1);

	piece[2].set_x(6);
	piece[2].set_y(2);

	piece[3].set_x(5);
	piece[3].set_y(2);

	tType = GameConfig::shapes::NOT_ZSHAPE;
}

void Tetromino::initP7() // | Shape
{
	piece[0].set_x(5);
	piece[0].set_y(1);

	piece[1].set_x(6);
	piece[1].set_y(1);

	piece[2].set_x(7);
	piece[2].set_y(1);

	piece[3].set_x(8);
	piece[3].set_y(1);

	tType = GameConfig::shapes::ISHAPE;
}

Point* Tetromino::getPoints()
{
	return piece;
}

void Tetromino::drawTetro() const
{
	for (int i = 0; i < POINTS_PER_PIECE; i++)
	{
		piece[i].drawPoint(tType);
	}
}

void Tetromino::moveTetro(GameConfig::p1Keys input, Board board)
{
	switch (input) //Which move was made
	{
	case GameConfig::p1Keys::P1_LEFT1:
	case GameConfig::p1Keys::P1_LEFT2:
	case GameConfig::p1Keys::P2_LEFT1:
	case GameConfig::p1Keys::P2_LEFT2:
		if (tetroValidLeft(board))
			moveLeft(false);
		drawTetro();
		break;

	case GameConfig::p1Keys::P1_RIGHT1:
	case GameConfig::p1Keys::P1_RIGHT2:
	case GameConfig::p1Keys::P2_RIGHT1:
	case GameConfig::p1Keys::P2_RIGHT2:
		if (tetroValidRight(board))
			moveRight(false);
		drawTetro();
		break;

	case GameConfig::p1Keys::P1_RC1:
	case GameConfig::p1Keys::P1_RC2:
	case GameConfig::p1Keys::P2_RC1:
	case GameConfig::p1Keys::P2_RC2:
		if (tetroValidRotateClockWise(board))
			rotateClockWise(false);
		break;

	case GameConfig::p1Keys::P1_RCC1:
	case GameConfig::p1Keys::P1_RCC2:
	case GameConfig::p1Keys::P2_RCC1:
	case GameConfig::p1Keys::P2_RCC2:
		if (tetroValidRotateCounterClockWise(board))
			rotateCounterClockWise(false);
		break;

	case GameConfig::p1Keys::P1_DROP1:
	case GameConfig::p1Keys::P1_DROP2:
	case GameConfig::p1Keys::P2_DROP1:
	case GameConfig::p1Keys::P2_DROP2:
		moveDown(false);
		break;

	}
}

void Tetromino::moveLeft(bool flagAI)
{
	for (int i = 0; i < POINTS_PER_PIECE; i++)
		piece[i].moveLeft(flagAI);
}

void Tetromino::moveRight(bool flagAI)
{
	for (int i = 3; i >= 0; i--)
		piece[i].moveRight(flagAI);
}

void Tetromino::moveDown(bool flagAI)
{
	for (int i = 3; i >= 0; i--)
		piece[i].moveDown(flagAI);
	drawTetro();
}

Tetromino* Tetromino::createCopyPostDown()
{
	Tetromino* temp = new Tetromino(*this);

	for (int i = 3; i >= 0; i--)
		temp->piece[i].set_y(temp->piece[i].get_y() + 1);

	return temp;
}

bool Tetromino::checkCollision(Tetromino* temp, Board board) const
{
	Point* points = temp->getPoints();

	for (int i = 0; i < POINTS_PER_PIECE; i++)
	{
		int x = points[i].get_x();
		int y = points[i].get_y();

		if (board.getMat(y - 1, x - 1) == 'X')
			return false;
	}
	return true;
}

//Tetro validations ==================================================
bool Tetromino::tetroValidLeft(Board board) const
{
	//Check borders
	int canMove = 0;
	for (int i = 0; i < POINTS_PER_PIECE; i++)
	{
		if (piece[i].get_x() - 1 > 0)
			canMove++;
	}
	if (canMove < POINTS_PER_PIECE)
		return false;

	Tetromino* copy = new Tetromino(*this);
	moveCopyLeft(copy);

	bool res = checkCollision(copy, board);
	delete copy;

	return res;
}

bool Tetromino::tetroValidRight(Board board) const
{
	int canMove = 0;
	for (int i = 0; i < POINTS_PER_PIECE; i++)
	{
		if (piece[i].get_x() + 1 <= GameConfig::BOARD_WIDTH)
			canMove++;
	}

	if (canMove < POINTS_PER_PIECE)
		return false;

	Tetromino* copy = new Tetromino(*this);
	moveCopyRight(copy);

	bool res = checkCollision(copy, board);
	delete copy;

	return res;
}

bool Tetromino::tetroValidDown(Board board) const
{
	int canMove = 0;
	for (int i = 0; i < POINTS_PER_PIECE; i++)
	{
		if (piece[i].get_y() + 1 <= GameConfig::BOARD_HEIGHT)
			canMove++;
	}

	if (canMove < POINTS_PER_PIECE)
		return false;

	Tetromino* copy = new Tetromino(*this);
	moveCopyDown(copy);

	bool res = checkCollision(copy, board);
	delete copy;

	return res;
}

bool Tetromino::tetroValidRotateClockWise(Board board) const
{
	Tetromino* copy = new Tetromino(*this);
	rotateCopyClockWise(copy);

	int canMove = 0;
	for (int i = 0; i < POINTS_PER_PIECE; i++) //Check if the copy's move is within borders
	{
		if (copy->piece[i].get_x() <= GameConfig::BOARD_WIDTH && copy->piece[i].get_x() >= 1 &&
			copy->piece[i].get_y() >= 1 && copy->piece[i].get_y() <= GameConfig::BOARD_HEIGHT)
			canMove++;
	}

	if (canMove < POINTS_PER_PIECE)
		return false;

	bool res = checkCollision(copy, board);
	delete copy;

	return res;
}

bool Tetromino::tetroValidRotateCounterClockWise(Board board) const
{
	Tetromino* copy = new Tetromino(*this);
	rotateCopyCounterClockWise(copy);

	int canMove = 0;
	for (int i = 0; i < POINTS_PER_PIECE; i++) //Check if the copy's move is within borders
	{
		if (copy->piece[i].get_x() <= GameConfig::BOARD_WIDTH && copy->piece[i].get_x() >= 1 &&
			copy->piece[i].get_y() >= 1 && copy->piece[i].get_y() <= GameConfig::BOARD_HEIGHT)
			canMove++;
	}

	if (canMove < POINTS_PER_PIECE)
		return false;

	bool res = checkCollision(copy, board);
	delete copy;

	return res;
}


//Tetro move =========================================================
void Tetromino::rotateClockWise(bool flagAI)
{
	for (int i = 0; i < POINTS_PER_PIECE; i++)
	{
		piece[i].removePoint(flagAI);

		int relX = piece[i].get_x() - piece[0].get_x();
		int relY = piece[i].get_y() - piece[0].get_y();

		piece[i].set_x(piece[0].get_x() - relY);
		piece[i].set_y(piece[0].get_y() + relX);
	}
	drawTetro();
}

void Tetromino::rotateCounterClockWise(bool flagAI)
{
	for (int i = 0; i < POINTS_PER_PIECE; i++)
	{
		piece[i].removePoint(flagAI);

		int relX = piece[i].get_x() - piece[0].get_x();
		int relY = piece[i].get_y() - piece[0].get_y();

		piece[i].set_x(piece[0].get_x() + relY);
		piece[i].set_y(piece[0].get_y() - relX);
	}
	drawTetro();
}


//Copy moves =========================================================
void Tetromino::moveCopyLeft(Tetromino* temp) const
{
	for (int i = 0; i < POINTS_PER_PIECE; i++)
		temp->piece[i].moveLeft(true);
}

void Tetromino::moveCopyRight(Tetromino* temp) const
{
	for (int i = 0; i < POINTS_PER_PIECE; i++)
		temp->piece[i].moveRight(true);
}

void Tetromino::moveCopyDown(Tetromino* temp) const
{
	for (int i = 0; i < POINTS_PER_PIECE; i++)
		temp->piece[i].moveDown(true);
}

void Tetromino::rotateCopyClockWise(Tetromino* temp) const
{
	for (int i = 0; i < POINTS_PER_PIECE; i++)
	{
		int relX = temp->piece[i].get_x() - temp->piece[0].get_x();
		int relY = temp->piece[i].get_y() - temp->piece[0].get_y();

		temp->piece[i].set_x(temp->piece[0].get_x() - relY);
		temp->piece[i].set_y(temp->piece[0].get_y() + relX);
	}
}

void Tetromino::rotateCopyCounterClockWise(Tetromino* temp) const
{
	for (int i = 0; i < POINTS_PER_PIECE; i++)
	{
		int relX = temp->piece[i].get_x() - temp->piece[0].get_x();
		int relY = temp->piece[i].get_y() - temp->piece[0].get_y();

		temp->piece[i].set_x(temp->piece[0].get_x() + relY);
		temp->piece[i].set_y(temp->piece[0].get_y() - relX);
	}
}