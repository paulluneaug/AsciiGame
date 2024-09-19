#pragma once

#include "Level.h"
#include <Windows.h>
#include <fstream> 
#include <iostream>
#include <stdio.h>
#include <sstream>
#include "Grid.h"
#include "Display.h"

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
	/// Launches the game's loop
	/// </summary>
	void Mainloop();
	
	/// <summary>
	/// Process the game's input
	/// </summary>
	/// <param name="irInBuf">The inputs buffer</param>
	/// <returns>True if an input was processed</returns>
	bool ProcessInputs(INPUT_RECORD  irInBuf[128]);

	/// <summary>
	/// Updates the level's entities
	/// </summary>
	void UpdateEntities();

private:

	bool m_stoppedGame;
	bool m_titleScreen;

	int m_levelIndex;
	Level* m_level;
	Display* m_display;

private:


	/// <summary>
	/// Handles a key event record
	/// </summary>
	/// <param name="event">The record to process</param>
	bool KeyEventProc(KEY_EVENT_RECORD event);

	void LoadNextLevel();
	void ReloadLevel();
	void LoadLevel(int levelIndex);

	void FinishGame();
};

