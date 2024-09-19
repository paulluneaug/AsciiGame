#pragma once

#include "Entity.h"

/// <summary>
/// Represents an entity that can be triggered by another
/// </summary>
class TriggerEntity : public Entity
{
public:

	/// <summary>
	/// Creates a trigger entity
	/// </summary>
	/// <param name="x">The entity's x position</param>
	/// <param name="y">The entity's y position</param>
	/// <param name="character">The entity's character</param>
	/// <param name="color">The entity's color</param>
	TriggerEntity(int x, int y, WCHAR character, WORD color);

	/// <summary>
	/// Called when an entity walks on the trigger
	/// </summary>
	/// <param name="entity">The entity that is now on top</param>
	virtual void OnEnter(Entity* entity);

	/// <summary>
	/// Called when an entity leaves the trigger
	/// </summary>
	/// <param name="entity">The entity that leaved the trigger</param>
	virtual void OnExit(Entity* entity);

	/// <summary>
	/// Gets the entity that is on top of the trigger
	/// </summary>
	/// <returns>The entity that is on top</returns>
	Entity* GetEntityOnTop();
	
	/// <summary>
	/// Checks if there is an entity on top of the trigger
	/// </summary>
	/// <returns>True if there is an entity on top of the trigger</returns>
	bool IsEntityOnTop();

	/// <summary>
	/// Updates the trigger entity
	/// </summary>
	void Update() override;


protected:
	Entity* m_entityOnTop;
};

