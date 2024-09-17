#include "Box.h"

Box::Box(int x, int y, WCHAR character) : Entity(x,y,character)
{
	_currentTarget = nullptr;
}

bool Box::Move(int dx, int dy, Level& const level)
{
	if (Entity::Move(dx, dy, level)) {

		if (_currentTarget != nullptr) {
			_currentTarget->OnExit();
		}

		std::vector<Entity*>& const entities = level.GetEntities();
		Target* target;
		for (Entity* entity : entities) {
			target = dynamic_cast<Target*>(entity);
			if (target != nullptr  && entity->GetX() == _x && entity->GetY() == _y) {
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

	int nextX = _x + dx;
	int nextY = _y + dy;

	std::vector<Entity*>& const entities = level.GetEntities();
	for (Entity* entity : entities) {
		if (dynamic_cast<Box*>(entity) != nullptr && entity->GetX() == nextX && entity->GetY() == nextY) {
			return false;
		}
	}

	return true;
}
