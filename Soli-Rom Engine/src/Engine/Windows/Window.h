#pragma once
#include "precompiledheaders.h"

namespace SoliRom
{
	class Window
	{
	public:
		Window();
		~Window();

		SDL_Renderer* getRenderer();

		SDL_Window* getWindow();
		
		int getWindowWidth();
		int getWindowHeight();

	private:
		std::string windowName = "WindowTest :)";
		SDL_Window* window = NULL;
		SDL_Surface* screensurface = NULL;
		SDL_Renderer* renderer = NULL;
		int tempMul = 4;

		SDL_Rect windowSIZE;
	};
}
