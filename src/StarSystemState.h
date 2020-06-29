#ifndef STARSYSTEMSTATE
#define STARSYSTEMSTATE
#include "GameState.h"
struct Star;
class StarSystemState : public GameState
{
private:
	Star* m_pStarSystem;
public:
	StarSystemState(Game* game, Star* starSystem);
	virtual void Update(float dt, sf::RenderWindow* window);
	virtual void Render(sf::RenderWindow* window);
};


#endif