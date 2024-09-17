#include "Box.h"

Box::Box(int x, int y, char character) : Entity(x,y,character)
{
	_currentTarget = nullptr;
}

bool Box::Move(int dx, int dy, Level level)
{
	if (Entity::Move(dx, dy, level)) {

		if (_currentTarget != nullptr) {
			_currentTarget->OnExit();
		}

		return true;

		// for sur les entities de level
		// On cherche une cible sur (x,y)
		// On l'active (OnEnter)
	}
	return false;
}

bool Box::CanMoveTo(int dx, int dy, Level level)
{
	bool result = Entity::CanMoveTo(dx, dy, level);
	if (!result) return result;

	// for sur les entities de level
	// On cherche une boite qui est sur (x,y) et on renvoie faux si on en trouve

	return result;
}
