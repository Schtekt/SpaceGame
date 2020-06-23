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
	GameState* m_pState;
public:
	Game();
	~Game();
	void Run();
};

#endif // !GAME_H
