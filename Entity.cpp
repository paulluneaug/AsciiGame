#include "Entity.h"
#include "TriggerEntity.h"

Entity::Entity(int x, int y, DoubleWChar character) : 
	m_x(x), 
	m_y(y), 
	m_character(character),
	m_canMove(true),
	m_canDraw(true)
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

const DoubleWChar& Entity::GetChars() const
{
	return m_character;
}

bool Entity::CanDraw() const
{
	return m_canDraw;
}

void Entity::SetPosition(int x, int y)
{
	m_x = x;
	m_y = y;
}

bool Entity::CanMoveTo(int dx, int dy, const Grid& r_grid, const std::vector<Entity*>& r_allEntities) const
{
	int newX = m_x + dx;
	int newY = m_y + dy;
	return r_grid.IsInBound(newX, newY) && r_grid.GetTileAtCoordinates(newX, newY) != Grid::WALL_TILE;
}

void Entity::Update()
{
}
