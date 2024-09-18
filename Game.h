#pragma once

#include "Level.h"
#include <iostream>
#include <fstream> 
#include <Windows.h>
#include <string>
#include <sstream>
#include "Grid.h"
#include <stdio.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

/// <summary>
/// Represents the Game and it's general logic
/// </summary>
class Game
{
public:

	/// <summary>
	/// Creates a game
	/// </summary>
	Game();

	/// <summary>
	/// Destroy a game
	/// </summary>
	~Game();

	/// <summary>
	/// Draws a level
	/// </summary>
	/// <param name="r_level">The level to draw</param>
	void Draw(Level& r_level);

	/// <summary>
	/// Draw an ascii art
	/// </summary>
	/// <param name="r_filename">The ascii art's filename</param>
	void Draw(const std::string& r_filename);

	/// <summary>
	/// Clears the screen
	/// </summary>
	void ClearScreen();

	/// <summary>
	/// Launches the game's loop
	/// </summary>
	void Loop();

	void ProcessInputs(INPUT_RECORD  irInBuf[128], DWORD& cNumRead, DWORD& i);

private:

	CHAR_INFO* m_buffer;
	Level* m_level;



	HANDLE m_hOutput;
	HANDLE m_hInput;
	DWORD m_fdwSaveOldMode;

	COORD m_dwBufferSize;
	COORD m_dwBufferCoord;
	SMALL_RECT m_rcRegion;

	bool m_stoppedGame;
	bool m_titleScreen;

	int m_levelIndex;

private:

	/// <summary>
	/// Convert a string to an int
	/// </summary>
	/// <param name="r_line">The string to read</param>
	/// <param name="r_out">The reference to the output int</param>
	/// <returns>True if the operation was a success</returns>
	bool ReadInt(const std::string& r_line, int& r_out);

	/// <summary>
	/// Prints an error on screen
	/// </summary>
	/// <param name="error">The error message to print</param>
	void ErrorExit(LPCSTR error);

	/// <summary>
	/// Handles a key event record
	/// </summary>
	/// <param name="event">The record to process</param>
	void KeyEventProc(KEY_EVENT_RECORD event);

	/// <summary>
	/// Finds a tile's character
	/// </summary>
	/// <param name="tile">The tile</param>
	/// <returns>The tile's character</returns>
	WCHAR GetCharForTile(unsigned char tile);

	void LoadNextLevel();
	void ReloadLevel();
	void LoadLevel(int levelIndex);

	void FinishGame();

	/// <summary>
	/// Writes an entity to the screen's buffer
	/// </summary>
	/// <param name="entity">The entity</param>
	void WriteEntityToBuffer(const Entity& entity);
};

