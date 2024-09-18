#include "Game.h"

Game::Game()
{
	m_titleScreen = true;
	m_stoppedGame = false;

	m_hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	m_hInput = (HANDLE)GetStdHandle(STD_INPUT_HANDLE);

	m_buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

	m_dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
	m_dwBufferCoord = { 0, 0 };
	m_rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };


	if (!GetConsoleMode(m_hInput, &m_fdwSaveOldMode))
		ErrorExit("GetConsoleMode");

	DWORD  fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(m_hInput, fdwMode))
		ErrorExit("SetConsoleMode");

	m_level.LoadLevelAtPath("Level0.txt");
}

void Game::Draw(Level& r_level)
{
	int levelWidth = r_level.GetGrid().GetWidth();
	int levelHeight = r_level.GetGrid().GetHeight();

	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++) {

			if (r_level.IsInBound(x,y)) {
				m_buffer[y][x].Char.UnicodeChar = r_level.GetTileAtCoordinates(x,y);
			}
			else {
				m_buffer[y][x].Char.UnicodeChar = ' ';
			}

			m_buffer[y][x].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
		}
	}

	for (Entity* entity : r_level.GetEntities()) {
		if (entity->CanDraw()) {
			m_buffer[entity->GetY()][entity->GetX()].Char.UnicodeChar = entity->GetChar();
		}
		
	}

	m_buffer[r_level.GetPlayer().GetY()][r_level.GetPlayer().GetX()].Char.UnicodeChar = r_level.GetPlayer().GetChar();

	WriteConsoleOutput(m_hOutput, (CHAR_INFO*)m_buffer, m_dwBufferSize,
		m_dwBufferCoord, &m_rcRegion);
}

void Game::Draw(const std::string& r_filename)
{
	std::fstream file(r_filename);

	int fileWidth;
	int fileHeight;
	std::string line;

	std::getline(file, line);
	ReadInt(line, fileWidth);

	std::getline(file, line);
	ReadInt(line, fileHeight);

	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		if (y < fileHeight) {
			std::getline(file, line);
		}
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			if (x < fileWidth && y < fileHeight) {
				m_buffer[y][x].Char.UnicodeChar = line[x];
			}
			else {
				m_buffer[y][x].Char.UnicodeChar = ' ';
			}

			m_buffer[y][x].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
		}
	}



	file.close();
	file.clear();

	WriteConsoleOutput(m_hOutput, (CHAR_INFO*)m_buffer, m_dwBufferSize,
		m_dwBufferCoord, &m_rcRegion);
}

void Game::ClearScreen()
{
	for (int iWidth = 0; iWidth < SCREEN_WIDTH; iWidth++) {
		for (int jHeight = 0; jHeight < SCREEN_HEIGHT; jHeight++) {
			m_buffer[jHeight][iWidth].Char.UnicodeChar = ' ';
			m_buffer[jHeight][iWidth].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
		}
	}

	WriteConsoleOutput(m_hOutput, (CHAR_INFO*)m_buffer, m_dwBufferSize,
		m_dwBufferCoord, &m_rcRegion);
}

void Game::Loop()
{
	DWORD i;
	INPUT_RECORD irInBuf[128];
	DWORD cNumRead;

	Draw("title.txt");

	while (!m_stoppedGame) {
		if (!ReadConsoleInput(
			m_hInput,      // input buffer handle
			irInBuf,     // buffer to read into
			128,         // size of read buffer
			&cNumRead)) // number of records read
			ErrorExit("ReadConsoleInput");

		// Dispatch the events to the appropriate handler.

		for (i = 0; i < cNumRead; i++)
		{
			if (irInBuf[i].EventType == KEY_EVENT) {
				KeyEventProc(irInBuf[i].Event.KeyEvent);
				break;
			}
			/*
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input
				KeyEventProc(irInBuf[i].Event.KeyEvent);
				break;

			case MOUSE_EVENT: // mouse input

			case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing

			case FOCUS_EVENT:  // disregard focus events

			case MENU_EVENT:   // disregard menu events
				break;

			default:
				ErrorExit("Unknown event type");
				break;
			}*/
		}
	}
}

bool Game::ReadInt(const std::string& r_line, int& r_out)
{
	std::istringstream sStream(r_line);
	int tmp;
	if (!(sStream >> tmp)) return false;

	r_out = tmp;
	return true;
}

VOID Game::ErrorExit(LPCSTR lpszMessage)
{
	std::cout << lpszMessage << std::endl;

	// Restore input mode on exit.

	SetConsoleMode(m_hOutput, m_fdwSaveOldMode);
	ExitProcess(0);
}

VOID Game::KeyEventProc(KEY_EVENT_RECORD ker)
{
	if (!ker.bKeyDown) return;

	if (m_titleScreen) {
		m_titleScreen = false;
	}
	else {
		int moveX = ker.wVirtualKeyCode == 37 ? -1 : (ker.wVirtualKeyCode == 39 ? 1 : 0);
		int moveY = ker.wVirtualKeyCode == 38 ? -1 : (ker.wVirtualKeyCode == 40 ? 1 : 0);

		m_level.GetPlayer().Move(moveX, moveY, m_level.GetGrid(), m_level.GetEntities());
	}
	Draw(m_level);
}


