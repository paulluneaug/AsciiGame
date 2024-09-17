#pragma once

#include "Level.h"
#include <iostream>
#include <fstream> 
#include <Windows.h>
#include <string>
#include <sstream>
#include <stdio.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

class Game
{
public:

	Game();

	void Draw(Level& const level);
	void Draw(std::string const filename);
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


	bool ReadInt(std::string const line, int& out);

	void ErrorExit(LPCSTR);
	void KeyEventProc(KEY_EVENT_RECORD);
};

