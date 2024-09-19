#include "Entity.h"
#include "TriggerEntity.h"
#include "Door.h"

Entity::Entity(int x, int y, WCHAR character, WORD color) :
	m_x(x),
	m_y(y),
	m_character(character),
	m_canMove(true),
	m_canDraw(true),
	m_color(color)
{
}


bool Entity::Move(int dx, int dy, const Grid& grid, const std::vector<Entity*>& r_allEntities)
{
	if (!m_canMove) return false;

	if (!CanMoveTo(dx,dy,grid, r_allEntities)) {
		return false;
	}

	m_x += dx;
	m_y += dy;

	TriggerEntity* triggerEntity;
	for (Entity* entity : r_allEntities) {
		triggerEntity = dynamic_cast<TriggerEntity*>(entity);
		if (triggerEntity != nullptr && entity->GetX() == m_x && entity->GetY() == m_y) {
			triggerEntity->OnEnter(this);
			break;
		}
	}

	return true;
}

int Entity::GetX() const
{
	return m_x;
}

int Entity::GetY() const
{
	return m_y;
}

WCHAR Entity::GetChar() const
{
	return m_character;
}

bool Entity::CanDraw() const
{
	return m_canDraw;
}

WORD Entity::GetColor() const
{
	return m_color;
}

void Entity::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

void Entity::SetDrawable(bool canDraw)
{
	m_canDraw = canDraw;
}

bool Entity::CanMoveTo(int dx, int dy, const Grid& r_grid, const std::vector<Entity*>& r_allEntities) const
{
	int newX = m_x + dx;
	int newY = m_y + dy;
	
	if (!Door::open) {
		for (Entity* entity : r_allEntities)
		{
			if (newX != entity->GetX() || newY != entity->GetY()) continue;

			if (dynamic_cast<Door*>(entity)) {
				return false;
			}
			break;
		}
	}


	return r_grid.IsInBound(newX, newY) && r_grid.GetTileAtCoordinates(newX, newY) != Grid::WALL_TILE;
}

void Entity::Update()
{
}
