#include "Game.h"
#include "Grid.h";
#include "KeyCode.h"
#include <tuple>

#include "DoubleWCharGlossary.h"

Game::Game() :
	m_titleScreen(true),
	m_stoppedGame(false),
	m_levelIndex(0)
{
	m_display = new Display();
	LoadLevel(m_levelIndex);
}

Game::~Game()
{
	if (m_display != nullptr)
	{
		delete m_display;
	}
	if (m_level != nullptr)
	{
		delete m_level;
	}
}

void Game::Mainloop()
{
	INPUT_RECORD irInBuf[128];

	m_display->DrawScreenFromFile("Ressources\\title.txt");

	while (!m_stoppedGame)
	{
		bool inputProcessed = ProcessInputs(irInBuf);
		if (!inputProcessed)
		{
			continue;
		}

		UpdateEntities();


		m_display->DrawLevel(*m_level);

		if (m_level->HasFinishedLevel()) {
			LoadNextLevel();
		}
	}
}

bool Game::ProcessInputs(INPUT_RECORD  irInBuf[128])
{
	DWORD cNumRead;
	DWORD i;

	if (!ReadConsoleInput(
		m_display->GetInputHandle(),      // input buffer handle
		irInBuf,     // buffer to read into
		128,         // size of read buffer
		&cNumRead)) // number of records read
	{
		m_display->ErrorExit("ReadConsoleInput");
		return false;
	}


	// Search the inputs for a keyboard input
	for (i = 0; i < cNumRead; i++)
	{
		if (irInBuf[i].EventType == KEY_EVENT) {
			return KeyEventProc(irInBuf[i].Event.KeyEvent);
		}
	}
	return false;
}

void Game::UpdateEntities()
{
	for (Entity* entity : m_level->GetEntities()) {
		entity->Update();
	}
}

bool Game::KeyEventProc(KEY_EVENT_RECORD key)
{
	if (!key.bKeyDown) return false;

	if (m_titleScreen)
	{
		m_titleScreen = false;
		return false;
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
		return true;
	}

	bool reloadLevel = key.wVirtualKeyCode == KeyCode::KEY_R;
	if (reloadLevel)
	{
		ReloadLevel();
		return true;
	}
	return false;
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
	m_display->DrawLevel(*m_level);
}

void Game::FinishGame()
{
	m_stoppedGame = true;

	m_display->DrawScreenFromFile("Ressources\\end.txt");

	int dxf;
	std::cin >> dxf;

}


