#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE
#include "GameState.h"
namespace sf
{
	class Text;
	class Font;
}
class GameOverState : public GameState
{
private:
	sf::Text* m_pText;
	sf::Font* m_pFont;
public:
	GameOverState(Game* game, sf::Font* font);
	~GameOverState();
	void Update(float dt, sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
};

#endif