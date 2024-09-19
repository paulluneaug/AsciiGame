#pragma once

#include "TriggerEntity.h"

/// <summary>
/// Represents a key that opens doors
/// </summary>
class Key : public TriggerEntity
{
public:

	/// <summary>
	/// Creates a key
	/// </summary>
	/// <param name="x">The key's x position</param>
	/// <param name="y">The key's y position</param>
	/// <param name="character">The key's character</param>
	/// <param name="color">The key's color</param>
	Key(int x, int y, WCHAR character, WORD color);

	/// <summary>
	/// Called when an entity walks on the key
	/// </summary>
	/// <param name="entity">The entity that is now on top</param>
	virtual void OnEnter(Entity* entity) override;

private:
	bool m_pickedUp;
};

