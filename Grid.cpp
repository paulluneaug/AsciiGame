#include "Grid.h"
#include "Box.h"

const unsigned char Grid::AIR_TILE = ' ';
const unsigned char Grid::WALL_TILE = '#';
const unsigned char Grid::INVALID_TILE = '?';

Grid::Grid(int width, int height) : m_width(width), m_height(height)
{
	m_terrain = new unsigned char[width * height];
}

Grid::~Grid()
{
	delete m_terrain;
}

int Grid::GetHeight() const
{
	return m_height;
}

int Grid::GetWidth() const
{
	return m_width;
}

bool Grid::IsInBound(int x, int y) const
{
	return 0 <= x && x < m_width
		&& 0 <= y && y < m_height;
}

unsigned char Grid::GetTileAtCoordinates(int x, int y) const
{
	if (IsInBound(x, y))
	{
		return GetTileFromChar(m_terrain[x + y * m_width]);
	}
	return INVALID_TILE;
}

void Grid::SetTile(int x, int y, char newChar)
{
	m_terrain[x + y * m_width] = GetTileFromChar(newChar);
}

unsigned char Grid::GetTileFromChar(char c) const
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