#pragma once
#include "Window.h"

namespace SoliRom
{
	class App
	{
	public:
		App();
		~App();

		void Run();

	private:
		Window* window;
	};
}