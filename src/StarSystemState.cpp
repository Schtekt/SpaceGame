#include "StarSystemState.h"
#include "Star.h"
#include <SFML/Graphics.hpp>
StarSystemState::StarSystemState(Game* game, Star* starSystem): GameState(game), m_pStarSystem(starSystem)
{
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
}

void StarSystemState::Render(sf::RenderWindow* window)
{
	window->clear();
	sf::CircleShape star;
	star.setRadius(m_pStarSystem->m_size * 2);
	star.setFillColor(*m_pStarSystem->m_pColor);
	star.setPosition(0, star.getRadius() + 10);

    int currPos = star.getRadius()*2 + 10;

    for (int i = 0; i < m_pStarSystem->m_nrOfPlanets; i++)
    {
        planet tmp = m_pStarSystem->m_pPlanets[i];
        sf::CircleShape planet;
        planet.setRadius(tmp.size);
        planet.setFillColor(*tmp.color);
        planet.setPosition(currPos, star.getRadius() * 2 + 10 - planet.getRadius());

        currPos += planet.getRadius() * 2 + 10;

        window->draw(planet);
    }

	window->draw(star);
	window->display();
}
