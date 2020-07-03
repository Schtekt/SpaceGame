#ifndef CARGO_H
#define CARGO_H
#include <vector>

namespace sf
{
	class Text;
	class Sprite;
	class Texture;
	class RenderWindow;
	class Font;
}
enum Resource;

class Cargo
{
private:
	sf::Font* m_pFont;
	std::vector<unsigned int> m_resourcesInCargo;
	std::vector<unsigned int> m_resourcesGoals;
	std::vector<sf::Text> m_resourceTexts;
	std::vector<sf::Texture*> m_textures;
	std::vector<sf::Sprite*> m_sprites;
public:
	Cargo(sf::Font* font);
	~Cargo();
	void AddResource(Resource rcs);
	void Render(sf::RenderWindow* window);
};

#endif