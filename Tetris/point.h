#pragma once
#include "gameConfig.h"

class Point
{
private:
	int _x; //Relative to board
	int _y;
	int _startX; //Absolute position at start
	int _startY;
public:
	void setStartXY(int x, int y);

	int get_x() const { return _x; }
	int get_y() const { return _y; }

	void set_x(int x) { _x = x; }
	void set_y(int y) { _y = y; }

	void moveLeft(bool flagAI);
	void moveDown(bool flagAI);
	void moveRight(bool flagAI);

	void drawPoint(GameConfig::shapes tType) const;
	void removePoint(bool flagAI);
};

