#include "Level.h"

#include "Box.h"
#include "Target.h"

Level::Level() : m_player(0, 0, 'P'), m_grid(0, 0)
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

const Player& Level::GetPlayer()
{
	return m_player;
}

const std::vector<Entity*>& Level::GetEntities()
{
	return m_entities;
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

	levelFile >> width;
	levelFile >> height;


	std::cout << "Width = " << width << "\n" << "Height = " << height << std::endl;

	m_grid = Grid(width, height);
	//m_entities = std::vector<std::unique_ptr<Entity>>(3);

	int iLine = 0;
	while (!levelFile.eof())
	{
		if (iLine >= height)
		{
			std::cout << "Invalid file datas (" << r_path << ") : The given height is smaller than the actual grid's height" << std::endl;
			return;
		}

		std::getline(levelFile, line);
		std::cout << "Reading Line " << line << std::endl;

		int iChar = 0;
		for (char tileChar : line)
		{
			if (iChar >= width)
			{
				std::cout << "Invalid file datas (" << r_path << ") : The given width is smaller than the actual grid's width";
				return;
			}

			m_grid.SetTile(iChar, iLine, tileChar);

			AddEntityAtIfNeeded(iChar, iLine, tileChar);
			++iChar;
		}
		++iLine;
	}

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
	case 'T':
		newEntity = new Target(x, y, 'T');
	default:
		return false;
	}

	m_entities.push_back(newEntity);
	return true;
}
