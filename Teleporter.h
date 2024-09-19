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
	/// <param name="character">The teleporter's characters and color</param>
	/// <param name="number">The teleporter's number</param>
	Teleporter(int x, int y, DoubleWChar character, int number);

	/// <summary>
	/// Sets the teleporter's linked teleporter
	/// </summary>
	/// <param name="linkedTeleporter">The linked teleporter</param>
	void SetLinkedTeleporter(Teleporter* linkedTeleporter);


	/// <summary>
	/// Teleports an entity to the teleporter
	/// </summary>
	/// <param name="entity">The entity to teleport</param>
	void TeleportEntity(Entity* entity);


	/// <summary>
	/// Called when an entity walks on the teleporter
	/// </summary>
	/// <param name="entity">The entity that is now on top</param>
	virtual void OnEnter(Entity* entity) override;

	/// <summary>
	/// Called when an entity leaves the target
	/// </summary>
	/// <param name="entity">The entity that leaved the teleporter</param>
	virtual void OnExit(Entity* entity) override;

private:

	int m_number;
	Teleporter* m_linkedTeleporter;
};

