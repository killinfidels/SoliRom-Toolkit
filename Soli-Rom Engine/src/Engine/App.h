#pragma once
#include "Windows/Window.h"

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