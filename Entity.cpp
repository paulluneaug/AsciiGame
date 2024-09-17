#include "Entity.h"

bool Entity::Move(int dx, int dy, Level level)
{
	if (!_canMove) return;

	if (!CanMoveTo(dx,dy,level)) {
		return;
	}

	this->_x += dx;
	this->_y += dy;
}

Entity::Entity(int x, int y, char character)
{
	this->_x = x;
	this->_y = y;
	this->_character = character;
	this->_canMove = true;
}

bool Entity::CanMoveTo(int dx, int dy, Level level)
{
	return true /*level.IsWall(_x + dx, _y + dy) */;
}
