#include "Target.h"
#include "Level.h"

Target::Target(int x, int y, WCHAR character, WORD color, Level& level) : Entity(x,y,character,color), m_level(level)
{
    m_boxOnTop = false;
}

void Target::OnEnter()
{
    m_boxOnTop = true;
    m_canDraw = false;
    m_level.RegisterActivatedTarget();
}

void Target::OnExit()
{
    m_boxOnTop = false;
    m_canDraw = true;
    m_level.UnregisterActivatedTarget();
}

bool Target::IsBoxOnTop()
{
    return m_boxOnTop;
}
