#include "precompiledheaders.h"
#include "Window.h"
#include "../Log.h"

namespace SoliRom
{
	Window::Window()
	{
		windowSIZE.x = 0;
		windowSIZE.y = 0;
		windowSIZE.w = 256 * tempMul;
		windowSIZE.h = 192 * tempMul;

		window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowSIZE.w, windowSIZE.h, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			SR_CORE_ERROR("Window: %s, failed. Error: %s", windowName.c_str(), SDL_GetError());
		}
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
		{
			SR_CORE_ERROR("Renderer: %s, failed. Error: %s", windowName, SDL_GetError());
		}
		else
		{

			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderPresent(renderer);
		}
	}

	Window::~Window()
	{
	}

	SDL_Renderer* Window::getRenderer()
	{
		if (renderer == NULL)
		{
			SR_CORE_WARN("%s window has no renderer", windowName);
			return nullptr;
		}
		
		return renderer;
	}
	SDL_Window* Window::getWindow()
	{
		return window;
	}
	int Window::getWindowWidth()
	{
		return windowSIZE.w;
	}
	int Window::getWindowHeight()
	{
		return windowSIZE.h;
	}
}