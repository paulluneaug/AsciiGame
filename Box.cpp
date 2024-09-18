#include "Box.h"

Box::Box(int x, int y, WCHAR character, WORD color) : Entity(x,y,character,color)
{
	m_currentTarget = nullptr;
}

bool Box::Move(int dx, int dy, const Grid& r_grid, const std::vector<Entity*>& r_allEntities)
{
	if (Entity::Move(dx, dy, r_grid, r_allEntities)) {

		if (m_currentTarget != nullptr) {
			m_currentTarget->OnExit();
		}

		Target* target;
		for (Entity* entity : r_allEntities) {
			target = dynamic_cast<Target*>(entity);
			if (target != nullptr  && entity->GetX() == m_x && entity->GetY() == m_y) {
				target->OnEnter();
				m_currentTarget = target;
				break;
			}
		}
		return true;
	}
	return false;
}

bool Box::CanMoveTo(int dx, int dy, const Grid& level, const std::vector<Entity*>& r_allEntities) const
{
	if (!Entity::CanMoveTo(dx, dy, level, r_allEntities)) return false;

	int nextX = m_x + dx;
	int nextY = m_y + dy;

	for (Entity* entity : r_allEntities) {
		if (dynamic_cast<Box*>(entity) != nullptr && entity->GetX() == nextX && entity->GetY() == nextY) {
			return false;
		}
	}

	return true;
}
