#include "Target.h"
#include "Level.h"

Target::Target(int x, int y, WCHAR character, WORD color, Level& level) : 
    TriggerEntity(x,y,character,color), 
    m_level(level)
{
    m_canMove = false;
}

void Target::OnEnter(Entity* entity)
{
    TriggerEntity::OnEnter(entity);
    if (dynamic_cast<Box*>(entity) != nullptr) {
        m_level.RegisterActivatedTarget();
    }
}

void Target::OnExit(Entity* entity)
{
    TriggerEntity::OnExit(entity);
    if (dynamic_cast<Box*>(entity) != nullptr) {
        m_level.UnregisterActivatedTarget();
    }
}