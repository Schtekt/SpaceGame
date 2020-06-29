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
	sf::Texture* m_pMovTex;

	float m_posX;
	float m_posY;
	float m_secModifier;

	int m_targetX;
	int m_targetY;

	float m_maxTravelDist;
	float m_textureTimer;

	bool m_moving;
public:
	Ship(int posX, int posY, int nrOfSectors, const char* texturePath, const char* movTexPath);
	~Ship();
	void Move(int posX, int posY);
	void Update(int offsetX, int offsetY, float dt, sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
	void GetPosition(int& x, int& y);
	float GetMaxTravelDist();
	bool isMoving();
	void SetSpeed(float speed);
};

#endif