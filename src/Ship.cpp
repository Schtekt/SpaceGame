#include "Ship.h"
#include <SFML/Graphics.hpp>
#include <math.h>
#define _USE_MATH_DEFINES
Ship::Ship(int posX, int posY,int nrOfSectors, const char* texturePath, const char* movTexPath): m_PosX(posX), m_PosY(posY), m_TargetX(posX),
m_TargetY(posY), m_pTex(new sf::Texture), m_pMovTex(new sf::Texture), m_pSprite(new sf::Sprite), m_Speed(10.f), m_MaxTravelDist(9.f), m_TextureTimer(0.f), m_SecModifier(-nrOfSectors),
m_Moving(false)
{
	m_pTex->loadFromFile(texturePath);
	m_pMovTex->loadFromFile(movTexPath);
	m_pSprite->setTexture(*m_pTex, true);
	m_pSprite->setPosition(m_PosX - m_pSprite->getLocalBounds().width / 2, m_PosY - m_pSprite->getLocalBounds().height / 2);
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
	m_TargetX = posX;
	m_TargetY = posY;
	m_pSprite->setTexture(*m_pMovTex);
}

void Ship::Update(int offsetX, int offsetY, float dt, sf::RenderWindow* window)
{
	if (m_SecModifier < 0)
		m_SecModifier = std::min(window->getSize().x, window->getSize().y) / -m_SecModifier;

	sf::Vector2f movVec(m_TargetX - m_PosX, m_TargetY - m_PosY);
	if (abs(movVec.x) > 0.1 || abs(movVec.y) > 0.1)
	{
		movVec /= sqrtf(movVec.x * movVec.x + movVec.y * movVec.y);
		m_PosX += movVec.x * dt * m_Speed;
		m_PosY += movVec.y * dt * m_Speed;

		m_pSprite->setRotation((movVec.x < 0.0f ? 1 : -1) * (acos(movVec.y) / (2 * 3.14159265358979323846)) * 360 + 180);

		m_TextureTimer += dt * 5;
		if((int)roundf(m_TextureTimer) % 2 == 1)
			m_pSprite->setTextureRect(sf::IntRect(0, 0, m_pMovTex->getSize().x / 2, m_pMovTex->getSize().y));
		else
			m_pSprite->setTextureRect(sf::IntRect(m_pMovTex->getSize().x / 2, 0, m_pMovTex->getSize().x, m_pMovTex->getSize().y));
		m_Moving = true;
	}
	else
	{
		m_Moving = false;
		m_pSprite->setTexture(*m_pTex);
		m_pSprite->setTextureRect(sf::IntRect(0, 0, m_pMovTex->getSize().x, m_pMovTex->getSize().y));
		m_TextureTimer = 0.f;
	}
	m_pSprite->setPosition((m_PosX - offsetX + 0.5f) * m_SecModifier, (m_PosY - offsetY + 0.5f)* m_SecModifier);
}

void Ship::Render(sf::RenderWindow* window)
{
	window->draw(*m_pSprite);
}

void Ship::GetPosition(int& x, int& y)
{
	x = (int)roundf(m_PosX);
	y = (int)roundf(m_PosY);
}

float Ship::GetMaxTravelDist()
{
	return m_MaxTravelDist;
}

bool Ship::IsMoving()
{
	return m_Moving;
}

void Ship::SetSpeed(float speed)
{
	m_Speed = speed;
}
