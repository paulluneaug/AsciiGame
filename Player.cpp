#include "Player.h"

Player::Player(int x, int y, DoubleWChar character) : 
	Entity(x, y, character)
{
}

bool Player::Move(int dx, int dy, const Grid& r_grid, const std::vector<Entity*>& r_allEntities)
{
	if (Entity::Move(dx, dy, r_grid, r_allEntities)) {

		for (Entity* entity : r_allEntities) {
			if (dynamic_cast<Box*>(entity) != nullptr && entity->GetX() == m_x && entity->GetY() == m_y) {
				entity->Move(dx, dy, r_grid, r_allEntities);
				break;
			}
		}

		return true;
	}

	return false;
}

bool Player::CanMoveTo(int dx, int dy, const Grid& r_grid, const std::vector<Entity*>& r_allEntities) const
{
	if (!Entity::CanMoveTo(dx, dy, r_grid, r_allEntities)) return false;

	int nextX = m_x + dx;
	int nextY = m_y + dy;

	for (Entity* entity : r_allEntities) {
		if (dynamic_cast<Box*>(entity) != nullptr && entity->GetX() == nextX && entity->GetY() == nextY) {
			return entity->CanMoveTo(dx, dy, r_grid, r_allEntities);
		}
	}

	return true;
}


