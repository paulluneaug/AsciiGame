#include "Level.h"

#include <cassert>
#include <sstream>

#include "Box.h"
#include "Target.h"

Level::Level() :
	m_player(nullptr),
	m_grid(nullptr),
	m_loaded(false)
{
}

Level::Level(const std::string& r_path) : Level::Level()
{
	LoadLevelAtPath(r_path);
}

Level::~Level()
{
	if (m_grid != nullptr)
	{
		delete m_grid;
	}

	for (Entity* entity : m_entities)
	{
		if (entity != nullptr)
		{
			delete entity;
		}
	}
	m_loaded = false;

	delete m_player;
}

bool Level::IsInBound(int x, int y) const
{
	return m_grid->IsInBound(x, y);
}

unsigned char Level::GetTileAtCoordinates(int x, int y) const
{
	return m_grid->GetTileAtCoordinates(x, y);
}

Player& Level::GetPlayer()
{
	assert(m_loaded);
	return *m_player;
}

const std::vector<Entity*>& Level::GetEntities() const
{
	assert(m_loaded);
	return m_entities;
}

const Grid& Level::GetGrid() const
{
	assert(m_loaded);
	return *m_grid;
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

	if (m_grid != nullptr) {
		delete m_grid;
	}
	m_grid = new Grid(width, height);

	// Goes through the rest of the file
	int iLine = 0;
	while (!levelFile.eof())
	{
		if (iLine >= height)
		{
			std::cout << "Invalid file datas (" << r_path << ") : The given height is smaller than the actual grid's height" << std::endl;
			return;
		}

		std::getline(levelFile, line);

		int iChar = 0;
		for (char tileChar : line)
		{
			if (iChar >= width)
			{
				std::cout << "Invalid file datas (" << r_path << ") : The given width is smaller than the actual grid's width";
				return;
			}

			m_grid->SetTile(iChar, iLine, tileChar);

			AddEntityAtIfNeeded(iChar, iLine, tileChar);
			++iChar;
		}
		++iLine;
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
		m_player = new Player(x, y, 'P');
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
