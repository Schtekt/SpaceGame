#ifndef GALAXYSTATE_H
#define GALAXYSTATE_H
#include "GameState.h"
class GalaxyState : public GameState
{
private:
	float m_galaxyOffsetX;
	float m_galaxyOffsetY;

	int m_sectorsOnScreen;
	
	int m_mousePosX;
	int m_mousePosY;
public:
	GalaxyState();
	virtual void Update(float dt, sf::RenderWindow* window);
	virtual void Render(sf::RenderWindow* window);
};

#endif