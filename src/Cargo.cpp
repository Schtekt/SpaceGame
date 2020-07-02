#include "Cargo.h"
#include "Resources.h"
#include <SFML/Graphics.hpp>
#include "Config.h"
#include <stdio.h>

Cargo::Cargo(sf::Font* font): m_pFont(font)
{
	for (unsigned int i = 0; i < Resource::NR_OF_ITEMS; i++)
	{
		sf::Text tmp;
		tmp.setFont(*m_pFont);
		tmp.setString(std::to_string(0));
		tmp.setFillColor(sf::Color::White);
		m_resourceValues.push_back(tmp);
	}


	// TODO LOAD SPRITES AND ADJUST TEXT POSITION TO THEM


	int offset = 0;

	for (int i = m_resourceValues.size() - 1; i >= 0; i--)
	{
		offset += m_resourceValues[i].getGlobalBounds().width + 20;
		m_resourceValues[i].setPosition(sf::Vector2f(Config::GetInstance().GetWindowSizeWidth() - offset, 0));
	}
}

Cargo::~Cargo()
{
}

void Cargo::AddResource(Resource rcs)
{
	int val;
	sscanf(m_resourceValues[rcs].getString().toAnsiString().c_str(), "%d", &val);
	m_resourceValues[rcs].setString(std::to_string(val + 1));
}

void Cargo::Render(sf::RenderWindow* window)
{
	// TODO DRAW SPRITES
	for (int i = 0; i < m_resourceValues.size(); i++)
	{
		window->draw(m_resourceValues[i]);
	}
}
