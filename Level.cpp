#include "Level.h"

#include "Box.h"
#include "Target.h"

const unsigned char Level::AIR_TILE = 0;
const unsigned char Level::WALL_TILE = 1;
const unsigned char Level::INVALID_TILE = 255;

Level::Level(const std::string& r_path)
{
	LoadLevelAtPath(r_path);
}

Level::~Level()
{
	delete m_terrain;

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
	return 0 <= x && x < m_width
		&& 0 <= y && y < m_height;
}

unsigned char Level::GetTileAtCoordinates(int x, int y) const
{
	if (IsInBound(x, y))
	{
		//return m_terrain[x + y * m_width];
	}
	return INVALID_TILE;
}

Player& const Level::GetPlayer()
{
	return m_player;
}

std::vector<Entity*>& const Level::GetEntities()
{
	return m_entities;
}

void Level::LoadLevelAtPath(const std::string& r_path)
{
	std::ifstream levelFile(r_path);
	std::string line;

	levelFile >> m_width;
	levelFile >> m_height;

	std::cout << "Width = " << m_width << "\n" << "Height = " << m_height << std::endl;

	m_terrain = new unsigned char[m_width * m_height]();
	//m_entities = std::vector<std::unique_ptr<Entity>>(3);

	int iLine = 0;
	while (!levelFile.eof()) 
	{
		if (iLine >= m_height)
		{
			std::cout << "Invalid file datas (" << r_path << ") : The given height is smaller than the actual grid's height" << std::endl;
			return;
		}

		std::getline(levelFile, line);
		std::cout << "Reading Line " << line << std::endl;

		int iChar = 0;
		for (char tileChar : line) 
		{
			if (iChar >= m_width) 
			{
				std::cout << "Invalid file datas (" << r_path << ") : The given width is smaller than the actual grid's width";
				return;
			}
			m_terrain[iChar + iLine * m_width] = GetTileFromChar(tileChar);
			AddEntityAtIfNeeded(iChar, iLine, tileChar);
			++iChar;
		}
		++iLine;
	}

}

unsigned char Level::GetTileFromChar(char c)
{
	switch (c)
	{
	case '#':
		return WALL_TILE;
	case ' ':
		return AIR_TILE;
	default:
		return AIR_TILE;
	}
}

bool Level::AddEntityAtIfNeeded(int x, int y, char entityChar)
{
	Entity* newEntity;// = nullptr;
	switch (entityChar)
	{
	case 'P':
		m_player = Player();
		return true;
	case 'B':
		newEntity = new Box();
	case 'T':
		newEntity = new Target();
	default:
		return false;
	}

	m_entities.push_back(newEntity);
	return true;
}
