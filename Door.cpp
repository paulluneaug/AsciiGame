#include "Door.h"

bool Door::open = false;

Door::Door(int x, int y, DoubleWChar character)
	:Entity(x,y,character)
{
}

void Door::Update()
{
	if (m_canDraw && open) {
		m_canDraw = false;
	}
}
