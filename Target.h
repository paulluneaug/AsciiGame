#pragma once

#include "Entity.h"

class Level;

class Target : public Entity
{
public:
	Target(int x, int y, WCHAR character, WORD color, Level& level);

	void OnEnter();
	void OnExit();

	bool IsBoxOnTop();

private:
	bool m_boxOnTop;
	Level& m_level;
};