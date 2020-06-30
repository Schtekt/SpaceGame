#include "StarSystemState.h"
#include "Star.h"
#include <SFML/Graphics.hpp>
#include "Ship.h"
#include "Config.h"
StarSystemState::StarSystemState(Game* game, Star* starSystem, sf::Font* font): GameState(game), m_pStarSystem(starSystem), m_pFont(font)
{
    m_pShip = new Ship(m_pStarSystem->m_size * 4 + 5, Config::getInstance().getWindowSizeHeight() / 2 - m_pStarSystem->m_size, Config::getInstance().getWindowSizeHeight(), "..//resources//spaceship.png", "..//resources//spaceship_flames.png");
    m_pShip->SetSpeed(100);
}

void StarSystemState::Update(float dt, sf::RenderWindow* window)
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
    }

    m_pShip->Update(0, 0, dt, window);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        int currPos = m_pStarSystem->m_size * 6 + 20;
        for (unsigned int i = 0; i < m_pStarSystem->m_nrOfPlanets; i++)
        {
            planet tmp = m_pStarSystem->m_pPlanets[i];
            

            sf::Vector2i planPos = sf::Vector2i(currPos, Config::getInstance().getWindowSizeHeight() / 2 - m_pStarSystem->m_size + tmp.size);
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            sf::Vector2i diff = planPos - mousePos + sf::Vector2i(tmp.size, tmp.size);
            float dist = sqrt(diff.x * diff.x + diff.y * diff.y);


            if (dist <= tmp.size)
            {
                m_pShip->Move(planPos.x + tmp.size, planPos.y + tmp.size);
            }
            currPos += tmp.size * 3 + 20;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
    {
        PopState();
    }
}

void StarSystemState::Render(sf::RenderWindow* window)
{
	window->clear();

	sf::Text exitText;
	exitText.setString("Press BACKSPACE to exit star system");
	exitText.setFont(*m_pFont);
	window->draw(exitText);

	sf::CircleShape star;
	star.setRadius(m_pStarSystem->m_size * 2);
	star.setFillColor(*m_pStarSystem->m_pColor);
    star.setPosition(0, Config::getInstance().getWindowSizeHeight() / 2 - star.getRadius() / 2);

    int currPos = star.getRadius()*3 + 20;

    for (int i = 0; i < m_pStarSystem->m_nrOfPlanets; i++)
    {
        planet tmp = m_pStarSystem->m_pPlanets[i];
        sf::CircleShape circPlan;
        circPlan.setRadius(tmp.size);
        circPlan.setFillColor(*tmp.color);
        circPlan.setPosition(currPos, Config::getInstance().getWindowSizeHeight() / 2 - star.getRadius() / 2 + circPlan.getRadius());

        currPos += circPlan.getRadius() * 3 + 20;

        sf::Vector2i planPos = (sf::Vector2i)circPlan.getPosition();
        sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
        sf::Vector2i diff = planPos - mousePos + sf::Vector2i(circPlan.getRadius(), circPlan.getRadius());
        float dist = sqrt(diff.x * diff.x + diff.y * diff.y);

        if (dist <= circPlan.getRadius())
        {
            sf::CircleShape highlight(circPlan.getRadius() + 1);
            highlight.setOrigin(sf::Vector2f(highlight.getRadius(), highlight.getRadius()));
            highlight.setPosition(sf::Vector2f(circPlan.getPosition().x + circPlan.getRadius(), circPlan.getPosition().y + circPlan.getRadius()));
            highlight.setFillColor(sf::Color::Transparent);
            highlight.setOutlineColor(sf::Color::Green);
            highlight.setOutlineThickness(2);
            window->draw(highlight);
        }

        window->draw(circPlan);
    }

    m_pShip->Render(window);

	window->draw(star);
	window->display();
}
