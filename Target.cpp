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
    m_level.RegisterActivatedTarget();
}

void Target::OnExit(Entity* entity)
{
    TriggerEntity::OnExit(entity);
    m_level.UnregisterActivatedTarget();
}