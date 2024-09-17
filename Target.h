#pragma once

#include "Entity.h"

class Target : public Entity
{
public:
	Target(int x, int y, char character);

	void OnEnter();
	void OnExit();

private:
	bool _boxOnTop;
};

