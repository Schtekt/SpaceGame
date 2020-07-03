#include "Cargo.h"
#include "Resources.h"
#include <SFML/Graphics.hpp>
#include "Config.h"
#include <stdio.h>
#include <random>
#include <iostream>

Cargo::Cargo(sf::Font* font): m_pFont(font)
{
	for (unsigned int i = 0; i < Resource::NR_OF_ITEMS; i++)
	{
		m_resourcesInCargo.push_back(0);
		m_resourcesGoals.push_back(rand() % 21 + 1);
		sf::Texture* tex = new sf::Texture();
		if (!tex->loadFromFile("..//resources//resource_" + std::to_string(i) + ".png"))
			std::cout << "Could not load texture!" << std::endl;
		m_textures.push_back(tex);

		sf::Sprite* spr = new sf::Sprite();
		m_sprites.push_back(spr);
		m_sprites[i]->setTexture(*m_textures[i]);


		sf::Text tmp;
		tmp.setFont(*m_pFont);
		tmp.setString(std::to_string(m_resourcesInCargo[i]) + "/" + std::to_string(m_resourcesGoals[i]));
		tmp.setFillColor(sf::Color::White);
		m_resourceTexts.push_back(tmp);
	}


	int offset = 0;

	for (int i = m_resourceTexts.size() - 1; i >= 0; i--)
	{
		offset += m_resourceTexts[i].getGlobalBounds().width + 30;
		m_resourceTexts[i].setPosition(sf::Vector2f(Config::GetInstance().GetWindowSizeWidth() - offset, 25));
		m_sprites[i]->setOrigin(sf::Vector2f(m_sprites[i]->getLocalBounds().width / 2, 0));
		m_sprites[i]->setPosition(sf::Vector2f(Config::GetInstance().GetWindowSizeWidth() - offset + m_resourceTexts[i].getGlobalBounds().width / 2, 10));
	}
}

Cargo::~Cargo()
{
	for (int i = 0; i < m_sprites.size(); i++)
	{
		delete m_sprites[i];
		delete m_textures[i];
	}
}

void Cargo::AddResource(Resource rcs)
{
	if (m_resourcesGoals[rcs] != m_resourcesInCargo[rcs])
	{
		m_resourcesInCargo[rcs] += 1;
		m_resourceTexts[rcs].setString(std::to_string(m_resourcesInCargo[rcs]) + "/" + std::to_string(m_resourcesGoals[rcs]));
	}
}

void Cargo::Render(sf::RenderWindow* window)
{
	for (int i = 0; i < m_resourceTexts.size(); i++)
	{
		window->draw(*m_sprites[i]);
		window->draw(m_resourceTexts[i]);
	}
}
