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

Entity::Entity(int x, int y, WCHAR character, WORD color)
{
	this->m_x = x;
	this->m_y = y;
	this->m_character = character;
	this->m_canMove = true;
	this->m_canDraw = true;
	this->m_color = color;
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

bool Entity::CanDraw() const
{
	return m_canDraw;
}

WORD Entity::GetColor() const
{
	return m_color;
}

bool Entity::CanMoveTo(int dx, int dy, const Grid& r_grid, const std::vector<Entity*>& r_allEntities) const
{
	int newX = m_x + dx;
	int newY = m_y + dy;
	return r_grid.IsInBound(newX, newY) && r_grid.GetTileAtCoordinates(newX, newY) != Grid::WALL_TILE;
}
