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

	private:
		std::string windowName = "WindowTest :)";
		SDL_Window* sdlwindow = NULL;
		SDL_Surface* screensurface = NULL;
		SDL_Renderer* renderer = NULL;
		int tempMul = 2;
		int x = 0,
			y = 0,
			width = 256 * tempMul,
			height = 192 * tempMul;
	};
}
