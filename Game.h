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

class Game
{
public:

	Game();

	void Draw(Level& r_level);
	void Draw(const std::string& r_filename);
	void ClearScreen();
	void Loop();

private:

	Level m_level;


	CHAR_INFO m_buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

	HANDLE m_hOutput;
	HANDLE m_hInput;
	DWORD m_fdwSaveOldMode;

	COORD m_dwBufferSize;
	COORD m_dwBufferCoord;
	SMALL_RECT m_rcRegion;

	bool m_stoppedGame;


	bool ReadInt(const std::string& r_line, int& r_out);

	void ErrorExit(LPCSTR);
	void KeyEventProc(KEY_EVENT_RECORD);
};

