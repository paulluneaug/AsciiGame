#pragma once
#include "Level.h"
class Display
{
public:
	static const int SCREEN_WIDTH = 80;
	static const int SCREEN_HEIGHT = 25;

private:

	CHAR_INFO* m_buffer;

	HANDLE m_hOutput;
	HANDLE m_hInput;
	DWORD m_fdwSaveOldMode;

	COORD m_dwBufferSize;
	COORD m_dwBufferCoord;
	SMALL_RECT m_rcRegion;

public:
	Display();
	~Display();

	/// <summary>
	/// Prints an error on screen
	/// </summary>
	/// <param name="error">The error message to print</param>
	void ErrorExit(LPCSTR error);

	/// <summary>
	/// Convert a string to an int
	/// </summary>
	/// <param name="r_line">The string to read</param>
	/// <param name="r_out">The reference to the output int</param>
	/// <returns>True if the operation was a success</returns>
	static bool ReadInt(const std::string& r_line, int& r_out);

	/// <summary>
	/// Draws a level
	/// </summary>
	/// <param name="r_level">The level to draw</param>
	void DrawLevel(Level& r_level);

	/// <summary>
	/// Draw an ascii art
	/// </summary>
	/// <param name="r_filename">The ascii art's filename</param>
	void DrawScreenFromFile(const std::string& r_filename);

	/// <summary>
	/// Clears the screen
	/// </summary>
	void ClearScreen();

	/// <summary>
	/// Writes an entity to the screen's buffer
	/// </summary>
	/// <param name="entity">The entity</param>
	void WriteEntityToBuffer(const Entity& entity);

	const HANDLE& GetInputHandle() const;

private:
	/// <summary>
	/// Finds a tile's character
	/// </summary>
	/// <param name="tile">The tile</param>
	/// <returns>The tile's character</returns>
	static void GetCharForTile(unsigned char tile, DoubleWChar& r_outChars);
};

