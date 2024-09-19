#include "Display.h"
#include "DoubleWCharGlossary.h"
#include <sstream>

Display::Display() 
{
	m_hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	m_hInput = (HANDLE)GetStdHandle(STD_INPUT_HANDLE);

	m_buffer = new CHAR_INFO[SCREEN_HEIGHT * SCREEN_WIDTH];

	m_dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
	m_dwBufferCoord = { 0, 0 };
	m_rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	int fontSize = 40;

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = fontSize;                   // Width of each character in the font
	cfi.dwFontSize.Y = fontSize * 2;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(m_hOutput, false, &cfi);


	if (!GetConsoleMode(m_hInput, &m_fdwSaveOldMode))
		ErrorExit("GetConsoleMode");

	DWORD  fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(m_hInput, fdwMode))
		ErrorExit("SetConsoleMode");


	HWND hwnd_console = GetConsoleWindow();
	SetWindowPos(hwnd_console, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);
	ShowWindow(hwnd_console, SW_SHOW);
}

Display::~Display()
{
	delete[] m_buffer;
}

void Display::DrawLevel(Level& r_level)
{
	DoubleWChar tileChars = DoubleWCharGlossary::OOB_TILE_CHAR;
	DoubleWChar oobTiles = DoubleWCharGlossary::OOB_TILE_CHAR;

	const Grid& levelGrid = r_level.GetGrid();
	int levelWidth = levelGrid.GetWidth();
	int levelHeight = levelGrid.GetHeight();

	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH / 2; x++) {

			if (r_level.IsInBound(x, y))
			{
				GetCharForTile(r_level.GetTileAtCoordinates(x, y), tileChars);

				tileChars.InsertIn(m_buffer, y * SCREEN_WIDTH + x * 2);

			}
			else {
				oobTiles.InsertIn(m_buffer, y * SCREEN_WIDTH + x * 2);
			}
		}
	}

	for (Entity* entity : r_level.GetEntities()) {
		if (entity->CanDraw()) {
			WriteEntityToBuffer(*entity);
		}
	}

	WriteEntityToBuffer(r_level.GetPlayer());

	WriteConsoleOutput(m_hOutput, (CHAR_INFO*)m_buffer, m_dwBufferSize,
		m_dwBufferCoord, &m_rcRegion);
}

void Display::DrawScreenFromFile(const std::string& r_filename)
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
				m_buffer[y * SCREEN_WIDTH + x].Char.UnicodeChar = line[x];
			}
			else {
				m_buffer[y * SCREEN_WIDTH + x].Char.UnicodeChar = ' ';
			}

			m_buffer[y * SCREEN_WIDTH + x].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
		}
	}

	file.close();
	file.clear();

	WriteConsoleOutput(m_hOutput, m_buffer, m_dwBufferSize,
		m_dwBufferCoord, &m_rcRegion);
}

void Display::ClearScreen()
{
	for (int iWidth = 0; iWidth < SCREEN_WIDTH; iWidth++) {
		for (int jHeight = 0; jHeight < SCREEN_HEIGHT; jHeight++) {
			m_buffer[jHeight * SCREEN_WIDTH + iWidth].Char.UnicodeChar = ' ';
			m_buffer[jHeight * SCREEN_WIDTH + iWidth].Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
		}
	}

	WriteConsoleOutput(m_hOutput, (CHAR_INFO*)m_buffer, m_dwBufferSize,
		m_dwBufferCoord, &m_rcRegion);
}

bool Display::ReadInt(const std::string& r_line, int& r_out)
{
	std::istringstream sStream(r_line);
	int tmp;
	if (!(sStream >> tmp)) return false;

	r_out = tmp;
	return true;
}

void Display::ErrorExit(LPCSTR error)
{
	std::cout << error << std::endl;

	// Restore input mode on exit.

	SetConsoleMode(m_hOutput, m_fdwSaveOldMode);
	ExitProcess(0);
}

void Display::GetCharForTile(unsigned char tile, DoubleWChar& r_outChars)
{
	switch (tile) {
	case Grid::EMPTY_TILE:
		r_outChars = DoubleWCharGlossary::EMPTY_TILE_CHAR;
		return;
	case Grid::WALL_TILE:
		r_outChars = DoubleWCharGlossary::WALL_TILE_CHAR;
		return;
	}

	r_outChars = DoubleWChar('?', '?', BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
	return;
}

void Display::WriteEntityToBuffer(const Entity& entity)
{
	DoubleWChar entityChar = entity.GetChars();
	entityChar.InsertIn(m_buffer, entity.GetY() * SCREEN_WIDTH + entity.GetX() * 2);
	//m_buffer[entity.GetY() * SCREEN_WIDTH + entity.GetX()].Attributes = entity.GetColor();
}

const HANDLE& Display::GetInputHandle() const
{
	return m_hInput;
}
