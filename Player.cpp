#include "Player.h"

Player::Player(int x, int y, WCHAR character) : Entity(x,y,character)
{
}

bool Player::Move(int dx, int dy, Level& const level)
{
	if (Entity::Move(dx, dy, level)) {

		std::vector<Entity*>& const entities = level.GetEntities();
		for (Entity* entity : entities) {
			if (dynamic_cast<Box*>(entity) != nullptr && entity->GetX() == _x && entity->GetY() == _y) {
				entity->Move(dx, dy, level);
				break;
			}
		}

		return true;
	}

	return false;
}

bool Player::CanMoveTo(int dx, int dy, Level& const level)
{
	if (!Entity::CanMoveTo(dx, dy, level)) return false;

	int nextX = _x + dx;
	int nextY = _y + dy;

	std::vector<Entity*> & const entities = level.GetEntities();
	for (Entity* entity : entities) {
		if (dynamic_cast<Box*>(entity) != nullptr && entity->GetX() == nextX && entity->GetY() == nextY) {
			return entity->CanMoveTo(dx, dy, level);
		}
	}

	return true;
}


