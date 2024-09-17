#pragma once

#include "Level.h"
#include "Windows.h"

class Entity
{
public:
	virtual bool Move(int dx, int dy, Level& const level);
	virtual bool CanMoveTo(int dx, int dy, Level& const level);

	Entity(int x,int y,WCHAR character);

	int GetX();
	int GetY();

protected:

	int _x;
	int _y;
	WCHAR _character;
	bool _canMove;
};

