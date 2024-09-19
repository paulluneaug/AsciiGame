#include "Teleporter.h"
#include <assert.h>

Teleporter::Teleporter(int x, int y, DoubleWChar character, int number)
	: TriggerEntity(x, y, character),
	m_number(number),
	m_linkedTeleporter(nullptr)
{
	m_canMove = false;
}

void Teleporter::SetLinkedTeleporter(Teleporter* linkedTeleporter)
{
	m_linkedTeleporter = linkedTeleporter;
}

void Teleporter::TeleportEntity(Entity* entity)
{
	entity->SetPosition(m_x, m_y);
	SetEntityOnTop(entity);
}

void Teleporter::OnEnter(Entity* entity)
{
	assert(m_linkedTeleporter != nullptr);

	if (!m_linkedTeleporter->IsEntityOnTop() && !IsEntityOnTop()) {
		m_linkedTeleporter->TeleportEntity(entity);
	}
}

void Teleporter::OnExit(Entity* entity)
{
	TriggerEntity::OnExit(entity);
}
