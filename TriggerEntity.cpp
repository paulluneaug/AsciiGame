#include "TriggerEntity.h"

TriggerEntity::TriggerEntity(int x, int y, WCHAR character, WORD color)
    : Entity(x,y,character,color)
    ,m_entityOnTop(nullptr)
{
}

void TriggerEntity::OnEnter(Entity* entity)
{
    m_canDraw = false;
    m_entityOnTop = entity;
}

void TriggerEntity::OnExit(Entity* entity)
{
    if (m_entityOnTop == entity && entity != nullptr) {
        m_canDraw = true;
        m_entityOnTop = nullptr;
    }
}

Entity* TriggerEntity::GetEntityOnTop()
{
    return m_entityOnTop;
}

bool TriggerEntity::IsEntityOnTop()
{
    return m_entityOnTop != nullptr;
}
