#include "Box.h"

Box::Box(int x, int y, WCHAR character) : Entity(x,y,character)
{
	m_currentTarget = nullptr;
}

bool Box::Move(int dx, int dy, Level& const level)
{
	if (Entity::Move(dx, dy, level)) {

		if (m_currentTarget != nullptr) {
			m_currentTarget->OnExit();
		}

		std::vector<Entity*>& const entities = level.GetEntities();
		Target* target;
		for (Entity* entity : entities) {
			target = dynamic_cast<Target*>(entity);
			if (target != nullptr  && entity->GetX() == m_x && entity->GetY() == m_y) {
				target->OnEnter();
				break;
			}
		}
		return true;
	}
	return false;
}

bool Box::CanMoveTo(int dx, int dy, Level& const level)
{
	if (!Entity::CanMoveTo(dx, dy, level)) return false;

	int nextX = m_x + dx;
	int nextY = m_y + dy;

	std::vector<Entity*>& const entities = level.GetEntities();
	for (Entity* entity : entities) {
		if (dynamic_cast<Box*>(entity) != nullptr && entity->GetX() == nextX && entity->GetY() == nextY) {
			return false;
		}
	}

	return true;
}
