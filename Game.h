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

	Level level;


	CHAR_INFO _buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

	HANDLE _hOutput;
	HANDLE _hInput;
	DWORD fdwSaveOldMode;

	COORD _dwBufferSize;
	COORD _dwBufferCoord;
	SMALL_RECT _rcRegion;

	bool stoppedGame;


	bool ReadInt(std::string const line, int& out);

	void ErrorExit(LPCSTR);
	void KeyEventProc(KEY_EVENT_RECORD);
};

