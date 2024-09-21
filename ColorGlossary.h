#pragma once
#include "Windows.h"

/// <summary>
/// Represents the game' colors
/// They are static and can be accessed anywhere
/// </summary>
class ColorGlossary
{
public:
	static const WORD OOB_COLOR = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN;
	static const WORD BACKGROUND_COLOR = BACKGROUND_RED;
	static const WORD EMPTY_TILE_COLOR = BACKGROUND_COLOR;
	static const WORD WALL_TILE_COLOR = BACKGROUND_GREEN | BACKGROUND_RED;
	static const WORD PLAYER_COLOR = BACKGROUND_COLOR;
	static const WORD BOX_COLOR = BACKGROUND_COLOR;
	static const WORD TARGET_COLOR = BACKGROUND_COLOR;
	static const WORD TELEPORTER_COLOR = BACKGROUND_COLOR;
};

