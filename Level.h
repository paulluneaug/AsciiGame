#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Entity.h"
#include "Player.h"


class Level
{
private:
	Grid m_grid;

	std::vector<Entity*> m_entities;
	Player m_player;

public:
	Level();
	~Level();

	void LoadLevelAtPath(const std::string& r_path);

	bool IsInBound(int x, int y) const;
	unsigned char GetTileAtCoordinates(int x, int y) const;
	
	const Player& GetPlayer() const;
	const std::vector<Entity*>& GetEntities() const;

	const Grid& GetGrid() const;

private:
	bool AddEntityAtIfNeeded(int x, int y, char entityChar);



};