#include "Door.h"

bool Door::open = false;

Door::Door(int x, int y, WCHAR character, WORD color)
	:Entity(x,y,character,color)
{
}

void Door::Update()
{
	if (m_canDraw && open) {
		m_canDraw = false;
	}
}
