#include "Level.h"
#include "Target.h"

Target::Target(int x, int y, DoubleWChar character, Level& level) : 
    TriggerEntity(x, y, character), 
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