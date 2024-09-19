#pragma once

#include "Entity.h"

class Level;

/// <summary>
/// Represents a target
/// </summary>
class Target : public Entity
{
public:
	/// <summary>
	/// Creates a target
	/// </summary>
	/// <param name="x">The target's x position</param>
	/// <param name="y">The target's y position</param>
	/// <param name="character">The target's character</param>
	/// <param name="color">The target's color</param>
	/// <param name="level">The level's reference</param>
	Target(int x, int y, DoubleWChar character, Level& level);

	/// <summary>
	/// Activate the target
	/// </summary>
	void OnEnter();

	/// <summary>
	/// Deactivate the target
	/// </summary>
	void OnExit();

	/// <summary>
	/// Checks if a box is on top of the target
	/// </summary>
	/// <returns>True if a box is on top of the target</returns>
	bool IsBoxOnTop();

private:
	bool m_boxOnTop;
	Level& m_level;
};