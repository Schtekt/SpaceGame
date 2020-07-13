#include "GameOverState.h"
#include "Timer.h"
#include <SFML/Graphics/Text.hpp>
#include "SFML/Graphics/RenderWindow.hpp"
#include <SFML/Window/Event.hpp>
GameOverState::GameOverState(Game* game, sf::Font* font): GameState(game), m_pText(new sf::Text()), m_pFont(font)
{
	float time = Timer::GetInstance().GetTime() / 1000.0f;
	char timeCharArr[16];
	sprintf(timeCharArr, "%.2f", time);
	std::string timeString = timeCharArr;
	

	m_pText->setFont(*m_pFont);
	m_pText->setString("Congratulations!\nYou finished the game in " + timeString + " seconds\n\nPress \"Enter\" to exit");
	m_pText->setFillColor(sf::Color::White);
	m_pText->setPosition(10, 10);
}

GameOverState::~GameOverState()
{
	delete m_pText;
}

void GameOverState::Update(float dt, sf::RenderWindow* window)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window->close();
			PopState();
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
			{
				window->close();
				PopState();
				return;
			}
		}
	}
}

void GameOverState::Render(sf::RenderWindow* window)
{
	window->clear();
	window->draw(*m_pText);
	window->display();
}
