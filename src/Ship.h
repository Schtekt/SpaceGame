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
	float m_Speed;
	sf::Sprite* m_pSprite;
	sf::Texture* m_pTex;
	sf::Texture* m_pMovTex;

	float m_PosX;
	float m_PosY;
	float m_SecModifier;

	int m_TargetX;
	int m_TargetY;

	float m_MaxTravelDist;
	float m_TextureTimer;

	bool m_Moving;
public:
	Ship(int posX, int posY, int nrOfSectors, const char* texturePath, const char* movTexPath);
	~Ship();
	void Move(int posX, int posY);
	void Update(int offsetX, int offsetY, float dt, sf::RenderWindow* window);
	void Render(sf::RenderWindow* window);
	void GetPosition(int& x, int& y);
	float GetMaxTravelDist();
	bool IsMoving();
	void SetSpeed(float speed);
};

#endif