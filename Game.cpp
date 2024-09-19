#include "Game.h"
#include "Grid.h";
#include "KeyCode.h"
#include <tuple>

//#include <filesystem>
#include "DoubleWCharGlossary.h"

Game::Game()
{

	m_titleScreen = true;
	m_stoppedGame = false;

	m_levelIndex = 0;

	m_hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	m_hInput = (HANDLE)GetStdHandle(STD_INPUT_HANDLE);

	m_buffer = new CHAR_INFO[SCREEN_HEIGHT * SCREEN_WIDTH];

	m_dwBufferSize = { SCREEN_WIDTH,SCREEN_HEIGHT };
	m_dwBufferCoord = { 0, 0 };
	m_rcRegion = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };


	if (!GetConsoleMode(m_hInput, &m_fdwSaveOldMode))
		ErrorExit("GetConsoleMode");

	DWORD  fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(m_hInput, fdwMode))
		ErrorExit("SetConsoleMode");


	HWND hwnd_console = GetConsoleWindow();
	SetWindowPos(hwnd_console, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);
	ShowWindow(hwnd_console, SW_SHOW);


	LoadLevel(m_levelIndex);
}

Game::~Game()
{
	delete[] m_buffer;
}

void Game::Draw(Level& r_level)
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

void Game::ClearScreen()
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

void Game::Loop()
{
	INPUT_RECORD irInBuf[128];

	Draw("Ressources\\title.txt");

	while (!m_stoppedGame)
	{
		ProcessInputs(irInBuf);

		UpdateEntities();

		Draw(*m_level);

		if (m_level->HasFinishedLevel()) {
			LoadNextLevel();
		}
	}
}

void Game::ProcessInputs(INPUT_RECORD  irInBuf[128])
{
	DWORD cNumRead;
	DWORD i;

	if (!ReadConsoleInput(
		m_hInput,      // input buffer handle
		irInBuf,     // buffer to read into
		128,         // size of read buffer
		&cNumRead)) // number of records read
	{
		ErrorExit("ReadConsoleInput");
	}


	// Dispatch the events to the appropriate handler.

	for (i = 0; i < cNumRead; i++)
	{
		if (irInBuf[i].EventType == KEY_EVENT) {
			KeyEventProc(irInBuf[i].Event.KeyEvent);
			break;
		}
	}
}

void Game::UpdateEntities()
{
	for (Entity* entity : m_level->GetEntities()) {
		entity->Update();
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

VOID Game::ErrorExit(LPCSTR error)
{
	std::cout << error << std::endl;

	// Restore input mode on exit.

	SetConsoleMode(m_hOutput, m_fdwSaveOldMode);
	ExitProcess(0);
}

VOID Game::KeyEventProc(KEY_EVENT_RECORD key)
{
	if (!key.bKeyDown) return;

	if (m_titleScreen)
	{
		m_titleScreen = false;
		return;
	}

	int moveX =
		key.wVirtualKeyCode == KeyCode::ARROW_LEFT ? -1 : 0 +
		key.wVirtualKeyCode == KeyCode::ARROW_RIGHT ? 1 : 0;

	int moveY =
		key.wVirtualKeyCode == KeyCode::ARROW_UP ? -1 : 0 +
		key.wVirtualKeyCode == KeyCode::ARROW_DOWN ? 1 : 0;

	if (moveX != 0 || moveY != 0)
	{
		m_level->GetPlayer().Move(moveX, moveY, m_level->GetGrid(), m_level->GetEntities());
		return;
	}

	bool reloadLevel = key.wVirtualKeyCode == KeyCode::KEY_R;
	if (reloadLevel)
	{
		ReloadLevel();
		return;
	}
}

void Game::GetCharForTile(unsigned char tile, DoubleWChar& r_outChars)
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

void Game::WriteEntityToBuffer(const Entity& entity)
{
	DoubleWChar entityChar = entity.GetChars();
	entityChar.InsertIn(m_buffer, entity.GetY() * SCREEN_WIDTH + entity.GetX() * 2);
	//m_buffer[entity.GetY() * SCREEN_WIDTH + entity.GetX()].Attributes = entity.GetColor();
}

void Game::LoadNextLevel()
{
	LoadLevel(++m_levelIndex);
}

void Game::ReloadLevel()
{
	LoadLevel(m_levelIndex);
}

void Game::LoadLevel(int levelIndex)
{
	std::ostringstream ss;
	ss << "Ressources\\Levels\\Level" << levelIndex << ".txt";
	std::string newLevelName = ss.str();


	if (m_level != nullptr)
	{
		delete m_level;
	}
	m_level = new Level(newLevelName);

	if (!m_level->HasFoundLevelFile())
	{
		FinishGame();
	}
}

void Game::FinishGame()
{
	m_stoppedGame = true;

	Draw("Ressources\\end.txt");

	int dxf;
	std::cin >> dxf;

}


