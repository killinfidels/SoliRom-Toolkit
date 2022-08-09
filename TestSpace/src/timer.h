#pragma once
#include "Soli-Rom.h"
#include <chrono>

//checks time elapsed
class Timer
{
public:
	Timer();
	~Timer();

	std::chrono::steady_clock::time_point t1;
	std::chrono::steady_clock::time_point t2;

	void start();
	bool check(int _milli);

private:

};

Timer::Timer()
{
	t1 = std::chrono::steady_clock::now();
	t2 = std::chrono::steady_clock::now();
}

Timer::~Timer()
{
}

void Timer::start()
{
	t1 = std::chrono::steady_clock::now();
}

bool Timer::check(int _milli)
{
	t2 = std::chrono::steady_clock::now();
	if (std::chrono::duration_cast<std::chrono::milliseconds>(t2.time_since_epoch() - t1.time_since_epoch()).count() > _milli)
	{
		return true;
	}
	
	return false;
}