#pragma once
#include "Grid.h"
#include "Windows.h"
#include <vector>

class Entity
{
public:
	virtual bool Move(int dx, int dy, const Grid& r_grid, const std::vector<Entity*>& r_allEntities);
	virtual bool CanMoveTo(int dx, int dy, const Grid& r_grid, const std::vector<Entity*>& r_allEntities) const;

	Entity(int x, int y, WCHAR character, WORD color);

	int GetX() const;
	int GetY() const;
	WCHAR GetChar() const;
	bool CanDraw() const;
	WORD GetColor() const;

protected:

	bool m_canDraw;
	int m_x;
	int m_y;
	WCHAR m_character;
	bool m_canMove;
	WORD m_color;
};

