#ifndef STARSYSTEMSTATE
#define STARSYSTEMSTATE
#include "GameState.h"
struct Star;
class Ship;
class StarSystemState : public GameState
{
private:
	Star* m_pStarSystem;
	Ship* m_pShip;
public:
	StarSystemState(Game* game, Star* starSystem);
	virtual void Update(float dt, sf::RenderWindow* window);
	virtual void Render(sf::RenderWindow* window);
};


#endif