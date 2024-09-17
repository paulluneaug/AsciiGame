#include "Entity.h"

bool Entity::Move(int dx, int dy, Level& const level)
{
	if (!m_canMove) return false;

	if (!CanMoveTo(dx,dy,level)) {
		return false;
	}

	this->m_x += dx;
	this->m_y += dy;

	return true;
}

Entity::Entity(int x, int y, WCHAR character)
{
	this->m_x = x;
	this->m_y = y;
	this->m_character = character;
	this->m_canMove = true;
}

int Entity::GetX()
{
	return m_x;
}

int Entity::GetY()
{
	return m_y;
}

bool Entity::CanMoveTo(int dx, int dy, Level& const level)
{
	return level.IsInBound(m_x + dx, m_y + dy);
}
