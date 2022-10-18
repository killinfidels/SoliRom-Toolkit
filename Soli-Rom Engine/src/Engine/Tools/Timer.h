#pragma once

namespace SoliRom
{
	class Timer
	{
	public:
		Timer();
		~Timer();

		//maybe add static members that track time from start of program and then base everything on that?
		//kinda dumb cus i read that float thingy is gonna get imprecise the longer it goes

	private:
		std::chrono::steady_clock::time_point startTime;
		std::chrono::duration<float> deltaTime;
		std::chrono::steady_clock::time_point pauseTime;
		std::chrono::duration<float> pauseDelta;
		bool running;

	public:
		void update();
		void Reset();
		//returns in seconds for some dumb reason
		float elapsed();
		bool checkElapsed(int _milli);
		bool Stop();
		bool Start();

	};
}

