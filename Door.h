#pragma once

#include "Entity.h"

/// <summary>
/// Represents a door that must be opened with a key
/// </summary>
class Door : public Entity
{
public:
	/// <summary>
	/// Creates a door
	/// </summary>
	/// <param name="x">The door's x position</param>
	/// <param name="y">The door's y position</param>
	/// <param name="character">The door's character</param>
	Door(int x, int y, DoubleWChar character);

	/// <summary>
	/// Updates the door
	/// </summary>
	void Update() override;

public:
	static bool open;

};

