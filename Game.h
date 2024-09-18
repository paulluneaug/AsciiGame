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
	~Game();

	void Draw(Level& r_level);
	void Draw(const std::string& r_filename);
	void ClearScreen();
	void Loop();

private:

	CHAR_INFO* m_buffer;
	Level m_level;



	HANDLE m_hOutput;
	HANDLE m_hInput;
	DWORD m_fdwSaveOldMode;

	COORD m_dwBufferSize;
	COORD m_dwBufferCoord;
	SMALL_RECT m_rcRegion;

	bool m_stoppedGame;
	bool m_titleScreen;


	bool ReadInt(const std::string& r_line, int& r_out);

	void ErrorExit(LPCSTR);
	void KeyEventProc(KEY_EVENT_RECORD);

	char GetCharForTile(unsigned char tile);
};

