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
	Grid* m_grid;

	std::vector<Entity*> m_entities;
	Player* m_player;

	bool m_loaded;

public:
	Level();
	Level(const std::string& r_path);
	~Level();

	void LoadLevelAtPath(const std::string& r_path);

	bool IsInBound(int x, int y) const;
	unsigned char GetTileAtCoordinates(int x, int y) const;
	
	Player& GetPlayer();
	const std::vector<Entity*>& GetEntities() const;

	const Grid& GetGrid() const;

private:
	bool AddEntityAtIfNeeded(int x, int y, char entityChar);

};