#pragma once

#include "Entity.h"
#include "Box.h"

/// <summary>
/// Represents the player
/// </summary>
class Player : public Entity
{
public:

	/// <summary>
	/// Creates a player
	/// </summary>
	/// <param name="x">The player's x position</param>
	/// <param name="y">The player's y position</param>
	/// <param name="character">The player's character</param>
	/// <param name="color">The player's color</param>
	Player(int x, int y, WCHAR character, WORD color);

	/// <summary>
	/// Moves the player in the specified direction if possible
	/// </summary>
	/// <param name="dx">Delta X</param>
	/// <param name="dy">Delta Y</param>
	/// <param name="r_grid">The current level's grid</param>
	/// <param name="r_allEntities">The current level's entities</param>
	/// <returns>True if the player was able to move</returns>
	bool Move(int dx, int dy, const Grid& r_grid, const std::vector<Entity*>& r_allEntities) override;

	/// <summary>
	/// Computes if the player can move in a direction
	/// </summary>
	/// <param name="dx">Delta X</param>
	/// <param name="dy">Delta Y</param>
	/// <param name="r_grid">The current level's grid</param>
	/// <param name="r_allEntities">The current level's entities</param>
	/// <returns>True if the player can move</returns>
	bool CanMoveTo(int dx, int dy, const Grid& r_grid, const std::vector<Entity*>& r_allEntities) const override;
};

