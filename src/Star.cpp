#include "Star.h"
#include <SFML/Graphics/Color.hpp>
#include "LehmerRand.h"
#include <vector>

struct Col
{
	static sf::Color starColors[7];
	static sf::Color planetColors[4];
};
static sf::Color starColors[7] = { sf::Color(155, 176, 255), sf::Color(170, 191, 255), sf::Color(202, 215, 255), sf::Color(248, 247, 255), sf::Color(255, 244, 234), sf::Color(255, 210, 161), sf::Color(255, 204, 111)};
static sf::Color planetColors[8] = { sf::Color(26, 26, 26), sf::Color(230, 230, 230), sf::Color(47, 106, 105), sf::Color(153, 61, 0),
									sf::Color(176, 127, 53), sf::Color(176, 143, 54), sf::Color(85, 128, 170), sf::Color(54, 104, 150) };

Star::Star(int x, int y, int minSize, int maxSize, bool genFullSystem) : m_pPlanets(nullptr)
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

	if (genFullSystem)
	{
		m_nrOfPlanets = lehm->Rand(0, 10);
		m_pPlanets = new planet[m_nrOfPlanets];

		for (int i = 0; i < m_nrOfPlanets; i++)
		{
			m_pPlanets[i].size = lehm->Rand(3, 20);
			m_pPlanets[i].color = &planetColors[lehm->Rand(0,7)];
		}

	}
}

Star::~Star()
{
	if(m_pPlanets)
		delete m_pPlanets;
}
