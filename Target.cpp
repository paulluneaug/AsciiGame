#include "Target.h"

Target::Target(int x, int y, WCHAR character) : Entity(x,y,character)
{
    m_boxOnTop = false;
}

void Target::OnEnter()
{
    m_boxOnTop = true;
}

void Target::OnExit()
{
    m_boxOnTop = false;
}

bool Target::IsBoxOnTop()
{
    return m_boxOnTop;
}
