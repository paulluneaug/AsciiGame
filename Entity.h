#pragma once

#include "Level.h"

class Entity
{
public:
	virtual bool Move(int dx, int dy, Level level);
	virtual bool CanMoveTo(int dx, int dy, Level level);

	Entity(int x,int y,char character);

protected:

	int _x;
	int _y;
	char _character;
	bool _canMove;
};

