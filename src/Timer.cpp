#include "Timer.h"
#include <SFML/System/Clock.hpp>

Timer::Timer()
{
	m_pClock = new sf::Clock;
}

Timer::~Timer()
{
	delete m_pClock;
}

void Timer::StartTimer()
{
	m_pClock->restart();
}

int Timer::GetTime()
{
	return m_pClock->getElapsedTime().asMilliseconds();
}

