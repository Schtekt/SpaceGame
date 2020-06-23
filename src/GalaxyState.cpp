#include "GalaxyState.h"
#include "SFML/Graphics.hpp"
#include "LehmerRand.h"

GalaxyState::GalaxyState()
{
    m_galaxyOffsetX = 1;
    m_galaxyOffsetY = -1;
    m_sectorsOnScreen = 30;
    m_selected = false;

    m_mousePosX = 0;
    m_mousePosY = 0;
    m_font = new sf::Font();
    m_font->loadFromFile("C:\\Windows\\Fonts\\Ebrima.ttf");
}

GalaxyState::~GalaxyState()
{
    delete m_font;
}

void GalaxyState::Update(float dt,sf::RenderWindow* window)
{
    sf::Event event;
    if (window->hasFocus())
    {
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

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            int sectorWidth = std::min(window->getSize().x, window->getSize().y) / m_sectorsOnScreen;
            sf::Vector2i galMousePos = sf::Mouse::getPosition(*window);
            galMousePos /= sectorWidth;
            galMousePos += sf::Vector2i(m_galaxyOffsetX, m_galaxyOffsetY);

            m_seletectedStar = new Star(galMousePos.x, galMousePos.y, 3, sectorWidth - 1);

            if (m_seletectedStar->m_exists)
            {
                m_selected = true;
                m_selectedPosX = galMousePos.x;
                m_selectedPosY = galMousePos.y;
            }
        }
    }

}

void GalaxyState::Render(sf::RenderWindow* window)
{
    window->clear();
    int sectorWidth = std::min(window->getSize().x,window->getSize().y) / m_sectorsOnScreen;

    sf::Vector2i galMousePos = sf::Mouse::getPosition(*window);
    galMousePos /= sectorWidth;
    galMousePos += sf::Vector2i(m_galaxyOffsetX, m_galaxyOffsetY);

    for (int x = 0; x < m_sectorsOnScreen; x++)
    {
        for (int y = 0; y < m_sectorsOnScreen; y++)
        {
            int coordX = x + m_galaxyOffsetX;
            int coordY = y + m_galaxyOffsetY;
            Star star(coordX, coordY, 5, sectorWidth - 2);
            if (star.m_exists)
            {
                sf::CircleShape tmp(star.m_size / 2 - 1);
                tmp.setPosition(x * sectorWidth + sectorWidth / 2 - tmp.getRadius(), y * sectorWidth + sectorWidth / 2 - tmp.getRadius());
                tmp.setFillColor(*star.m_pColor);
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

    sf::Text coordinatesText;
    coordinatesText.setFont(*m_font);
    coordinatesText.setPosition(sf::Vector2f(0, 0));
    coordinatesText.setString(std::to_string(m_galaxyOffsetX) + ", " + std::to_string(-m_galaxyOffsetY));
    window->draw(coordinatesText);

    if (m_selected)
    {
        sf::RenderTexture tex;
        tex.create(window->getSize().x, window->getSize().y / 5);
        tex.clear(sf::Color::Blue);
        Star star(m_selectedPosX, m_selectedPosY, 3, 20, true);

        sf::CircleShape tmp(star.m_size * 2);
        tmp.setFillColor(*star.m_pColor);
        tmp.setPosition(0, tex.getSize().y / 2 - tmp.getRadius());
        tex.draw(tmp);
        for (int i = 0; i < star.m_nrOfPlanets; i++)
        {
            sf::CircleShape planTmp(star.m_pPlanets[i].size);
            planTmp.setFillColor(*star.m_pPlanets[i].color);
            planTmp.setPosition(tmp.getRadius() * 2 + 10 + i*40, tex.getSize().y / 2 - star.m_pPlanets[i].size / 2);
            tex.draw(planTmp);
        }

        sf::Sprite starSysDisplay;
        starSysDisplay.setTexture(tex.getTexture());
        starSysDisplay.setPosition(0, window->getSize().y * 4 / 5);
        window->draw(starSysDisplay);
    }
    window->display();
}
