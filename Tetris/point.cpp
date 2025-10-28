#include "point.h"
#include "general.h"
#include "gameConfig.h"
#include <iostream>

using namespace std;

void Point::drawPoint(GameConfig::shapes tType) const
{
	gotoxy(_x + _startX, _y + _startY - 1);
	if (tType == GameConfig::shapes::BOMB)
		cout << '*' << endl;
	else
		cout << '#' << endl;
}

void Point::removePoint(bool flagAI)
{
	if (!flagAI)
	{
	gotoxy(_x + _startX, _y + _startY - 1);
	cout << ' ' << endl;
	}
}

void Point::setStartXY(int x, int y) {
	_startX = x;
	_startY = y;
}

void Point::moveDown(bool flagAI)
{
	removePoint(flagAI);
	_y++;
}

void Point::moveLeft(bool flagAI)
{
	removePoint(flagAI);
	_x--;
}

void Point::moveRight(bool flagAI)
{
	removePoint(flagAI);
	_x++;
}
