#include "Target.h"

Target::Target(int x, int y, char character) : Entity(x,y,character)
{
    _boxOnTop = false;
}



void Target::OnEnter()
{
    _boxOnTop = true;
}

void Target::OnExit()
{
    _boxOnTop = false;
}
