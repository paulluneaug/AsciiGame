#pragma once

#include "Entity.h"
#include "Target.h"

/// <summary>
/// Represents a box that can be moved by the player
/// </summary>
class Box : public Entity
{
public:

	/// <summary>
	/// Creates a box
	/// </summary>
	/// <param name="x">The box's x position</param>
	/// <param name="y">The box's y position</param>
	/// <param name="character">The box's character</param>
	Box(int x, int y, DoubleWChar character);

	/// <summary>
	/// Moves the box in the specified direction if possible
	/// </summary>
	/// <param name="dx">Delta X</param>
	/// <param name="dy">Delta Y</param>
	/// <param name="r_grid">The current level's grid</param>
	/// <param name="r_allEntities">The current level's entities</param>
	/// <returns>True if the box was able to move</returns>
	bool Move(int dx, int dy, const Grid& r_grid, const std::vector<Entity*>& r_allEntities) override;

	/// <summary>
	/// Computes if the box can move in a direction
	/// </summary>
	/// <param name="dx">Delta X</param>
	/// <param name="dy">Delta Y</param>
	/// <param name="r_grid">The current level's grid</param>
	/// <param name="r_allEntities">The current level's entities</param>
	/// <returns>True if the box can move</returns>
	bool CanMoveTo(int dx, int dy, const Grid& r_grid, const std::vector<Entity*>& r_allEntities) const override;

private:
	Target* m_currentTarget;
};

