#pragma once
#include "Grid.h"
#include "Windows.h"
#include "DoubleWChar.h"
#include <vector>

/// <summary>
/// Represents an entity
/// </summary>
class Entity
{
public:

	/// <summary>
	/// Creates an entity
	/// </summary>
	/// <param name="x">The entity's x position</param>
	/// <param name="y">The entity's y position</param>
	/// <param name="character">The entity's character</param>
	/// <param name="color">The entity's color</param>
	Entity(int x, int y, DoubleWChar character);

	/// <summary>
	/// Moves the entity in the specified direction if possible
	/// </summary>
	/// <param name="dx">Delta X</param>
	/// <param name="dy">Delta Y</param>
	/// <param name="r_grid">The current level's grid</param>
	/// <param name="r_allEntities">The current level's entities</param>
	/// <returns>True if the entity was able to move</returns>
	virtual bool Move(int dx, int dy, const Grid& r_grid, const std::vector<Entity*>& r_allEntities);

	/// <summary>
	/// Computes if the entity can move in a direction
	/// </summary>
	/// <param name="dx">Delta X</param>
	/// <param name="dy">Delta Y</param>
	/// <param name="r_grid">The current level's grid</param>
	/// <param name="r_allEntities">The current level's entities</param>
	/// <returns>True if the entity can move</returns>
	virtual bool CanMoveTo(int dx, int dy, const Grid& r_grid, const std::vector<Entity*>& r_allEntities) const;

	/// <summary>
	/// Gets the entity's x position
	/// </summary>
	/// <returns>The entity's x position</returns>
	int GetX() const;
	
	/// <summary>
	/// Gets the entity's y position
	/// </summary>
	/// <returns>The entity's y position</returns>
	int GetY() const;
	
	/// <summary>
	/// Gets the entity's character
	/// </summary>
	/// <returns>The entity's character</returns>
	const DoubleWChar& GetChars() const;
	
	/// <summary>
	/// Gets if the entity can be drawn
	/// </summary>
	/// <returns>True if the entity is drawable</returns>
	bool CanDraw() const;

protected:

	bool m_canDraw;
	int m_x;
	int m_y;
	DoubleWChar m_character;
	bool m_canMove;
	WORD m_color;
};

