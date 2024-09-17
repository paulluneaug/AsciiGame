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
public:
	static const unsigned char AIR_TILE;
	static const unsigned char WALL_TILE;
	static const unsigned char INVALID_TILE;

private:
	int m_width;
	int m_height;

	unsigned char* m_terrain;

	std::vector<Entity*> m_entities;
	Player m_player;

public:
	Level(const std::string& path);
	~Level();

	bool IsInBound(int x, int y) const;
	unsigned char GetTileAtCoordinates(int x, int y) const;
	
	Player& const GetPlayer();
	std::vector<Entity*>& const GetEntities();

private:
	void LoadLevelAtPath(const std::string& path);
	unsigned char GetTileFromChar(char c);
	bool AddEntityAtIfNeeded(int x, int y, char entityChar);



};