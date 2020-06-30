#ifndef STARSYSTEMSTATE
#define STARSYSTEMSTATE
#include "GameState.h"
struct Star;

namespace sf
{
	class Font;
}

class Ship;
class StarSystemState : public GameState
{
private:
	Star* m_pStarSystem;
	Ship* m_pShip;
	sf::Font* m_pFont;
public:
	StarSystemState(Game* game, Star* starSystem, sf::Font* font);
	virtual void Update(float dt, sf::RenderWindow* window);
	virtual void Render(sf::RenderWindow* window);
};


#endif