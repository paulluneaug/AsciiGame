#include "Level.h"

#include <sstream>
#include <cassert>

#include "Box.h"
#include "Target.h"

Level::Level() : 
	m_player(0, 0, 'P'),
	m_grid(0, 0),
	m_loaded(false)
{
}

Level::~Level()
{
	for (Entity* entity : m_entities)
	{
		if (entity != NULL)
		{
			delete entity;
		}
	}
}

bool Level::IsInBound(int x, int y) const
{
	return m_grid.IsInBound(x, y);
}

unsigned char Level::GetTileAtCoordinates(int x, int y) const
{
	return m_grid.GetTileAtCoordinates(x, y);
}

Player& Level::GetPlayer()
{
	assert(m_loaded);
	return m_player;
}

const std::vector<Entity*>& Level::GetEntities() const
{
	assert(m_loaded);
	return m_entities;
}

const Grid& Level::GetGrid() const
{
	assert(m_loaded);
	return m_grid;
}


void Level::LoadLevelAtPath(const std::string& r_path)
{
	std::ifstream levelFile(r_path);
	std::string line;

	if (levelFile.fail()) {
		std::cout << "Can't find level at path = " << r_path << std::endl;
		return;
	}

	int width, height;
	std::getline(levelFile, line); // The first line contains the dimensions of the grid

	// Parses the line 
	std::stringstream sStream = std::stringstream();
	sStream << line;

	sStream >> width;
	sStream >> height;

	m_grid = Grid(width, height);

	// Goes through the rest of the file
	for(int iLine = 0; iLine < height;iLine++)
	{
		if (iLine < height) {
			std::getline(levelFile, line);
		}

		for(int iChar = 0; iChar < width; iChar++){
			m_grid.SetTile(iChar, iLine, line[iChar]);
			AddEntityAtIfNeeded(iChar, iLine, line[iChar]);
		}
	}

	levelFile.close();

	m_loaded = true;
}

bool Level::AddEntityAtIfNeeded(int x, int y, char entityChar)
{
	Entity* newEntity = nullptr;
	switch (entityChar)
	{
	case 'P':
		m_player = Player(x, y, 'P');
		return true;
	case 'B':
		newEntity = new Box(x, y, 'B');
		break;
	case 'T':
		newEntity = new Target(x, y, 'T');
		break;
	default:
		return false;
	}

	if (newEntity != nullptr) {
		m_entities.push_back(newEntity);
	}
	
	return true;
}
