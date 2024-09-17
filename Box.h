#pragma once

#include "Entity.h"
#include "Target.h"

class Box : public Entity
{
public:
	Box(int x, int y, WCHAR character);
	bool Move(int dx, int dy, Level& const level) override;
	bool CanMoveTo(int dx, int dy, Level& const level) override;

private:
	Target* m_currentTarget;
};

