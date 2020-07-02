#include "GalaxyState.h"
#include "SFML/Graphics.hpp"
#include "LehmerRand.h"
#include "Ship.h"
#include "Star.h"
#include "Game.h"
#include "StarSystemState.h"
#include "Cargo.h"

GalaxyState::GalaxyState(Game* game) : m_sectorsOnScreen(30), m_Grid(false), m_pSeletectedStar(nullptr), m_galaxyOffsetX(0), m_galaxyOffsetY(0), m_Selected(false),
m_pShip(new Ship(0, 0, 30, "..//resources//spaceship.png", "..//resources//spaceship_flames.png")), m_mousePosX(0), m_mousePosY(0), GameState(game),m_pCargo(nullptr)
{
    m_pFont = new sf::Font();
    char* winDir = getenv("WinDir"); //Get the window directory
    m_pFont->loadFromFile(std::string(winDir) + "\\Fonts\\Ebrima.ttf");
    m_pCargo = new Cargo(m_pFont);
}

GalaxyState::~GalaxyState()
{
    delete m_pFont;
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && m_pSeletectedStar && !m_pShip->IsMoving())
        {
            StarSystemState* systemState = new StarSystemState(m_pGame, m_pSeletectedStar, m_pFont, m_pCargo);
            GameState::ChangeState(systemState);
        }


        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !m_pShip->IsMoving())
        {
            int sectorWidth = std::min(window->getSize().x, window->getSize().y) / m_sectorsOnScreen;
            sf::Vector2i galMousePos = sf::Mouse::getPosition(*window);
            galMousePos /= sectorWidth;
            galMousePos += sf::Vector2i(std::roundf(m_galaxyOffsetX), std::roundf(m_galaxyOffsetY));

            sf::Vector2i travelDiff = galMousePos - shipPos;
            float travelLength = sqrt(travelDiff.x * travelDiff.x + travelDiff.y * travelDiff.y);
            if (travelLength <= m_pShip->GetMaxTravelDist())
            {
                if (!m_pSeletectedStar)
                    delete m_pSeletectedStar;

                m_pSeletectedStar = new Star(galMousePos.x, galMousePos.y, 3, sectorWidth - 1, true);

                if (m_pSeletectedStar->m_Exists)
                {
                    m_pShip->Move(galMousePos.x, galMousePos.y);

                    m_SelectedPosX = galMousePos.x;
                    m_SelectedPosY = galMousePos.y;
                }
            }
        }

        if (m_pSeletectedStar && !m_pShip->IsMoving())
        {
            if (m_pSeletectedStar->m_Exists)
                m_Selected = true;
        }
        else
            m_Selected = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            m_Grid = true;
        }
        else
        {
            m_Grid = false;
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
            if (star.m_Exists)
            {
                sf::CircleShape tmp(star.m_Size / 2 - 1);
                tmp.setPosition(x * sectorWidth + sectorWidth / 2 - tmp.getRadius(), y * sectorWidth + sectorWidth / 2 - tmp.getRadius());
                tmp.setFillColor(*star.m_pColor);
                window->draw(tmp);

                if (galMousePos == sf::Vector2i(coordX, coordY) || (m_SelectedPosX == coordX && m_SelectedPosY == coordY))
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

    if (m_Grid)
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
    coordinatesText.setFont(*m_pFont);
    coordinatesText.setPosition(sf::Vector2f(0, 0));
    coordinatesText.setString(std::to_string((int)std::roundf(m_galaxyOffsetX)) + ", " + std::to_string((int)std::roundf(m_galaxyOffsetY)));
    window->draw(coordinatesText);

    sf::Vector2i shipPos;
    m_pShip->GetPosition(shipPos.x, shipPos.y);

    sf::Text shipPosText;
    shipPosText.setFont(*m_pFont);
    shipPosText.setColor(sf::Color::Green);
    shipPosText.setPosition(sf::Vector2f(0, coordinatesText.getLocalBounds().height));
    shipPosText.setString(std::to_string(shipPos.x) + ", " + std::to_string(shipPos.y));
    window->draw(shipPosText);

    if (m_Selected)
    {
        sf::RenderTexture tex;
        tex.create(window->getSize().x, window->getSize().y / 5);
        tex.clear(sf::Color::Blue);
        Star star(m_SelectedPosX, m_SelectedPosY, 3, 20, true);

		sf::Text enterText;
		enterText.setFont(*m_pFont);
		enterText.setString("Press ENTER to enter star system");
		enterText.setOrigin(enterText.getLocalBounds().width, 0);
		enterText.setScale(1, -1);
		enterText.setPosition(window->getSize().x - 10, tex.getSize().y);
		tex.draw(enterText);

        sf::CircleShape tmp(star.m_Size * 2);
        tmp.setFillColor(*star.m_pColor);
        tmp.setPosition(0, tex.getSize().y / 2 - tmp.getRadius());
        tex.draw(tmp);

        int currPos = tmp.getRadius()*2 + 20;
        for (int i = 0; i < star.m_NrOfPlanets; i++)
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
    m_pCargo->Render(window);
    window->display();
}

bool GalaxyState::AddVisitedPlanet(int nr)
{
	visitedPlanet tmp;
	tmp.galaxyCoordX = m_SelectedPosX;
	tmp.galaxyCoordY = m_SelectedPosY;
	tmp.planetNr = nr;

	if (!IsPlanetVisited(nr))
	{
		m_visitedPlanets.push_back(tmp);
		return true;
	}
	return false;
}

bool GalaxyState::IsPlanetVisited(int nr)
{
	visitedPlanet tmp;
	tmp.galaxyCoordX = m_SelectedPosX;
	tmp.galaxyCoordY = m_SelectedPosY;
	tmp.planetNr = nr;

	for (int i = 0; i < m_visitedPlanets.size(); i++)
	{
		if (m_visitedPlanets[i].galaxyCoordX == tmp.galaxyCoordX && m_visitedPlanets[i].galaxyCoordY == tmp.galaxyCoordY
			&& m_visitedPlanets[i].planetNr == tmp.planetNr)
		{
			return true;
		}
	}
	return false;
}
