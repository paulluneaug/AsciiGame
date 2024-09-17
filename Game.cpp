#include "Game.h"

Game::Game()
{
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

void Game::Draw(const Level& r_level)
{
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

	for (int jHeight = 0; jHeight < SCREEN_HEIGHT; jHeight++) {
		if (jHeight < fileHeight) {
			std::getline(file, line);
		}

		for (int iWidth = 0; iWidth < SCREEN_WIDTH; iWidth++) {

			if (iWidth <= fileWidth && jHeight < fileHeight) {
				m_buffer[jHeight][iWidth].Char.UnicodeChar = line[iWidth];
			}
			else {
				m_buffer[jHeight][iWidth].Char.UnicodeChar = ' ';
			}

			m_buffer[jHeight][iWidth].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
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
			}
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

	int moveX = ker.wVirtualKeyCode == 37 ? -1 : (ker.wVirtualKeyCode == 39 ? 1 : 0);
	int moveY = ker.wVirtualKeyCode == 38 ? -1 : (ker.wVirtualKeyCode == 40 ? 1 : 0);

	std::cout << moveX << " " << moveY << std::endl;

	Draw(m_level);
}


