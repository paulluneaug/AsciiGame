#include "Teleporter.h"

Teleporter::Teleporter(int x, int y, WCHAR character, WORD color, int number)
	: TriggerEntity(x, y, character, color),
	m_number(number),
	m_linkedTeleporter(nullptr)
{
	m_canMove = false;
}
