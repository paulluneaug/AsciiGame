#include "Level.h"

#include <cassert>
#include <sstream>

#include "Box.h"
#include "Target.h"
#include "DoubleWCharGlossary.h"

Level::Level() :
	m_player(nullptr),
	m_grid(nullptr),
	m_loaded(false),
	m_currentActivatedTargets(0),
	m_maxTargets(0),
	m_foundLevelFile(false)
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

void Level::RegisterActivatedTarget()
{
	m_currentActivatedTargets = min(m_maxTargets, m_currentActivatedTargets + 1);
}

void Level::UnregisterActivatedTarget()
{
	m_currentActivatedTargets = max(0, m_currentActivatedTargets - 1);
}

bool Level::HasFinishedLevel() const
{
	return m_currentActivatedTargets == m_maxTargets;
}

bool Level::HasFoundLevelFile() const
{
	return m_foundLevelFile;
}


void Level::LoadLevelAtPath(const std::string& r_path)
{
	std::ifstream levelFile(r_path);
	std::string line;

	m_foundLevelFile = levelFile.good();
	if (!m_foundLevelFile) {
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
	m_maxTargets = 0;
	m_currentActivatedTargets = 0;

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
	levelFile.clear();

	m_loaded = true;
}

bool Level::AddEntityAtIfNeeded(int x, int y, char entityChar)
{
	Entity* newEntity = nullptr;
	switch (entityChar)
	{
	case 'P':
		m_player = new Player(x, y, DoubleWCharGlossary::PLAYER_CHAR);
		return true;
	case 'B':
		newEntity = new Box(x, y, DoubleWCharGlossary::BOX_CHAR);
		break;
	case 'T':
		newEntity = new Target(x, y, DoubleWCharGlossary::TARGET_CHAR, *this);
		m_maxTargets++;
		break;
	default:
		return false;
	}

	if (newEntity != nullptr) {
		m_entities.push_back(newEntity);
	}

	return true;
}
