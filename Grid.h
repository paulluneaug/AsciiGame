#pragma once
#include <string>

class Grid
{
public:
	static const unsigned char EMPTY_TILE = 0;
	static const unsigned char WALL_TILE = 1;
	static const unsigned char INVALID_TILE = 255;

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

	void PrintGrid() const;

private:
	unsigned char GetTileFromChar(char c) const;
};

