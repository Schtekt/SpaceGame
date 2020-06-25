#include "GalaxyState.h"
#include "SFML/Graphics.hpp"
#include "LehmerRand.h"
#include "Ship.h"
GalaxyState::GalaxyState() : m_sectorsOnScreen(30), m_grid(false), m_pSeletectedStar(nullptr), m_galaxyOffsetX(0), m_galaxyOffsetY(0), m_selected(false),
m_pShip(new Ship(0, 0, 30, "..//resources//spaceship.png", "..//resources//spaceship_flames.png")), m_mousePosX(0), m_mousePosY(0)
{
   
    m_font = new sf::Font();
    char* winDir = getenv("WinDir"); //Get the window directory
    m_font->loadFromFile(std::string(winDir) + "\\Fonts\\Ebrima.ttf");
}

GalaxyState::~GalaxyState()
{
    delete m_font;
}

void GalaxyState::Update(float dt,sf::RenderWindow* window)
{
    //Input
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


        sf::Vector2i shipPos;
        m_pShip->GetPosition(shipPos.x, shipPos.y);
        sf::Vector2i diff;
        diff.x = shipPos.x - m_galaxyOffsetX - m_sectorsOnScreen / 2;
        diff.y = shipPos.y - m_galaxyOffsetY - m_sectorsOnScreen / 2;
        float len = sqrtf(diff.x * diff.x + diff.y * diff.y);

        if (len > 10)
        {
            m_galaxyOffsetX += diff.x * (len - 10) / len;
            m_galaxyOffsetY += diff.y * (len - 10) / len;

            m_galaxyOffsetX = roundf(m_galaxyOffsetX);
            m_galaxyOffsetY = roundf(m_galaxyOffsetY);
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
            galMousePos += sf::Vector2i(std::roundf(m_galaxyOffsetX), std::roundf(m_galaxyOffsetY));


            if (!m_pSeletectedStar)
                delete m_pSeletectedStar;

            m_pSeletectedStar = new Star(galMousePos.x, galMousePos.y, 3, sectorWidth - 1);

            if (m_pSeletectedStar->m_exists)
            {
                sf::Vector2i travelDiff = galMousePos - shipPos;
                float travelLength = sqrt(travelDiff.x * travelDiff.x + travelDiff.y * travelDiff.y);
                if (travelLength <= m_pShip->GetMaxTravelDist() && !m_pShip->isMoving())
                {
                    m_pShip->Move(galMousePos.x, galMousePos.y);

                    m_selectedPosX = galMousePos.x;
                    m_selectedPosY = galMousePos.y;
                }
            }
        }

        if (m_pSeletectedStar && !m_pShip->isMoving())
        {
            if (m_pSeletectedStar->m_exists)
                m_selected = true;
        }
        else
            m_selected = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            m_grid = true;
        }
        else
        {
            m_grid = false;
        }
    }
    //Other Stuff
    int sectorWidth = std::min(window->getSize().x, window->getSize().y) / m_sectorsOnScreen;
    m_pShip->Update((int)roundf(m_galaxyOffsetX),(int)roundf(m_galaxyOffsetY),dt, window);



}

void GalaxyState::Render(sf::RenderWindow* window)
{
    window->clear();
    int sectorWidth = std::min(window->getSize().x,window->getSize().y) / m_sectorsOnScreen;

    sf::Vector2i galMousePos = sf::Mouse::getPosition(*window);
    galMousePos /= sectorWidth;
    galMousePos += sf::Vector2i(std::roundf(m_galaxyOffsetX), std::roundf(m_galaxyOffsetY));

    for (int x = 0; x < m_sectorsOnScreen; x++)
    {
        for (int y = 0; y < m_sectorsOnScreen; y++)
        {
            int coordX = x + std::roundf(m_galaxyOffsetX);
            int coordY = y + std::roundf(m_galaxyOffsetY);
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

    if (m_grid)
    {
        for (int y = 0; y < m_sectorsOnScreen - 1; y++)
        {
            int coordY = y + std::roundf(m_galaxyOffsetY);
            sf::Vertex vertices[] =
            {
                sf::Vertex(sf::Vector2f(0, y * sectorWidth + sectorWidth), sf::Color(50,50,50)),
                sf::Vertex(sf::Vector2f(window->getSize().x, y * sectorWidth + sectorWidth), sf::Color(50,50,50))
            };
            window->draw(vertices, 2, sf::Lines);
        }
        for (int x = 0; x < m_sectorsOnScreen - 1; x++)
        {
            int coordX = x + std::roundf(m_galaxyOffsetY);
            sf::Vertex vertices[] =
            {
                sf::Vertex(sf::Vector2f(x * sectorWidth + sectorWidth, 0), sf::Color(50,50,50)),
                sf::Vertex(sf::Vector2f(x * sectorWidth + sectorWidth, window->getSize().y), sf::Color(50,50,50))
            };
            window->draw(vertices, 2, sf::Lines);
        }

        sf::CircleShape shipTrav(m_pShip->GetMaxTravelDist() * sectorWidth);
        sf::Vector2i shipPos;
        m_pShip->GetPosition(shipPos.x, shipPos.y);
        shipTrav.setOrigin(shipTrav.getRadius(), shipTrav.getRadius());
        shipTrav.setPosition((shipPos.x - m_galaxyOffsetX + 0.5)* sectorWidth, (shipPos.y -m_galaxyOffsetY + 0.5)* sectorWidth);
        shipTrav.setFillColor(sf::Color::Transparent);
        shipTrav.setOutlineColor(sf::Color::Red);
        shipTrav.setOutlineThickness(2);
        window->draw(shipTrav);

    }
    sf::Text coordinatesText;
    coordinatesText.setFont(*m_font);
    coordinatesText.setPosition(sf::Vector2f(0, 0));
    coordinatesText.setString(std::to_string((int)std::roundf(m_galaxyOffsetX)) + ", " + std::to_string((int)std::roundf(m_galaxyOffsetY)));
    window->draw(coordinatesText);

    sf::Vector2i shipPos;
    m_pShip->GetPosition(shipPos.x, shipPos.y);

    sf::Text shipPosText;
    shipPosText.setFont(*m_font);
    shipPosText.setColor(sf::Color::Green);
    shipPosText.setPosition(sf::Vector2f(0, coordinatesText.getLocalBounds().height));
    shipPosText.setString(std::to_string(shipPos.x) + ", " + std::to_string(shipPos.y));
    window->draw(shipPosText);

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

        int currPos = tmp.getRadius()*2 + 20;
        for (int i = 0; i < star.m_nrOfPlanets; i++)
        {
            sf::CircleShape planTmp(star.m_pPlanets[i].size);
            planTmp.setFillColor(*star.m_pPlanets[i].color);
            planTmp.setPosition(currPos, tex.getSize().y / 2 - planTmp.getRadius());
            currPos += planTmp.getRadius()*2 + 20;
            tex.draw(planTmp);
        }

        sf::Sprite starSysDisplay;
        starSysDisplay.setTexture(tex.getTexture());
        starSysDisplay.setPosition(0, window->getSize().y * 4 / 5);
        window->draw(starSysDisplay);
    }

    m_pShip->Render(window);
    window->display();
}
