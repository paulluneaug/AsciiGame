#include "Key.h"
#include "Player.h"
#include "Door.h"

Key::Key(int x, int y, DoubleWChar character)
	:TriggerEntity(x,y,character)
{
	m_canDraw = true;
}

void Key::OnEnter(Entity* entity)
{
	if (m_canDraw && dynamic_cast<Player*>(entity) != nullptr) {
		m_canDraw = false;
		Door::open = true;
	}
}
