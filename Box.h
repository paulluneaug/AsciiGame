#pragma once

#include "Entity.h"
#include "Target.h"

class Box : public Entity
{
public:
	Box(int x, int y, char character);
	bool Move(int dx, int dy, Level level) override;
	bool CanMoveTo(int dx, int dy, Level level) override;

private:
	Target* _currentTarget;
};

