#ifndef GALAXYSTATE_H
#define GALAXYSTATE_H
#include "GameState.h"
#include "Star.h"

namespace sf
{
	class Font;
}

class GalaxyState : public GameState
{
private:
	float m_galaxyOffsetX;
	float m_galaxyOffsetY;

	int m_sectorsOnScreen;
	
	int m_mousePosX;
	int m_mousePosY;

	sf::Font* m_font;

	bool m_selected;
	int m_selectedPosX;
	int m_selectedPosY;
	Star* m_seletectedStar;
public:
	GalaxyState();
	~GalaxyState();
	virtual void Update(float dt, sf::RenderWindow* window);
	virtual void Render(sf::RenderWindow* window);
};

#endif