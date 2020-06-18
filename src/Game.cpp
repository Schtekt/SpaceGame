#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "GalaxyState.h"

unsigned int width = 1280;
unsigned int height = 1024;

Game::Game()
{
	m_pWindow = new sf::RenderWindow(sf::VideoMode(width, height), "Another space game!");
	state = new GalaxyState();
}

Game::~Game()
{
	delete m_pWindow;
}

void Game::run()
{
	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(1280, 1024), "Another space game!");
	while (window.isOpen())
	{
		sf::Event event;
		state->Update(clock.restart().asSeconds(), &window);
		state->Render(&window);
	}
}
