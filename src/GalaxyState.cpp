#include "GalaxyState.h"
#include "SFML/Graphics.hpp"
#include "LehmerRand.h"
#include "Star.h"
GalaxyState::GalaxyState()
{
    m_galaxyOffsetX = 1;
    m_galaxyOffsetY = -1;
    m_sectorsOnScreen = 30;

    m_mousePosX = 0;
    m_mousePosY = 0;
}

void GalaxyState::Update(float dt,sf::RenderWindow* window)
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window->close();
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        m_galaxyOffsetX += 30 * dt;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        m_galaxyOffsetX -= 30 * dt;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        m_galaxyOffsetY += 30 * dt;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        m_galaxyOffsetY -= 30 * dt;
    }

}

void GalaxyState::Render(sf::RenderWindow* window)
{
    window->clear();
    int sectorWidth = window->getSize().x / m_sectorsOnScreen;
    int sectorHeight = window->getSize().y / m_sectorsOnScreen;

    sf::Vector2i galMousePos = sf::Mouse::getPosition(*window);
    galMousePos /= 35;
    galMousePos += sf::Vector2i(m_galaxyOffsetX, m_galaxyOffsetY);

    for (int x = 0; x < m_sectorsOnScreen; x++)
    {
        for (int y = 0; y < m_sectorsOnScreen; y++)
        {
            int coordX = x + m_galaxyOffsetX;
            int coordY = y + m_galaxyOffsetY;
            Star star(coordX, coordY, 3, sectorWidth - 1);
            if (star.Exists())
            {
                sf::CircleShape tmp(star.Size() / 2);
                tmp.setPosition(x * sectorWidth + sectorWidth / 2 - tmp.getRadius(), y * sectorWidth + sectorWidth / 2 - tmp.getRadius());
                tmp.setFillColor(star.Color());
                window->draw(tmp);

                if (galMousePos == sf::Vector2i(coordX, coordY))
                {
                    sf::CircleShape highlight(tmp.getRadius() + 1);
                    highlight.setPosition(x * sectorWidth + sectorWidth / 2 - tmp.getRadius() - 1, y * sectorWidth + sectorWidth / 2 - tmp.getRadius() - 1);
                    highlight.setFillColor(sf::Color::Transparent);
                    highlight.setOutlineColor(sf::Color::Green);
                    highlight.setOutlineThickness(2);
                    window->draw(highlight);
                }
            }
        }
    }

    window->display();
}
