#ifndef GAMESTATE_H
#define GAMESTATE_H

namespace sf
{
	class RenderWindow;
}
class Game;
class GameState
{
protected:
	GameState* m_pLastState;
	Game* m_pGame;
public:
	GameState(Game* game);
	virtual ~GameState();
	void ChangeState(GameState* state);
	void PopState();
	virtual void Update(float dt, sf::RenderWindow* window) = 0;
	virtual void Render(sf::RenderWindow* window) = 0;
};

#endif