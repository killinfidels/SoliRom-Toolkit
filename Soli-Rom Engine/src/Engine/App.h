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

		Window* getWindow();
	private:
		Window* window;
	};
}