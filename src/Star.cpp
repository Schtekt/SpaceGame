#include "Star.h"
#include <SFML/Graphics/Color.hpp>
#include "LehmerRand.h"

struct Col
{
	static sf::Color starColors[7];
};
static sf::Color starColors[7] = { sf::Color(155, 176, 255), sf::Color(170, 191, 255), sf::Color(202, 215, 255), sf::Color(248, 247, 255), sf::Color(255, 244, 234), sf::Color(255, 210, 161), sf::Color(255, 204, 111)};


Star::Star(int x, int y, int minSize, int maxSize)
{
	LehmerRand* lehm = LehmerRand::GetInstance();
	unsigned int seed = (x & 0xFFFF) << 16 | (y & 0xFFFF);
	lehm->SetSeed(seed);
	m_exists = lehm->Rand(0,50) == 2;

	if (!m_exists)
		return;
	m_size = (float)lehm->Rand(3, 35);
	int rand = lehm->Rand(0, 6);
	m_pColor = &starColors[rand];
}

bool Star::Exists()
{
	return m_exists;
}

float Star::Size()
{
	return m_size;
}

sf::Color Star::Color()
{
	return *m_pColor;
}
