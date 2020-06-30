#ifndef GALAXYSTATE_H
#define GALAXYSTATE_H
#include "GameState.h"

namespace sf
{
	class Font;
}

class Ship;
class Star;
class Game;
class GalaxyState : public GameState
{
private:
	float m_galaxyOffsetX;
	float m_galaxyOffsetY;

	int m_sectorsOnScreen;
	
	int m_mousePosX;
	int m_mousePosY;

	sf::Font* m_pFont;

	bool m_selected;
	int m_selectedPosX;
	int m_selectedPosY;
	Star* m_pSeletectedStar;
	Ship* m_pShip;

	bool m_grid;
public:
	GalaxyState(Game* game);
	~GalaxyState();
	virtual void Update(float dt, sf::RenderWindow* window);
	virtual void Render(sf::RenderWindow* window);
};

#endif