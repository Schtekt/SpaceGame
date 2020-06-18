#ifndef GAME_H
#define GAME_H
namespace sf
{
	class RenderWindow;
}
class GameState;

class Game
{
private:
	sf::RenderWindow* m_pWindow;
	GameState* state;
public:
	Game();
	~Game();
	void run();
};

#endif // !GAME_H
