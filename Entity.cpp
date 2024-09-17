#include "Entity.h"

bool Entity::Move(int dx, int dy, Level& const level)
{
	if (!_canMove) return false;

	if (!CanMoveTo(dx,dy,level)) {
		return false;
	}

	this->_x += dx;
	this->_y += dy;

	return true;
}

Entity::Entity(int x, int y, WCHAR character)
{
	this->_x = x;
	this->_y = y;
	this->_character = character;
	this->_canMove = true;
}

int Entity::GetX()
{
	return _x;
}

int Entity::GetY()
{
	return _y;
}

bool Entity::CanMoveTo(int dx, int dy, Level& const level)
{
	return level.IsInBound(_x + dx, _y + dy);
}
