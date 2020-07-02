#ifndef TIMER_H
#define TIMER_H

namespace sf
{
	class Clock;
}

class Timer {
private:
	sf::Clock* clock;

	Timer();

public:
	Timer(Timer const&) = delete;
	void operator=(Timer const&) = delete;

	static Timer& GetInstance()
	{
		static Timer instance;
		return instance;
	}

	void StartTimer();
	int GetTime();
};

#endif