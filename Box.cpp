#include "Box.h"

Box::Box(int x, int y, DoubleWChar character) : 
	Entity(x, y, character)
{
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
