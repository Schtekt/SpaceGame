#include "Ship.h"
#include <SFML/Graphics.hpp>
#include <math.h>
#define _USE_MATH_DEFINES
Ship::Ship(int posX, int posY, const char* texturePath): m_posX(posX), m_posY(posY), m_targetX(posX),
m_targetY(posY), m_angle(0.0f), m_pTex(new sf::Texture), m_pSprite(new sf::Sprite), m_speed(50.f), m_maxTravelDist(9.f)
{
	m_pTex->loadFromFile(texturePath);
	m_pSprite->setTexture(*m_pTex, true);
	m_pSprite->setPosition(m_posX - m_pSprite->getLocalBounds().width / 2, m_posY - m_pSprite->getLocalBounds().height / 2);
	m_pSprite->setRotation(m_angle);
	m_pSprite->setOrigin(sf::Vector2f(m_pSprite->getLocalBounds().width / 2, m_pSprite->getLocalBounds().height / 2));
}

Ship::~Ship()
{
	delete m_pTex;
	delete m_pSprite;
}

void Ship::Move(int posX, int posY)
{
	m_targetX = posX;
	m_targetY = posY;
}

void Ship::Update(int offsetX, int offsetY, float dt, sf::RenderWindow* window)
{
	sf::Vector2f movVec(m_targetX - m_posX, m_targetY - m_posY);
	if (abs(movVec.x) > 0.5 || abs(movVec.y) > 0.5)
	{
		movVec /= sqrtf(movVec.x * movVec.x + movVec.y * movVec.y);
		m_posX += movVec.x * dt * m_speed;
		m_posY += movVec.y * dt * m_speed;

		m_pSprite->setRotation( (movVec.x < 0.0f ? 1 : -1)* (acos(movVec.y)/ (2 * 3.14159265358979323846))*360 + 180);
	}
	m_pSprite->setPosition(std::roundf(m_posX - offsetX), std::roundf(m_posY - offsetY));
}

void Ship::Render(sf::RenderWindow* window)
{
	window->draw(*m_pSprite);
}

void Ship::GetPosition(int& x, int& y)
{
	x = m_posX;
	y = m_posY;
}

float Ship::GetMaxTravelDist()
{
	return m_maxTravelDist;
}

bool Ship::isMoving()
{
	return roundf(m_posX) != m_targetX || roundf(m_posY) != m_targetY;
}
