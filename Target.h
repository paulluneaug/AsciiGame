#pragma once

#include "TriggerEntity.h"

class Level;

/// <summary>
/// Represents a target
/// </summary>
class Target : public TriggerEntity
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
	/// Called when an entity walks on the target
	/// </summary>
	/// <param name="entity">The entity that is now on top</param>
	virtual void OnEnter(Entity* entity) override;

	/// <summary>
	/// Called when an entity leaves the target
	/// </summary>
	/// <param name="entity">The entity that leaved the target</param>
	virtual void OnExit(Entity* entity) override;

private:
	Level& m_level;
};