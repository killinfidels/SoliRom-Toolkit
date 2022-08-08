#pragma once
#include "precompiledheaders.h"

namespace SoliRom
{
	class Window
	{
	public:
		Window(float _sizeMul);
		~Window();

		SDL_Renderer* getRenderer();

		SDL_Window* getWindow();
		
		int getWindowWidth();
		int getWindowHeight();

	private:
		std::string windowName = "feed him :)";
		SDL_Window* window = NULL;
		SDL_Surface* screensurface = NULL;
		SDL_Renderer* renderer = NULL;
		float tempMul = 1;

		SDL_Rect windowSIZE;
	};
}
