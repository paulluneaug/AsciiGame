#pragma once

#include "Entity.h"

class Target : public Entity
{
public:
	Target(int x, int y, WCHAR character, WORD color);

	void OnEnter();
	void OnExit();

	bool IsBoxOnTop();

private:
	bool m_boxOnTop;
};