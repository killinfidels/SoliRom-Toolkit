#pragma once
#include "Windows/Window.h"

namespace SoliRom
{
	class App
	{
	public:
		App(int _windowSizeMul);
		~App();

		void Run();

		Window* getWindow();
	private:
		Window* window;
	};
}