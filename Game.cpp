#include "Game.h"

Game::Game()
{
	_hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

	_buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

	_dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
	_dwBufferCoord = { 0, 0 };
	_rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };
}

void Game::Draw(Level& const level)
{
}

void Game::Draw(std::string const filename)
{

    std::fstream file(filename);

    int fileWidth;
    int fileHeight;
    std::string line;

    std::getline(file, line);
    ReadInt(line, fileWidth);

    std::getline(file, line);
    ReadInt(line, fileHeight);

    for (int jHeight = 0; jHeight < SCREEN_HEIGHT; jHeight++) {
        if (jHeight < fileHeight) {
            std::getline(file, line);
        }

        for (int iWidth = 0; iWidth < SCREEN_WIDTH; iWidth++) {

            if (iWidth <= fileWidth && jHeight < fileHeight) {
                _buffer[jHeight][iWidth].Char.UnicodeChar = line[iWidth];
            }
            else {
                _buffer[jHeight][iWidth].Char.UnicodeChar = ' ';
            }

            _buffer[jHeight][iWidth].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
        }
    }

    file.close();
    file.clear();

    WriteConsoleOutput(_hOutput, (CHAR_INFO*)_buffer, _dwBufferSize,
        _dwBufferCoord, &_rcRegion);
}

void Game::ClearScreen()
{
    for (int iWidth = 0; iWidth < SCREEN_WIDTH; iWidth++) {
        for (int jHeight = 0; jHeight < SCREEN_HEIGHT; jHeight++) {
            _buffer[jHeight][iWidth].Char.UnicodeChar = ' ';
            _buffer[jHeight][iWidth].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
        }
    }

    WriteConsoleOutput(_hOutput, (CHAR_INFO*)_buffer, _dwBufferSize,
        _dwBufferCoord, &_rcRegion);
}

bool Game::ReadInt(std::string const line, int& out)
{
    std::istringstream sStream(line);
    int tmp;
    if (!(sStream >> tmp)) return false;

    out = tmp;
    return true;
}


