#pragma once

#include "Entity.h"
#include "Box.h"

class Player : public Entity
{
public:
	Player(int x, int y, WCHAR character);
	bool Move(int dx, int dy, const Grid& r_grid, const std::vector<Entity*>& r_allEntities) override;
	bool CanMoveTo(int dx, int dy, const Grid& r_grid, const std::vector<Entity*>& r_allEntities) const override;
};

