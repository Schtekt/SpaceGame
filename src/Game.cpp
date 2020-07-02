#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "GalaxyState.h"
#include "Config.h"

unsigned int width = 720;
unsigned int height = 720;

void Game::ChangeState(GameState* state)
{
	m_pState = state;
}

Game::Game()
{
	m_pWindow = new sf::RenderWindow(sf::VideoMode(Config::GetInstance().GetWindowSizeWidth(), Config::GetInstance().GetWindowSizeHeight()), "Another space game!");
	m_pState = new GalaxyState(this);
}

Game::~Game()
{
	delete m_pWindow;
}

void Game::Run()
{
	sf::Clock clock;
	while (m_pWindow->isOpen())
	{
		sf::Event event;
		m_pState->Update(clock.restart().asSeconds(), m_pWindow);
		m_pState->Render(m_pWindow);
	}
}
