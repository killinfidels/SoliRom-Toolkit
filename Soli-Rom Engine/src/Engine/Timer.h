#pragma once

namespace SoliRom
{
	class Timer
	{
	public:
		Timer();
		~Timer();

	private:
		std::chrono::steady_clock::time_point startTime;
		std::chrono::duration<float> deltaTime;
		void update();

	public:
		void reset();
		float elapsed();
		bool checkElapsed(int _milli);
	};
}

