#include "Grid.h"
#include "Box.h"
#include <iostream>


Grid::Grid(int width, int height) : m_width(width), m_height(height)
{
	m_terrain = new unsigned char[width * height]();
}

Grid::~Grid()
{
	delete[] m_terrain;
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
		return m_terrain[x + y * m_width];
	}
	return INVALID_TILE;
}

void Grid::SetTile(int x, int y, char newChar)
{
	m_terrain[x + y * m_width] = GetTileFromChar(newChar);
}

void Grid::PrintGrid() const
{
	std::cout << "Terrain Ptr : " << &m_terrain << std::endl;
	for (int y = 0; y < m_height; ++y) 
	{

		for (int x = 0; x < m_width; ++x) 
		{
			std::cout << m_terrain[x + y * m_width];
		}
		std::cout << std::endl;
	}
}

unsigned char Grid::GetTileFromChar(const char c) const
{
	switch (c)
	{
	case '#':
		return WALL_TILE;
	case ' ':
		return EMPTY_TILE;
	default:
		return EMPTY_TILE;
	}
}