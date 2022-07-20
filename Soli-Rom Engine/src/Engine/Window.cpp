#include "precompiledheaders.h"
#include "Window.h"

namespace SoliRom
{
	Window::Window()
	{
		sdlwindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if (sdlwindow == NULL)
		{
			printf("Window: %s, failed. Error: %s", windowName.c_str(), SDL_GetError());
		}
		screensurface = SDL_GetWindowSurface(sdlwindow);
		SDL_FillRect(screensurface, NULL, SDL_MapRGB(screensurface->format, 0xFF, 0xFF, 0xFF));
		SDL_UpdateWindowSurface(sdlwindow);
	}

	Window::~Window()
	{
	}
}