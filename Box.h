#pragma once

#include "Entity.h"
#include "Target.h"

class Box : public Entity
{
public:
	Box(int x, int y, WCHAR character, WORD color);
	bool Move(int dx, int dy, const Grid& r_grid, const std::vector<Entity*>& r_allEntities) override;
	bool CanMoveTo(int dx, int dy, const Grid& r_grid, const std::vector<Entity*>& r_allEntities) const override;

private:
	Target* m_currentTarget;
};

