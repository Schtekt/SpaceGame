#include "Ship.h"
#include <SFML/Graphics.hpp>
#include <math.h>
#define _USE_MATH_DEFINES
Ship::Ship(int posX, int posY,int nrOfSectors, const char* texturePath, const char* movTexPath): m_posX(posX), m_posY(posY), m_targetX(posX),
m_targetY(posY), m_pTex(new sf::Texture), m_pMovTex(new sf::Texture), m_pSprite(new sf::Sprite), m_speed(10.f), m_maxTravelDist(9.f), m_textureTimer(0.f), m_secModifier(-nrOfSectors),
m_moving(false)
{
	m_pTex->loadFromFile(texturePath);
	m_pMovTex->loadFromFile(movTexPath);
	m_pSprite->setTexture(*m_pTex, true);
	m_pSprite->setPosition(m_posX - m_pSprite->getLocalBounds().width / 2, m_posY - m_pSprite->getLocalBounds().height / 2);
	m_pSprite->setOrigin(sf::Vector2f(m_pSprite->getLocalBounds().width / 2, m_pSprite->getLocalBounds().height / 2));
}

Ship::~Ship()
{
	delete m_pTex;
	delete m_pSprite;
	delete m_pMovTex;
}

void Ship::Move(int posX, int posY)
{
	m_targetX = posX;
	m_targetY = posY;
	m_pSprite->setTexture(*m_pMovTex);
}

void Ship::Update(int offsetX, int offsetY, float dt, sf::RenderWindow* window)
{
	if (m_secModifier < 0)
		m_secModifier = std::min(window->getSize().x, window->getSize().y) / -m_secModifier;

	sf::Vector2f movVec(m_targetX - m_posX, m_targetY - m_posY);
	if (abs(movVec.x) > 0.1 || abs(movVec.y) > 0.1)
	{
		movVec /= sqrtf(movVec.x * movVec.x + movVec.y * movVec.y);
		m_posX += movVec.x * dt * m_speed;
		m_posY += movVec.y * dt * m_speed;

		m_pSprite->setRotation((movVec.x < 0.0f ? 1 : -1) * (acos(movVec.y) / (2 * 3.14159265358979323846)) * 360 + 180);

		m_textureTimer += dt * 5;
		if((int)roundf(m_textureTimer) % 2 == 1)
			m_pSprite->setTextureRect(sf::IntRect(0, 0, m_pMovTex->getSize().x / 2, m_pMovTex->getSize().y));
		else
			m_pSprite->setTextureRect(sf::IntRect(m_pMovTex->getSize().x / 2, 0, m_pMovTex->getSize().x, m_pMovTex->getSize().y));
		m_moving = true;
	}
	else
	{
		m_moving = false;
		m_pSprite->setTexture(*m_pTex);
		m_pSprite->setTextureRect(sf::IntRect(0, 0, m_pMovTex->getSize().x, m_pMovTex->getSize().y));
		m_textureTimer = 0.f;
	}
	m_pSprite->setPosition((m_posX - offsetX + 0.5f) * m_secModifier, (m_posY - offsetY + 0.5f)* m_secModifier);
}

void Ship::Render(sf::RenderWindow* window)
{
	window->draw(*m_pSprite);
}

void Ship::GetPosition(int& x, int& y)
{
	x = (int)roundf(m_posX);
	y = (int)roundf(m_posY);
}

float Ship::GetMaxTravelDist()
{
	return m_maxTravelDist;
}

bool Ship::isMoving()
{
	return m_moving;
}
