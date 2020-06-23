#ifndef SHIP_H
#define SHIP_H

namespace sf
{
	class Sprite;
	class Texture;
	class RenderWindow;
}

class Ship
{
private:
	float m_speed;
	sf::Sprite* m_pSprite;
	sf::Texture* m_pTex;

	float m_posX;
	float m_posY;

	float m_angle;

	int m_targetX;
	int m_targetY;

public:
	Ship(int posX, int posY, const char* texturePath);
	~Ship();
	void Move(int posX, int posY);
	void Update(int offsetX, int offsetY, float dt, sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
};

#endif