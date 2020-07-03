#ifndef STARSYSTEMSTATE
#define STARSYSTEMSTATE
#include "GameState.h"
struct Star;

namespace sf
{
	class Font;
	class Texture;
}

class Ship;
class Cargo;
class StarSystemState : public GameState
{
private:
	Star* m_pStarSystem;
	Ship* m_pShip;
	sf::Font* m_pFont;
	Cargo* m_pCargo;
	sf::Texture** m_ppResTex;
public:
	StarSystemState(Game* game, Star* starSystem, sf::Font* font, Cargo* cargo);
	~StarSystemState();
	virtual void Update(float dt, sf::RenderWindow* window);
	virtual void Render(sf::RenderWindow* window);
};


#endif