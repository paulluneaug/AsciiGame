#include "Entity.h"

bool Entity::Move(int dx, int dy, const Grid& grid, const std::vector<Entity*>& r_allEntities)
{
	if (!m_canMove) return false;

	if (!CanMoveTo(dx,dy,grid, r_allEntities)) {
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

int Entity::GetX() const
{
	return m_x;
}

int Entity::GetY() const
{
	return m_y;
}

WCHAR Entity::GetChar() const
{
	return m_character;
}

bool Entity::CanMoveTo(int dx, int dy, const Grid& level, const std::vector<Entity*>& r_allEntities)
{
	return level.IsInBound(m_x + dx, m_y + dy);
}
