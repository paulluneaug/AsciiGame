#pragma once

#include "TriggerEntity.h"

/// <summary>
/// Represents a teleporter
/// </summary>
class Teleporter : public TriggerEntity
{
public:

	/// <summary>
	/// Creates a teleporter
	/// </summary>
	/// <param name="x">The teleporter's x position</param>
	/// <param name="y">The teleporter's y position</param>
	/// <param name="character">The teleporter's character</param>
	/// <param name="color">The teleporter's color</param>
	/// <param name="number">The teleporter's number</param>
	Teleporter(int x, int y, WCHAR character, WORD color, int number);

private:

	int m_number;
	Entity* m_linkedTeleporter;
};

