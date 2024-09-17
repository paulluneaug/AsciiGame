#pragma once
#include <string>

class Grid
{
public:
	static const unsigned char AIR_TILE;
	static const unsigned char WALL_TILE;
	static const unsigned char INVALID_TILE;

private:
	int m_width;
	int m_height;

	unsigned char* m_terrain;

public:
	Grid(int width, int height);
	~Grid();

	// Getters
	int GetHeight() const;
	int GetWidth() const;

	bool IsInBound(int x, int y) const;
	unsigned char GetTileAtCoordinates(int x, int y) const;

	void SetTile(int x, int y, char newChar);

private:
	unsigned char GetTileFromChar(char c);
};

