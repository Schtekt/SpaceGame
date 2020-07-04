#include "Timer.h"
#include <SFML/System/Clock.hpp>

Timer::Timer()
{
	clock = new sf::Clock;
}

void Timer::StartTimer()
{
	clock->restart();
}

int Timer::GetTime()
{
	return clock->getElapsedTime().asMilliseconds();
}

