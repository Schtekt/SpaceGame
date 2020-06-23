#include "Ship.h"
#include <SFML/Graphics.hpp>
Ship::Ship(int posX, int posY, const char* texturePath): m_posX(posX), m_posY(posY), m_targetX(posX),
m_targetY(posY), m_angle(0.0f), m_pTex(new sf::Texture), m_pSprite(new sf::Sprite)
{
	m_pTex->loadFromFile(texturePath);
	m_pSprite->setTexture(*m_pTex, true);
	m_pSprite->setPosition(m_posX - m_pSprite->getLocalBounds().width / 2, m_posY - m_pSprite->getLocalBounds().height / 2);
	m_pSprite->setRotation(m_angle);
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
	m_pSprite->setPosition(m_posX - offsetX, m_posY - offsetY);
}

void Ship::Render(sf::RenderWindow* window)
{
	window->draw(*m_pSprite);
}
