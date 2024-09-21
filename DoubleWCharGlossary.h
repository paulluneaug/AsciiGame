#pragma once
#include "DoubleWChar.h"
#include "ColorGlossary.h"

/// <summary>
/// Represents the game's DoubleWChar
/// One entity uses one DoubleWChar to be drawn
/// </summary>
class DoubleWCharGlossary
{
public:
	const static DoubleWChar& OOB_TILE_CHAR;
	const static DoubleWChar& WALL_TILE_CHAR;
	const static DoubleWChar& EMPTY_TILE_CHAR;
	const static DoubleWChar& PLAYER_CHAR;
	const static DoubleWChar& BOX_CHAR;
	const static DoubleWChar& TARGET_CHAR;
	const static DoubleWChar& KEY_CHAR;
	const static DoubleWChar& DOOR_CHAR;
};

