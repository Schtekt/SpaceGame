#ifndef LEHMERRAND_H
#define LEHMERRAND_H
#include <stdint.h>
class LehmerRand
{
private:
	int m_Seed;
	LehmerRand();

public:
	static LehmerRand* m_pLehm;
	void SetSeed(int seed);
	uint32_t Rand();
	int Rand(int min, int max);
	static LehmerRand* GetInstance();
	~LehmerRand();
	LehmerRand(LehmerRand& other) = delete;
	void operator=(const LehmerRand&) = delete;
};
#endif