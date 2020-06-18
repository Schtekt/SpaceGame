#ifndef GAMESTATE_H
#define GAMESTATE_H

namespace sf
{
	class RenderWindow;
}

class GameState
{
public:
	virtual void Update(float dt, sf::RenderWindow* window) = 0;
	virtual void Render(sf::RenderWindow* window) = 0;
};

#endif