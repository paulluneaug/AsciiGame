#include "Player.h"

Player::Player(int x, int y, char character) : Entity(x,y,character)
{
}

bool Player::Move(int dx, int dy, Level level)
{
	if (Entity::Move(dx, dy, level)) {
		// for sur les entities de level
		// On cherche les boites qui sont sur (x,y)
		// On les bouges
		// Ok c'est moche

		return true;
	}

	return false;
}

bool Player::CanMoveTo(int dx, int dy, Level level)
{
	bool result = Entity::CanMoveTo(dx, dy, level);
	if (!result) return result;

	// for sur les entities de level
	// On cherche une boite qui est sur (x,y) et on appelle CanMoveTo(dx,dy,level)

	return result;
}


