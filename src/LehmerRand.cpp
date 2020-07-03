#include "LehmerRand.h"

LehmerRand::LehmerRand()
{
	m_Seed = 0;
}

void LehmerRand::SetSeed(int seed)
{
	m_Seed = seed;
}

uint32_t LehmerRand::Rand()
{
    m_Seed += 0xe120fc15;
    uint64_t tmp;
    tmp = (uint64_t)m_Seed * 0x4a39b70d;
    uint32_t m1 = (tmp >> 32) ^ tmp;
    tmp = (uint64_t)m1 * 0x12fad5c9;
    uint32_t m2 = (tmp >> 32) ^ tmp;
    return m2;
}

int LehmerRand::Rand(int min, int max)
{
    return (Rand() % (max + 1 - min)) + min;
}

LehmerRand* LehmerRand::GetInstance()
{
    static LehmerRand instance;
    return &instance;
}

LehmerRand::~LehmerRand()
{
}
