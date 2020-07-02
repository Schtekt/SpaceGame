#ifndef STAR_H
#define STAR_H
#include "Resources.h"
namespace sf
{
    class Color;
}


struct planet
{
    int size;
    sf::Color* color;
	Resource resource;
};



struct Star
{

    bool m_Exists = false;
    float m_Size = .0f;
    sf::Color* m_pColor;
    int m_NrOfPlanets;
    planet* m_pPlanets;

    Star(int x, int y, int minSize, int maxSize, bool genFullSystem = false);
    ~Star();
};

#endif