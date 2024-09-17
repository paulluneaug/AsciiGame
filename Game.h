#pragma once

#include "Level.h"
#include <iostream>
#include <fstream> 
#include <Windows.h>
#include <string>
#include <sstream>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

class Game
{
public:

	Game();

	void Draw(Level& const level);
	void Draw(std::string const filename);
	void ClearScreen();

private:
	CHAR_INFO _buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

	HANDLE _hOutput;

	COORD _dwBufferSize;
	COORD _dwBufferCoord;
	SMALL_RECT _rcRegion;

	bool ReadInt(std::string const line, int& out);
};

