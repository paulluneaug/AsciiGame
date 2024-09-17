#pragma once

#include "Entity.h"
#include "Box.h"

class Player : public Entity
{
public:
	Player(int x, int y, WCHAR character);
	bool Move(int dx, int dy, Level& const level) override;
	bool CanMoveTo(int dx, int dy, Level& const level) override;
};

