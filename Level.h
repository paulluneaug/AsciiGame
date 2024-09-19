#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include "Entity.h"
#include "Player.h"

/// <summary>
/// Represents a level
/// </summary>
class Level
{
private:
	Grid* m_grid;

	std::vector<Entity*> m_entities;
	Player* m_player;

	bool m_loaded;
	bool m_foundLevelFile;

	int m_currentActivatedTargets;
	int m_maxTargets;

public:

	/// <summary>
	/// Creates a level
	/// </summary>
	Level();
	Level(const std::string& r_path);

	/// <summary>
	/// Destroy the level
	/// </summary>
	~Level();

	/// <summary>
	/// Loads a level
	/// </summary>
	/// <param name="r_path">The level's filename</param>
	void LoadLevelAtPath(const std::string& r_path);

	/// <summary>
	/// Checks if the coordinates are within the level's bounds
	/// </summary>
	/// <param name="x">The x coordinate</param>
	/// <param name="y">The y coordinate</param>
	/// <returns>True if the coordinates are within the level's bounds</returns>
	bool IsInBound(int x, int y) const;

	/// <summary>
	/// Gets a tile
	/// </summary>
	/// <param name="x">The tile's x coordinate</param>
	/// <param name="y">The tile's y coordinate</param>
	/// <returns>The tile</returns>
	unsigned char GetTileAtCoordinates(int x, int y) const;

	/// <summary>
	/// Gets the player
	/// </summary>
	/// <returns>The player</returns>
	Player& GetPlayer();

	/// <summary>
	/// Gets the level's entities
	/// </summary>
	/// <returns>The level's entities</returns>
	const std::vector<Entity*>& GetEntities() const;

	/// <summary>
	/// Gets the level's grid
	/// </summary>
	/// <returns>The grid</returns>
	const Grid& GetGrid() const;

	/// <summary>
	/// Registers an activated target
	/// </summary>
	void RegisterActivatedTarget();

	/// <summary>
	/// Unregister an activated target
	/// </summary>
	void UnregisterActivatedTarget();

	/// <summary>
	/// Checks if the level is finished
	/// </summary>
	/// <returns>True if the level is finished</returns>
	bool HasFinishedLevel() const;

	/// <summary>
	/// 
	/// </summary>
	/// <returns>True if the level file was found</returns>
	bool HasFoundLevelFile() const;

private:

	/// <summary>
	/// Checks if an entity has to be created, and creates it if needed
	/// </summary>
	/// <param name="x">The entity's x position</param>
	/// <param name="y">The entity's y position</param>
	/// <param name="entityChar">The linked character</param>
	/// <returns>True if an entity was created</returns>
	bool AddEntityAtIfNeeded(int x, int y, char entityChar);

};