#include "precompiledheaders.h"
#include "Timer.h"

namespace SoliRom
{
	Timer::Timer()
	{
		running = false;
		Reset();
		update();
	}

	Timer::~Timer()
	{
		//farts and shits :)
	}

	void Timer::Reset()
	{
		startTime = std::chrono::steady_clock::now();
		pauseDelta = startTime - startTime;
		deltaTime = startTime - startTime;
		if (!running)
			pauseTime = std::chrono::steady_clock::now();
		
	}

	void Timer::update()
	{
		if (running)
		{
			deltaTime = std::chrono::steady_clock::now() - startTime - pauseDelta;
		}
		else
		{
			//SR_CORE_WARN("Timer paused, cannot update time");
		}
	}

	float Timer::elapsed()
	{
		return deltaTime.count();
	}

	bool Timer::checkElapsed(int _milli)
	{
		if (deltaTime.count() > _milli / 1000.0f)
			return true;

		return false;
	}

	bool Timer::Stop()
	{ 
		if (running)
		{
			pauseTime = std::chrono::steady_clock::now();
			running = false;
			return true;
		}
		else
		{
			//SR_CORE_WARN("Cannot pause timer, timer is already paused");
			return false;
		}
	}

	bool Timer::Start()
	{
		if (!running)
		{
			pauseDelta += std::chrono::steady_clock::now() - pauseTime;
			running = true;
			return true;
		}
		else
		{
			return false;
			//SR_CORE_WARN("Cannot resume timer, timer is not paused");
		}
	}
}