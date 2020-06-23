#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "GalaxyState.h"
#include "Config.h"

unsigned int width = 720;
unsigned int height = 720;

Game::Game()
{
	m_pWindow = new sf::RenderWindow(sf::VideoMode(Config::getInstance().getWindowSizeWidth(), Config::getInstance().getWindowSizeHeight()), "Another space game!");
	state = new GalaxyState();
}

Game::~Game()
{
	delete m_pWindow;
}

void Game::run()
{
	sf::Clock clock;
	while (m_pWindow->isOpen())
	{
		sf::Event event;
		state->Update(clock.restart().asSeconds(), m_pWindow);
		state->Render(m_pWindow);
	}
}
