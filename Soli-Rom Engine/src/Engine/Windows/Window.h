#pragma once
#include "precompiledheaders.h"

namespace SoliRom
{
	class Window
	{
	public:

		Window();
		//Use App.CreateWindow instead
		Window(std::string _name, int _width, int _height);
		~Window();

		SDL_Renderer* getRenderer();

		SDL_Window* getWindow();
		
		int getWindowWidth();
		int getWindowHeight();


	private:
		std::string name = "NO WINDOW";
		SDL_Window* window = NULL;
		SDL_Surface* screensurface = NULL;
		SDL_Renderer* renderer = NULL;
		int tempMul = 4;

		int width, height;
	};
}
