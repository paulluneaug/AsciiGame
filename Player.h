#pragma once

#include "Entity.h"

class Player : public Entity
{
public:
	Player(int x, int y, char character);
	bool Move(int dx, int dy, Level level) override;
	bool CanMoveTo(int dx, int dy, Level level) override;
};

