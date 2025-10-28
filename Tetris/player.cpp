#include "player.h"
#include "board.h"
#include "tetromino.h"

void Computer::calcBestMove(Board board, int& dest_col, int& rotations, Tetromino* pTetro)
{
	if (pTetro->getTetroShape() == GameConfig::shapes::BOMB)
		calcBestMoveBomb(board, dest_col, pTetro);

	else
		calcBestMoveShape(board, dest_col, rotations, pTetro);
}

void Computer::calcAnyMove(Board board, int& dest_col, int& rotations, Tetromino* pTetro)
{
	if (pTetro->getTetroShape() == GameConfig::shapes::BOMB)
	{
		dest_col = 0;
		rotations = 0;
	}

	else
		calcAnyMoveShape(board, dest_col, rotations, pTetro);
}

void Computer::calcBestMoveBomb(Board board, int& dest_col, Tetromino* pTetro)
{
	int currPointsCleared = 0, pointsCleared = 0;
	int currBestCol = 0, currBestDepth = 0;

	for (int row = GameConfig::BOARD_HEIGHT - 1; row >= 0; row--)
	{
		for (int col = GameConfig::BOARD_WIDTH - 1; col >= 0; col--)
		{
			pointsCleared = 0;

			if ((board.getMat(col, row) == ' ') && makeMoveBombCopy(board, col - 6, row, pTetro, pointsCleared))
			{
				if (currPointsCleared < pointsCleared)
				{
					currPointsCleared = pointsCleared;
					currBestCol = col;
				}
	
				
			}
		}
	}
	dest_col = currBestCol - 6;
}

bool Computer::makeMoveBombCopy(Board board, int dest_col, int depth, Tetromino* pTetro, int& pointsCleared)
{
	bool legalMove = true;

	Tetromino copy(*pTetro);
	Board boardCopy(board);

	while ((dest_col != 0 || depth > 1) && legalMove == true)
	{
		if (dest_col < 0 && legalMove)
		{
			if (legalMove = copy.tetroValidLeft(board))
			{
				copy.moveCopyLeft(&copy);
				dest_col++;
			}
		}
		else if (dest_col > 0 && legalMove)
		{
			if (legalMove = copy.tetroValidRight(board))
			{
				copy.moveCopyRight(&copy);
				dest_col--;
			}
		}
		if (depth > 0 && legalMove)
		{
			if (legalMove = copy.tetroValidDown(board))
			{
				copy.moveCopyDown(&copy);
				depth--;
			}
		}
	}

	if (legalMove)
		boardCopy.bombBoard(&copy, pointsCleared, true);

	return legalMove;
}

void Computer::calcBestMoveShape(Board board, int& dest_col, int& rotations, Tetromino* pTetro)
{
	int currRotations = 0;
	int currBestDepth = 0, currBestCol = 0;
	int currFilledLines = 0, copyFilledLines = 0;

	int numOfRotations = 3;

	switch (pTetro->getTetroShape())
	{
	case::GameConfig::shapes::SQUARE:
		numOfRotations = 0;
	case::GameConfig::shapes::NOT_ZSHAPE:
	case::GameConfig::shapes::ZSHAPE:
	case::GameConfig::shapes::ISHAPE:
		numOfRotations = 1;
	}

	for (int i = 0; i <= numOfRotations; i++)
	{
		for (int row = GameConfig::BOARD_HEIGHT - 1; row >= 0; row--)
		{
			for (int col = GameConfig::BOARD_WIDTH - 1; col >= 0; col--)
			{
				if ((board.getMat(col, row) == ' ') && makeMoveCopy(board, col - 6, i, row, pTetro, copyFilledLines))
				{
					if (currFilledLines > copyFilledLines)
						continue;
					
					else if (copyFilledLines > currFilledLines)
					{
						currFilledLines = copyFilledLines;
						currBestCol = col;
						currBestDepth = row;
						currRotations = i;
					}
					else
					{
						//If same amount of lines are filled, prefer more in depth.
						//could be irrelevant cause we check this bottom up
						if (currBestDepth > row)
							continue;
						
						else if (currBestDepth < row)
						{
							currFilledLines = copyFilledLines;
							currBestCol = col;
							currBestDepth = row;
							currRotations = i;
						}
						else
						{
							//If the depth is the same, prefer the move that is furthest from the center
							if (abs(col - 6) > abs(currBestCol - 6))
							{
								currFilledLines = copyFilledLines;
								currBestCol = col;
								currBestDepth = row;
								currRotations = i;
							}
						}
					}
				}
			}
		}
	}

	dest_col = currBestCol - 6;
	rotations = currRotations;
}

void Computer::calcAnyMoveShape(Board board, int& dest_col, int& rotations, Tetromino* pTetro)
{
	int copyFilledLines = 0;
	int numOfRotations = 3;
	bool flagStop = false;

	switch (pTetro->getTetroShape())
	{
		case::GameConfig::shapes::SQUARE:
			numOfRotations = 0;
		case::GameConfig::shapes::NOT_ZSHAPE:
		case::GameConfig::shapes::ZSHAPE:
		case::GameConfig::shapes::ISHAPE:
			numOfRotations = 1;
	}

	for (int i = 0; i <= numOfRotations && !flagStop; i++)
	{
		for (int row = GameConfig::BOARD_HEIGHT - 1; row >= 0 && !flagStop ; row--)
		{
			for (int col = GameConfig::BOARD_WIDTH - 1; col >= 0 && !flagStop ;col--)
			{
				if ((board.getMat(col, row) == ' ') && makeMoveCopy(board, col - 6, i, row, pTetro, copyFilledLines))
				{
					dest_col = col - 6;
					rotations = i;
					flagStop = true;
				
				}
				
			}
		}
	}
}

bool Computer::makeMoveCopy(Board board, int dest_col, int rotations, int depth , Tetromino* pTetro, int& filledLines)
{
	bool legalMove = true;
	Tetromino copy(*pTetro);

	while ((dest_col != 0 || rotations != 0 || depth > 1) && legalMove == true)
	{
		if (dest_col < 0 && legalMove)
		{
			if (legalMove = copy.tetroValidLeft(board))
			{
				copy.moveCopyLeft(&copy);
				dest_col++;
			}
		}
		else if (dest_col > 0 && legalMove)
		{
			if (legalMove = copy.tetroValidRight(board))
			{
				copy.moveCopyRight(&copy);
				dest_col--;
			}
		}
		if (depth > 0 && legalMove)
		{
			if (legalMove = copy.tetroValidDown(board))
			{
				copy.moveCopyDown(&copy);
				depth--;
			}
		}
		if (rotations != 0 && legalMove)
		{
			if (legalMove = copy.tetroValidRotateClockWise(board))
			{
				copy.rotateCopyClockWise(&copy);
				rotations--;
			}
		}
	}
	if (legalMove)
	{
		board.addTetroCopy(&copy);
		filledLines = board.calcFilledLines();
		board.removeTetroCopy(&copy);
	}
	return legalMove;
}