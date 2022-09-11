#include "precompiledheaders.h"
#include "Timer.h"
#include "Engine/Log.h"

namespace SoliRom
{
	Timer::Timer()
	{
		startTime = std::chrono::steady_clock::now();
		deltaTime = std::chrono::steady_clock::now() - startTime;
	}

	Timer::~Timer()
	{
		//farts and shits :)
	}

	void Timer::reset()
	{
		startTime = startTime = std::chrono::steady_clock::now();
	}

	void Timer::update()
	{
		deltaTime = std::chrono::steady_clock::now() - startTime;
	}

	float Timer::elapsed()
	{
		update();
		return deltaTime.count();
	}

	bool Timer::checkElapsed(int _milli)
	{
		update();
		if (deltaTime.count() > _milli / 1000.0f)
			return true;

		return false;
	}
}