#include "precompiledheaders.h"
#include "Window.h"
#include "../Log.h"

namespace SoliRom
{
	Window::Window(std::string _name, int _width, int _height)
	{
		name = _name;
		width = _width;
		height = _height;

		//Create sdl window
		window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		if (window == NULL)
		{
			SR_CORE_ERROR("Window: %s, failed. Error: %s", name, SDL_GetError());
		}
		else
		{
			//Create sdl renderer
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			//allows alpha blending -- more blendmodes https://wiki.libsdl.org/SDL_BlendMode
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			if (renderer == NULL)
			{
				SR_CORE_ERROR("Renderer: %s, failed. Error: %s", name, SDL_GetError());
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(renderer);
				SDL_RenderPresent(renderer);
			}
		}
	}

	std::string Window::getWindowName()
	{
		return name;
	}

	Window::~Window()
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);

		renderer = NULL;
		window = NULL;
	}

	SDL_Renderer* Window::getSDL_Renderer()
	{
		return renderer;
	}

	SDL_Window* Window::getSDL_Window()
	{
		return window;
	}
	int Window::getWidth()
	{
		SDL_GetWindowSize(window, &width, NULL);
		return width;
	}
	int Window::getHeight()
	{
		SDL_GetWindowSize(window, NULL, &height);
		return height;
	}
}