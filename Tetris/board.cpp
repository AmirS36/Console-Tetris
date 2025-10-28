#include "board.h"

Board::Board()
{
	player = new Player();
}

Board::Board(const Board& other)
{
	for (int i = 0; i < GameConfig::BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < GameConfig::BOARD_WIDTH; j++)
		{
			mat[i][j] = other.mat[i][j];
		}
	}
	score = other.score;
	side = other.side;
	player = other.player;
}

void Board::setBoard(Side side, PlayerType playerType)
{
	for (int i = 0; i < GameConfig::BOARD_WIDTH; i++)
	{
		for (int j = 0; j < GameConfig::BOARD_HEIGHT; j++)
		{
			this->mat[j][i] = ' ';
		}
	}
	this->side = side;
	score = 0;

	
	if (playerType == PlayerType::COMPUTER)
		player = new Computer();

	else
		player = new Human();
}

void Board::setDifficulty(Difficulty diff)
{
	Computer* temp = dynamic_cast<Computer*>(player);

	if (temp != nullptr)
		temp->setDifficulty(diff);
}


string Board::getDifficulty() const
{
	Computer* temp = dynamic_cast<Computer*>(player);
	string diff;
	if (temp != nullptr)
	{
		if (temp->getDifficulty() == Difficulty::EASY)
			diff = "EASY";
		else if (temp->getDifficulty() == Difficulty::MEDIUM)
			diff = "MEDIUM";
		else if (temp->getDifficulty() == Difficulty::HARD)
			diff = "HARD";
		return diff;
	}

}

void Board::reset(Side side)
{
	for (int i = 0; i < GameConfig::BOARD_WIDTH; i++)
	{
		for (int j = 0; j < GameConfig::BOARD_HEIGHT; j++)
		{
			this->mat[j][i] = ' ';
		}
	}
	this->side = side;
	score = 0;
}

void Board::addTetro(Tetromino* pTetro)
{
	Point* points = pTetro->getPoints();

	for (int i = 0; i < POINTS_PER_PIECE; i++)
	{
		int x = points[i].get_x();
		int y = points[i].get_y();
		this->mat[y - 1][x - 1] = 'X';
	}
	printBoard();
	updateBoard();
	printBoard();
}

void Board::addTetroCopy(Tetromino* pTetro)
{
	Point* points = pTetro->getPoints();

	for (int i = 0; i < POINTS_PER_PIECE; i++)
	{
		int x = points[i].get_x();
		int y = points[i].get_y();
		this->mat[y - 1][x - 1] = 'X';
	}
}

void Board::removeTetroCopy(Tetromino* pTetro)
{
	Point* points = pTetro->getPoints();

	for (int i = 0; i < POINTS_PER_PIECE; i++)
	{
		int x = points[i].get_x();
		int y = points[i].get_y();
		this->mat[y - 1][x - 1] = ' ';
	}
}

bool Board::isPointInBounds(int row, int col)
{
	return !(row < 0 || row > GameConfig::BOARD_HEIGHT - 1 || col < 0 || col > GameConfig::BOARD_WIDTH - 1);
}

bool Board::isPointGrounded(int row, int col, bool(&visitedPointsMat)[GameConfig::BOARD_HEIGHT][GameConfig::BOARD_WIDTH])
{
	if (!isPointInBounds(row, col) || mat[row][col] != 'X' || visitedPointsMat[row][col])
		return false;

	visitedPointsMat[row][col] = true;

	if (row == GameConfig::BOARD_HEIGHT - 1)
		return true;

	return isPointGrounded(row + 1, col, visitedPointsMat) ||
		isPointGrounded(row, col - 1, visitedPointsMat) ||
		isPointGrounded(row, col + 1, visitedPointsMat);
}

void Board::bombBoard(Tetromino* pTetro)
{
	Point* points = pTetro->getPoints();

	//update all bombarded sqaures in the board

	for (int row = points[0].get_y() - 4; row < points[0].get_y() + 4; row++)
	{
		for (int col = points[0].get_x() - 4; col < points[0].get_x() + 4; col++)
		{
			if (isPointInBounds(row, col))
				mat[row][col] = '*';
		}
	}

	//print the board with the bombing effect
	printBoard();
	Sleep(100);


	//clear the board
	for (int row = GameConfig::BOARD_HEIGHT - 1; row >= 0; row--)
	{
		for (int col = GameConfig::BOARD_WIDTH - 1; col >= 0; col--)
		{
			if (mat[row][col] == '*')
				mat[row][col] = ' ';
		
		}

	}

	printBoard();

	for (int row = GameConfig::BOARD_HEIGHT - 1; row >= 0; row--)
	{
		for (int col = GameConfig::BOARD_WIDTH - 1; col >= 0; col--)
		{
			bool visitedPointsMat[GameConfig::BOARD_HEIGHT][GameConfig::BOARD_WIDTH] = { false };

			if (mat[row][col] == 'X' && !isPointGrounded(row, col, visitedPointsMat))
			{
				int currY = row;
				while (isPointInBounds(currY + 1, col) && mat[currY + 1][col] != 'X')
				{
					mat[currY][col] = ' ';
					currY++;
					mat[currY][col] = 'X';
					printBoard();
					Sleep(10);
				}
			}
		}
	}

	printBoard();

}

void Board::bombBoard(Tetromino* pTetro, int& pointsCleared, bool flagAI)
{
	Point* points = pTetro->getPoints();

	//update all bombarded sqaures in the board

	for (int row = points[0].get_y() - 4 ; row < points[0].get_y() + 4; row++)
	{
		for (int col = points[0].get_x() - 4 ; col < points[0].get_x() + 4; col++)
		{
			if(isPointInBounds(row, col))
			{
				if(mat[row][col] == 'X')
					pointsCleared++;

				mat[row][col] = '*';				
			}
		}
	}

	//print the board with the bombing effect
	if (!flagAI)
	{
		printBoard();
		Sleep(100);
	}

	 
	//clear the board
	for (int row = GameConfig::BOARD_HEIGHT - 1; row >= 0; row--)
	{
		for (int col = GameConfig::BOARD_WIDTH - 1; col >= 0; col--)
		{
			if (mat[row][col] == '*')
			{
				mat[row][col] = ' ';
				
			}
		}

	}

	if (!flagAI)
		printBoard();

	for (int row = GameConfig::BOARD_HEIGHT - 1; row >= 0; row--)
	{
		for (int col = GameConfig::BOARD_WIDTH - 1; col >= 0; col--)
		{
			bool visitedPointsMat[GameConfig::BOARD_HEIGHT][GameConfig::BOARD_WIDTH] = { false };

			if (mat[row][col] == 'X' && !isPointGrounded(row, col, visitedPointsMat))
			{
				int currY = row;
				while (isPointInBounds(currY + 1, col) && mat[currY + 1][col] != 'X')
				{
					mat[currY][col] = ' ';
					currY++;
					mat[currY][col] = 'X';
					if (!flagAI)
						printBoard();
					Sleep(10);
				}
			}
		}
	}
	if (!flagAI)
		printBoard();

}

bool Board::checkColl(Tetromino* pTetro) const
{
	Point* points = pTetro->getPoints();

	for (int i = 0; i < POINTS_PER_PIECE; i++)
	{
		int x = points[i].get_x();
		int y = points[i].get_y();

		if (mat[y - 1][x - 1] == 'X')
			return false;
	}
	return true;
}

void Board::updateBoard()
{
	int rowsCleared = 0;
	int rowPointCounter;

	for (int row = GameConfig::BOARD_HEIGHT - 1; row >= 0; row--)
	{
		rowPointCounter = 0;

		for (int col = GameConfig::BOARD_WIDTH - 1; col >= 0; col--)
		{
			if (mat[row][col] == 'X')
				rowPointCounter++;
		}

		if (rowPointCounter == GameConfig::BOARD_WIDTH)
		{
			deleteRow(row);
			rowsCleared++;
			row--; //In case there are back to back rows to delete
		}
	}

	//Scoring system 
	switch (rowsCleared)
	{
	case 1:
		score += (int)GameConfig::scoring::EASY_LINE1;
		break;
	case 2:
		score += (int)GameConfig::scoring::EASY_LINE2;
		break;
	case 3:
		score += (int)GameConfig::scoring::EASY_LINE3;
		break;
	case 4:
		score += (int)GameConfig::scoring::EASY_LINE4;
		break;
	}
}

void Board::deleteRow(int row)
{
	for (int r = row; r >= 1; r--)
	{
		for (int col = GameConfig::BOARD_WIDTH - 1; col >= 0; col--)
		{
			mat[r][col] = mat[r - 1][col];
		}
	}
	deleteRowEffect(row);
}

void Board::deleteRowEffect(int row) const
{
	if (side == LEFT)
	{
		gotoxy(GameConfig::PLAYER1_BOARD_X + 1, row + GameConfig::PLAYER1_BOARD_Y);
		cout << "============";
		Sleep(100);
	}
	else if (side == RIGHT)
	{
		gotoxy(GameConfig::PLAYER2_BOARD_X + 1, row + GameConfig::PLAYER2_BOARD_Y);
		cout << "============";
		Sleep(100);
	}
}

void Board::printBoard() const
{
	if (side == LEFT)
	{
		for (int col = 0; col < GameConfig::BOARD_WIDTH; col++)
		{
			for (int row = 0; row < GameConfig::BOARD_HEIGHT; row++)
			{
				gotoxy(col + GameConfig::PLAYER1_BOARD_X + 1, row + GameConfig::PLAYER1_BOARD_Y);
				if (mat[row][col] == 'X')
					cout << '#';
				else if(mat[row][col] == '*')
					cout << '*';
				else
					cout << ' ';
			}
		}

		gotoxy(GameConfig::PLAYER1_SCORE_X, GameConfig::PLAYER1_SCORE_Y + 1);
		cout << score;

		gotoxy(GameConfig::PLAYER1_SCORE_X, GameConfig::PLAYER1_SCORE_Y + 3);
		string tempString = getDifficulty();
		cout << tempString;
	}

	else if (side == RIGHT)
	{
		for (int col = 0; col < GameConfig::BOARD_WIDTH; col++)
		{
			for (int row = 0; row < GameConfig::BOARD_HEIGHT; row++)
			{
				gotoxy(col + GameConfig::PLAYER2_BOARD_X + 1, row + GameConfig::PLAYER2_BOARD_Y);
				if (mat[row][col] == 'X')
					cout << '#';
				else if (mat[row][col] == '*')
					cout << '*';
				else
					cout << ' ';
			}
		}
		gotoxy(GameConfig::PLAYER2_SCORE_X, GameConfig::PLAYER2_SCORE_Y + 1);
		cout << score;
		
		gotoxy(GameConfig::PLAYER2_SCORE_X, GameConfig::PLAYER2_SCORE_Y + 3);
		string tempString2 = getDifficulty();
		cout << tempString2;
	}
}

void Board::calcBestMove(Tetromino* pTetro, int& dest_col, int& rotations)
{
	Computer* computerPlayer = dynamic_cast<Computer*>(player);

	int randIQ = rand();

	if (computerPlayer != nullptr)
	{
		if (computerPlayer->getDifficulty() == Difficulty::HARD)
			computerPlayer->calcBestMove(*this, dest_col, rotations, pTetro);
		else if (computerPlayer->getDifficulty() == Difficulty::MEDIUM)
		{
			if (randIQ % 40 != 0)
				computerPlayer->calcBestMove(*this, dest_col, rotations, pTetro);
			else
				computerPlayer->calcAnyMove(*this, dest_col, rotations, pTetro);
		}
		
		else
			if (randIQ % 10 != 0)
				computerPlayer->calcBestMove(*this, dest_col, rotations, pTetro);
			else
				computerPlayer->calcAnyMove(*this, dest_col, rotations, pTetro);
	}
}

int Board::calcFilledLines() const
{
	int filledLines = 0;
	int rowPointCounter;

	for (int row = GameConfig::BOARD_HEIGHT - 1; row >= 0; row--)
	{
		rowPointCounter = 0;

		for (int col = GameConfig::BOARD_WIDTH - 1; col >= 0; col--)
		{
			if (mat[row][col] == 'X')
				rowPointCounter++;
		}

		if (rowPointCounter == GameConfig::BOARD_WIDTH)
			filledLines++;
	}
	return filledLines;
}

