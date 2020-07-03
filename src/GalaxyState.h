#ifndef GALAXYSTATE_H
#define GALAXYSTATE_H
#include "GameState.h"
#include <vector>
namespace sf
{
	class Font;
}

class Ship;
class Star;
class Game;
class Cargo;

struct visitedPlanet
{
	int galaxyCoordX;
	int galaxyCoordY;
	unsigned int planetNr;
};

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
	int m_SelectedPosX;
	int m_SelectedPosY;
	Star* m_pSeletectedStar;
	Ship* m_pShip;
	
	bool m_Grid;
	
	std::vector<visitedPlanet> m_visitedPlanets;
	Cargo* m_pCargo;
public:
	GalaxyState(Game* game);
	~GalaxyState();
	virtual void Update(float dt, sf::RenderWindow* window);
	virtual void Render(sf::RenderWindow* window);

	bool AddVisitedPlanet(int nr);
	bool IsPlanetVisited(int nr);
};

#endif