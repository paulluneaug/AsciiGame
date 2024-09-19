#pragma once
#include <string>
#include <Windows.h>

/// <summary>
/// Represents the game's grid
/// </summary>
class Grid
{
public:
	static const unsigned char EMPTY_TILE = 0;
	static const unsigned char WALL_TILE = 1;
	static const unsigned char INVALID_TILE = 255;

	static const WORD WALL_COLOR = BACKGROUND_RED | BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN;
	static const WORD DEFAULT_COLOR = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN;
	static const WORD EMPTY_COLOR = BACKGROUND_RED;

private:
	int m_width;
	int m_height;

	unsigned char* m_terrain;

public:

	/// <summary>
	/// Creates a grid
	/// </summary>
	/// <param name="width">The grid's width</param>
	/// <param name="height">The grid's height</param>
	Grid(int width, int height);

	/// <summary>
	/// Destroys a grid
	/// </summary>
	~Grid();

	// Getters
	
	/// <summary>
	/// Gets the grid's height
	/// </summary>
	/// <returns>The grid's height</returns>
	int GetHeight() const;

	/// <summary>
	/// Gets the grid's width
	/// </summary>
	/// <returns>The grid's width</returns>
	int GetWidth() const;


	/// <summary>
	/// Checks if the coordinates are within the bounds of the grid
	/// </summary>
	/// <param name="x">The x coordinate</param>
	/// <param name="y">The y coordinate</param>
	/// <returns>True if the coordinates are within the bounds of the grid </returns>
	bool IsInBound(int x, int y) const;

	/// <summary>
	/// Gets a tile
	/// </summary>
	/// <param name="x">The tile's x coordinate</param>
	/// <param name="y">The tile's y coordinate</param>
	/// <returns>The tile</returns>
	unsigned char GetTileAtCoordinates(int x, int y) const;

	/// <summary>
	/// Set a tile's value
	/// </summary>
	/// <param name="x">The tile's x coordinate</param>
	/// <param name="y">The tile's y coordinate</param>
	/// <param name="newChar">The new tile's value</param>
	void SetTile(int x, int y, char newChar);

	/// <summary>
	/// Prints the grid to the console
	/// </summary>
	void PrintGrid() const;


private:

	/// <summary>
	/// Get a tile from a character
	/// </summary>
	/// <param name="c">The character</param>
	/// <returns>The tile</returns>
	unsigned char GetTileFromChar(char c) const;
};

