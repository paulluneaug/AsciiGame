#include "Target.h"

Target::Target(int x, int y, WCHAR character) : Entity(x,y,character)
{
    m_boxOnTop = false;
}

void Target::OnEnter()
{
    m_boxOnTop = true;
    m_canDraw = false;
}

void Target::OnExit()
{
    m_boxOnTop = false;
    m_canDraw = true;
}

bool Target::IsBoxOnTop()
{
    return m_boxOnTop;
}
