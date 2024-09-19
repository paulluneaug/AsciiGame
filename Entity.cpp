#include "Entity.h"

Entity::Entity(int x, int y, WCHAR character, WORD color) :
	m_x(x),
	m_y(y),
	m_character(character),
	m_canMove(true),
	m_canDraw(true),
	m_color(color)
{
}


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
