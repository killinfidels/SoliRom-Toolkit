#pragma once
#include "Soli-Rom.h"
#include <chrono>

//checks time elapsed
class Timer
{
public:
	Timer()
	{
		t1 = std::chrono::steady_clock::now() - std::chrono::days(100000);
		t2 = std::chrono::steady_clock::now();
	}
	~Timer()
	{

	}

	std::chrono::steady_clock::time_point t1;
	std::chrono::steady_clock::time_point t2;

	void start()
	{
		t1 = std::chrono::steady_clock::now();
	}

	bool check(int _milliInterval)
	{
		t2 = std::chrono::steady_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(t2.time_since_epoch() - t1.time_since_epoch()).count() > _milliInterval)
		{
			return true;
		}
	
		return false;
	}

	int difference()
	{
		t2 = std::chrono::steady_clock::now();
		return std::chrono::duration_cast<std::chrono::milliseconds>(t2.time_since_epoch() - t1.time_since_epoch()).count();
	}

private:

};
