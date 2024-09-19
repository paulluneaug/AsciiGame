#include "Key.h"
#include "Player.h"
#include "Door.h"

Key::Key(int x, int y, WCHAR character, WORD color)
	:TriggerEntity(x,y,character,color),
	m_pickedUp(false)
{
}

void Key::OnEnter(Entity* entity)
{
	if (!m_pickedUp && dynamic_cast<Player*>(entity) != nullptr) {
		m_pickedUp = true;
		m_canDraw = false;

		Door::open = true;
	}
}
